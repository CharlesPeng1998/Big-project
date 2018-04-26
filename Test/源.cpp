/*******将配置文件中的配置组写入线性表中*******/
		/*******EXPERIMENTAL*******/
/*******还要注意考虑某行是否为注释*******/
#define _CRT_SECURE_NO_WARNINGS
//#define TEST
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <io.h>
#include <conio.h>
#include <experimental/filesystem>
#include <sstream>
using namespace std;

#define MAX_LINE_CHAR_NUM 256 //一行可能最多的字符数量

//项的类别
#define ANNOTATION 1
#define VALUE 2

struct cfg_item {
	char cfg_item_name[32] = { 0 };

	int type= NULL; /*该项的类别（在这个程序当中我们认为每一行都是一个项）
	               因此项的类别有：注释(ANNOTATION)，值(VALUE)，空(NULL)*/

	char cfg_item_value[128] = { 0 }; //值一律作为字符串处理
	char *annotation; //记录该行的注释 
	cfg_item *next;
	//以上两项均动态申请内存
};

struct Group
{
	char group_name[32] = { 0 };
	cfg_item *item_head;
	Group *next;
};


int main()
{
	fstream file("test.txt", ios::in | ios::out);

	char line[100];
	while (!file.eof())
	{
		file.getline(line, 100, '\n');
		cout << line << endl;
	}

	file.clear();
	file.seekg(0, ios::beg);

	file << "fuck\nshit\ndamn\n" << endl;

	return 0;
}