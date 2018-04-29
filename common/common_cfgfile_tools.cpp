/*1751367 计2 彭健聪*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <experimental/filesystem>
#include "..\common\common_cfgfile_tools.hpp"
using namespace std;

static int file_length(fstream &fp)
{
	int file_len, now_pos;

	/* 当前为错误状态则返回-1 */
	if (fp.fail())
		return -1;

	/* 取fp当前指针位置 */
	now_pos = int(fp.tellg());

	/* 将文件指针移动到最后，此时tellp的结果就是文件大小 */
	fp.seekg(0, ios::end);
	file_len = int(fp.tellp());

	/* 指针移动回函数调用前的原位置 */
	fp.seekg(now_pos, ios::beg);

	return file_len;
}

static int file_resize(const char *filename, fstream &fp, int newsize)
{
	int now_pos;

	/* 当前为错误状态则返回-1 */
	if (fp.fail())
		return -1;

	/* 取fp当前指针位置 */
	now_pos = int(fp.tellg());

	/* 如果大小是负数则直接返回-1 */
	if (newsize < 0)
		return -1;

	experimental::filesystem::resize_file(filename, newsize);

	/* 如果当前文件指针超过了文件大小，则回到文件头 */
	if (now_pos > newsize)
		fp.seekg(0, ios::beg);

	return 0;
}

//打开配置文件
int open_cfgfile(fstream &fp, const char *cfgname, int opt)
{	
	if (opt == OPEN_OPT_RDONLY)
	{
		fp.open(cfgname, ios::in);

		if (fp.is_open())
		{
			return 1;
		}
		else return 0;
	}
	else if (opt == OPEN_OPT_RDWR)
	{
		fp.open(cfgname, ios::in | ios::out);
		if (fp.is_open())
		{
			return 1;
		}

		fp.open(cfgname, ios::out | ios::in | ios::trunc); //建立文件
		return 1;
	}

	return 0;
}

//关闭配置文件
void close_cfgfile(fstream &fp)
{
	fp.close();
}

//该函数用于读取配置文件并生成二维链表(忽略注释，在游戏当中读取配置文件使用）
Group *read_cfg_no_anno(fstream &cfgfile)
{
	//创建表头
	Group *group_head = new Group;
	group_head->item_head = new cfg_item;

	Group *group_ptr1 = group_head;
	cfg_item *item_ptr1 = group_head->item_head;
	cfg_item *item_ptr2 = item_ptr1;

	while (!cfgfile.eof())
	{
		//字符串流
		istringstream istr;

		//读取一行
		char line[MAX_LINE_CHAR_NUM+1]; //临时存储本行的内容
		char annotation[MAX_LINE_CHAR_NUM+1]; //临时存储本行的注释内容

		cfgfile.getline(line, MAX_LINE_CHAR_NUM, '\n');

		//考虑本行从开头就是注释的情况
		if (line[0] == '#')
		{
			//item_ptr1->type = ANNOTATION;
			//将本行的全部内容作为注释
			//strcpy(annotation, line);

			//strcpy(item_ptr1->annotation, annotation);
		}
		else if (line[0] == '[')
		{
			/*若发现了一个组名，则需要结束当前组的项链表的建立，
			并且创建一个新的组结点，重新开始项链表的建立*/

			//结束当前组的项链表的建立
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

			//赋值组名
			line[strlen(line) - 1] = '\0';
			strcpy(group_ptr1->group_name, line + 1);

			continue;
		}
		else if (line[0] != '\0')
		{
			item_ptr1->type = VALUE;
			//本行为有效项（非注释）的情况

			//将本行中第一个等号改为空格，方便后续的读取
			for (int i = 0; i < int(strlen(line)); i++)
			{
				if (line[i] == '=')
				{
					line[i] = ' ';
					break;
				}
			}

			//将本行加入到字符串流当中s
			istr.str(line);
			//读取项目名
			istr >> item_ptr1->cfg_item_name;
			//读取项目值
			istr >> item_ptr1->cfg_item_value;

			//本行的剩余部分则作为注释
			//istr.getline(annotation, MAX_LINE_CHAR_NUM, '\n');
			//istr.getline(annotation, MAX_LINE_CHAR_NUM);
			//strcpy(item_ptr1->annotation, annotation);
		}

		/*每次ptr1移动到下一个结点之前将ptr2移动到当前结点
		以便于创建一个新的组结点时，将当前的项结点指向NULL*/
		item_ptr2 = item_ptr1;

		if (cfgfile.eof())
		{
			//如果文件读取完毕则将结点指向NULL
			item_ptr1->next = NULL;
			group_ptr1->next = NULL;
		}
		else
		{
			item_ptr1->next = new cfg_item;

			if (item_ptr1->next == NULL)
			{
				cout << "这个地方不大行" << endl;
				return 0;
			}

			item_ptr1 = item_ptr1->next;
		}
	}

	cfgfile.clear();
	cfgfile.seekg(0, ios::beg);

	return group_head;
}

//该函数用于将二维链表当中的配置信息打印在屏幕上(检查修改结果用）
void print_cfg(Group *group_head)
{
	Group *group_ptr1 = group_head;
	cfg_item *item_ptr1 = group_head->item_head;

	while (group_ptr1 != NULL)
	{
		item_ptr1 = group_ptr1->item_head;

		//打印组名
		if (group_ptr1->group_name[0] != '\0')
		{
			cout << '[' << group_ptr1->group_name << ']' << endl;
		}

		while (item_ptr1 != NULL)
		{
			if (item_ptr1->type == ANNOTATION)
			{
				//若本项名为NULL，则该项其实为注释,直接打印即可
				cout << item_ptr1->annotation << endl;
			}
			else if (item_ptr1->type == VALUE)
			{
				cout << item_ptr1->cfg_item_name << " = " << item_ptr1->cfg_item_value << endl;;
				//cout << item_ptr1->annotation << endl;
			}

			item_ptr1 = item_ptr1->next;
		}

		group_ptr1 = group_ptr1->next;
	}
}

//该函数将二维链表中的配置信息写入文本文件(返回文件指针的位置）
int write_cfg(fstream &cfgfile,Group *group_head)
{
	cfgfile.clear();
	cfgfile.seekg(0, ios::beg);
	
	Group *group_ptr1 = group_head;
	cfg_item *item_ptr1 = group_head->item_head;

	while (group_ptr1 != NULL)
	{
		item_ptr1 = group_ptr1->item_head;

		//打印组名
		if (group_ptr1->group_name[0] != '\0')
		{
			cfgfile << '[' << group_ptr1->group_name << ']' << endl;
		}

		while (item_ptr1 != NULL)
		{
			if (item_ptr1->type == ANNOTATION)
			{
				//该项为注释,直接打印即可
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

	return int(cfgfile.tellp());
}

//该函数用于释放二维链表
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

//检查指定配置组是否存在
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

//检查配置组中指定项是否存在
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

//添加配置组
int group_add(fstream &fp, const char *group_name)
{
	Group *group_head = read_cfg(fp);

	//若该组已存在，则返回0
	if (group_exist(group_head, group_name))
	{
		return 0;
	}

	//遍历配置组链表至末端，并建立新的结点
	Group *group_ptr = group_head;

	while (group_ptr->next != NULL)
	{
		group_ptr = group_ptr->next;
	}

	group_ptr->next = new Group;
	if (group_ptr->next == NULL)
	{
		//内存申请失败，即添加配置组失败

		//释放链表
		delete_cfg(group_head);
		return 0;
	}

	//赋值组名
	strcpy(group_ptr->next->group_name, group_name);

	/*开一个空项,个人感觉这个步骤有必要
	不然在后续的项处理当中可能会遇到麻烦*/
	group_ptr->next->item_head = new cfg_item;

	if (group_ptr->next->item_head = NULL)
	{
		//内存申请失败,则判定添加配置组失败，需要将申请的组结点释放
		delete group_ptr->next;
		group_ptr->next = NULL;

		//释放链表
		delete_cfg(group_head);
		return 0;
	}

	//写入文件
	int curr_pos = write_cfg(fp, group_head);

	//释放链表
	delete_cfg(group_head);

	fp.clear();
	fp.seekg(0, ios::beg);

	return 1;
}

//删除配置组
int group_del(fstream &fp, const char *filename, const char *group_name)
{
	//将一个配置组结点及其以下的项链表释放，并将前一结点连接到后一结点
	
	int group_num=0;
	//首先还是得先建立二维链表
	Group *group_head = read_cfg(fp);

	//若该组不存在，则返回0
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

			//将该组下的项链表释放
			while (item_ptr1 != NULL)
			{
				item_ptr1 = item_ptr1->next;
				delete item_ptr2;

				item_ptr2 = item_ptr1;
			}

			//前一结点和后一结点连接
			group_ptr2->next = group_ptr1->next;
			//释放当前结点
			delete group_ptr1;
			group_ptr1 = group_ptr2;

			group_num++;
		}
		else
		{
			group_ptr2 = group_ptr1;
		}
	}

	//写入文件
	int curr_pos = write_cfg(fp, group_head);
	//压缩文件大小
	file_resize(filename, fp, curr_pos);

	delete_cfg(group_head);

	fp.clear();
	fp.seekg(0, ios::beg);

	return group_num;
}

//添加配置项
int item_add(fstream &fp, const char *group_name, const char *item_name, const void *item_value, const enum ITEM_TYPE item_type)
{
	Group *group_head = read_cfg(fp);
	Group *group_ptr = group_head;
	cfg_item *item_ptr;

	if (group_name != NULL)
	{
		if (!group_exist(group_head, group_name))
		{
			delete_cfg(group_head);
			return 0;
		}

		//遍历二维链表,寻找指定配置组
		while (group_ptr != NULL)
		{
			if (strcmp(group_ptr->group_name, group_name)==0)
			{
				//检查需要添加的项是否已经存在
				if (item_exist(group_ptr->item_head, item_name))
				{
					delete_cfg(group_head);
					return 0;
				}

				//遍历项链表到尾部
				item_ptr = group_ptr->item_head;
				while (item_ptr->next != NULL)
				{
					item_ptr = item_ptr->next;
				}

				item_ptr->next = new cfg_item;
				if (item_ptr->next == NULL)
				{
					//内存申请失败，判定添加项失败
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
		//若组名为NULL，则在最后一组添加最后一项

		//遍历到最后一个配置组
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
			//内存申请失败，判定添加项失败
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

	//写入文件
	int curr_pos = write_cfg(fp, group_head);
	
	delete_cfg(group_head);

	fp.clear();
	fp.seekg(0, ios::beg);

	return 1;
}

//删除配置项
int item_del(fstream &fp, const char *filename, const char *group_name, const char *item_name)
{
	int item_num = 0;
	//首先还是得先建立二维链表
	Group *group_head = read_cfg(fp);

	Group *group_ptr = group_head;
	cfg_item *item_ptr1;
	cfg_item *item_ptr2;

	if (group_name != NULL)
	{
		//若该组不存在，则返回0
		if (!group_exist(group_head, group_name))
		{
			delete_cfg(group_head);
			return 0;
		}

		while (group_ptr != NULL)
		{
			if (strcmp(group_ptr->group_name, group_name) == 0)
			{
				//若该项不存在则返回0
				if (!item_exist(group_ptr->item_head, item_name))
				{
					delete_cfg(group_head);
					return 0;
				}
				
				//创建一个临时表头
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

				//最后真正的表头指向临时表头的下一个结点
				group_ptr->item_head = temp_head->next;
				delete temp_head;

				break;
			}

			group_ptr = group_ptr->next;
		}
	}
	else
	{
		//对应简单配置文件，相当于在配置组链表的表头当中删除指定项

		//若该项不存在则返回0
		if (!item_exist(group_head->item_head, item_name))
		{
			delete_cfg(group_head);
			return 0;
		}
		
		//创建一个临时表头
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

		//最后真正的表头指向临时表头的下一个结点
		group_head->item_head = temp_head->next;
		delete temp_head;
	}

	//写入文件
	int curr_pos = write_cfg(fp, group_head);
	//压缩文件大小
	file_resize(filename, fp, curr_pos);
	
	delete_cfg(group_head);

	fp.clear();
	fp.seekg(0, ios::beg);

	return item_num;
}

//更新配置项
int item_update(fstream &fp, const char *filename, const char *group_name, const char *item_name, const void *item_value, const enum ITEM_TYPE item_type)
{
	Group *group_head = read_cfg(fp);
	Group *group_ptr = group_head;
	cfg_item *item_ptr1;
	cfg_item *item_ptr2;

	//指定配置组不存在则返回0
	if (!group_exist(group_head, group_name))
	{
		delete_cfg(group_head);
		return 0;
	}

	while (group_ptr != NULL)
	{
		if (strcmp(group_ptr->group_name, group_name) == 0)
		{
			//若指定项不存在，则在改组的最后加入
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
					//内存申请失败，判定添加项失败
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
			//若指定项存在，先找位置靠前的进行修改，然后逐个删除后续重复项
			else
			{
				item_ptr1 = item_ptr2 = group_ptr->item_head;

				while (item_ptr1 != NULL)
				{
					//找到位置考前的项进行修改
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

				//逐个删除后续重复项
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

	//写入文件
	int curr_pos = write_cfg(fp, group_head);
	//压缩文件大小
	file_resize(filename, fp, curr_pos);
	
	delete_cfg(group_head);

	fp.clear();
	fp.seekg(0, ios::beg);

	return 1;
}

//获取项的值(忽略注释）
int item_get_value(fstream &fp, const char *group_name, const char *item_name, void *item_value, const enum ITEM_TYPE item_type)
{
	Group *group_head = read_cfg_no_anno(fp);
	Group *group_ptr = group_head;
	cfg_item *item_ptr;

	//指定配置组不存在，返回0
	if (!group_exist(group_head, group_name))
	{
		delete_cfg(group_head);
		return 0;
	}

	while (group_ptr != NULL)
	{
		if (strcmp(group_ptr->group_name, group_name)==0)
		{
			//指定配置组中的指定项不存在，返回0
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

	fp.clear();
	fp.seekg(0, ios::beg);

	return 1;
}

//该函数用于读取配置文件并生成二维链表(不忽略注释，互测使用）
Group *read_cfg(fstream &cfgfile)
{
	//创建表头
	Group *group_head = new Group;
	group_head->item_head = new cfg_item;

	Group *group_ptr1 = group_head;
	cfg_item *item_ptr1 = group_head->item_head;
	cfg_item *item_ptr2 = item_ptr1;

	while (!cfgfile.eof())
	{
		//字符串流
		istringstream istr;

		//读取一行
		char line[MAX_LINE_CHAR_NUM + 1]; //临时存储本行的内容
		char annotation[MAX_LINE_CHAR_NUM + 1]; //临时存储本行的注释内容

		cfgfile.getline(line, MAX_LINE_CHAR_NUM, '\n');

		//考虑本行从开头就是注释的情况
		if (line[0] == '#')
		{
			item_ptr1->type = ANNOTATION;
			//将本行的全部内容作为注释
			strcpy(annotation, line);

			strcpy(item_ptr1->annotation, annotation);
		}
		else if (line[0] == '[')
		{
			/*若发现了一个组名，则需要结束当前组的项链表的建立，
			并且创建一个新的组结点，重新开始项链表的建立*/

			//结束当前组的项链表的建立
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

			//赋值组名
			line[strlen(line) - 1] = '\0';
			strcpy(group_ptr1->group_name, line + 1);

			continue;
		}
		else if (line[0] != '\0')
		{
			item_ptr1->type = VALUE;
			//本行为有效项（非注释）的情况

			//将本行中第一个等号改为空格，方便后续的读取
			for (int i = 0; i < int(strlen(line)); i++)
			{
				if (line[i] == '=')
				{
					line[i] = ' ';
					break;
				}
			}

			//将本行加入到字符串流当中s
			istr.str(line);
			//读取项目名
			istr >> item_ptr1->cfg_item_name;
			//读取项目值
			istr >> item_ptr1->cfg_item_value;

			//本行的剩余部分则作为注释
			istr.getline(annotation, MAX_LINE_CHAR_NUM, '\n');
			istr.getline(annotation, MAX_LINE_CHAR_NUM);
			strcpy(item_ptr1->annotation, annotation);
		}

		/*每次ptr1移动到下一个结点之前将ptr2移动到当前结点
		以便于创建一个新的组结点时，将当前的项结点指向NULL*/
		item_ptr2 = item_ptr1;

		if (cfgfile.eof())
		{
			//如果文件读取完毕则将结点指向NULL
			item_ptr1->next = NULL;
			group_ptr1->next = NULL;
		}
		else
		{
			item_ptr1->next = new cfg_item;

			if (item_ptr1->next == NULL)
			{
				cout << "这个地方不大行" << endl;
				return 0;
			}

			item_ptr1 = item_ptr1->next;
		}
	}

	cfgfile.clear();
	cfgfile.seekg(0, ios::beg);

	return group_head;
}