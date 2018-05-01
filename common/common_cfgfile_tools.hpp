/*1751367 ��2 ����*/
#pragma once

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <fstream>
using namespace std;


#define OPEN_OPT_RDONLY 0 //��ֻ����ʽ�򿪣��򲻿��򷵻�ʧ��)
#define OPEN_OPT_RDWR 1 //�Զ�д��ʽ�򿪣��򲻿��ļ��򴴽���
#define MAX_LINE_CHAR_NUM 600 //һ�п��������ַ�����

//������
#define ANNOTATION 1
#define VALUE 2

struct cfgitem {
	char cfg_item_name[32] = { 0 };

	int type = NULL; /*�������������������������Ϊÿһ�ж���һ���
					 ����������У�ע��(ANNOTATION)��ֵ(VALUE)����(NULL)*/

	char cfg_item_value[128] = { 0 }; //ֵһ����Ϊ�ַ�������
	char annotation[50] = { 0 }; //��¼���е�ע�� 
	cfgitem *next=NULL;
};

struct Group
{
	char group_name[32] = { 0 };
	cfgitem *item_head=NULL;
	Group *next=NULL;
};

enum ITEM_TYPE
{
	TYPE_INT,
	TYPE_DOUBLE,
	TYPE_STRING,
	TYPE_CHARACTER,
	TYPE_NULL
};

static int file_length(fstream &fp);
static int file_resize(const char *filename, fstream &fp, int newsize);
int open_cfgfile(fstream &fp, const char *cfgname, int opt);
void close_cfgfile(fstream &fp);
Group *read_cfg_no_anno(fstream &cfgfile);
Group *read_cfg(fstream &cfgfile);
void print_cfg(Group *group_head);
void delete_cfg(Group *group_head);
bool group_exist(Group *group_head, const char *group_name);
bool item_exist(cfgitem *item_head, const char *item_name);
int group_add(fstream &fp, const char *group_name);
int group_del(fstream &fp, const char *filename, const char *group_name);
int write_cfg(fstream &cfgfile, Group *group_head);
int item_add(fstream &fp, const char *group_name, const char *item_name, const void *item_value, const enum ITEM_TYPE item_type);
int item_del(fstream &fp, const char *filename, const char *group_name, const char *item_name);
int item_update(fstream &fp, const char *filename, const char *group_name, const char *item_name, const void *item_value, const enum ITEM_TYPE item_type);
int item_get_value(fstream &fp, const char *group_name, const char *item_name, void *item_value, const enum ITEM_TYPE item_type);