/* 1751456 ��2 ʯ��� */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <strstream>
#include <stdio.h>
#include <conio.h>
#include <Windows.h>

using namespace std;
// false����C++ true����C
//#define C true 
#define C true
const int nul = 1;//����null


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
�������ƣ�
��    �ܣ���ʾ��ʾ��Ϣ
���������
�� �� ֵ��
˵    ����
***************************************************************************/
static void to_be_continued(const char *prompt)
{
	if (prompt)
		cout << prompt << "�����س�������...";
	else
		cout << "���س�������...";

	/* ���Գ��س�������������루ע�⣺_getch�Ļس���\r����getchar��\n��*/
	while (_getch() != '\r')
		;
	cout << endl;

	return;
}

/***************************************************************************
�������ƣ�
��    �ܣ���Ϊcfg_item�к��й����壬������ֻ�ܳ�ʼ����һ�����ú�����ʼ��
���������
�� �� ֵ��
˵    ����
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

//C����
#if C
int test_readconfig_c(const char *cfgname, const char **group_name, struct cfg_item *item)
{
	FILE *fp;
	int ret, i, j;
	char tmp[256];

	/* ��һ��ģ�⣬��������� */
	if (1) {
		remove(cfgname); //ɾ���ļ�

		fp = open_cfgfile(cfgname, OPEN_OPT_RDWR);
		if (fp == NULL) {
			printf("�޷��������ļ�(%s).\n", cfgname);
			return -1;
		}

		for (i = 0; group_name[i]; i++) {
			if ((ret = group_add(fp, group_name[i])) <= 0)
				printf("����[%s]ʧ��.\n", group_name[i]);
			else
				printf("����[%s]�ɹ�.\n", group_name[i]);
		}
		if ((ret = group_add(fp, group_name[0])) <= 0)
			printf("������������[%s]ʧ��.\n", group_name[0]);
		else
			printf("������������[%s]�ɹ�.\n", group_name[0]);

		close_cfgfile(fp); //�ر��ļ���ģ�Ȿ���������

		sprintf(tmp, "��������ļ�%s���۲��Ƿ����8������", cfgname);
		to_be_continued(tmp);
	}

	/* �ڶ���ģ�⣬ÿ����������� */
	if (1) {
		fp = open_cfgfile(cfgname, OPEN_OPT_RDWR);
		if (fp == NULL) {
			printf("�޷��������ļ�(%s).\n", cfgname);
			return -1;
		}

		for (i = 0; group_name[i]; i++) {
			for (j = 0; item[j].cfg_item_name; j++) {
				sprintf(tmp, "%s-%s", group_name[i], item[j].cfg_item_name);
				/* ˵����item_add�ĵ�3��������void*����˲���ʲô���ͣ�������union��һ����Ա�ĵ�ַ����������Ա��ַ */
				if ((ret = item_add(fp, group_name[i], tmp, &(item[j].cfg_item_value.ivalue), item[j].cfg_item_type)) <= 0)
					printf("����[%s]/%s ʧ��.\n", group_name[i], tmp);
				else
					printf("����[%s]/%s �ɹ�.\n", group_name[i], tmp);
			}
		}
		sprintf(tmp, "%s-%s", group_name[0], item[0].cfg_item_name);
		if ((ret = item_add(fp, group_name[0], tmp, &(item[0].cfg_item_value.ivalue), item[0].cfg_item_type)) <= 0)
			printf("������������[%s]/%s ʧ��.\n", group_name[0], tmp);
		else
			printf("������������[%s]/%s �ɹ�.\n", group_name[0], tmp);

		close_cfgfile(fp); //�ر��ļ���ģ�Ȿ���������

		sprintf(tmp, "��������ļ�%s���۲��Ƿ����8�������6��������", cfgname);
		to_be_continued(tmp);
	}

	/* ������һ��ģ�⣬ɾ���鼰�� */
	if (1) {
		//ɾ��ĩβ��������
		fp = open_cfgfile(cfgname, OPEN_OPT_RDWR);
		if (fp == NULL) {
			printf("�޷��������ļ�(%s).\n", cfgname);
			return -1;
		}
		if ((ret = group_add(fp, "��ʱ������")) <= 0)
			printf("������������[%s]ʧ��.\n", "��ʱ������");
		else
			printf("������������[%s]�ɹ�.\n", "��ʱ������");
		if ((ret = item_add(fp, "��ʱ������", "��ʱ������", NULL, TYPE_NULL)) <= 0)
			printf("������������[%s]/%s ʧ��.\n", "��ʱ������", "��ʱ������");
		else
			printf("������������[%s]/%s �ɹ�.\n", "��ʱ������", "��ʱ������");
		//����λ��ĩβ��ֻ��һ�����ʱ������

		printf("��������ɾ��<��ʱ������>��%d��\n", item_del(fp, "��ʱ������", "��ʱ������"));

		close_cfgfile(fp); //�ر��ļ���ģ�Ȿ���������

		sprintf(tmp, "��������ļ�%s���۲���ʱ�������Ƿ��ѱ�ɾ��", cfgname);
		to_be_continued(tmp);

		//ɾ��ĩβ��������
		fp = open_cfgfile(cfgname, OPEN_OPT_RDWR);
		if (fp == NULL) {
			printf("�޷��������ļ�(%s).\n", cfgname);
			return -1;
		}
		printf("��������ɾ��[��ʱ������]��%d��\n", group_del(fp, "��ʱ������"));

		close_cfgfile(fp); //�ر��ļ���ģ�Ȿ���������

		sprintf(tmp, "��������ļ�%s���۲���ʱ�������Ƿ��ѱ�ɾ��", cfgname);
		to_be_continued(tmp);
	}

	/* ����������ģ�⣬ɾ���鼰�� */
	if (1) {
		sprintf(tmp, "��������ļ�%s����[������3]�������ɷݣ�������2-������B�������ɷݣ��Һ����ֵ���Ͳ�ͬ", cfgname);
		to_be_continued(tmp);

		fp = open_cfgfile(cfgname, OPEN_OPT_RDWR);
		if (fp == NULL) {
			printf("�޷��������ļ�(%s).\n", cfgname);
			return -1;
		}

		printf("ɾ��[������3]��%d��\n", group_del(fp, "������3"));
		printf("ɾ��[������5]��%d��\n", group_del(fp, "������5"));
		printf("��������ɾ��[������X]��%d��\n", group_del(fp, "������X"));		//ɾ����ƥ����

		printf("ɾ��<������2-������B>��%d��\n", item_del(fp, "������2", "������2-������B"));
		printf("��������ɾ��<������X-������>��%d��\n", item_del(fp, "������X", "������X-������"));		//ɾ����ƥ�����е���
		printf("��������ɾ��<������1-������>��%d��\n", item_del(fp, "������1", "������1-������"));		//ɾ�����е���ƥ����

		close_cfgfile(fp); //�ر��ļ���ģ�Ȿ���������

		sprintf(tmp, "��������ļ�%s���۲�[������3]/[������5]/<������2-������B>�Ƿ��ѱ�ɾ��", cfgname);
		to_be_continued(tmp);
	}

	/* ���Ĵ�ģ�⣬�޸��� */
	if (1) {
		fp = open_cfgfile(cfgname, OPEN_OPT_RDWR);
		if (fp == NULL) {
			printf("�޷��������ļ�(%s).\n", cfgname);
			return -1;
		}

		int a = 54321;
		double b = 1023.4567;
		char c = 'N';

		/* �Ѵ�������� */
		if (item_update(fp, "������4", "������4-������B", &a, TYPE_INT)>0)
			printf("������4-������B�޸ĳɹ�\n");
		else
			printf("������4-������B�޸�ʧ��\n");
		if (item_update(fp, "������1", "������1-������D", "helloworld", TYPE_STRING))
			printf("������1-������D�޸ĳɹ�\n");
		else
			printf("������1-������D�޸�ʧ��\n");
		if (item_update(fp, "������8", "������8-������E", &b, TYPE_DOUBLE))
			printf("������8-������E�޸ĳɹ�\n");
		else
			printf("������8-������E�޸�ʧ��\n");
		if (item_update(fp, "������6", "������6-������F", NULL, TYPE_NULL))
			printf("������6-������F�޸ĳɹ�\n");
		else
			printf("������6-������F�޸�ʧ��\n");
		if (item_update(fp, "������7", "������7-������C", &c, TYPE_CHARACTER))
			printf("������7-������C�޸ĳɹ�\n");
		else
			printf("������7-������C�޸�ʧ��\n");

		/* ����������� */
		item_update(fp, "������6", "������6-������U", NULL, TYPE_NULL);
		item_update(fp, "������7", "������7-������V", &c, TYPE_CHARACTER);
		item_update(fp, "������7", "������6-������W", NULL, TYPE_NULL);
		item_update(fp, "������4", "������4-������X", &a, TYPE_INT);
		item_update(fp, "������1", "������1-������Y", "helloworld", TYPE_STRING);
		item_update(fp, "������8", "������8-������Z", &b, TYPE_DOUBLE);

		/*  ��������  */
		if (item_update(fp, "������0", "������0-������", &c, TYPE_CHARACTER))
			printf("��������������0-�������޸ĳɹ�\n");
		else
			printf("��������������0-�������޸�ʧ��\n");

		close_cfgfile(fp); //�ر��ļ���ģ�Ȿ���������

		sprintf(tmp, "��������ļ�%s���۲����������Ƿ����޸�", cfgname);
		to_be_continued(tmp);
	}

	/* �����ģ�⣬�� */
	if (1) {
		fp = open_cfgfile(cfgname, OPEN_OPT_RDONLY);
		if (fp == NULL) {
			printf("�޷��������ļ�(%s).\n", cfgname);
			return -1;
		}

		int a;
		double b;
		char c, s[80];

		/* �Ѵ�������� */
		if (item_get_value(fp, "������4", "������4-������B", &a, TYPE_INT) > 0)
			printf("[������4]/������4-������B=%d\n", a);
		if (item_get_value(fp, "������1", "������1-������F", &a, TYPE_INT) > 0)
			printf("[������1]/������1-������F=%d\n", a);
		if (item_get_value(fp, "������6", "������6-������D", &c, TYPE_CHARACTER) > 0)
			printf("[������6]/������6-������D=%c\n", c);
		if (item_get_value(fp, "������8", "������8-������C", s, TYPE_STRING) > 0)
			printf("[������8]/������8-������C=%s\n", s);
		if (item_get_value(fp, "������7", "������7-������E", NULL, TYPE_NULL) > 0)
			printf("[������7]/������7-������E=<NULL>\n");
		if (item_get_value(fp, "������6", "������6-������B", &b, TYPE_DOUBLE) > 0)
			printf("[������6]/������6-������B=%f\n", b);
		if (item_get_value(fp, "������1", "������100", NULL, TYPE_NULL) > 0)
			printf("[������1]/������100=<NULL>\n");
		else
			printf("[������1]/������100 ������\n");
		if (item_get_value(fp, "������X", "������", NULL, TYPE_NULL) > 0)
			printf("��������[������X]/������=<NULL>\n");
		else
			printf("��������[������X]/������ ������\n");

		close_cfgfile(fp); //�ر��ļ���ģ�Ȿ���������

		sprintf(tmp, "��������ļ�%s���۲��������ö�ȡ�Ƿ���ȷ", cfgname);
		to_be_continued(tmp);
	}

	/* ������ģ�� ר�Ų�������Ϊnull����� */
	if (nul) {
		printf("\n�����������¼������Ϊnull�����\n");
		//���null�飨Ӧ���ɹ���
		fp = open_cfgfile(cfgname, OPEN_OPT_RDWR);
		if (fp == NULL) {
			printf("�޷��������ļ�(%s).\n", cfgname);
			return -1;
		}
		if ((ret = group_add(fp, NULL)) <= 0)
			printf("���Ӽ���ʧ��.\n");
		else
			printf("���Ӽ���ɹ�.\n");
		close_cfgfile(fp);
		sprintf(tmp, "��������ļ�%s������ļ��Ƿ��б仯", cfgname);
		to_be_continued(tmp);

		//���null��Ŀ
		fp = open_cfgfile(cfgname, OPEN_OPT_RDWR);
		if (fp == NULL) {
			printf("�޷��������ļ�(%s).\n", cfgname);
			return -1;
		}
		int a = 10;
		double b = 18.3232;
		if (item_add(fp, NULL, "����1", NULL, TYPE_NULL)>0)
			printf("����<����1>�ɹ�.\n");
		else
			printf("����<����1>ʧ��.\n");
		if (item_add(fp, NULL, "����2", &a, TYPE_INT)>0)
			printf("����<����2>�ɹ�.\n");
		else
			printf("����<����2>ʧ��.\n");
		close_cfgfile(fp);
		sprintf(tmp, "��������ļ�%s������ļ��ʼ�Ƿ����������������", cfgname);
		to_be_continued(tmp);

		//ɾ��null��Ŀ
		fp = open_cfgfile(cfgname, OPEN_OPT_RDWR);
		if (fp == NULL) {
			printf("�޷��������ļ�(%s).\n", cfgname);
			return -1;
		}
		printf("�ɹ�ɾ��<����1>��%d��\n", item_del(fp, NULL, "����1"));
		printf("�ɹ�ɾ��<����>��%d��\n", item_del(fp, NULL, "����"));
		close_cfgfile(fp);
		sprintf(tmp, "��������ļ�%s���۲��ļ��Ƿ���ɾ������������", cfgname);
		to_be_continued(tmp);

		//����null��Ŀ
		fp = open_cfgfile(cfgname, OPEN_OPT_RDWR);
		if (fp == NULL) {
			printf("�޷��������ļ�(%s).\n", cfgname);
			return -1;
		}
		if (item_update(fp, NULL, "����2", &b, TYPE_DOUBLE) > 0)
			printf("�ɹ��޸ļ���2\n");
		if (item_update(fp, NULL, "����3", NULL, TYPE_NULL) > 0)
			printf("�ɹ��޸ļ���3\n");
		close_cfgfile(fp);
		sprintf(tmp, "��������ļ�%s������ļ��Ƿ����޸���������", cfgname);
		to_be_continued(tmp);

		//��ȡnull��Ŀֵ
		fp = open_cfgfile(cfgname, OPEN_OPT_RDWR);
		if (fp == NULL) {
			printf("�޷��������ļ�(%s).\n", cfgname);
			return -1;
		}
		double value;
		if (item_get_value(fp, NULL, "����2", &value, TYPE_DOUBLE) > 0) {
			printf("����2=%f\n", value);
		}
		close_cfgfile(fp);
		sprintf(tmp, "��������ļ�%s���۲��������ö�ȡ�Ƿ���ȷ", cfgname);
		to_be_continued(tmp);

		//ɾ��null�飨Ӧ���ɹ���
		fp = open_cfgfile(cfgname, OPEN_OPT_RDWR);
		if (fp == NULL) {
			printf("�޷��������ļ�(%s).\n", cfgname);
			return -1;
		}
		printf("ɾ��[NULL]��%d��\n", group_del(fp, NULL));
		close_cfgfile(fp);
		sprintf(tmp, "��������ļ�%s���۲�����Ƿ�ɾ��", cfgname);
		to_be_continued(tmp);

	}
	return 0;
}
//C++����
#else
int test_readconfig_cpp(const char *cfgname, const char **group_name, struct cfg_item *item)
{
	fstream fp;
	int ret, i;
	char tmp[256];

	/* ��һ��ģ�⣬��������� */
	if (1) {
		remove(cfgname); //ɾ���ļ�

		if (open_cfgfile(fp, cfgname, OPEN_OPT_RDWR) == 0) {
			cout << "�޷��������ļ�(" << cfgname << ")." << endl;
			return -1;
		}
		for (i = 0; group_name[i]; i++) {
			if ((ret = group_add(fp, group_name[i])) <= 0)
				cout << "����[" << group_name[i] << "]ʧ��." << endl;
			else
				cout << "����[" << group_name[i] << "]�ɹ�." << endl;
		}
		if ((ret = group_add(fp, group_name[0])) <= 0)
			cout << "������������[" << group_name[0] << "]ʧ��.\n";
		else
			cout << "������������[" << group_name[0] << "]�ɹ�.\n";

		close_cfgfile(fp); //�ر��ļ���ģ�Ȿ���������

		sprintf(tmp, "��������ļ�%s���۲��Ƿ����8������", cfgname);
		to_be_continued(tmp);
	}

	/* �ڶ���ģ�⣬ÿ����������� */
	if (1) {
		int j;

		if (open_cfgfile(fp, cfgname, OPEN_OPT_RDWR) == 0) {
			cout << "�޷��������ļ�(" << cfgname << ")." << endl;
			return -1;
		}

		for (i = 0; group_name[i]; i++) {
			for (j = 0; item[j].cfg_item_name; j++) {
				sprintf(tmp, "%s-%s", group_name[i], item[j].cfg_item_name);
				/* ˵����item_add�ĵ�3��������void*����˲���ʲô���ͣ�������union��һ����Ա�ĵ�ַ����������Ա��ַ */
				if ((ret = item_add(fp, group_name[i], tmp, &(item[j].cfg_item_value.ivalue), item[j].cfg_item_type)) <= 0)
					cout << "����[" << group_name[i] << "]/" << tmp << "ʧ��." << endl;
				else
					cout << "����[" << group_name[i] << "]/" << tmp << "�ɹ�." << endl;
			}
		}
		sprintf(tmp, "%s-%s", group_name[0], item[0].cfg_item_name);
		if ((ret = item_add(fp, group_name[0], tmp, &(item[0].cfg_item_value.ivalue), item[0].cfg_item_type)) <= 0)
			cout << "������������[" << group_name[0] << "]/" << tmp << " ʧ��.\n";
		else
			cout << "������������[" << group_name[0] << "]/" << tmp << " �ɹ�.\n";

		close_cfgfile(fp); //�ر��ļ���ģ�Ȿ���������

		sprintf(tmp, "��������ļ�%s���۲��Ƿ����8�������6��������", cfgname);
		to_be_continued(tmp);
	}

	/* ������һ��ģ�⣬ɾ���鼰�� */
	if (1) {
		if (open_cfgfile(fp, cfgname, OPEN_OPT_RDWR) == 0) {
			cout << "�޷��������ļ�(" << cfgname << ")." << endl;
			return -1;
		}

		if ((ret = group_add(fp, "��ʱ������")) <= 0)
			cout << "������������[��ʱ������]ʧ��.\n";
		else
			cout << "������������[��ʱ������]�ɹ�.\n";
		if ((ret = item_add(fp, "��ʱ������", "��ʱ������", NULL, TYPE_NULL)) <= 0)
			cout << "������������[��ʱ������]/��ʱ������ ʧ��.\n";
		else
			cout << "������������[��ʱ������]/��ʱ������ �ɹ�.\n";
		//����λ��ĩβ��ֻ��һ�����ʱ������

		cout << "��������ɾ��<��ʱ������>��" << item_del(fp, cfgname, "��ʱ������", "��ʱ������") << "��\n";

		close_cfgfile(fp); //�ر��ļ���ģ�Ȿ���������

		if (open_cfgfile(fp, cfgname, OPEN_OPT_RDWR) == 0) {
			cout << "�޷��������ļ�(" << cfgname << ")." << endl;
			return -1;
		}
		cout << "��������ɾ��[��ʱ������]��" << group_del(fp, cfgname, "��ʱ������") << "��\n";
		close_cfgfile(fp); //�ر��ļ���ģ�Ȿ���������

		sprintf(tmp, "��������ļ�%s���۲���ʱ�������Ƿ��ѱ�ɾ��", cfgname);
		to_be_continued(tmp);
	}

	/* ����������ģ�⣬ɾ���鼰�� */
	if (1) {
		sprintf(tmp, "��������ļ�%s����[������3]�������ɷݣ�������2-������B�������ɷݣ��Һ����ֵ���Ͳ�ͬ", cfgname);
		to_be_continued(tmp);

		if (open_cfgfile(fp, cfgname, OPEN_OPT_RDWR) == 0) {
			cout << "�޷��������ļ�(" << cfgname << ")." << endl;
			return -1;
		}

		cout << "ɾ��[������3]��" << group_del(fp, cfgname, "������3") << "��" << endl;
		cout << "ɾ��[������5]��" << group_del(fp, cfgname, "������5") << "��" << endl;
		cout << "��������ɾ��[������X]��" << group_del(fp, cfgname, "������X") << "��" << endl;;		//ɾ����ƥ����

		cout << "ɾ��<������2-������B>��" << item_del(fp, cfgname, "������2", "������2-������B") << "��" << endl;
		cout << "��������ɾ��<������X-������>��" << item_del(fp, cfgname, "������X", "������X-������") << "��\n";		//ɾ����ƥ�����е���
		cout << "��������ɾ��<������1-������>��" << item_del(fp, cfgname, "������1", "������1 - ������") << "��\n";		//ɾ�����е���ƥ����


		close_cfgfile(fp); //�ر��ļ���ģ�Ȿ���������

		sprintf(tmp, "��������ļ�%s���۲�[������3]/[������5]/<������2-������B>�Ƿ��ѱ�ɾ��", cfgname);
		to_be_continued(tmp);
	}

	/* ���Ĵ�ģ�⣬�޸��� */
	if (1) {
		if (open_cfgfile(fp, cfgname, OPEN_OPT_RDWR) == 0) {
			cout << "�޷��������ļ�(" << cfgname << ")." << endl;
			return -1;
		}

		int a = 54321;
		double b = 1023.4567;
		char c = 'N';
		/* �Ѵ�������� */
		item_update(fp, cfgname, "������4", "������4-������B", &a, TYPE_INT);
		item_update(fp, cfgname, "������1", "������1-������D", "helloworld", TYPE_STRING);
		item_update(fp, cfgname, "������8", "������8-������E", &b, TYPE_DOUBLE);
		item_update(fp, cfgname, "������6", "������6-������F", NULL, TYPE_NULL);
		item_update(fp, cfgname, "������7", "������7-������C", &c, TYPE_CHARACTER);

		/* ����������� */
		item_update(fp, cfgname, "������6", "������6-������U", NULL, TYPE_NULL);
		item_update(fp, cfgname, "������7", "������7-������V", &c, TYPE_CHARACTER);
		item_update(fp, cfgname, "������7", "������6-������W", NULL, TYPE_NULL);
		item_update(fp, cfgname, "������4", "������4-������X", &a, TYPE_INT);
		item_update(fp, cfgname, "������1", "������1-������Y", "helloworld", TYPE_STRING);
		item_update(fp, cfgname, "������8", "������8-������Z", &b, TYPE_DOUBLE);

		/*  ��������  */
		if (item_update(fp, cfgname, "������0", "������0-������", &c, TYPE_CHARACTER))
			cout << "��������������0-�������޸ĳɹ�\n";
		else
			cout << "��������������0-�������޸�ʧ��\n";

		close_cfgfile(fp); //�ر��ļ���ģ�Ȿ���������

		sprintf(tmp, "��������ļ�%s���۲����������Ƿ����޸�", cfgname);
		to_be_continued(tmp);
	}

	/* �����ģ�⣬�� */
	if (1) {
		if (open_cfgfile(fp, cfgname, OPEN_OPT_RDONLY) == 0) {
			cout << "�޷��������ļ�(" << cfgname << ")." << endl;
			return -1;
		}

		int a;
		double b;
		char c, s[80];

		/* �Ѵ�������� */
		if (item_get_value(fp, "������4", "������4-������B", &a, TYPE_INT) > 0)
			printf("[������4]/������4-������B=%d\n", a);
		else
			printf("[������4]/������4-������B ������\n");
		if (item_get_value(fp, "������1", "������1-������F", &a, TYPE_INT) > 0)
			printf("[������1]/������1-������F=%d\n", a);
		else
			printf("[������1]/������1-������F ������\n");
		if (item_get_value(fp, "������6", "������6-������D", &c, TYPE_CHARACTER) > 0)
			printf("[������6]/������6-������D=%c\n", c);
		else
			printf("[������6]/������6-������D ������\n");
		if (item_get_value(fp, "������8", "������8-������C", s, TYPE_STRING) > 0)
			printf("[������8]/������8-������C=%s\n", s);
		else
			printf("[������8]/������8-������C ������\n");
		if (item_get_value(fp, "������7", "������7-������E", NULL, TYPE_NULL) > 0)
			printf("[������7]/������7-������E=<NULL>\n");
		else
			printf("[������7]/������7-������E ������\n");
		if (item_get_value(fp, "������6", "������6-������B", &b, TYPE_DOUBLE) > 0)
			printf("[������6]/������6-������B=%f\n", b);
		else
			printf("[������6]/������6-������B ������\n");
		if (item_get_value(fp, "������1", "������100", NULL, TYPE_NULL) > 0)
			printf("[������1]/������100=<NULL>\n");
		else
			printf("[������1]/������100 ������\n");
		if (item_get_value(fp, "������X", "������", NULL, TYPE_NULL) > 0)
			printf("��������[������X]/������=<NULL>\n");
		else
			printf("��������[������X]/������ ������\n");

		close_cfgfile(fp); //�ر��ļ���ģ�Ȿ���������

		sprintf(tmp, "��������ļ�%s���۲��������ö�ȡ�Ƿ���ȷ", cfgname);
		to_be_continued(tmp);
	}

	/* ������ģ�� ר�Ų�������Ϊnull����� */
	if (nul) {
		cout << endl << "�����������¼������Ϊnull�����" << endl;
		//���null�飨Ӧ���ɹ���
		if (open_cfgfile(fp, cfgname, OPEN_OPT_RDONLY) == 0) {
			cout << "�޷��������ļ�(" << cfgname << ")." << endl;
			return -1;
		}
		if ((ret = group_add(fp, NULL)) <= 0)
			cout << "���Ӽ���ʧ��.\n";
		else
			cout << "���Ӽ���ɹ�.\n";
		close_cfgfile(fp);
		sprintf(tmp, "��������ļ�%s������ļ��Ƿ��б仯", cfgname);
		to_be_continued(tmp);

		//���null��Ŀ
		if (open_cfgfile(fp, cfgname, OPEN_OPT_RDWR) == 0) {
			cout << "�޷��������ļ�(" << cfgname << ")." << endl;
			return -1;
		}
		int a = 10;
		double b = 18.3232;
		if (item_add(fp, NULL, "����1", NULL, TYPE_NULL)>0)
			cout << "����<����1>�ɹ�.\n";
		else
			cout << "����<����1>ʧ��.\n";
		if (item_add(fp, NULL, "����2", &a, TYPE_INT)>0)
			cout << "����<����2>�ɹ�.\n";
		else
			cout << "����<����2>ʧ��.\n";
		close_cfgfile(fp);
		sprintf(tmp, "��������ļ�%s������ļ��ʼ�Ƿ����������������", cfgname);
		to_be_continued(tmp);

		//ɾ��null��Ŀ
		if (open_cfgfile(fp, cfgname, OPEN_OPT_RDWR) == 0) {
			cout << "�޷��������ļ�(" << cfgname << ")." << endl;
			return -1;
		}
		int del;
		del = item_del(fp, cfgname, NULL, "��ʼֵ");
		cout << "�ɹ�ɾ��<����1>��" << item_del(fp, cfgname, NULL, "����1") << "��\n";
		cout << "�ɹ�ɾ��<����>��" << item_del(fp, cfgname, NULL, "����") << "��\n";

		close_cfgfile(fp);
		sprintf(tmp, "��������ļ�%s���۲��ļ��Ƿ���ɾ������������", cfgname);
		to_be_continued(tmp);

		//����null��Ŀ
		if (open_cfgfile(fp, cfgname, OPEN_OPT_RDWR) == 0) {
			cout << "�޷��������ļ�(" << cfgname << ")." << endl;
			return -1;
		}
		if (item_update(fp, cfgname, NULL, "����2", &b, TYPE_DOUBLE) > 0)
			cout << "�ɹ��޸ļ���2\n";
		if (item_update(fp, cfgname, NULL, "����3", NULL, TYPE_NULL) > 0)
			cout << "�ɹ��޸ļ���3\n";

		close_cfgfile(fp);
		sprintf(tmp, "��������ļ�%s������ļ��Ƿ����޸���������", cfgname);
		to_be_continued(tmp);

		//��ȡnull��Ŀֵ
		if (open_cfgfile(fp, cfgname, OPEN_OPT_RDONLY) == 0) {
			cout << "�޷��������ļ�(" << cfgname << ")." << endl;
			return -1;
		}
		double value;
		if (item_get_value(fp, NULL, "����2", &value, TYPE_DOUBLE) > 0) {
			cout << "����2=" << value << "\n";
		}
		close_cfgfile(fp);
		sprintf(tmp, "��������ļ�%s���۲��������ö�ȡ�Ƿ���ȷ", cfgname);
		to_be_continued(tmp);
	}

	//ɾ��null�飨Ӧ���ɹ���
	if (open_cfgfile(fp, cfgname, OPEN_OPT_RDONLY) == 0) {
		cout << "�޷��������ļ�(" << cfgname << ")." << endl;
		return -1;
	}
	cout << "ɾ��[NULL]��" << group_del(fp, cfgname, NULL) << "��\n";
	close_cfgfile(fp);
	sprintf(tmp, "��������ļ�%s���۲�����Ƿ�ɾ��", cfgname);
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
		"������1",
		"������2",
		"������3",
		"������4",
		"������5",
		"������6",
		"������7",
		"������8",
		NULL
	};

	struct cfg_item item[] =
	{
		{ "������A",TYPE_INT, 0 },		//������union�ĳ�ʼ����ֻ�ܳ�ʼ����һ��Ԫ��
	{ "������B", TYPE_DOUBLE, 0 },
	{ "������C",TYPE_STRING, 0 },
	{ "������D",TYPE_CHARACTER, 0 },
	{ "������E", TYPE_NULL, 0 },
	{ "������F",TYPE_INT, 0 },
	{ NULL,TYPE_NULL, 0 }
	};
	set_item(item); //��union����ֵ
#if C
	test_readconfig_c(cfgname, group_name, item);
#else
	test_readconfig_cpp(cfgname, group_name, item);
#endif
	return 0;
}
