/*******�������ļ��е�������д�����Ա���*******/
		/*******EXPERIMENTAL*******/
/*******��Ҫע�⿼��ĳ���Ƿ�Ϊע��*******/
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

#define MAX_LINE_CHAR_NUM 256 //һ�п��������ַ�����

//������
#define ANNOTATION 1
#define VALUE 2

struct cfg_item {
	char cfg_item_name[32] = { 0 };

	int type= NULL; /*�������������������������Ϊÿһ�ж���һ���
	               ����������У�ע��(ANNOTATION)��ֵ(VALUE)����(NULL)*/

	char cfg_item_value[128] = { 0 }; //ֵһ����Ϊ�ַ�������
	char *annotation; //��¼���е�ע�� 
	cfg_item *next;
	//�����������̬�����ڴ�
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