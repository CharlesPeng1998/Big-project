/* 1751456 计2 石佳琛 */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <strstream>
#include <stdio.h>
#include <conio.h>
#include <Windows.h>

using namespace std;
// false测试C++ true测试C
//#define C true 
#define C true
const int nul = 1;//测试null


#if C
extern "C"
{
#include "../common/common_cfgfile_tools.h"
}
#else
#include "../common/common_cfgfile_tools.hpp"
#endif

union cfg_value {
	int ivalue;
	double dvalue;
	char svalue[128];
	char cvalue;
	void *value;
};

struct cfg_item {
	const char *cfg_item_name;
	enum ITEM_TYPE cfg_item_type;
	union cfg_value cfg_item_value;
};

/***************************************************************************
函数名称：
功    能：显示提示信息
输入参数：
返 回 值：
说    明：
***************************************************************************/
static void to_be_continued(const char *prompt)
{
	if (prompt)
		cout << prompt << "，按回车键继续...";
	else
		cout << "按回车键继续...";

	/* 忽略除回车键外的所有输入（注意：_getch的回车是\r，而getchar是\n）*/
	while (_getch() != '\r')
		;
	cout << endl;

	return;
}

/***************************************************************************
函数名称：
功    能：因为cfg_item中含有共用体，共用体只能初始化第一项，因此用函数初始化
输入参数：
返 回 值：
说    明：
***************************************************************************/
static void set_item(struct cfg_item *item)
{
	item[0].cfg_item_value.ivalue = 123;
	item[1].cfg_item_value.dvalue = 123.45;
	strcpy(item[2].cfg_item_value.svalue, "Hello");
	item[3].cfg_item_value.cvalue = 'Y';
	//	item[4].cfg_item_value.ivalue = 0;
	item[5].cfg_item_value.ivalue = 99999;
	//	item[6].cfg_item_value.ivalue = 0;
}

//C部分
#if C
int test_readconfig_c(const char *cfgname, const char **group_name, struct cfg_item *item)
{
	FILE *fp;
	int ret, i, j;
	char tmp[256];

	/* 第一次模拟，添加若干组 */
	if (1) {
		remove(cfgname); //删除文件

		fp = open_cfgfile(cfgname, OPEN_OPT_RDWR);
		if (fp == NULL) {
			printf("无法打开配置文件(%s).\n", cfgname);
			return -1;
		}

		for (i = 0; group_name[i]; i++) {
			if ((ret = group_add(fp, group_name[i])) <= 0)
				printf("增加[%s]失败.\n", group_name[i]);
			else
				printf("增加[%s]成功.\n", group_name[i]);
		}
		if ((ret = group_add(fp, group_name[0])) <= 0)
			printf("【新增】增加[%s]失败.\n", group_name[0]);
		else
			printf("【新增】增加[%s]成功.\n", group_name[0]);

		close_cfgfile(fp); //关闭文件，模拟本次设置完成

		sprintf(tmp, "请打开配置文件%s，观察是否仅有8个空组", cfgname);
		to_be_continued(tmp);
	}

	/* 第二次模拟，每组添加若干项 */
	if (1) {
		fp = open_cfgfile(cfgname, OPEN_OPT_RDWR);
		if (fp == NULL) {
			printf("无法打开配置文件(%s).\n", cfgname);
			return -1;
		}

		for (i = 0; group_name[i]; i++) {
			for (j = 0; item[j].cfg_item_name; j++) {
				sprintf(tmp, "%s-%s", group_name[i], item[j].cfg_item_name);
				/* 说明：item_add的第3个参数是void*，因此不管什么类型，均传入union第一个成员的地址，即其它成员地址 */
				if ((ret = item_add(fp, group_name[i], tmp, &(item[j].cfg_item_value.ivalue), item[j].cfg_item_type)) <= 0)
					printf("增加[%s]/%s 失败.\n", group_name[i], tmp);
				else
					printf("增加[%s]/%s 成功.\n", group_name[i], tmp);
			}
		}
		sprintf(tmp, "%s-%s", group_name[0], item[0].cfg_item_name);
		if ((ret = item_add(fp, group_name[0], tmp, &(item[0].cfg_item_value.ivalue), item[0].cfg_item_type)) <= 0)
			printf("【新增】增加[%s]/%s 失败.\n", group_name[0], tmp);
		else
			printf("【新增】增加[%s]/%s 成功.\n", group_name[0], tmp);

		close_cfgfile(fp); //关闭文件，模拟本次设置完成

		sprintf(tmp, "请打开配置文件%s，观察是否仅有8个组均有6个配置项", cfgname);
		to_be_continued(tmp);
	}

	/* 第三·一次模拟，删除组及项 */
	if (1) {
		//删除末尾的配置项
		fp = open_cfgfile(cfgname, OPEN_OPT_RDWR);
		if (fp == NULL) {
			printf("无法打开配置文件(%s).\n", cfgname);
			return -1;
		}
		if ((ret = group_add(fp, "临时配置组")) <= 0)
			printf("【新增】增加[%s]失败.\n", "临时配置组");
		else
			printf("【新增】增加[%s]成功.\n", "临时配置组");
		if ((ret = item_add(fp, "临时配置组", "临时设置项", NULL, TYPE_NULL)) <= 0)
			printf("【新增】增加[%s]/%s 失败.\n", "临时配置组", "临时设置项");
		else
			printf("【新增】增加[%s]/%s 成功.\n", "临时配置组", "临时设置项");
		//增加位于末尾的只有一项的临时配置组

		printf("【新增】删除<临时设置项>共%d项\n", item_del(fp, "临时配置组", "临时设置项"));

		close_cfgfile(fp); //关闭文件，模拟本次设置完成

		sprintf(tmp, "请打开配置文件%s，观察临时设置项是否已被删除", cfgname);
		to_be_continued(tmp);

		//删除末尾的配置组
		fp = open_cfgfile(cfgname, OPEN_OPT_RDWR);
		if (fp == NULL) {
			printf("无法打开配置文件(%s).\n", cfgname);
			return -1;
		}
		printf("【新增】删除[临时配置组]共%d组\n", group_del(fp, "临时配置组"));

		close_cfgfile(fp); //关闭文件，模拟本次设置完成

		sprintf(tmp, "请打开配置文件%s，观察临时配置组是否已被删除", cfgname);
		to_be_continued(tmp);
	}

	/* 第三·二次模拟，删除组及项 */
	if (1) {
		sprintf(tmp, "请打开配置文件%s，将[配置组3]复制若干份，配置组2-设置项B复制若干份，且后面的值类型不同", cfgname);
		to_be_continued(tmp);

		fp = open_cfgfile(cfgname, OPEN_OPT_RDWR);
		if (fp == NULL) {
			printf("无法打开配置文件(%s).\n", cfgname);
			return -1;
		}

		printf("删除[配置组3]共%d组\n", group_del(fp, "配置组3"));
		printf("删除[配置组5]共%d组\n", group_del(fp, "配置组5"));
		printf("【新增】删除[配置组X]共%d组\n", group_del(fp, "配置组X"));		//删除无匹配组

		printf("删除<配置组2-设置项B>共%d项\n", item_del(fp, "配置组2", "配置组2-设置项B"));
		printf("【新增】删除<配置组X-设置项>共%d项\n", item_del(fp, "配置组X", "配置组X-设置项"));		//删除无匹配组中的项
		printf("【新增】删除<配置组1-设置项>共%d项\n", item_del(fp, "配置组1", "配置组1-设置项"));		//删除组中的无匹配项

		close_cfgfile(fp); //关闭文件，模拟本次设置完成

		sprintf(tmp, "请打开配置文件%s，观察[配置组3]/[配置组5]/<配置组2-设置项B>是否已被删除", cfgname);
		to_be_continued(tmp);
	}

	/* 第四次模拟，修改项 */
	if (1) {
		fp = open_cfgfile(cfgname, OPEN_OPT_RDWR);
		if (fp == NULL) {
			printf("无法打开配置文件(%s).\n", cfgname);
			return -1;
		}

		int a = 54321;
		double b = 1023.4567;
		char c = 'N';

		/* 已存在项，更新 */
		if (item_update(fp, "配置组4", "配置组4-设置项B", &a, TYPE_INT)>0)
			printf("配置组4-设置项B修改成功\n");
		else
			printf("配置组4-设置项B修改失败\n");
		if (item_update(fp, "配置组1", "配置组1-设置项D", "helloworld", TYPE_STRING))
			printf("配置组1-设置项D修改成功\n");
		else
			printf("配置组1-设置项D修改失败\n");
		if (item_update(fp, "配置组8", "配置组8-设置项E", &b, TYPE_DOUBLE))
			printf("配置组8-设置项E修改成功\n");
		else
			printf("配置组8-设置项E修改失败\n");
		if (item_update(fp, "配置组6", "配置组6-设置项F", NULL, TYPE_NULL))
			printf("配置组6-设置项F修改成功\n");
		else
			printf("配置组6-设置项F修改失败\n");
		if (item_update(fp, "配置组7", "配置组7-设置项C", &c, TYPE_CHARACTER))
			printf("配置组7-设置项C修改成功\n");
		else
			printf("配置组7-设置项C修改失败\n");

		/* 不存在项，新增 */
		item_update(fp, "配置组6", "配置组6-设置项U", NULL, TYPE_NULL);
		item_update(fp, "配置组7", "配置组7-设置项V", &c, TYPE_CHARACTER);
		item_update(fp, "配置组7", "配置组6-设置项W", NULL, TYPE_NULL);
		item_update(fp, "配置组4", "配置组4-设置项X", &a, TYPE_INT);
		item_update(fp, "配置组1", "配置组1-设置项Y", "helloworld", TYPE_STRING);
		item_update(fp, "配置组8", "配置组8-设置项Z", &b, TYPE_DOUBLE);

		/*  不存在组  */
		if (item_update(fp, "配置组0", "配置组0-设置项", &c, TYPE_CHARACTER))
			printf("【新增】配置组0-设置项修改成功\n");
		else
			printf("【新增】配置组0-设置项修改失败\n");

		close_cfgfile(fp); //关闭文件，模拟本次设置完成

		sprintf(tmp, "请打开配置文件%s，观察上述配置是否已修改", cfgname);
		to_be_continued(tmp);
	}

	/* 第五次模拟，读 */
	if (1) {
		fp = open_cfgfile(cfgname, OPEN_OPT_RDONLY);
		if (fp == NULL) {
			printf("无法打开配置文件(%s).\n", cfgname);
			return -1;
		}

		int a;
		double b;
		char c, s[80];

		/* 已存在项，更新 */
		if (item_get_value(fp, "配置组4", "配置组4-设置项B", &a, TYPE_INT) > 0)
			printf("[配置组4]/配置组4-设置项B=%d\n", a);
		if (item_get_value(fp, "配置组1", "配置组1-设置项F", &a, TYPE_INT) > 0)
			printf("[配置组1]/配置组1-设置项F=%d\n", a);
		if (item_get_value(fp, "配置组6", "配置组6-设置项D", &c, TYPE_CHARACTER) > 0)
			printf("[配置组6]/配置组6-设置项D=%c\n", c);
		if (item_get_value(fp, "配置组8", "配置组8-设置项C", s, TYPE_STRING) > 0)
			printf("[配置组8]/配置组8-设置项C=%s\n", s);
		if (item_get_value(fp, "配置组7", "配置组7-设置项E", NULL, TYPE_NULL) > 0)
			printf("[配置组7]/配置组7-设置项E=<NULL>\n");
		if (item_get_value(fp, "配置组6", "配置组6-设置项B", &b, TYPE_DOUBLE) > 0)
			printf("[配置组6]/配置组6-设置项B=%f\n", b);
		if (item_get_value(fp, "配置组1", "设置项100", NULL, TYPE_NULL) > 0)
			printf("[配置组1]/设置项100=<NULL>\n");
		else
			printf("[配置组1]/设置项100 不存在\n");
		if (item_get_value(fp, "配置组X", "设置项", NULL, TYPE_NULL) > 0)
			printf("【新增】[配置组X]/设置项=<NULL>\n");
		else
			printf("【新增】[配置组X]/设置项 不存在\n");

		close_cfgfile(fp); //关闭文件，模拟本次设置完成

		sprintf(tmp, "请打开配置文件%s，观察上述配置读取是否正确", cfgname);
		to_be_continued(tmp);
	}

	/* 第六次模拟 专门测试组名为null的情况 */
	if (nul) {
		printf("\n【新增】以下检测组名为null的情况\n");
		//添加null组（应不成功）
		fp = open_cfgfile(cfgname, OPEN_OPT_RDWR);
		if (fp == NULL) {
			printf("无法打开配置文件(%s).\n", cfgname);
			return -1;
		}
		if ((ret = group_add(fp, NULL)) <= 0)
			printf("增加简单组失败.\n");
		else
			printf("增加简单组成功.\n");
		close_cfgfile(fp);
		sprintf(tmp, "请打开配置文件%s，检查文件是否有变化", cfgname);
		to_be_continued(tmp);

		//添加null项目
		fp = open_cfgfile(cfgname, OPEN_OPT_RDWR);
		if (fp == NULL) {
			printf("无法打开配置文件(%s).\n", cfgname);
			return -1;
		}
		int a = 10;
		double b = 18.3232;
		if (item_add(fp, NULL, "简单项1", NULL, TYPE_NULL)>0)
			printf("增加<简单项1>成功.\n");
		else
			printf("增加<简单项1>失败.\n");
		if (item_add(fp, NULL, "简单项2", &a, TYPE_INT)>0)
			printf("增加<简单项2>成功.\n");
		else
			printf("增加<简单项2>失败.\n");
		close_cfgfile(fp);
		sprintf(tmp, "请打开配置文件%s，检查文件最开始是否已添加了上述简单项", cfgname);
		to_be_continued(tmp);

		//删除null项目
		fp = open_cfgfile(cfgname, OPEN_OPT_RDWR);
		if (fp == NULL) {
			printf("无法打开配置文件(%s).\n", cfgname);
			return -1;
		}
		printf("成功删除<简单项1>共%d项\n", item_del(fp, NULL, "简单项1"));
		printf("成功删除<简单项>共%d项\n", item_del(fp, NULL, "简单项"));
		close_cfgfile(fp);
		sprintf(tmp, "请打开配置文件%s，观察文件是否已删除了上述简单项", cfgname);
		to_be_continued(tmp);

		//更新null项目
		fp = open_cfgfile(cfgname, OPEN_OPT_RDWR);
		if (fp == NULL) {
			printf("无法打开配置文件(%s).\n", cfgname);
			return -1;
		}
		if (item_update(fp, NULL, "简单项2", &b, TYPE_DOUBLE) > 0)
			printf("成功修改简单项2\n");
		if (item_update(fp, NULL, "简单项3", NULL, TYPE_NULL) > 0)
			printf("成功修改简单项3\n");
		close_cfgfile(fp);
		sprintf(tmp, "请打开配置文件%s，检查文件是否已修改上述简单项", cfgname);
		to_be_continued(tmp);

		//读取null项目值
		fp = open_cfgfile(cfgname, OPEN_OPT_RDWR);
		if (fp == NULL) {
			printf("无法打开配置文件(%s).\n", cfgname);
			return -1;
		}
		double value;
		if (item_get_value(fp, NULL, "简单项2", &value, TYPE_DOUBLE) > 0) {
			printf("简单项2=%f\n", value);
		}
		close_cfgfile(fp);
		sprintf(tmp, "请打开配置文件%s，观察上述配置读取是否正确", cfgname);
		to_be_continued(tmp);

		//删除null组（应不成功）
		fp = open_cfgfile(cfgname, OPEN_OPT_RDWR);
		if (fp == NULL) {
			printf("无法打开配置文件(%s).\n", cfgname);
			return -1;
		}
		printf("删除[NULL]共%d组\n", group_del(fp, NULL));
		close_cfgfile(fp);
		sprintf(tmp, "请打开配置文件%s，观察简单项是否被删除", cfgname);
		to_be_continued(tmp);

	}
	return 0;
}
//C++部分
#else
int test_readconfig_cpp(const char *cfgname, const char **group_name, struct cfg_item *item)
{
	fstream fp;
	int ret, i;
	char tmp[256];

	/* 第一次模拟，添加若干组 */
	if (1) {
		remove(cfgname); //删除文件

		if (open_cfgfile(fp, cfgname, OPEN_OPT_RDWR) == 0) {
			cout << "无法打开配置文件(" << cfgname << ")." << endl;
			return -1;
		}
		for (i = 0; group_name[i]; i++) {
			if ((ret = group_add(fp, group_name[i])) <= 0)
				cout << "增加[" << group_name[i] << "]失败." << endl;
			else
				cout << "增加[" << group_name[i] << "]成功." << endl;
		}
		if ((ret = group_add(fp, group_name[0])) <= 0)
			cout << "【新增】增加[" << group_name[0] << "]失败.\n";
		else
			cout << "【新增】增加[" << group_name[0] << "]成功.\n";

		close_cfgfile(fp); //关闭文件，模拟本次设置完成

		sprintf(tmp, "请打开配置文件%s，观察是否仅有8个空组", cfgname);
		to_be_continued(tmp);
	}

	/* 第二次模拟，每组添加若干项 */
	if (1) {
		int j;

		if (open_cfgfile(fp, cfgname, OPEN_OPT_RDWR) == 0) {
			cout << "无法打开配置文件(" << cfgname << ")." << endl;
			return -1;
		}

		for (i = 0; group_name[i]; i++) {
			for (j = 0; item[j].cfg_item_name; j++) {
				sprintf(tmp, "%s-%s", group_name[i], item[j].cfg_item_name);
				/* 说明：item_add的第3个参数是void*，因此不管什么类型，均传入union第一个成员的地址，即其它成员地址 */
				if ((ret = item_add(fp, group_name[i], tmp, &(item[j].cfg_item_value.ivalue), item[j].cfg_item_type)) <= 0)
					cout << "增加[" << group_name[i] << "]/" << tmp << "失败." << endl;
				else
					cout << "增加[" << group_name[i] << "]/" << tmp << "成功." << endl;
			}
		}
		sprintf(tmp, "%s-%s", group_name[0], item[0].cfg_item_name);
		if ((ret = item_add(fp, group_name[0], tmp, &(item[0].cfg_item_value.ivalue), item[0].cfg_item_type)) <= 0)
			cout << "【新增】增加[" << group_name[0] << "]/" << tmp << " 失败.\n";
		else
			cout << "【新增】增加[" << group_name[0] << "]/" << tmp << " 成功.\n";

		close_cfgfile(fp); //关闭文件，模拟本次设置完成

		sprintf(tmp, "请打开配置文件%s，观察是否仅有8个组均有6个配置项", cfgname);
		to_be_continued(tmp);
	}

	/* 第三·一次模拟，删除组及项 */
	if (1) {
		if (open_cfgfile(fp, cfgname, OPEN_OPT_RDWR) == 0) {
			cout << "无法打开配置文件(" << cfgname << ")." << endl;
			return -1;
		}

		if ((ret = group_add(fp, "临时配置组")) <= 0)
			cout << "【新增】增加[临时配置组]失败.\n";
		else
			cout << "【新增】增加[临时配置组]成功.\n";
		if ((ret = item_add(fp, "临时配置组", "临时设置项", NULL, TYPE_NULL)) <= 0)
			cout << "【新增】增加[临时配置组]/临时设置项 失败.\n";
		else
			cout << "【新增】增加[临时配置组]/临时设置项 成功.\n";
		//增加位于末尾的只有一项的临时配置组

		cout << "【新增】删除<临时设置项>共" << item_del(fp, cfgname, "临时配置组", "临时设置项") << "项\n";

		close_cfgfile(fp); //关闭文件，模拟本次设置完成

		if (open_cfgfile(fp, cfgname, OPEN_OPT_RDWR) == 0) {
			cout << "无法打开配置文件(" << cfgname << ")." << endl;
			return -1;
		}
		cout << "【新增】删除[临时配置组]共" << group_del(fp, cfgname, "临时配置组") << "组\n";
		close_cfgfile(fp); //关闭文件，模拟本次设置完成

		sprintf(tmp, "请打开配置文件%s，观察临时配置组是否已被删除", cfgname);
		to_be_continued(tmp);
	}

	/* 第三·二次模拟，删除组及项 */
	if (1) {
		sprintf(tmp, "请打开配置文件%s，将[配置组3]复制若干份，配置组2-设置项B复制若干份，且后面的值类型不同", cfgname);
		to_be_continued(tmp);

		if (open_cfgfile(fp, cfgname, OPEN_OPT_RDWR) == 0) {
			cout << "无法打开配置文件(" << cfgname << ")." << endl;
			return -1;
		}

		cout << "删除[配置组3]共" << group_del(fp, cfgname, "配置组3") << "组" << endl;
		cout << "删除[配置组5]共" << group_del(fp, cfgname, "配置组5") << "组" << endl;
		cout << "【新增】删除[配置组X]共" << group_del(fp, cfgname, "配置组X") << "组" << endl;;		//删除无匹配组

		cout << "删除<配置组2-设置项B>共" << item_del(fp, cfgname, "配置组2", "配置组2-设置项B") << "项" << endl;
		cout << "【新增】删除<配置组X-设置项>共" << item_del(fp, cfgname, "配置组X", "配置组X-设置项") << "项\n";		//删除无匹配组中的项
		cout << "【新增】删除<配置组1-设置项>共" << item_del(fp, cfgname, "配置组1", "配置组1 - 设置项") << "项\n";		//删除组中的无匹配项


		close_cfgfile(fp); //关闭文件，模拟本次设置完成

		sprintf(tmp, "请打开配置文件%s，观察[配置组3]/[配置组5]/<配置组2-设置项B>是否已被删除", cfgname);
		to_be_continued(tmp);
	}

	/* 第四次模拟，修改项 */
	if (1) {
		if (open_cfgfile(fp, cfgname, OPEN_OPT_RDWR) == 0) {
			cout << "无法打开配置文件(" << cfgname << ")." << endl;
			return -1;
		}

		int a = 54321;
		double b = 1023.4567;
		char c = 'N';
		/* 已存在项，更新 */
		item_update(fp, cfgname, "配置组4", "配置组4-设置项B", &a, TYPE_INT);
		item_update(fp, cfgname, "配置组1", "配置组1-设置项D", "helloworld", TYPE_STRING);
		item_update(fp, cfgname, "配置组8", "配置组8-设置项E", &b, TYPE_DOUBLE);
		item_update(fp, cfgname, "配置组6", "配置组6-设置项F", NULL, TYPE_NULL);
		item_update(fp, cfgname, "配置组7", "配置组7-设置项C", &c, TYPE_CHARACTER);

		/* 不存在项，新增 */
		item_update(fp, cfgname, "配置组6", "配置组6-设置项U", NULL, TYPE_NULL);
		item_update(fp, cfgname, "配置组7", "配置组7-设置项V", &c, TYPE_CHARACTER);
		item_update(fp, cfgname, "配置组7", "配置组6-设置项W", NULL, TYPE_NULL);
		item_update(fp, cfgname, "配置组4", "配置组4-设置项X", &a, TYPE_INT);
		item_update(fp, cfgname, "配置组1", "配置组1-设置项Y", "helloworld", TYPE_STRING);
		item_update(fp, cfgname, "配置组8", "配置组8-设置项Z", &b, TYPE_DOUBLE);

		/*  不存在组  */
		if (item_update(fp, cfgname, "配置组0", "配置组0-设置项", &c, TYPE_CHARACTER))
			cout << "【新增】配置组0-设置项修改成功\n";
		else
			cout << "【新增】配置组0-设置项修改失败\n";

		close_cfgfile(fp); //关闭文件，模拟本次设置完成

		sprintf(tmp, "请打开配置文件%s，观察上述配置是否已修改", cfgname);
		to_be_continued(tmp);
	}

	/* 第五次模拟，读 */
	if (1) {
		if (open_cfgfile(fp, cfgname, OPEN_OPT_RDONLY) == 0) {
			cout << "无法打开配置文件(" << cfgname << ")." << endl;
			return -1;
		}

		int a;
		double b;
		char c, s[80];

		/* 已存在项，更新 */
		if (item_get_value(fp, "配置组4", "配置组4-设置项B", &a, TYPE_INT) > 0)
			printf("[配置组4]/配置组4-设置项B=%d\n", a);
		else
			printf("[配置组4]/配置组4-设置项B 不存在\n");
		if (item_get_value(fp, "配置组1", "配置组1-设置项F", &a, TYPE_INT) > 0)
			printf("[配置组1]/配置组1-设置项F=%d\n", a);
		else
			printf("[配置组1]/配置组1-设置项F 不存在\n");
		if (item_get_value(fp, "配置组6", "配置组6-设置项D", &c, TYPE_CHARACTER) > 0)
			printf("[配置组6]/配置组6-设置项D=%c\n", c);
		else
			printf("[配置组6]/配置组6-设置项D 不存在\n");
		if (item_get_value(fp, "配置组8", "配置组8-设置项C", s, TYPE_STRING) > 0)
			printf("[配置组8]/配置组8-设置项C=%s\n", s);
		else
			printf("[配置组8]/配置组8-设置项C 不存在\n");
		if (item_get_value(fp, "配置组7", "配置组7-设置项E", NULL, TYPE_NULL) > 0)
			printf("[配置组7]/配置组7-设置项E=<NULL>\n");
		else
			printf("[配置组7]/配置组7-设置项E 不存在\n");
		if (item_get_value(fp, "配置组6", "配置组6-设置项B", &b, TYPE_DOUBLE) > 0)
			printf("[配置组6]/配置组6-设置项B=%f\n", b);
		else
			printf("[配置组6]/配置组6-设置项B 不存在\n");
		if (item_get_value(fp, "配置组1", "设置项100", NULL, TYPE_NULL) > 0)
			printf("[配置组1]/设置项100=<NULL>\n");
		else
			printf("[配置组1]/设置项100 不存在\n");
		if (item_get_value(fp, "配置组X", "设置项", NULL, TYPE_NULL) > 0)
			printf("【新增】[配置组X]/设置项=<NULL>\n");
		else
			printf("【新增】[配置组X]/设置项 不存在\n");

		close_cfgfile(fp); //关闭文件，模拟本次设置完成

		sprintf(tmp, "请打开配置文件%s，观察上述配置读取是否正确", cfgname);
		to_be_continued(tmp);
	}

	/* 第六次模拟 专门测试组名为null的情况 */
	if (nul) {
		cout << endl << "【新增】以下检测组名为null的情况" << endl;
		//添加null组（应不成功）
		if (open_cfgfile(fp, cfgname, OPEN_OPT_RDONLY) == 0) {
			cout << "无法打开配置文件(" << cfgname << ")." << endl;
			return -1;
		}
		if ((ret = group_add(fp, NULL)) <= 0)
			cout << "增加简单组失败.\n";
		else
			cout << "增加简单组成功.\n";
		close_cfgfile(fp);
		sprintf(tmp, "请打开配置文件%s，检查文件是否有变化", cfgname);
		to_be_continued(tmp);

		//添加null项目
		if (open_cfgfile(fp, cfgname, OPEN_OPT_RDWR) == 0) {
			cout << "无法打开配置文件(" << cfgname << ")." << endl;
			return -1;
		}
		int a = 10;
		double b = 18.3232;
		if (item_add(fp, NULL, "简单项1", NULL, TYPE_NULL)>0)
			cout << "增加<简单项1>成功.\n";
		else
			cout << "增加<简单项1>失败.\n";
		if (item_add(fp, NULL, "简单项2", &a, TYPE_INT)>0)
			cout << "增加<简单项2>成功.\n";
		else
			cout << "增加<简单项2>失败.\n";
		close_cfgfile(fp);
		sprintf(tmp, "请打开配置文件%s，检查文件最开始是否已添加了上述简单项", cfgname);
		to_be_continued(tmp);

		//删除null项目
		if (open_cfgfile(fp, cfgname, OPEN_OPT_RDWR) == 0) {
			cout << "无法打开配置文件(" << cfgname << ")." << endl;
			return -1;
		}
		int del;
		del = item_del(fp, cfgname, NULL, "起始值");
		cout << "成功删除<简单项1>共" << item_del(fp, cfgname, NULL, "简单项1") << "项\n";
		cout << "成功删除<简单项>共" << item_del(fp, cfgname, NULL, "简单项") << "项\n";

		close_cfgfile(fp);
		sprintf(tmp, "请打开配置文件%s，观察文件是否已删除了上述简单项", cfgname);
		to_be_continued(tmp);

		//更新null项目
		if (open_cfgfile(fp, cfgname, OPEN_OPT_RDWR) == 0) {
			cout << "无法打开配置文件(" << cfgname << ")." << endl;
			return -1;
		}
		if (item_update(fp, cfgname, NULL, "简单项2", &b, TYPE_DOUBLE) > 0)
			cout << "成功修改简单项2\n";
		if (item_update(fp, cfgname, NULL, "简单项3", NULL, TYPE_NULL) > 0)
			cout << "成功修改简单项3\n";

		close_cfgfile(fp);
		sprintf(tmp, "请打开配置文件%s，检查文件是否已修改上述简单项", cfgname);
		to_be_continued(tmp);

		//读取null项目值
		if (open_cfgfile(fp, cfgname, OPEN_OPT_RDONLY) == 0) {
			cout << "无法打开配置文件(" << cfgname << ")." << endl;
			return -1;
		}
		double value;
		if (item_get_value(fp, NULL, "简单项2", &value, TYPE_DOUBLE) > 0) {
			cout << "简单项2=" << value << "\n";
		}
		close_cfgfile(fp);
		sprintf(tmp, "请打开配置文件%s，观察上述配置读取是否正确", cfgname);
		to_be_continued(tmp);
	}

	//删除null组（应不成功）
	if (open_cfgfile(fp, cfgname, OPEN_OPT_RDONLY) == 0) {
		cout << "无法打开配置文件(" << cfgname << ")." << endl;
		return -1;
	}
	cout << "删除[NULL]共" << group_del(fp, cfgname, NULL) << "组\n";
	close_cfgfile(fp);
	sprintf(tmp, "请打开配置文件%s，观察简单项是否被删除", cfgname);
	to_be_continued(tmp);

	return 0;
}
#endif
int main()
{
#if C
	const char *cfgname = "sjc_1751456_c.cfg";
#else
	const char *cfgname = "sjc_1751456_cpp.cfg";
#endif
	const char *group_name[] = {
		"配置组1",
		"配置组2",
		"配置组3",
		"配置组4",
		"配置组5",
		"配置组6",
		"配置组7",
		"配置组8",
		NULL
	};

	struct cfg_item item[] =
	{
		{ "设置项A",TYPE_INT, 0 },		//共用体union的初始化，只能初始化第一个元素
	{ "设置项B", TYPE_DOUBLE, 0 },
	{ "设置项C",TYPE_STRING, 0 },
	{ "设置项D",TYPE_CHARACTER, 0 },
	{ "设置项E", TYPE_NULL, 0 },
	{ "设置项F",TYPE_INT, 0 },
	{ NULL,TYPE_NULL, 0 }
	};
	set_item(item); //给union赋初值
#if C
	test_readconfig_c(cfgname, group_name, item);
#else
	test_readconfig_cpp(cfgname, group_name, item);
#endif
	return 0;
}
