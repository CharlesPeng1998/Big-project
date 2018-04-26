/*1751367 ��2 ����*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include "..\common\common_cfgfile_tools.hpp"
using namespace std;

//�������ļ�
int open_cfgfile(fstream &fp, const char *cfgname, int opt)
{	
	switch (opt)
	{
	case OPEN_OPT_RDONLY:
		fp.open(cfgname, ios::in);
		break;	

	case OPEN_OPT_RDWR:
		fp.open(cfgname, ios::in | ios::out);
		break;
	}

	if (fp.is_open())
	{
		return 1;
	}
	else return 0;
}

//�ر������ļ�
void close_cfgfile(fstream &fp)
{
	fp.close();
}

//�ú������ڶ�ȡ�����ļ������ɶ�ά����
Group *read_cfg(fstream &cfgfile)
{
	//������ͷ
	Group *group_head = new Group;
	group_head->item_head = new cfg_item;

	Group *group_ptr1 = group_head;
	cfg_item *item_ptr1 = group_head->item_head;
	cfg_item *item_ptr2 = item_ptr1;

	while (!cfgfile.eof())
	{
		//�ַ�����
		istringstream istr;

		//��ȡһ��
		char line[MAX_LINE_CHAR_NUM]; //��ʱ�洢���е�����
		char annotation[MAX_LINE_CHAR_NUM]; //��ʱ�洢���е�ע������

		cfgfile.getline(line, MAX_LINE_CHAR_NUM, '\n');

		//���Ǳ��дӿ�ͷ����ע�͵����
		if (line[0] == '#')
		{
			item_ptr1->type = ANNOTATION;
			//�����е�ȫ��������Ϊע��
			strcpy(annotation, line);

			strcpy(item_ptr1->annotation, annotation);
		}
		else if (line[0] == '[')
		{
			/*��������һ������������Ҫ������ǰ���������Ľ�����
			���Ҵ���һ���µ����㣬���¿�ʼ������Ľ���*/

			//������ǰ���������Ľ���
			if (item_ptr1 != item_ptr2)
			{
				delete item_ptr1;
				item_ptr2->next = NULL;
			}
			else item_ptr1->next = NULL;

			group_ptr1->next = new Group;
			group_ptr1 = group_ptr1->next;
			group_ptr1->item_head = new cfg_item;

			item_ptr1 = group_ptr1->item_head;
			item_ptr2 = item_ptr1;

			//��ֵ����
			line[strlen(line) - 1] = '\0';
			strcpy(group_ptr1->group_name, line + 1);

			continue;
		}
		else if (line[0] != '\0')
		{
			item_ptr1->type = VALUE;
			//����Ϊ��Ч���ע�ͣ������

			//�������е�һ���ȺŸ�Ϊ�ո񣬷�������Ķ�ȡ
			for (int i = 0; i < int(strlen(line)); i++)
			{
				if (line[i] == '=')
				{
					line[i] = ' ';
					break;
				}
			}

			//�����м��뵽�ַ���������
			istr.str(line);
			//��ȡ��Ŀ��
			istr >> item_ptr1->cfg_item_name;
			//��ȡ��Ŀֵ
			istr >> item_ptr1->cfg_item_value;

			//���е�ʣ�ಿ������Ϊע��
			istr.getline(annotation, MAX_LINE_CHAR_NUM, '\n');
			strcpy(item_ptr1->annotation, annotation);
		}

		/*ÿ��ptr1�ƶ�����һ�����֮ǰ��ptr2�ƶ�����ǰ���
		�Ա��ڴ���һ���µ�����ʱ������ǰ������ָ��NULL*/
		item_ptr2 = item_ptr1;

		if (cfgfile.eof())
		{
			//����ļ���ȡ����򽫽��ָ��NULL
			item_ptr1->next = NULL;
			group_ptr1->next = NULL;
		}
		else
		{
			item_ptr1->next = new cfg_item;
			item_ptr1 = item_ptr1->next;
		}
	}

	return group_head;
}

//�ú������ڽ���ά�����е�������Ϣ��ӡ����Ļ��(����޸Ľ���ã�
void print_cfg(Group *group_head)
{
	Group *group_ptr1 = group_head;
	cfg_item *item_ptr1 = group_head->item_head;

	while (group_ptr1 != NULL)
	{
		item_ptr1 = group_ptr1->item_head;

		//��ӡ����
		if (group_ptr1->group_name[0] != '\0')
		{
			cout << '[' << group_ptr1->group_name << ']' << endl;
		}

		while (item_ptr1 != NULL)
		{
			if (item_ptr1->type == ANNOTATION)
			{
				//��������ΪNULL���������ʵΪע��,ֱ�Ӵ�ӡ����
				cout << item_ptr1->annotation << endl;
			}
			else if (item_ptr1->type == VALUE)
			{
				cout << item_ptr1->cfg_item_name << " = " << item_ptr1->cfg_item_value;
				cout << item_ptr1->annotation << endl;
			}

			item_ptr1 = item_ptr1->next;
		}

		group_ptr1 = group_ptr1->next;
	}
}

//�ú�������ά�����е�������Ϣд���ı��ļ�
void write_cfg(fstream &cfgfile,Group *group_head)
{
	cfgfile.seekg(0, ios::beg);
	cfgfile.clear();

	Group *group_ptr1 = group_head;
	cfg_item *item_ptr1 = group_head->item_head;

	while (group_ptr1 != NULL)
	{
		item_ptr1 = group_ptr1->item_head;

		//��ӡ����
		if (group_ptr1->group_name[0] != '\0')
		{
			cfgfile << '[' << group_ptr1->group_name << ']' << endl;
		}

		while (item_ptr1 != NULL)
		{
			if (item_ptr1->type == ANNOTATION)
			{
				//����Ϊע��,ֱ�Ӵ�ӡ����
				cfgfile << item_ptr1->annotation << endl;
			}
			else if (item_ptr1->type == VALUE)
			{
				cfgfile << item_ptr1->cfg_item_name << " = " << item_ptr1->cfg_item_value;
				cfgfile << item_ptr1->annotation << endl;
			}

			item_ptr1 = item_ptr1->next;
		}

		group_ptr1 = group_ptr1->next;
	}
}

//�ú��������ͷŶ�ά����
void delete_cfg(Group *group_head)
{
	Group *group_ptr1 = group_head;
	Group *group_ptr2 = group_head;
	cfg_item *item_ptr1 = group_head->item_head;
	cfg_item *item_ptr2 = group_head->item_head;

	while (group_ptr1 != NULL)
	{
		group_ptr1 = group_ptr1->next;
		item_ptr1 = group_ptr2->item_head;
		item_ptr2 = group_ptr2->item_head;

		while (item_ptr1 != NULL)
		{
			item_ptr1 = item_ptr1->next;
			delete item_ptr2;

			item_ptr2 = item_ptr1;
		}

		delete group_ptr2;
		group_ptr2 = group_ptr1;
	}
}

//���ָ���������Ƿ����
bool group_exist(Group *group_head,const char *group_name)
{
	bool exist = 0;
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
bool item_exist(cfg_item *item_head, const char *item_name)
{
	bool exist = 0;
	cfg_item *item_ptr = item_head;

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

//���������(չʾ�ȴ�ӡ����Ļ�ϼ�����Ƿ�����)
int group_add(fstream &fp, const char *group_name)
{
	Group *group_head = read_cfg(fp);

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

	group_ptr->next = new Group;
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
	group_ptr->next->item_head = new cfg_item;

	if (group_ptr->next->item_head = NULL)
	{
		//�ڴ�����ʧ��,���ж����������ʧ�ܣ���Ҫ������������ͷ�
		delete group_ptr->next;
		group_ptr->next = NULL;

		//�ͷ�����
		delete_cfg(group_head);
		return 0;
	}

	//������д���ļ�
	print_cfg(group_head);
	//write_cfg(fp, group_head);

	//�ͷ�����
	delete_cfg(group_head);
	return 1;
}

//ɾ��������
int group_del(fstream &fp, const char *filename, const char *group_name)
{
	//��һ���������㼰�����µ��������ͷţ�����ǰһ������ӵ���һ���
	
	int group_num=0;
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

	cfg_item *item_ptr1;
	cfg_item *item_ptr2;

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
				delete item_ptr2;

				item_ptr2 = item_ptr1;
			}

			//ǰһ���ͺ�һ�������
			group_ptr2->next = group_ptr1->next;
			//�ͷŵ�ǰ���
			delete group_ptr1;
			group_ptr1 = group_ptr2;

			group_num++;
		}
		else
		{
			group_ptr2 = group_ptr1;
		}
	}

	//������
	print_cfg(group_head);

	delete_cfg(group_head);

	return group_num;
}

//���������
int item_add(fstream &fp, const char *group_name, const char *item_name, const void *item_value, const enum ITEM_TYPE item_type)
{
	Group *group_head = read_cfg(fp);
	Group *group_ptr = group_head;
	cfg_item *item_ptr;
#if 1
	if (!group_exist(group_head, group_name))
	{
		delete_cfg(group_head);
		return 0;
	}

	if (group_name != NULL)
	{
		//������ά����,Ѱ��ָ��������
		while (group_ptr != NULL)
		{
			if (strcmp(group_ptr->group_name, group_name)==0)
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

				item_ptr->next = new cfg_item;
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

				stringstream oss;
				switch (item_type)
				{
				case TYPE_INT:oss << *(int *)item_value; break;
				case TYPE_DOUBLE:oss << *(double *)item_value; break;
				case TYPE_CHARACTER:oss << *(char *)item_value; break;
				case TYPE_STRING:oss << (char *)item_value; break;
				case TYPE_NULL:oss << '\0'; break;
				}

				oss >> item_ptr->cfg_item_value;
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

		item_ptr->next = new cfg_item;
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

		stringstream oss;
		switch (item_type)
		{
		case TYPE_INT:oss << *(int *)item_value; break;
		case TYPE_DOUBLE:oss << *(double *)item_value; break;
		case TYPE_CHARACTER:oss << *(char *)item_value; break;
		case TYPE_STRING:oss << (char *)item_value; break;
		case TYPE_NULL:oss << '\0'; break;
		}

		oss >> item_ptr->cfg_item_value;
	}
#endif 
	print_cfg(group_head);
	
	delete_cfg(group_head);
	return 1;
}

//ɾ��������
int item_del(fstream &fp, const char *filename, const char *group_name, const char *item_name)
{
	int item_num = 0;
	//���Ȼ��ǵ��Ƚ�����ά����
	Group *group_head = read_cfg(fp);

	//�����鲻���ڣ��򷵻�0
	if (!group_exist(group_head, group_name))
	{
		delete_cfg(group_head);
		return 0;
	}

	Group *group_ptr = group_head;
	cfg_item *item_ptr1;
	cfg_item *item_ptr2;

	if (group_name != NULL)
	{
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
				cfg_item *temp_head = new cfg_item;
				temp_head->next = group_ptr->item_head;

				item_ptr1 = item_ptr2 = temp_head;

				while (item_ptr1->next != NULL)
				{
					item_ptr1 = item_ptr1->next;

					if (strcmp(item_ptr1->cfg_item_name, item_name) == 0)
					{
						item_ptr2->next = item_ptr1->next;
						delete item_ptr1;
						item_ptr1 = item_ptr2;

						item_num++;
					}
					else item_ptr2 = item_ptr1;
				}

				//��������ı�ͷָ����ʱ��ͷ����һ�����
				group_ptr->item_head = temp_head->next;
				delete temp_head;

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
		cfg_item *temp_head = new cfg_item;
		temp_head->next = group_head->item_head;

		item_ptr1 = item_ptr2 = temp_head;

		while (item_ptr1->next != NULL)
		{
			item_ptr1 = item_ptr1->next;

			if (strcmp(item_ptr1->cfg_item_name, item_name) == 0)
			{
				item_ptr2->next = item_ptr1->next;
				delete item_ptr1;
				item_ptr1 = item_ptr2;

				item_num++;
			}
			else item_ptr2 = item_ptr1;
		}

		//��������ı�ͷָ����ʱ��ͷ����һ�����
		group_head->item_head = temp_head->next;
		delete temp_head;
	}

	print_cfg(group_head);
	
	delete_cfg(group_head);
	return item_num;
}

//����������
int item_update(fstream &fp, const char *filename, const char *group_name, const char *item_name, const void *item_value, const enum ITEM_TYPE item_type)
{
	Group *group_head = read_cfg(fp);
	Group *group_ptr = group_head;
	cfg_item *item_ptr1;
	cfg_item *item_ptr2;

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

				item_ptr1->next = new cfg_item;

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

				stringstream oss;
				switch (item_type)
				{
				case TYPE_INT:oss << *(int *)item_value; break;
				case TYPE_DOUBLE:oss << *(double *)item_value; break;
				case TYPE_CHARACTER:oss << *(char *)item_value; break;
				case TYPE_STRING:oss << (char *)item_value; break;
				case TYPE_NULL:oss << '\0'; break;
				}

				oss >> item_ptr1->cfg_item_value;
			}
			//��ָ������ڣ�����λ�ÿ�ǰ�Ľ����޸ģ�Ȼ�����ɾ�������ظ���
			else
			{
				item_ptr1 = item_ptr2 = group_ptr->item_head;

				while (item_ptr1 != NULL)
				{
					//�ҵ�λ�ÿ�ǰ��������޸�
					if (strcmp(item_ptr1->cfg_item_name,item_name)==0)
					{
						stringstream oss;
						switch (item_type)
						{
						case TYPE_INT:oss << *(int *)item_value; break;
						case TYPE_DOUBLE:oss << *(double *)item_value; break;
						case TYPE_CHARACTER:oss << *(char *)item_value; break;
						case TYPE_STRING:oss << (char *)item_value; break;
						case TYPE_NULL:oss << '\0'; break;
						}

						oss >> item_ptr1->cfg_item_value;
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
						delete item_ptr1;
						item_ptr1 = item_ptr2;
					}
					else item_ptr2 = item_ptr1;
				}
			}

			break;
		}

		group_ptr = group_ptr->next;
	}

	print_cfg(group_head);
	
	delete_cfg(group_head);
	return 1;
}

//��ȡ���ֵ
int item_get_value(fstream &fp, const char *group_name, const char *item_name, void *item_value, const enum ITEM_TYPE item_type)
{
	Group *group_head = read_cfg(fp);
	Group *group_ptr = group_head;
	cfg_item *item_ptr;

	//ָ�������鲻���ڣ�����0
	if (!group_exist(group_head, group_name))
	{
		delete_cfg(group_head);
		return 0;
	}

	while (group_ptr != NULL)
	{
		if (strcmp(group_ptr->group_name, group_name)==0)
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
					istringstream istr;
					istr.str(item_ptr->cfg_item_value);

					switch (item_type)
					{
					case TYPE_INT:istr >> *(int *)item_value; break;
					case TYPE_DOUBLE:istr >> *(double *)item_value; break;
					case TYPE_CHARACTER:istr >> *(char *)item_value; break;
					case TYPE_STRING:istr >> (char *)item_value; break;
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

	return 1;
}