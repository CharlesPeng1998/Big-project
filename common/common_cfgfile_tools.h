#pragma once

#include <stdio.h>

enum ITEM_TYPE { TYPE_INT = 0, TYPE_DOUBLE, TYPE_STRING, TYPE_CHARACTER, TYPE_NULL }; 

#define OPEN_OPT_RDONLY		0	//��ֻ����ʽ�򿪣��򲻿��򷵻�ʧ�ܣ�
#define OPEN_OPT_RDWR		1	//�Զ�д��ʽ�򿪣��򲻿��ļ��򴴽���


#define MAX_LINE_CHAR_NUM 256 //һ�п��������ַ�����

//������
#define ANNOTATION 1
#define VALUE 2

typedef struct cfg_item {
	char cfg_item_name[32];

	int type; /*�������������������������Ϊÿһ�ж���һ���
					 ����������У�ע��(ANNOTATION)��ֵ(VALUE)����(NULL)*/

	char cfg_item_value[128]; //ֵһ����Ϊ�ַ�������
	char annotation[50]; //��¼���е�ע�� 
	struct cfg_item *next;
}cfg_item;

typedef struct Group
{
	char group_name[32];
	struct cfg_item *item_head;
	struct Group *next;
}Group;

/* �������λ�ã��������һ�С��������һ�����С����������һ��Ŀ�ʼ�� */
enum INSERT_POS_TYPE { FIRST_LINE_AFTER_GROUP = 0, FIRST_SPACE_LINE_AFTER_GROUP, BEFORE_NEXT_GROUP};

static int file_resize(FILE *fp, int newsize);
void init_cfg_item(cfg_item *item);
void init_Group(Group *group);
Group *read_cfg(FILE *cfgfile);
void print_cfg(Group *group_head);
int write_cfg(FILE *cfgfile, Group *group_head);
void delete_cfg(Group *group_head);
int group_exist(Group *group_head, const char *group_name);
int item_exist(cfg_item *item_head, const char *item_name);
FILE *open_cfgfile(const char *cfgname, int opt);
void close_cfgfile(FILE *fp);
int group_add(FILE *fp, const char *group_name);
int group_del(FILE *fp, const char *group_name);
int item_add(FILE *fp, const char *group_name, const char *item_name, const void *item_value, const enum ITEM_TYPE item_type);
int item_del(FILE *fp, const char *group_name, const char *item_name);
int item_update(FILE *fp, const char *group_name, const char *item_name, const void *item_value, const enum ITEM_TYPE item_type);
int item_get_value(FILE *fp, const char *group_name, const char *item_name, void *item_value, const enum ITEM_TYPE item_type);
