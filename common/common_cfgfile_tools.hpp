/*1751367 计2 彭健聪*/
#pragma once

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <fstream>
using namespace std;


#define OPEN_OPT_RDONLY 0 //以只读方式打开（打不开则返回失败)
#define OPEN_OPT_RDWR 1 //以读写方式打开（打不开文件则创建）
#define MAX_LINE_CHAR_NUM 600 //一行可能最多的字符数量

//项的类别
#define ANNOTATION 1
#define VALUE 2

struct cfgitem {
	char cfg_item_name[32] = { 0 };

	int type = NULL; /*该项的类别（在这个程序当中我们认为每一行都是一个项）
					 因此项的类别有：注释(ANNOTATION)，值(VALUE)，空(NULL)*/

	char cfg_item_value[128] = { 0 }; //值一律作为字符串处理
	char annotation[50] = { 0 }; //记录该行的注释 
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