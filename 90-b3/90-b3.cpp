/*1751367 ��2 ����*/
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
		cout << "���ļ��ɹ�" << endl;
	}
	else
	{
		cout << "���ļ�ʧ��" << endl;
		return -1;
	}


	//group_add(cfgfile, "��������һ��������");

	//int i = 1000999;
	//item_add(cfgfile, "��������һ��������", "damn", &i, TYPE_INT);
	
	item_del(cfgfile, "������6", "������6-������D");

	
	return 0;
}