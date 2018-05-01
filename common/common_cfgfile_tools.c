/*1751367 ��2 ����*/
#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include <conio.h>
#include "..\common\common_cfgfile_tools.h"

//cfg_item�ṹ���ʼ������
void init_cfg_item(cfgitem *item)
{
	item->cfg_item_name[0] = '\0';
	item->annotation[0] = '\0';
	item->cfg_item_value[0] = '\0';
	item->next = NULL;
	item->type = 0;
}

static int file_resize(FILE *fp, int newsize)
{
	int now_pos = ftell(fp);
	/* �����С�Ǹ�����ֱ�ӷ���-1 */
	if (newsize < 0)
		return -1;

	_chsize(_fileno(fp), newsize);

	/* �����ǰ�ļ�ָ�볬�����ļ���С����rewind */
	if (now_pos > newsize)
		rewind(fp);

	return 0;
}

//Group�ṹ���ʼ������
void init_Group(Group *group)
{
	group->group_name[0] = '\0';
	group->item_head = NULL;
	group->next = NULL;
}

//�������ļ�
FILE *open_cfgfile(const char *cfgname, int opt)
{
	FILE *cfgfile=NULL;

	switch (opt)
	{
	case OPEN_OPT_RDONLY:
		cfgfile = fopen(cfgname, "r");
		break;

	case OPEN_OPT_RDWR:
		cfgfile = fopen(cfgname, "r+");
		if (cfgfile == NULL)
			cfgfile = fopen(cfgname, "w+");
		break;
	}

	return cfgfile;
}

//�ر������ļ�
void close_cfgfile(FILE *fp)
{
	fclose(fp);
}

//�ú������ڶ�ȡ�����ļ������ɶ�ά����
Group *read_cfg(FILE *cfgfile)
{
	//������ͷ
	Group *group_head = (Group *)malloc(sizeof(Group));
	init_Group(group_head);

	group_head->item_head = (cfgitem *)malloc(sizeof(cfgitem));
	init_cfg_item(group_head->item_head);

	Group *group_ptr1 = group_head;
	cfgitem *item_ptr1 = group_head->item_head;
	cfgitem *item_ptr2 = item_ptr1;

	//��ȡһ��
	char line[MAX_LINE_CHAR_NUM]; //��ʱ�洢���е�����

	while (fgets(line, MAX_LINE_CHAR_NUM, cfgfile))
	{
		//���Ǳ��дӿ�ͷ����ע�͵����
		if (line[0] == '#')
		{
			item_ptr1->type = ANNOTATION;

			sscanf(line, "%s",item_ptr1->annotation);
		}
		else if (line[0] == '[')
		{
			/*��������һ������������Ҫ������ǰ���������Ľ�����
			���Ҵ���һ���µ����㣬���¿�ʼ������Ľ���*/

			//������ǰ���������Ľ���
			if (item_ptr1 != item_ptr2)
			{
				free(item_ptr1);
				item_ptr2->next = NULL;
			}
			else item_ptr1->next = NULL;

			group_ptr1->next = (Group *)malloc(sizeof(Group));
			init_Group(group_ptr1->next);

			group_ptr1 = group_ptr1->next;
			group_ptr1->item_head = (cfgitem *)malloc(sizeof(cfgitem));
			init_cfg_item(group_ptr1->item_head);

			item_ptr1 = group_ptr1->item_head;
			item_ptr2 = item_ptr1;

			//��ֵ����
			line[strlen(line) - 2] = '\0';
			strcpy(group_ptr1->group_name, line + 1);

			continue;
		}
		else if (line[0] != '\0')
		{
			item_ptr1->type = VALUE;
			//����Ϊ��Ч���ע�ͣ������

			//�������е�һ���ȺŸ�Ϊ�ո񣬷�������Ķ�ȡ
			for (int i = 0; i < (int)(strlen(line)); i++)
			{
				if (line[i] == '=')
				{
					line[i] = ' ';
					break;
				}
			}

			sscanf(line, "%s%s%s", 
				item_ptr1->cfg_item_name, 
				item_ptr1->cfg_item_value, 
				item_ptr1->annotation);
		}

		/*ÿ��ptr1�ƶ�����һ�����֮ǰ��ptr2�ƶ�����ǰ���
		�Ա��ڴ���һ���µ�����ʱ������ǰ������ָ��NULL*/
		item_ptr2 = item_ptr1;

		if (feof(cfgfile))
		{
			//����ļ���ȡ����򽫽��ָ��NULL
			item_ptr1->next = NULL;
			group_ptr1->next = NULL;
		}
		else
		{
			item_ptr1->next = (cfgitem*)malloc(sizeof(cfgitem));
			init_cfg_item(item_ptr1->next);

			item_ptr1 = item_ptr1->next;
		}
	}

	fseek(cfgfile, 0, SEEK_SET);
	return group_head;
}

//�ú������ڽ���ά�����е�������Ϣ��ӡ����Ļ��(����޸Ľ���ã�
void print_cfg(Group *group_head)
{
	Group *group_ptr1 = group_head;
	cfgitem *item_ptr1 = group_head->item_head;

	while (group_ptr1 != NULL)
	{
		item_ptr1 = group_ptr1->item_head;

		//��ӡ����
		if (group_ptr1->group_name[0] != '\0')
		{
			printf("[%s]\n", group_ptr1->group_name);
		}

		while (item_ptr1 != NULL)
		{
			if (item_ptr1->type == ANNOTATION)
			{
				//��������ΪNULL���������ʵΪע��,ֱ�Ӵ�ӡ����
				printf("%s\n", item_ptr1->annotation);
			}
			else if (item_ptr1->type == VALUE)
			{
				printf("%s = %s    %s\n", item_ptr1->cfg_item_name, item_ptr1->cfg_item_value, item_ptr1->annotation);
			}

			item_ptr1 = item_ptr1->next;
		}

		group_ptr1 = group_ptr1->next;
	}
}

//�ú�������ά�����е�������Ϣд���ı��ļ�(�����ļ�ָ���λ�ã�
int write_cfg(FILE *cfgfile, Group *group_head)
{
	fseek(cfgfile, 0, SEEK_SET);

	Group *group_ptr1 = group_head;
	cfgitem *item_ptr1 = group_head->item_head;

	while (group_ptr1 != NULL)
	{
		item_ptr1 = group_ptr1->item_head;

		//��ӡ����
		if (group_ptr1->group_name[0] != '\0')
		{
			fprintf(cfgfile,"[%s]\n", group_ptr1->group_name);
		}

		while (item_ptr1 != NULL)
		{
			if (item_ptr1->type == ANNOTATION)
			{
				//����Ϊע��,ֱ�Ӵ�ӡ����
				fprintf(cfgfile, "%s\n", item_ptr1->annotation);
			}
			else if (item_ptr1->type == VALUE)
			{
				fprintf(cfgfile, "%s = %s    %s\n",
					item_ptr1->cfg_item_name, 
					item_ptr1->cfg_item_value, 
					item_ptr1->annotation);
			}

			item_ptr1 = item_ptr1->next;
		}

		group_ptr1 = group_ptr1->next;
	}

	return (int)(ftell(cfgfile));
}

//�ú��������ͷŶ�ά����
void delete_cfg(Group *group_head)
{
	Group *group_ptr1 = group_head;
	Group *group_ptr2 = group_head;
	cfgitem *item_ptr1 = group_head->item_head;
	cfgitem *item_ptr2 = group_head->item_head;

	while (group_ptr1 != NULL)
	{
		group_ptr1 = group_ptr1->next;
		item_ptr1 = group_ptr2->item_head;
		item_ptr2 = group_ptr2->item_head;

		while (item_ptr1 != NULL)
		{
			item_ptr1 = item_ptr1->next;
			free(item_ptr2);

			item_ptr2 = item_ptr1;
		}

		free(group_ptr2);
		group_ptr2 = group_ptr1;
	}
}

//���ָ���������Ƿ����
int group_exist(Group *group_head, const char *group_name)
{
	int exist = 0;
	Group *group_ptr = group_head;

	while (group_ptr != NULL)
	{
		if (strcmp(group_ptr->group_name, group_name) == 0)
		{
			exist = 1;
			break;
		}

		group_ptr = group_ptr->next;
	}

	return exist;
}

//�����������ָ�����Ƿ����
int item_exist(cfgitem *item_head, const char *item_name)
{
	int exist = 0;
	cfgitem *item_ptr = item_head;

	while (item_ptr != NULL)
	{
		if (strcmp(item_ptr->cfg_item_name, item_name) == 0)
		{
			exist = 1;
			break;
		}

		item_ptr = item_ptr->next;
	}

	return exist;
}

//���������
int group_add(FILE *cfgfile, const char *group_name)
{
	if (group_name == NULL)
	{
		return 0;
	}

	Group *group_head = read_cfg(cfgfile);

	//�������Ѵ��ڣ��򷵻�0
	if (group_exist(group_head, group_name))
	{
		return 0;
	}

	//����������������ĩ�ˣ��������µĽ��
	Group *group_ptr = group_head;

	while (group_ptr->next != NULL)
	{
		group_ptr = group_ptr->next;
	}

	group_ptr->next = (Group *)malloc(sizeof(Group));
	init_Group(group_ptr->next);

	if (group_ptr->next == NULL)
	{
		//�ڴ�����ʧ�ܣ������������ʧ��

		//�ͷ�����
		delete_cfg(group_head);
		return 0;
	}

	//��ֵ����
	strcpy(group_ptr->next->group_name, group_name);

	/*��һ������,���˸о���������б�Ҫ
	��Ȼ�ں���������п��ܻ������鷳*/
	group_ptr->next->item_head = (cfgitem *)malloc(sizeof(cfgitem));
	init_cfg_item(group_ptr->next->item_head);
	
	if (group_ptr->next->item_head = NULL)
	{
		//�ڴ�����ʧ��,���ж����������ʧ�ܣ���Ҫ������������ͷ�
		free(group_ptr->next);
		group_ptr->next = NULL;

		//�ͷ�����
		delete_cfg(group_head);
		return 0;
	}

	//д���ļ�
	int curr_pos = write_cfg(cfgfile, group_head);

	//�ͷ�����
	delete_cfg(group_head);

	fseek(cfgfile, 0, SEEK_SET);
	return 1;
}

//ɾ��������
int group_del(FILE *fp, const char *group_name)
{
	//��һ���������㼰�����µ��������ͷţ�����ǰһ������ӵ���һ���

	if (group_name == NULL)
	{
		return 0;
	}

	int group_num = 0;
	//���Ȼ��ǵ��Ƚ�����ά����
	Group *group_head = read_cfg(fp);

	//�����鲻���ڣ��򷵻�0
	if (!group_exist(group_head, group_name))
	{
		delete_cfg(group_head);
		return 0;
	}

	Group *group_ptr1 = group_head;
	Group *group_ptr2 = group_head;

	cfgitem *item_ptr1;
	cfgitem *item_ptr2;

	while (group_ptr1->next != NULL)
	{
		group_ptr1 = group_ptr1->next;

		if (strcmp(group_ptr1->group_name, group_name) == 0)
		{
			item_ptr1 = item_ptr2 = group_ptr1->item_head;

			//�������µ��������ͷ�
			while (item_ptr1 != NULL)
			{
				item_ptr1 = item_ptr1->next;
				free(item_ptr2);

				item_ptr2 = item_ptr1;
			}

			//ǰһ���ͺ�һ�������
			group_ptr2->next = group_ptr1->next;
			//�ͷŵ�ǰ���
			free(group_ptr1);
			group_ptr1 = group_ptr2;

			group_num++;
		}
		else
		{
			group_ptr2 = group_ptr1;
		}
	}

	//д���ļ�
	int curr_pos = write_cfg(fp, group_head);
	//ѹ���ļ���С
	file_resize(fp, curr_pos);

	delete_cfg(group_head);

	fseek(fp, 0, SEEK_SET);

	return group_num;
}

//���������
int item_add(FILE *fp, const char *group_name, const char *item_name, const void *item_value, const enum ITEM_TYPE item_type)
{
	Group *group_head = read_cfg(fp);
	Group *group_ptr = group_head;
	cfgitem *item_ptr;

	if (group_name != NULL)
	{
		if (!group_exist(group_head, group_name))
		{
			delete_cfg(group_head);
			return 0;
		}

		//������ά����,Ѱ��ָ��������
		while (group_ptr != NULL)
		{
			if (strcmp(group_ptr->group_name, group_name) == 0)
			{
				//�����Ҫ��ӵ����Ƿ��Ѿ�����
				if (item_exist(group_ptr->item_head, item_name))
				{
					delete_cfg(group_head);
					return 0;
				}

				//����������β��
				item_ptr = group_ptr->item_head;
				while (item_ptr->next != NULL)
				{
					item_ptr = item_ptr->next;
				}

				item_ptr->next = (cfgitem *)malloc(sizeof(cfgitem));
				init_cfg_item(item_ptr->next);

				if (item_ptr->next == NULL)
				{
					//�ڴ�����ʧ�ܣ��ж������ʧ��
					delete_cfg(group_head);
					return 0;
				}

				item_ptr = item_ptr->next;
				item_ptr->type = VALUE;
				item_ptr->next = NULL;
				strcpy(item_ptr->cfg_item_name, item_name);

				switch (item_type)
				{
				case TYPE_INT:
					sprintf(item_ptr->cfg_item_value, "%d", *(int *)item_value);
					break;
				case TYPE_DOUBLE:
					sprintf(item_ptr->cfg_item_value, "%f", *(double *)item_value);
					break;
				case TYPE_CHARACTER:
					sprintf(item_ptr->cfg_item_value, "%c", *(char *)item_value);
					break;
				case TYPE_STRING:
					sprintf(item_ptr->cfg_item_value, "%s", (char *)item_value);
					break;
				case TYPE_NULL:
					sprintf(item_ptr->cfg_item_value, "%c", '\0');
					break;
				}

				break;
			}

			group_ptr = group_ptr->next;
		}
	}
	else
	{
		//������ΪNULL���������һ��������һ��

		//���������һ��������
		while (group_ptr->next != NULL)
		{
			group_ptr = group_ptr->next;
		}

		item_ptr = group_ptr->item_head;

		while (item_ptr->next != NULL)
		{
			item_ptr = item_ptr->next;
		}

		item_ptr->next = (cfgitem *)malloc(sizeof(cfgitem));
		init_cfg_item(item_ptr->next);

		if (item_ptr->next == NULL)
		{
			//�ڴ�����ʧ�ܣ��ж������ʧ��
			delete_cfg(group_head);
			return 0;
		}

		item_ptr = item_ptr->next;
		item_ptr->type = VALUE;
		item_ptr->next = NULL;
		strcpy(item_ptr->cfg_item_name, item_name);

		switch (item_type)
		{
		case TYPE_INT:
			sprintf(item_ptr->cfg_item_value, "%d", *(int *)item_value);
			break;
		case TYPE_DOUBLE:
			sprintf(item_ptr->cfg_item_value, "%f", *(double *)item_value);
			break;
		case TYPE_CHARACTER:
			sprintf(item_ptr->cfg_item_value, "%c", *(char *)item_value);
			break;
		case TYPE_STRING:
			sprintf(item_ptr->cfg_item_value, "%s", (char *)item_value);
			break;
		case TYPE_NULL:
			sprintf(item_ptr->cfg_item_value, "%c", '\0');
			break;
		}
	}

	//д���ļ�
	int curr_pos = write_cfg(fp, group_head);

	delete_cfg(group_head);

	fseek(fp, 0, SEEK_SET);
	return 1;
}

//ɾ��������
int item_del(FILE *fp, const char *group_name, const char *item_name)
{
	int item_num = 0;
	//���Ȼ��ǵ��Ƚ�����ά����
	Group *group_head = read_cfg(fp);

	Group *group_ptr = group_head;
	cfgitem *item_ptr1;
	cfgitem *item_ptr2;

	if (group_name != NULL)
	{
		//�����鲻���ڣ��򷵻�0
		if (!group_exist(group_head, group_name))
		{
			delete_cfg(group_head);
			return 0;
		}

		while (group_ptr != NULL)
		{
			if (strcmp(group_ptr->group_name, group_name) == 0)
			{
				//����������򷵻�0
				if (!item_exist(group_ptr->item_head, item_name))
				{
					delete_cfg(group_head);
					return 0;
				}

				//����һ����ʱ��ͷ
				cfgitem *temp_head = (cfgitem *)malloc(sizeof(cfgitem));
				init_cfg_item(temp_head);

				temp_head->next = group_ptr->item_head;

				item_ptr1 = item_ptr2 = temp_head;

				while (item_ptr1->next != NULL)
				{
					item_ptr1 = item_ptr1->next;

					if (strcmp(item_ptr1->cfg_item_name, item_name) == 0)
					{
						item_ptr2->next = item_ptr1->next;
						free(item_ptr1);
						item_ptr1 = item_ptr2;

						item_num++;
					}
					else item_ptr2 = item_ptr1;
				}

				//��������ı�ͷָ����ʱ��ͷ����һ�����
				group_ptr->item_head = temp_head->next;
				free(temp_head);

				break;
			}

			group_ptr = group_ptr->next;
		}
	}
	else
	{
		//��Ӧ�������ļ����൱��������������ı�ͷ����ɾ��ָ����

		//����������򷵻�0
		if (!item_exist(group_head->item_head, item_name))
		{
			delete_cfg(group_head);
			return 0;
		}

		//����һ����ʱ��ͷ
		cfgitem *temp_head = (cfgitem *)malloc(sizeof(cfgitem));
		init_cfg_item(temp_head);

		temp_head->next = group_head->item_head;

		item_ptr1 = item_ptr2 = temp_head;

		while (item_ptr1->next != NULL)
		{
			item_ptr1 = item_ptr1->next;

			if (strcmp(item_ptr1->cfg_item_name, item_name) == 0)
			{
				item_ptr2->next = item_ptr1->next;
				free(item_ptr1);
				item_ptr1 = item_ptr2;

				item_num++;
			}
			else item_ptr2 = item_ptr1;
		}

		//��������ı�ͷָ����ʱ��ͷ����һ�����
		group_head->item_head = temp_head->next;
		free(temp_head);
	}

	//д���ļ�
	int curr_pos = write_cfg(fp, group_head);
	//ѹ���ļ���С
	file_resize(fp, curr_pos);

	delete_cfg(group_head);

	fseek(fp, 0, SEEK_SET);
	return item_num;
}

//����������
int item_update(FILE *fp, const char *group_name, const char *item_name, const void *item_value, const enum ITEM_TYPE item_type)
{
	Group *group_head = read_cfg(fp);
	Group *group_ptr = group_head;
	cfgitem *item_ptr1;
	cfgitem *item_ptr2;

	//ָ�������鲻�����򷵻�0
	if (!group_exist(group_head, group_name))
	{
		delete_cfg(group_head);
		return 0;
	}

	while (group_ptr != NULL)
	{
		if (strcmp(group_ptr->group_name, group_name) == 0)
		{
			//��ָ������ڣ����ڸ����������
			if (!item_exist(group_ptr->item_head, item_name))
			{
				item_ptr1 = group_ptr->item_head;

				while (item_ptr1->next != NULL)
				{
					item_ptr1 = item_ptr1->next;
				}

				item_ptr1->next = (cfgitem *)malloc(sizeof(cfgitem));
				init_cfg_item(item_ptr1->next);

				if (item_ptr1->next == NULL)
				{
					//�ڴ�����ʧ�ܣ��ж������ʧ��
					delete_cfg(group_head);
					return 0;
				}

				item_ptr1 = item_ptr1->next;
				item_ptr1->type = VALUE;
				item_ptr1->next = NULL;
				strcpy(item_ptr1->cfg_item_name, item_name);

				switch (item_type)
				{
				case TYPE_INT:
					sprintf(item_ptr1->cfg_item_value, "%d", *(int *)item_value);
					break;
				case TYPE_DOUBLE:
					sprintf(item_ptr1->cfg_item_value, "%f", *(double *)item_value);
					break;
				case TYPE_CHARACTER:
					sprintf(item_ptr1->cfg_item_value, "%c", *(char *)item_value);
					break;
				case TYPE_STRING:
					sprintf(item_ptr1->cfg_item_value, "%s", (char *)item_value);
					break;
				case TYPE_NULL:
					sprintf(item_ptr1->cfg_item_value, "%c", '\0');
					break;
				}

			}
			//��ָ������ڣ�����λ�ÿ�ǰ�Ľ����޸ģ�Ȼ�����ɾ�������ظ���
			else
			{
				item_ptr1 = item_ptr2 = group_ptr->item_head;

				while (item_ptr1 != NULL)
				{
					//�ҵ�λ�ÿ�ǰ��������޸�
					if (strcmp(item_ptr1->cfg_item_name, item_name) == 0)
					{
						switch (item_type)
						{
						case TYPE_INT:
							sprintf(item_ptr1->cfg_item_value, "%d", *(int *)item_value);
							break;
						case TYPE_DOUBLE:
							sprintf(item_ptr1->cfg_item_value, "%f", *(double *)item_value);
							break;
						case TYPE_CHARACTER:
							sprintf(item_ptr1->cfg_item_value, "%c", *(char *)item_value);
							break;
						case TYPE_STRING:
							sprintf(item_ptr1->cfg_item_value, "%s", (char *)item_value);
							break;
						case TYPE_NULL:
							sprintf(item_ptr1->cfg_item_value, "%c", '\0');
							break;
						}

						break;
					}

					item_ptr1 = item_ptr1->next;
				}

				//���ɾ�������ظ���
				item_ptr2 = item_ptr1;

				while (item_ptr1->next != NULL)
				{
					item_ptr1 = item_ptr1->next;

					if (strcmp(item_ptr1->cfg_item_name, item_name) == 0)
					{
						item_ptr2->next = item_ptr1->next;
						free(item_ptr1);
						item_ptr1 = item_ptr2;
					}
					else item_ptr2 = item_ptr1;
				}
			}

			break;
		}

		group_ptr = group_ptr->next;
	}

	//д���ļ�
	int curr_pos = write_cfg(fp, group_head);
	//ѹ���ļ���С
	file_resize(fp, curr_pos);

	delete_cfg(group_head);

	fseek(fp, 0, SEEK_SET);
	return 1;
}

//��ȡ���ֵ
int item_get_value(FILE *fp, const char *group_name, const char *item_name, void *item_value, const enum ITEM_TYPE item_type)
{
	Group *group_head = read_cfg_no_anno(fp);
	Group *group_ptr = group_head;
	cfgitem *item_ptr;

	//ָ�������鲻���ڣ�����0
	if (!group_exist(group_head, group_name))
	{
		delete_cfg(group_head);
		return 0;
	}

	while (group_ptr != NULL)
	{
		if (strcmp(group_ptr->group_name, group_name) == 0)
		{
			//ָ���������е�ָ������ڣ�����0
			if (!item_exist(group_ptr->item_head, item_name))
			{
				delete_cfg(group_head);
				return 0;
			}

			item_ptr = group_ptr->item_head;
			while (item_ptr != NULL)
			{
				if (strcmp(item_ptr->cfg_item_name, item_name) == 0)
				{
					switch (item_type)
					{
					case TYPE_INT:
						sscanf(item_ptr->cfg_item_value, "%d", (int *)item_value);
						break;
					case TYPE_DOUBLE:
						sscanf(item_ptr->cfg_item_value, "%lf", (double *)item_value);
						break;
					case TYPE_CHARACTER:
						sscanf(item_ptr->cfg_item_value, "%c", (char *)item_value);
						break;
					case TYPE_STRING:
						sscanf(item_ptr->cfg_item_value, "%s", (char *)item_value);
						break;
					case TYPE_NULL:return 0;
					}

					break;
				}

				item_ptr = item_ptr->next;
			}
			break;
		}
		group_ptr = group_ptr->next;
	}

	fseek(fp, 0, SEEK_SET);

	return 1;
}

//�ú������ڶ�ȡ�����ļ������ɶ�ά��������ע�ͣ�ȡ����ֵʹ�ã�
Group *read_cfg_no_anno(FILE *cfgfile)
{
	//������ͷ
	Group *group_head = (Group *)malloc(sizeof(Group));
	init_Group(group_head);

	group_head->item_head = (cfgitem *)malloc(sizeof(cfgitem));
	init_cfg_item(group_head->item_head);

	Group *group_ptr1 = group_head;
	cfgitem *item_ptr1 = group_head->item_head;
	cfgitem *item_ptr2 = item_ptr1;

	//��ȡһ��
	char line[MAX_LINE_CHAR_NUM]; //��ʱ�洢���е�����

	while (fgets(line, MAX_LINE_CHAR_NUM, cfgfile))
	{
		//���Ǳ��дӿ�ͷ����ע�͵����
		if (line[0] == '#')
		{
			//item_ptr1->type = ANNOTATION;

			//sscanf(line, "%s", item_ptr1->annotation);
		}
		else if (line[0] == '[')
		{
			/*��������һ������������Ҫ������ǰ���������Ľ�����
			���Ҵ���һ���µ����㣬���¿�ʼ������Ľ���*/

			//������ǰ���������Ľ���
			if (item_ptr1 != item_ptr2)
			{
				free(item_ptr1);
				item_ptr2->next = NULL;
			}
			else item_ptr1->next = NULL;

			group_ptr1->next = (Group *)malloc(sizeof(Group));
			init_Group(group_ptr1->next);

			group_ptr1 = group_ptr1->next;
			group_ptr1->item_head = (cfgitem *)malloc(sizeof(cfgitem));
			init_cfg_item(group_ptr1->item_head);

			item_ptr1 = group_ptr1->item_head;
			item_ptr2 = item_ptr1;

			//��ֵ����
			line[strlen(line) - 2] = '\0';
			strcpy(group_ptr1->group_name, line + 1);

			continue;
		}
		else if (line[0] != '\0')
		{
			item_ptr1->type = VALUE;
			//����Ϊ��Ч���ע�ͣ������

			//�������е�һ���ȺŸ�Ϊ�ո񣬷�������Ķ�ȡ
			for (int i = 0; i < (int)(strlen(line)); i++)
			{
				if (line[i] == '=')
				{
					line[i] = ' ';
					break;
				}
			}

			sscanf(line, "%s%s",
				item_ptr1->cfg_item_name,
				item_ptr1->cfg_item_value);
		}

		/*ÿ��ptr1�ƶ�����һ�����֮ǰ��ptr2�ƶ�����ǰ���
		�Ա��ڴ���һ���µ�����ʱ������ǰ������ָ��NULL*/
		item_ptr2 = item_ptr1;

		if (feof(cfgfile))
		{
			//����ļ���ȡ����򽫽��ָ��NULL
			item_ptr1->next = NULL;
			group_ptr1->next = NULL;
		}
		else
		{
			item_ptr1->next = (cfgitem*)malloc(sizeof(cfgitem));
			init_cfg_item(item_ptr1->next);

			item_ptr1 = item_ptr1->next;
		}
	}

	fseek(cfgfile, 0, SEEK_SET);

	return group_head;
}