/*1751367 计2 彭健聪*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <cstdio>

using namespace std;

extern "C"
{
#include "../common/common_cfgfile_tools.h"
}

int main()
{

	FILE *cfgfile = open_cfgfile("test.cfg", OPEN_OPT_RDWR);

	if (cfgfile != NULL)
	{
		cout << "打开文件成功" << endl;
	}
	else
	{
		cout << "打开文件失败" << endl;
		return -1;
	}


	//group_add(cfgfile, "这是另外一个配置组");

	//int i = 1000999;
	//item_add(cfgfile, "这是另外一个配置组", "damn", &i, TYPE_INT);
	
	item_del(cfgfile, "配置组6", "配置组6-设置项D");

	
	return 0;
}