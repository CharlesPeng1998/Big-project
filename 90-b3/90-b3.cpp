/*1751367 ��2 ����*/
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include "..\common\common_cfgfile_tools.hpp"

using namespace std;

int main()
{

	fstream cfgfile;
	if (!open_cfgfile(cfgfile, "test.cfg", OPEN_OPT_RDWR))
	{
		cout << "���ļ�ʧ��" << endl;
	}
	else cout << "�ļ��򿪳ɹ�" << endl;
	double i;
	item_get_value(cfgfile, "test1", "item2", &i, TYPE_DOUBLE);

	cout << i << endl;



	return 0;
}