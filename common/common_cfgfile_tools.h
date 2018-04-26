#pragma once

#include <stdio.h>

enum ITEM_TYPE { TYPE_INT = 0, TYPE_DOUBLE, TYPE_STRING, TYPE_CHARACTER, TYPE_NULL }; 

#define OPEN_OPT_RDONLY		0	//��ֻ����ʽ�򿪣��򲻿��򷵻�ʧ�ܣ�
#define OPEN_OPT_RDWR		1	//�Զ�д��ʽ�򿪣��򲻿��ļ��򴴽���

/* �������λ�ã��������һ�С��������һ�����С����������һ��Ŀ�ʼ�� */
enum INSERT_POS_TYPE { FIRST_LINE_AFTER_GROUP = 0, FIRST_SPACE_LINE_AFTER_GROUP, BEFORE_NEXT_GROUP};

FILE *open_cfgfile(const char *cfgname, int opt);
void close_cfgfile(FILE *fp);
int group_add(FILE *fp, const char *group_name);
int group_del(FILE *fp, const char *group_name);
int item_add(FILE *fp, const char *group_name, const char *item_name, const void *item_value, const enum ITEM_TYPE item_type);
int item_del(FILE *fp, const char *group_name, const char *item_name);
int item_update(FILE *fp, const char *group_name, const char *item_name, const void *item_value, const enum ITEM_TYPE item_type);
int item_get_value(FILE *fp, const char *group_name, const char *item_name, void *item_value, const enum ITEM_TYPE item_type);
