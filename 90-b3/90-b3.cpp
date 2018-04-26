/*1751367 计2 彭健聪*/
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
		cout << "打开文件失败" << endl;
	}
	else cout << "文件打开成功" << endl;
	double i;
	item_get_value(cfgfile, "test1", "item2", &i, TYPE_DOUBLE);

	cout << i << endl;



	return 0;
}