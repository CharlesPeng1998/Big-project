/*1751367 ��2 ����*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <ctime>
#include <cmath>
#include <cstdio>
#include <conio.h>
#include <Windows.h>
#include <fstream>
#include "cmd_console_tools.h"
#include "..\common\common_cfgfile_tools.hpp"
#include "common.h"
#include "../90-b0/90-b0.h"
using namespace std;

//�˵����������մ�Ų˵����ָ�����飬�����û����뷵��һ���ַ�
char menu(const char *items[], int n)
{
	//��¼���˵���ĳ���
	int max_len = int(strlen(items[0]));
	for (int i = 1; i < n; i++)
	{
		if (int(strlen(items[i])) > max_len) max_len = int(strlen(items[i]));
	}

	while (1)
	{
		//������˵���ĳ��ȴ�ӡ����
		for (int i = 0; i < max_len; i++)
		{
			cout << "-";
		}
		cout << endl;

		//��ӡ�˵���
		for (int i = 0; i < n; i++)
		{
			cout << items[i] << endl;
		}

		//������˵���ĳ��ȴ�ӡ����
		for (int i = 0; i < max_len; i++)
		{
			cout << "-";
		}
		cout << endl;
		
		//�����û�����ѡ����
		cout << "[��ѡ��:]";
		char choice = _getch();

		if (choice >= 97) choice -= 32;//������Сд��ĸ��������Ҫת��Ϊ��д��ĸ

		//�����û����뷵�ز�ͬ�ַ�
		for (int i = 0; i < n; i++)
		{
			if (choice == items[i][0]) return items[i][0];
			else;
		}
		cls();
		continue;
	}
}

//����ָ������λ�ü���Χ��ͬ��ĺ������ǵݹ飩
void mark(int(*rand_matrix)[10], char(*mark_matrix)[10], int cord_row, int cord_col, int Max_row, int Max_col)
{
	mark_matrix[cord_row][cord_col] = '*';
	bool stat = 1;//���ڴ洢Ѱ����������һ���״̬
	int target = rand_matrix[cord_row][cord_col];

	while (stat)
	{
		stat = 0;
		for (int i = 0; i < Max_row; i++)
		{
			for (int j = 0; j < Max_col; j++)
			{
				if (rand_matrix[i][j] == target && mark_matrix[i][j] == '*')
				{
					if (i > 0 && rand_matrix[i - 1][j] == target && mark_matrix[i - 1][j] != '*')
					{
						mark_matrix[i - 1][j] = '*';
						stat = 1;
					}

					if (i < Max_row - 1 && rand_matrix[i + 1][j] == target && mark_matrix[i + 1][j] != '*')
					{
						mark_matrix[i + 1][j] = '*';
						stat = 1;
					}

					if (j > 0 && rand_matrix[i][j - 1] == target && mark_matrix[i][j - 1] != '*')
					{
						mark_matrix[i][j - 1] = '*';
						stat = 1;
					}

					if (j<Max_col - 1 && rand_matrix[i][j + 1] == target && mark_matrix[i][j + 1] != '*')
					{
						mark_matrix[i][j + 1] = '*';
						stat = 1;
					}
				}
			}
		}

		if (stat == 0) break;
	}
}

//�ڲ������ƶ�����(���ݴ�������Ĳ�ͬ���в�ͬ���ƶ�����)
void matrix_move(int(*rand_matrix)[10], char(*mark_matrix)[10], int row, int col,int move_type)
{
	switch (move_type)
	{
	case DOWN: //����ð��ԭ��ʹ0�ϸ���ÿ�еĶ���
	{
		int temp;
		char ctemp;

		for (int i = 0; i < col; i++)
		{
			for (int j = row - 1; j>0; j--)
			{
				for (int k = row - 1; k > 0; k--)
				{
					if (rand_matrix[k][i] == 0)
					{
						temp = rand_matrix[k][i];
						rand_matrix[k][i] = rand_matrix[k - 1][i];
						rand_matrix[k - 1][i] = temp;

						ctemp = mark_matrix[k][i];
						mark_matrix[k][i] = mark_matrix[k - 1][i];
						mark_matrix[k - 1][i] = ctemp;
					}
				}
			}
		}
		break;
	}
	case LEFT:
	{
		int num_invalid = 0;//���ڼ�¼�����Ҳ����Ч�е�����
		int temp;

		for (int i = col - 1; i >= 0; i--)
		{
			if (rand_matrix[row - 1][i] == 0) num_invalid++;
			else break;
		}

		for (int i = 0; i < col-num_invalid; i++)
		{
			while (rand_matrix[row - 1][i] == 0)
			{
				for (int j = 0; j < row; j++)
				{
					for (int k = i; k < col - 1-num_invalid; k++)
					{
						temp = rand_matrix[j][k + 1];
						rand_matrix[j][k + 1] = rand_matrix[j][k];
						rand_matrix[j][k] = temp;
					}
				}
				col--;
			}
			
		}
		break;
	}
	}
}

//�ú��������жϱ����Ƿ����
bool end_judge(int(*rand_matrix)[10], int row, int col)
{
	bool end = true;

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (i > 0 && rand_matrix[i][j]!=0 && rand_matrix[i - 1][j] == rand_matrix[i][j])
			{
				end = false;
			}
			else if (i < row - 1 && rand_matrix[i][j] != 0 && rand_matrix[i + 1][j] == rand_matrix[i][j])
			{
				end = false;
			}
			else if (j > 0 && rand_matrix[i][j] != 0 && rand_matrix[i][j - 1] == rand_matrix[i][j])
			{
				end = false;
			}
			else if (j < col - 1 && rand_matrix[i][j] != 0 && rand_matrix[i][j + 1] == rand_matrix[i][j])
			{
				end = false;
			}


		}
	}
	return end;
}

/*�ú���������ʾ��ʼ����
  gameΪ��Ϸ������
  typeΪ���ܵ����ͣ��зָ���/�޷ָ��ߣ�
  ���ݴ���Ĳ�����ͬ��ʾ��ͬ������*/
void print_frame(int row, int col,int game,int type)
{
	switch (game)
	{
	case POPSTAR:
	{
		switch (type)
		{
		case UNDIVIDED:
		{
			//���������д��ڵĴ�С
			setconsoleborder(55 + (col - 8) * 6, 32 + (row - 8) * 3);
			gotoxy(0, 1);

			cout << "      ";
			//��ӡ�к�
			for (int i = 0; i < col; i++)
			{
				cout << i << "     ";
			}

			cout << endl << endl << endl;
			//��ӡӢ���к�
			for (int i = 0; i < row; i++)
			{
				cout << char(i + 65) << endl << endl << endl;
			}

			gotoxy(2, 2);
			//���������ӡ�ϱ߿�
			print_unicode("�X", COLOR_HWHITE, COLOR_BLACK, 1);
			print_unicode("�T", COLOR_HWHITE, COLOR_BLACK, col * 3);
			print_unicode("�[", COLOR_HWHITE, COLOR_BLACK, 1);

			//��ӡ���ұ߿�
			for (int i = 3; i < row * 3 + 3; i++)
			{
				gotoxy(2, i);
				print_unicode("�U", COLOR_HWHITE, COLOR_BLACK, 1);
				for (int j = 0; j < col * 2; j++)
				{
					print_unicode("   ", COLOR_HWHITE, COLOR_BLACK, 1);
				}

				print_unicode("�U", COLOR_HWHITE, COLOR_BLACK, 1);
			}

			//��ӡ�±߿�
			gotoxy(2, row * 3 + 3);
			print_unicode("�^", COLOR_HWHITE, COLOR_BLACK, 1);
			print_unicode("�T", COLOR_HWHITE, COLOR_BLACK, col * 3);
			print_unicode("�a", COLOR_HWHITE, COLOR_BLACK, 1);

			break;
		}

		case DIVIDED:
		{
			int curr_x, curr_y;//�����������꣬Ѱ�Ҵ�ӡλ��ʱ��Ҫ�õ�
			
			//���������д��ڵĴ�С
			setconsoleborder(69 + (col - 8) * 8, 39 + (row - 8) * 4);
			gotoxy(0, 1);

			cout << "      ";
			//��ӡ�к�
			for (int i = 0; i < col; i++)
			{
				cout << i << "       ";
			}

			cout << endl << endl << endl;
			//��ӡӢ���к�
			for (int i = 0; i < row; i++)
			{
				cout << char(i + 65) << endl << endl << endl<<endl;
			}

			gotoxy(2, 2);
			//��ӡ�ϱ߿�
			print_unicode("�X", COLOR_HWHITE, COLOR_BLACK, 1);

			for (int i = 0; i < col - 1; i++)
			{
				print_unicode("�T", COLOR_HWHITE, COLOR_BLACK, 3);
				print_unicode("�h", COLOR_HWHITE, COLOR_BLACK, 1);
			}

			print_unicode("�T", COLOR_HWHITE, COLOR_BLACK, 3);
			print_unicode("�[", COLOR_HWHITE, COLOR_BLACK, 1);

			for (int i = 0; i < row - 1; i++)
			{
				for (int j = 0; j < 3; j++)
				{		
					cout << endl;
					getxy(curr_x, curr_y);
					gotoxy(curr_x + 2, curr_y);
					print_unicode("�U", COLOR_HWHITE, COLOR_BLACK, 1);

					for (int k = 0; k < col - 1; k++)
					{
						print_unicode("      ", COLOR_HWHITE, COLOR_BLACK, 1);
						print_unicode("��", COLOR_HWHITE, COLOR_BLACK, 1);
					}
					print_unicode("      ", COLOR_HWHITE, COLOR_BLACK, 1);

					print_unicode("�U", COLOR_HWHITE, COLOR_BLACK, 1);
					//cout << endl;
				}

				cout << endl;
				getxy(curr_x, curr_y);
				gotoxy(curr_x + 2, curr_y);
				print_unicode("�c", COLOR_HWHITE, COLOR_BLACK, 1);
				for (int j = 0; j < col - 1; j++)
				{
					print_unicode("������", COLOR_HWHITE, COLOR_BLACK, 1);
					print_unicode("��", COLOR_HWHITE, COLOR_BLACK, 1);
				}
				print_unicode("������", COLOR_HWHITE, COLOR_BLACK, 1);
				print_unicode("�f", COLOR_HWHITE, COLOR_BLACK, 1);
				//cout << endl;
			}

			for (int j = 0; j < 3; j++)
			{
				cout << endl;
				getxy(curr_x, curr_y);
				gotoxy(curr_x + 2, curr_y);
				print_unicode("�U", COLOR_HWHITE, COLOR_BLACK, 1);

				for (int k = 0; k < col - 1; k++)
				{
					print_unicode("      ", COLOR_HWHITE, COLOR_BLACK, 1);
					print_unicode("��", COLOR_HWHITE, COLOR_BLACK, 1);
				}
				print_unicode("      ", COLOR_HWHITE, COLOR_BLACK, 1);

				print_unicode("�U", COLOR_HWHITE, COLOR_BLACK, 1);
				//cout << endl;
			}

			//��ӡ�±߿�
			cout << endl;
			getxy(curr_x, curr_y);
			gotoxy(curr_x + 2, curr_y);
			print_unicode("�^", COLOR_HWHITE, COLOR_BLACK, 1);

			for (int i = 0; i < col - 1; i++)
			{
				print_unicode("�T", COLOR_HWHITE, COLOR_BLACK, 3);
				print_unicode("�k", COLOR_HWHITE, COLOR_BLACK, 1);
			}

			print_unicode("�T", COLOR_HWHITE, COLOR_BLACK, 3);
			print_unicode("�a", COLOR_HWHITE, COLOR_BLACK, 1);
		}
		}

		break;
	}
	case MAKE10:
	{
		switch (type)
		{
		case UNDIVIDED:
		{
			//���������д��ڵĴ�С
			setconsoleborder(35 + (col - 5) * 6, 22 + (row - 5) * 3);

			gotoxy(0, 1);
			//���������ӡ�ϱ߿�
			print_unicode("��", COLOR_HWHITE, COLOR_BLACK, 1);
			print_unicode("��", COLOR_HWHITE, COLOR_BLACK, col * 3);
			print_unicode("��", COLOR_HWHITE, COLOR_BLACK, 1);

			//��ӡ���ұ߿�
			for (int i = 2; i < row * 3 + 2; i++)
			{
				print_unicode("��", COLOR_HWHITE, COLOR_BLACK, 1);
				for (int j = 0; j < col * 2; j++)
				{
					print_unicode("   ", COLOR_HWHITE, COLOR_BLACK, 1);
				}

				print_unicode("��", COLOR_HWHITE, COLOR_BLACK, 1);
				cout << endl;
			}

			//��ӡ�±߿�
			print_unicode("��", COLOR_HWHITE, COLOR_BLACK, 1);
			print_unicode("��", COLOR_HWHITE, COLOR_BLACK, col * 3);
			print_unicode("��", COLOR_HWHITE, COLOR_BLACK, 1);

			break;
		}
		case DIVIDED:
		{
			setconsoleborder(43 + (col - 5) * 8, 26 + (row - 5) * 4);
			
			gotoxy(0, 1);
			//��ӡ�ϱ߿�
			print_unicode("��", COLOR_HWHITE, COLOR_BLACK, 1);

			for (int i = 0; i < col - 1; i++)
			{
				print_unicode("��", COLOR_HWHITE, COLOR_BLACK, 3);
				print_unicode("��", COLOR_HWHITE, COLOR_BLACK, 1);
			}

			print_unicode("��", COLOR_HWHITE, COLOR_BLACK, 3);
			print_unicode("��", COLOR_HWHITE, COLOR_BLACK, 1);

			//��ӡ���ұ߿�
			for (int i = 0; i < row - 1; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					print_unicode("��", COLOR_HWHITE, COLOR_BLACK, 1);

					for (int k = 0; k < col - 1; k++)
					{
						print_unicode("      ", COLOR_HWHITE, COLOR_BLACK, 1);
						print_unicode("��", COLOR_HWHITE, COLOR_BLACK, 1);
					}
					print_unicode("      ", COLOR_HWHITE, COLOR_BLACK, 1);

					print_unicode("��", COLOR_HWHITE, COLOR_BLACK, 1);
					cout << endl;
				}

				print_unicode("��", COLOR_HWHITE, COLOR_BLACK, 1);
				for (int j = 0; j < col - 1; j++)
				{
					print_unicode("������", COLOR_HWHITE, COLOR_BLACK, 1);
					print_unicode("��", COLOR_HWHITE, COLOR_BLACK, 1);
				}
				print_unicode("������", COLOR_HWHITE, COLOR_BLACK, 1);
				print_unicode("��", COLOR_HWHITE, COLOR_BLACK, 1);
				cout << endl;

			}

			for (int j = 0; j < 3; j++)
			{
				print_unicode("��", COLOR_HWHITE, COLOR_BLACK, 1);

				for (int k = 0; k < col - 1; k++)
				{
					print_unicode("      ", COLOR_HWHITE, COLOR_BLACK, 1);
					print_unicode("��", COLOR_HWHITE, COLOR_BLACK, 1);
				}
				print_unicode("      ", COLOR_HWHITE, COLOR_BLACK, 1);

				print_unicode("��", COLOR_HWHITE, COLOR_BLACK, 1);
				cout << endl;
			}

			//��ӡ�±߿�
			print_unicode("��", COLOR_HWHITE, COLOR_BLACK, 1);

			for (int i = 0; i < col - 1; i++)
			{
				print_unicode("��", COLOR_HWHITE, COLOR_BLACK, 3);
				print_unicode("��", COLOR_HWHITE, COLOR_BLACK, 1);
			}

			print_unicode("��", COLOR_HWHITE, COLOR_BLACK, 3);
			print_unicode("��", COLOR_HWHITE, COLOR_BLACK, 1);
		}
		}
	}
	}
}

/*�ú������ڴ�ӡһ��ɫ��
  ���Զ���ɫ��ĳ��Ϳ�
  ��Ҫɫ�����Ϸ��
  �Լ�ɫ������ͣ�����/��ǰ/ѡ�У�*/
void print_block(int value, int cord_x, int cord_y,int game,int type)
{
	switch (game)
	{
	case POPSTAR:
	{
		int bg_color=0;//��¼ɫ��ı���ɫ
		
		gotoxy(cord_x, cord_y);
		
		//�����ڲ������ֵѡ��ͬ��ɫ����ɫ
		switch (value)
		{
		case 1:bg_color = COLOR_HRED; break;
		case 2:bg_color = COLOR_HBLUE; break;
		case 3:bg_color = COLOR_HGREEN; break;
		case 4:bg_color = COLOR_HYELLOW; break;
		case 5:bg_color = COLOR_HPINK; break;
		case 0:type=EMP; break; //���ڲ�����ֵΪ0���ӡ�տ飬����ܱ���ɫ
		}

		//����ɫ������ʹ�ӡ��ͬ��ǰ��ɫ
		switch (type)
		{
		case NORMAL:
		{	
			setcolor(bg_color, COLOR_BLACK);
			
			cout << "�X" << "�T" << "�[";
			getxy(cord_x, cord_y);
			gotoxy(cord_x - 6, cord_y + 1);
			cout << "�U" <<"��"<< "�U";
			getxy(cord_x, cord_y);
			gotoxy(cord_x - 6, cord_y + 1);
			cout << "�^" << "�T" << "�a";

			setcolor();
			break;
		}
		case CHOSEN:
		{
			setcolor(bg_color, COLOR_WHITE);

			cout << "�X" << "�T" << "�[";
			getxy(cord_x, cord_y);
			gotoxy(cord_x - 6, cord_y + 1);
			cout << "�U" << "��" << "�U";
			getxy(cord_x, cord_y);
			gotoxy(cord_x - 6, cord_y + 1);
			cout << "�^" << "�T" << "�a";

			setcolor();
			break;
		}
		case EMP:
		{
			setcolor(COLOR_HWHITE, COLOR_HWHITE);

			cout << "�X" << "�T" << "�[";
			getxy(cord_x, cord_y);
			gotoxy(cord_x - 6, cord_y + 1);
			cout << "�U" << "��" << "�U";
			getxy(cord_x, cord_y);
			gotoxy(cord_x - 6, cord_y + 1);
			cout << "�^" << "�T" << "�a";

			setcolor();
			break;
		}
		}

		break;
	}

	case MAKE10:
	{
		if (type==CHOSEN) setcolor(COLOR_HGREEN, 0);
		else if (type==EMP) setcolor(COLOR_HWHITE, COLOR_HWHITE);
		else
		{
			//����ֵ�Ĳ�ͬ��ӡ��ͬ��ɫ����
			switch (value)
			{
			case 1:setcolor(COLOR_WHITE, 0); break;
			case 2:setcolor(COLOR_HYELLOW, 0); break;
			case 3:setcolor(COLOR_HPINK, 0); break;
			case 4:setcolor(COLOR_HRED, 0); break;
			case 5:setcolor(COLOR_HCYAN, 0); break;
			case 6:setcolor(COLOR_HGREEN, 0); break;
			case 7:setcolor(COLOR_HBLUE, 0); break;
			case 8:setcolor(COLOR_HBLACK, 0); break;
			case 9:setcolor(COLOR_WHITE, 0); break;
			case 10:setcolor(COLOR_YELLOW, 0); break;
			case 11:setcolor(COLOR_PINK, 0); break;
			case 12:setcolor(COLOR_RED, 0); break;
			case 13:setcolor(COLOR_CYAN, 0); break;
			case 14:setcolor(COLOR_GREEN, 0); break;
			case 15:setcolor(COLOR_BLUE, 0); break;
			case 16:setcolor(COLOR_HBLUE, 0); break;
			case 17:setcolor(COLOR_HPINK, 0); break;
			case 18:setcolor(COLOR_RED, 0); break;
			case 19:setcolor(COLOR_HBLUE, 0); break;
			case 20:setcolor(COLOR_PINK, 0); break;
			}
		}

		gotoxy(cord_x, cord_y);
		if (value < 10)
		{
			cout << "��" << "��" << "��";
			getxy(cord_x, cord_y);
			gotoxy(cord_x - 6, cord_y + 1);
			cout << "��" << ' ' << value << "��";
			getxy(cord_x, cord_y);
			gotoxy(cord_x - 6, cord_y + 1);
			cout << "��" << "��" << "��";
		}
		else
		{
			cout << "��" << "��" << "��";
			getxy(cord_x, cord_y);
			gotoxy(cord_x - 6, cord_y + 1);
			cout << "��" << value << "��";
			getxy(cord_x, cord_y);
			gotoxy(cord_x - 6, cord_y + 1);
			cout << "��" << "��" << "��";
		}

		setcolor();
	}
	}
}

//�ú�������һ��ɫ�������
void block_move(int(*rand_matrix)[10], int cord_row, int cord_col, int game,int direction)
{
	int target = rand_matrix[cord_row][cord_col];
	int cord_x = 4 + cord_col * 6;
	int cord_y = 3 + cord_row * 3;
	
	switch (game)
	{
	case POPSTAR:
		switch (direction)
		{
		case DOWN:
			for (int i = 0; i < 4; i++)
			{
				print_block(target, 4 + cord_col * 6, 3 + cord_row * 3,POPSTAR, EMP);
				print_block(target, cord_x, cord_y, POPSTAR, NORMAL);

				cord_y++;
				Sleep(10);
			}
			break;
		case LEFT:
			for (int i = 0; i < 7; i++)
			{
				print_block(target, 4 + cord_col * 6, 3 + cord_row * 3, POPSTAR, EMP);
				print_block(target, cord_x, cord_y, POPSTAR, NORMAL);

				cord_x--;
				Sleep(10);
			}
			break;
		}
		break;

	case MAKE10:
		int target = rand_matrix[cord_row][cord_col];
		int cord_x = 2 + cord_col * 8;
		int cord_y = 3 + cord_row * 4;

		for (int i = 0; i < 3; i++)
		{
			print_block(target, 2 + cord_col * 8, 2 + cord_row * 4, MAKE10, EMP);
			print_block(target, cord_x, cord_y, MAKE10, NORMAL);

			cord_y++;
			Sleep(10);
		}

		print_block(target, 2 + cord_col * 8, 2 + cord_row * 4, MAKE10, EMP);
		gotoxy(cord_x, cord_row * 4 + 5);

		setcolor(COLOR_HWHITE, COLOR_BLACK);
		cout << "������";
		setcolor();
		print_block(target, cord_x, cord_y, MAKE10, NORMAL);
		break;
	}
}

//�ú���������ʾ��Ϸ������������ļ�ʹ�ã�
void print_game_area(Game_area game_area, Block block)
{
	//������ʱ��¼���꣬��������ƶ�
	Cord temp_cord;

	if (game_area.divided != 1)
	{
		//�޷ָ��߰汾

		//��Ļ��С�������ɣ��������ܻ�����չ
		setconsoleborder(game_area.matrix_col*block.width + 10+game_area.extra_col, game_area.matrix_row*block.height + 10+game_area.extra_line);

		//�Ҵ����Ȱѽ�����ʾ������ȥ������ʾ���б��
		gotoxy(game_area.orig_cord.cord_x + 2, game_area.orig_cord.cord_y + 1);

		//���������ӡ�ϱ߿�
		print_unicode_cfg(game_area.border[0], game_area.game_area_color.bg_color, game_area.game_area_color.fg_color, 1, game_area.delay_time);
		print_unicode_cfg(game_area.border[4], game_area.game_area_color.bg_color, game_area.game_area_color.fg_color, game_area.matrix_col * block.width / 2, game_area.delay_time);
		print_unicode_cfg(game_area.border[2], game_area.game_area_color.bg_color, game_area.game_area_color.fg_color, 1, game_area.delay_time);

		//��ӡ���ұ߿�
		for (int i = 0; i < game_area.matrix_row * block.height; i++)
		{
			getxy(temp_cord.cord_x, temp_cord.cord_y);
			gotoxy(game_area.orig_cord.cord_x + 2, temp_cord.cord_y + 1);

			print_unicode_cfg(game_area.border[5], game_area.game_area_color.bg_color, game_area.game_area_color.fg_color, 1, game_area.delay_time);
			for (int j = 0; j < game_area.matrix_col*block.width; j++)
			{
				print_unicode_cfg(" ", game_area.game_area_color.bg_color, game_area.game_area_color.fg_color, 1, game_area.delay_time);
			}

			print_unicode_cfg(game_area.border[5], game_area.game_area_color.bg_color, game_area.game_area_color.fg_color, 1, game_area.delay_time);
		}

		//��ӡ�±߿�
		getxy(temp_cord.cord_x, temp_cord.cord_y);
		gotoxy(game_area.orig_cord.cord_x + 2, temp_cord.cord_y + 1);

		print_unicode_cfg(game_area.border[1], game_area.game_area_color.bg_color, game_area.game_area_color.fg_color, 1, game_area.delay_time);
		print_unicode_cfg(game_area.border[4], game_area.game_area_color.bg_color, game_area.game_area_color.fg_color, game_area.matrix_col * block.width / 2, game_area.delay_time);
		print_unicode_cfg(game_area.border[3], game_area.game_area_color.bg_color, game_area.game_area_color.fg_color, 1, game_area.delay_time);

		//Ȼ���ٿ���Ҫ��Ҫ��ӡ���б��
		if (game_area.show_row_col_number == 1)
		{
			setcolor(0, COLOR_HBLUE);

			gotoxy(game_area.orig_cord.cord_x, game_area.orig_cord.cord_y);

			cout << "      ";
			//��ӡ�к�
			for (int i = 0; i < game_area.matrix_col; i++)
			{
				cout << i;
				for (int j = 0; j < block.width - 1; j++)
				{
					cout << ' ';
				}
			}

			for (int i = 0; i < 3; i++)
			{
				getxy(temp_cord.cord_x, temp_cord.cord_y);
				gotoxy(game_area.orig_cord.cord_x, temp_cord.cord_y + 1);
			}

			//��ӡӢ���к�
			for (int i = 0; i < game_area.matrix_row; i++)
			{
				cout << char(i + 65);

				for (int j = 0; j < block.height; j++)
				{
					getxy(temp_cord.cord_x, temp_cord.cord_y);
					gotoxy(game_area.orig_cord.cord_x, temp_cord.cord_y + 1);
				}
			}
		}
	}

	else if (game_area.divided == 1)
	{
		//���зָ��߰汾
		setconsoleborder(game_area.matrix_col*(block.width + 2) + 10 + game_area.extra_line, game_area.matrix_row*(block.height + 1) + 10 + game_area.extra_col);

		gotoxy(game_area.orig_cord.cord_x + 2, game_area.orig_cord.cord_y + 1);

		//��ӡ�ϱ߿�
		print_unicode_cfg(game_area.border[0], game_area.game_area_color.bg_color, game_area.game_area_color.fg_color, 1, game_area.delay_time);

		for (int i = 0; i < game_area.matrix_col - 1; i++)
		{
			print_unicode_cfg(game_area.border[4], game_area.game_area_color.bg_color, game_area.game_area_color.fg_color, block.width / 2, game_area.delay_time);
			print_unicode_cfg(game_area.border[6], game_area.game_area_color.bg_color, game_area.game_area_color.fg_color, 1, game_area.delay_time);
		}

		print_unicode_cfg(game_area.border[4], game_area.game_area_color.bg_color, game_area.game_area_color.fg_color, block.width / 2, game_area.delay_time);
		print_unicode_cfg(game_area.border[2], game_area.game_area_color.bg_color, game_area.game_area_color.fg_color, 1, game_area.delay_time);

		for (int i = 0; i < game_area.matrix_row - 1; i++)
		{
			for (int j = 0; j < block.height; j++)
			{
				getxy(temp_cord.cord_x, temp_cord.cord_y);
				gotoxy(game_area.orig_cord.cord_x + 2, temp_cord.cord_y + 1);

				print_unicode_cfg(game_area.border[5], game_area.game_area_color.bg_color, game_area.game_area_color.fg_color, 1, game_area.delay_time);

				for (int k = 0; k < game_area.matrix_col - 1; k++)
				{
					print_unicode_cfg(" ", game_area.game_area_color.bg_color, game_area.game_area_color.fg_color, block.width, game_area.delay_time);
					print_unicode_cfg(game_area.border[5], game_area.game_area_color.bg_color, game_area.game_area_color.fg_color, 1, game_area.delay_time);
				}
				print_unicode_cfg(" ", game_area.game_area_color.bg_color, game_area.game_area_color.fg_color, block.width, game_area.delay_time);
				print_unicode_cfg(game_area.border[5], game_area.game_area_color.bg_color, game_area.game_area_color.fg_color, 1, game_area.delay_time);
			}

			getxy(temp_cord.cord_x, temp_cord.cord_y);
			gotoxy(game_area.orig_cord.cord_x + 2, temp_cord.cord_y + 1);

			print_unicode_cfg(game_area.border[8], game_area.game_area_color.bg_color, game_area.game_area_color.fg_color, 1, game_area.delay_time);
			for (int j = 0; j < game_area.matrix_col - 1; j++)
			{
				print_unicode_cfg(game_area.border[4], game_area.game_area_color.bg_color, game_area.game_area_color.fg_color, block.width / 2, game_area.delay_time);
				print_unicode_cfg(game_area.border[10], game_area.game_area_color.bg_color, game_area.game_area_color.fg_color, 1, game_area.delay_time);
			}
			print_unicode_cfg(game_area.border[4], game_area.game_area_color.bg_color, game_area.game_area_color.fg_color, block.width / 2, game_area.delay_time);
			print_unicode_cfg(game_area.border[9], game_area.game_area_color.bg_color, game_area.game_area_color.fg_color, 1, game_area.delay_time);
		}

		for (int j = 0; j < block.height; j++)
		{
			getxy(temp_cord.cord_x, temp_cord.cord_y);
			gotoxy(game_area.orig_cord.cord_x + 2, temp_cord.cord_y + 1);

			print_unicode_cfg(game_area.border[5], game_area.game_area_color.bg_color, game_area.game_area_color.fg_color, 1, game_area.delay_time);

			for (int k = 0; k < game_area.matrix_col - 1; k++)
			{
				print_unicode_cfg(" ", game_area.game_area_color.bg_color, game_area.game_area_color.fg_color, block.width, game_area.delay_time);
				print_unicode_cfg(game_area.border[5], game_area.game_area_color.bg_color, game_area.game_area_color.fg_color, 1, game_area.delay_time);
			}
			print_unicode_cfg(" ", game_area.game_area_color.bg_color, game_area.game_area_color.fg_color, block.width, game_area.delay_time);
			print_unicode_cfg(game_area.border[5], game_area.game_area_color.bg_color, game_area.game_area_color.fg_color, 1, game_area.delay_time);
		}

		//��ӡ�±߿�
		getxy(temp_cord.cord_x, temp_cord.cord_y);
		gotoxy(game_area.orig_cord.cord_x + 2, temp_cord.cord_y + 1);
		print_unicode_cfg(game_area.border[1], game_area.game_area_color.bg_color, game_area.game_area_color.fg_color, 1, game_area.delay_time);

		for (int i = 0; i < game_area.matrix_col - 1; i++)
		{
			print_unicode_cfg(game_area.border[4], game_area.game_area_color.bg_color, game_area.game_area_color.fg_color, block.width / 2, game_area.delay_time);
			print_unicode_cfg(game_area.border[7], game_area.game_area_color.bg_color, game_area.game_area_color.fg_color, 1, game_area.delay_time);
		}

		print_unicode_cfg(game_area.border[4], game_area.game_area_color.bg_color, game_area.game_area_color.fg_color, block.width / 2, game_area.delay_time);
		print_unicode_cfg(game_area.border[3], game_area.game_area_color.bg_color, game_area.game_area_color.fg_color, 1, game_area.delay_time);

		//Ȼ���ٿ���Ҫ��Ҫ��ӡ���б��
		if (game_area.show_row_col_number == 1)
		{
			setcolor(0, COLOR_HBLUE);

			gotoxy(game_area.orig_cord.cord_x, game_area.orig_cord.cord_y);

			cout << "      ";
			//��ӡ�к�
			for (int i = 0; i < game_area.matrix_col; i++)
			{
				cout << i;
				for (int j = 0; j < block.width + 1; j++)
				{
					cout << ' ';
				}
			}

			for (int i = 0; i < 3; i++)
			{
				getxy(temp_cord.cord_x, temp_cord.cord_y);
				gotoxy(game_area.orig_cord.cord_x, temp_cord.cord_y + 1);
			}

			//��ӡӢ���к�
			for (int i = 0; i < game_area.matrix_row; i++)
			{
				cout << char(i + 65);

				for (int j = 0; j < block.height + 1; j++)
				{
					getxy(temp_cord.cord_x, temp_cord.cord_y);
					gotoxy(game_area.orig_cord.cord_x, temp_cord.cord_y + 1);
				}
			}
		}
	}

	setcolor();
}

//�ú������ڴ�ӡһ�����飨��������ļ�ʹ�ã�
void print_block_cfg(int value, Game_area game_area, Cord cord, Block block, Block_color block_color, int type)
{
	if (block.type == MAKE10)
	{
		//��ϷΪ�ϳ�ʮ�����
		block.value.value_num = value;

		//����ɫ������ͣ����� / ѡ�� / �հ�
		if (type == CHOSEN)
		{
			setcolor(block_color.chosen_block_color.bg_color, block_color.chosen_block_color.fg_color);
		}
		else if (type == EMP)
		{
			setcolor(game_area.game_area_color.bg_color, game_area.game_area_color.bg_color);
		}
		else
		{
			//����ֵ�Ĳ�ͬ��ӡ��ͬ��ɫ����
			switch (value)
			{
			case 1:setcolor(block_color.block_color_1.bg_color, block_color.block_color_1.fg_color); break;
			case 2:setcolor(block_color.block_color_2.bg_color, block_color.block_color_2.fg_color); break;
			case 3:setcolor(block_color.block_color_3.bg_color, block_color.block_color_3.fg_color); break;
			case 4:setcolor(block_color.block_color_4.bg_color, block_color.block_color_4.fg_color); break;
			case 5:setcolor(block_color.block_color_5.bg_color, block_color.block_color_5.fg_color); break;
			case 6:setcolor(block_color.block_color_6.bg_color, block_color.block_color_6.fg_color); break;
			case 7:setcolor(block_color.block_color_7.bg_color, block_color.block_color_7.fg_color); break;
			case 8:setcolor(block_color.block_color_8.bg_color, block_color.block_color_8.fg_color); break;
			case 9:setcolor(block_color.block_color_9.bg_color, block_color.block_color_9.fg_color); break;
			case 10:setcolor(block_color.block_color_10.bg_color, block_color.block_color_10.fg_color); break;
			case 11:setcolor(block_color.block_color_11.bg_color, block_color.block_color_11.fg_color); break;
			}
		}
	}
	else if (block.type == POPSTAR)
	{
		//��ϷΪ�ϳ�ʮ�����
		strcpy(block.value.value_star, "��");

		if (value == 0) type = EMP;

		//����ɫ������ͣ����� / ѡ�� / �հ�
		if (type == CHOSEN)
		{
			setcolor(block_color.chosen_block_color.bg_color, block_color.chosen_block_color.fg_color);
		}
		else if (type == EMP)
		{
			setcolor(game_area.game_area_color.bg_color, game_area.game_area_color.bg_color);
		}
		else
		{
			//����ֵ�Ĳ�ͬ��ӡ��ͬ��ɫ����
			switch (value)
			{
			case 1:setcolor(block_color.block_color_1.bg_color, block_color.block_color_1.fg_color); break;
			case 2:setcolor(block_color.block_color_2.bg_color, block_color.block_color_2.fg_color); break;
			case 3:setcolor(block_color.block_color_3.bg_color, block_color.block_color_3.fg_color); break;
			case 4:setcolor(block_color.block_color_4.bg_color, block_color.block_color_4.fg_color); break;
			case 5:setcolor(block_color.block_color_5.bg_color, block_color.block_color_5.fg_color); break;
			}
		}
	}

	//�ƶ���ָ����ʼ����
	gotoxy(cord.cord_x, cord.cord_y);

	//���ȴ�ӡһ��ɫ��ĵ�һ��
	cout << block.frame[0];
	for (int i = 0; i < block.width / 2 - 2; i++)
	{
		cout << block.frame[4];
	}
	cout << block.frame[2];

	//�������ǻ��ڵڶ��е��д�ӡɫ���ֵ
	getxy(cord.cord_x, cord.cord_y);
	gotoxy(cord.cord_x - block.width, cord.cord_y + 1);

	cout << block.frame[5];
	for (int i = 0; i < (block.width - 4) / 4; i++)
	{
		cout << ' ';
	}

	switch (block.type)
	{
	case POPSTAR:cout << block.value.value_star; break;
	case MAKE10:cout << setw(2) << block.value.value_num; break;
	}

	for (int i = 0; i < (block.width - 4) / 4; i++)
	{
		cout << ' ';
	}

	cout << block.frame[5];

	//���Ŵ�ӡʣ�µĳ����һ�������ɫ��߿�
	for (int i = 0; i < block.height - 3; i++)
	{
		getxy(cord.cord_x, cord.cord_y);
		gotoxy(cord.cord_x - block.width, cord.cord_y + 1);

		cout << block.frame[5];
		for (int i = 0; i < block.width / 2 - 2; i++)
		{
			cout << "  ";
		}
		cout << block.frame[5];
	}

	//������Ǵ�ӡ���һ��
	getxy(cord.cord_x, cord.cord_y);
	gotoxy(cord.cord_x - block.width, cord.cord_y + 1);

	cout << block.frame[1];
	for (int i = 0; i < block.width / 2 - 2; i++)
	{
		cout << block.frame[4];
	}
	cout << block.frame[3];

	setcolor();
}

//�ú�������һ��ɫ����ƶ�����������ļ�ʹ�ã�
void block_move_cfg(Game_area game_area, Block block, Block_color block_color, int cord_row, int cord_col, int direction)
{
	//��¼���ƶ�ɫ���ֵ
	int target = game_area.rand_matrix[cord_row][cord_col];

	//��������дû�зָ�����Ϸ�����µ��ƶ���
	if (game_area.divided != 1)
	{
		//��ɫ������Ļ�е���ʼ����
		Cord orig_cord, curr_cord;
		orig_cord.cord_x = (game_area.orig_cord.cord_x + 4) + cord_col * block.width;
		orig_cord.cord_y = (game_area.orig_cord.cord_y + 2) + cord_row * block.height;

		curr_cord.cord_x = orig_cord.cord_x;
		curr_cord.cord_y = orig_cord.cord_y;

		//��Ȼ�����������ƶ�
		if (direction == DOWN)
		{
			for (int i = 0; i < block.height + 1; i++)
			{
				//ɫ��ԭλ�ô�ӡ�հ�
				print_block_cfg(target, game_area, orig_cord, block, block_color, EMP);
				print_block_cfg(target, game_area, curr_cord, block, block_color, NORMAL);

				curr_cord.cord_y++;
				Sleep(block.move_delay_time);
			}
		}

		//�������������ƶ�
		else if (direction == LEFT)
		{
			for (int i = 0; i < block.width + 1; i++)
			{
				//ɫ��ԭλ�ô�ӡ�հ�
				print_block_cfg(target, game_area, orig_cord, block, block_color, EMP);
				print_block_cfg(target, game_area, curr_cord, block, block_color, NORMAL);

				curr_cord.cord_x--;
				Sleep(block.move_delay_time);
			}

		}
	}

	//������д�зָ��߰汾��
	else if (game_area.divided == 1)
	{
		//��ɫ������Ļ�е���ʼ����
		Cord orig_cord, curr_cord;
		orig_cord.cord_x = (game_area.orig_cord.cord_x + 4) + cord_col * (block.width + 2);
		orig_cord.cord_y = (game_area.orig_cord.cord_y + 2) + cord_row * (block.height + 1);

		curr_cord.cord_x = orig_cord.cord_x;
		curr_cord.cord_y = orig_cord.cord_y;

		if (direction == DOWN)
		{
			for (int i = 0; i < block.height + 1; i++)
			{
				//ɫ��ԭλ�ô�ӡ�հ�
				print_block_cfg(target, game_area, orig_cord, block, block_color, EMP);
				print_block_cfg(target, game_area, curr_cord, block, block_color, NORMAL);

				curr_cord.cord_y++;
				Sleep(block.move_delay_time);
			}

			print_block_cfg(target, game_area, orig_cord, block, block_color, EMP);
			gotoxy(curr_cord.cord_x, curr_cord.cord_y - 1);

			print_unicode(game_area.border[4], game_area.game_area_color.bg_color, game_area.game_area_color.fg_color, block.width / 2);
			print_block_cfg(target, game_area, curr_cord, block, block_color, NORMAL);
		}
		else if (direction == LEFT)
		{
			Cord temp_cord; //һ���ƶ������Ҫ�õ�����ʱ����

			for (int i = 0; i < block.width + 1; i++)
			{
				//ɫ��ԭλ�ô�ӡ�հ�
				print_block_cfg(target, game_area, orig_cord, block, block_color, EMP);
				print_block_cfg(target, game_area, curr_cord, block, block_color, NORMAL);

				curr_cord.cord_x--;
				Sleep(block.move_delay_time);
			}

			print_block_cfg(target, game_area, orig_cord, block, block_color, EMP);
			gotoxy(orig_cord.cord_x - 2, orig_cord.cord_y);

			for (int i = 0; i < block.height; i++)
			{
				print_unicode(game_area.border[5], game_area.game_area_color.bg_color, game_area.game_area_color.fg_color, 1);

				getxy(temp_cord.cord_x, temp_cord.cord_y);
				gotoxy(temp_cord.cord_x, temp_cord.cord_y + 1);
			}
			print_block_cfg(target, game_area, curr_cord, block, block_color, NORMAL);
		}
	}
}

//��ӡ��ȡ����Ϣ�������ã�
void print_game_cfg(Game_area game_area, Block block, Block_color block_color)
{
	cout << "��ϷĿ��:" << game_area.goal << endl;
	cout << "�Ƿ���Ҫ�ָ���:" << game_area.divided << endl;
	cout << "�Ƿ���ʾ���б��:" << game_area.show_row_col_number << endl;
	cout << "����:" << game_area.matrix_row << endl;
	cout << "����:" << game_area.matrix_col << endl;

	for (int i = 0; i < 11; i++)
	{
		cout << game_area.border[i] << ' ';
	}
	cout << endl;

	cout << "��Ϸ������ɫ���:" << game_area.game_area_color.bg_color << ' ' << game_area.game_area_color.fg_color << endl;
	cout << "��Ϸ������ʼ����:" << game_area.orig_cord.cord_x << ' ' << game_area.orig_cord.cord_y << endl;

	cout << "��ǰ��Ϸ:" << block.type << endl;
	cout << "ɫ����:" << block.width << endl;
	cout << "ɫ��߶�:" << block.height << endl;

	for (int i = 0; i < 6; i++)
	{
		cout << block.frame[i] << ' ';
	}
	cout << endl;

	cout << "ɫ����ɫ:" << endl;
	cout << "1." << block_color.block_color_1.bg_color << ' ' << block_color.block_color_1.fg_color << endl;
	cout << "2." << block_color.block_color_2.bg_color << ' ' << block_color.block_color_2.fg_color << endl;
	cout << "3." << block_color.block_color_3.bg_color << ' ' << block_color.block_color_3.fg_color << endl;
	cout << "4." << block_color.block_color_4.bg_color << ' ' << block_color.block_color_4.fg_color << endl;
	cout << "5." << block_color.block_color_5.bg_color << ' ' << block_color.block_color_5.fg_color << endl;
	cout << "6." << block_color.block_color_6.bg_color << ' ' << block_color.block_color_6.fg_color << endl;
	cout << "7." << block_color.block_color_7.bg_color << ' ' << block_color.block_color_7.fg_color << endl;
	cout << "8." << block_color.block_color_8.bg_color << ' ' << block_color.block_color_8.fg_color << endl;
	cout << "9." << block_color.block_color_9.bg_color << ' ' << block_color.block_color_9.fg_color << endl;
	cout << "10." << block_color.block_color_10.bg_color << ' ' << block_color.block_color_10.fg_color << endl;
	cout << "11." << block_color.block_color_11.bg_color << ' ' << block_color.block_color_11.fg_color << endl;
	cout << "Chosen:" << block_color.chosen_block_color.bg_color << ' ' << block_color.chosen_block_color.fg_color << endl;
}

//�ú��������ڼ����ƶ�ɫ�飨������µĿɶ�ȡ�����ļ��汾ʹ�ã�
void kb_move_cfg(Game_area &game_area, Block block, Block_color block_color)
{
	Cord cord;
	Cord orig_cord;
	int ret, maction;
	int keycode1, keycode2;
	int loop = 1;

	bool illegal = 0;

	enable_mouse();
	setcursor(CURSOR_INVISIBLE);	//�رչ��

	while (loop)
	{
		ret = read_keyboard_and_mouse(cord.cord_x, cord.cord_y, maction, keycode1, keycode2);

		if (ret == CCT_MOUSE_EVENT) {
			//����ǰ���λ�õ�����ת��Ϊ��Ӧ�������ˣ����ж�λ�õ�ǰλ���Ƿ�Ϸ�
			if (cord_to_rc_cfg(game_area, cord, block))
			{
				//�����ǰ������ڷ�������һ�����ڷ��鲻ͬ�Ŵ�ӡλ����Ϣ������������ӡ������Ƶ��
				if ((game_area.curr_row != game_area.last_row) || (game_area.curr_col != game_area.last_col) || illegal)
				{
					//�ƶ��󽫵�ǰ��ѡ��ķ���ָ�
					for (int i = 0; i < game_area.matrix_row; i++)
					{
						for (int j = 0; j < game_area.matrix_col; j++)
						{
							if (game_area.mark_matrix[i][j] == '*')
							{
								switch (game_area.divided)
								{
								case 1:
									orig_cord.cord_x = (game_area.orig_cord.cord_x + 4) + j * (block.width + 2);
									orig_cord.cord_y = (game_area.orig_cord.cord_y + 2) + i * (block.height + 1);
									break;

								case 0:
									orig_cord.cord_x = (game_area.orig_cord.cord_x + 4) + j * block.width;
									orig_cord.cord_y = (game_area.orig_cord.cord_y + 2) + i * block.height;
									break;
								}
								print_block_cfg(game_area.rand_matrix[i][j], game_area, orig_cord, block, block_color, NORMAL);
							}
						}
					}

					orig_mark(game_area.mark_matrix, game_area.matrix_row, game_area.matrix_col);

					if (game_area.divided != 1)
					{
						orig_cord.cord_x = (game_area.orig_cord.cord_x + 4) + game_area.curr_col * block.width;
						orig_cord.cord_y = (game_area.orig_cord.cord_y + 2) + game_area.curr_row * block.height;
						print_block_cfg(game_area.rand_matrix[game_area.curr_row][game_area.curr_col], game_area, orig_cord, block, block_color, CHOSEN);

						orig_cord.cord_x = (game_area.orig_cord.cord_x + 4) + game_area.last_col * block.width;
						orig_cord.cord_y = (game_area.orig_cord.cord_y + 2) + game_area.last_row * block.height;
						print_block_cfg(game_area.rand_matrix[game_area.last_row][game_area.last_col], game_area, orig_cord, block, block_color, NORMAL);
					}
					else if (game_area.divided == 1)
					{
						orig_cord.cord_x = (game_area.orig_cord.cord_x + 4) + game_area.curr_col * (block.width + 2);
						orig_cord.cord_y = (game_area.orig_cord.cord_y + 2) + game_area.curr_row * (block.height + 1);
						print_block_cfg(game_area.rand_matrix[game_area.curr_row][game_area.curr_col], game_area, orig_cord, block, block_color, CHOSEN);

						orig_cord.cord_x = (game_area.orig_cord.cord_x + 4) + game_area.last_col * (block.width + 2);
						orig_cord.cord_y = (game_area.orig_cord.cord_y + 2) + game_area.last_row * (block.height + 1);
						print_block_cfg(game_area.rand_matrix[game_area.last_row][game_area.last_col], game_area, orig_cord, block, block_color, NORMAL);
					}

					//��ӡ�����������λ��
					if (game_area.bot_info)
					{
						if (game_area.divided)
						{
							gotoxy(0, game_area.orig_cord.cord_y + game_area.matrix_row*(block.height + 1) + 3);
						}
						else gotoxy(0, game_area.orig_cord.cord_y + game_area.matrix_row*block.height + 3);
						cout << "                                                              ";
						if (game_area.divided)
						{
							gotoxy(0, game_area.orig_cord.cord_y + game_area.matrix_row*(block.height + 1) + 3);
						}
						else gotoxy(0, game_area.orig_cord.cord_y + game_area.matrix_row*block.height + 3);
						setcolor(game_area.norm_info_color.bg_color, game_area.norm_info_color.fg_color);
						cout << "[��ǰ���] " << char(game_area.curr_row + 65) << "��" << game_area.curr_col << "��";
						setcolor();
					}

					illegal = 0;

				}
			}
			else //λ�÷Ƿ�
			{
				if (!illegal)
				{
					if (game_area.divided != 1)
					{
						orig_cord.cord_x = (game_area.orig_cord.cord_x + 4) + game_area.last_col * block.width;
						orig_cord.cord_y = (game_area.orig_cord.cord_y + 2) + game_area.last_row * block.height;
						print_block_cfg(game_area.rand_matrix[game_area.last_row][game_area.last_col], game_area, orig_cord, block, block_color, NORMAL);
					}
					else if (game_area.divided == 1)
					{
						orig_cord.cord_x = (game_area.orig_cord.cord_x + 4) + game_area.last_col * (block.width + 2);
						orig_cord.cord_y = (game_area.orig_cord.cord_y + 2) + game_area.last_row * (block.height + 1);
						print_block_cfg(game_area.rand_matrix[game_area.last_row][game_area.last_col], game_area, orig_cord, block, block_color, NORMAL);
					}

					if (game_area.bot_info)
					{
						if (game_area.divided)
						{
							gotoxy(0, game_area.orig_cord.cord_y + game_area.matrix_row*(block.height + 1) + 3);
						}
						else gotoxy(0, game_area.orig_cord.cord_y + game_area.matrix_row*block.height + 3);
						cout << "                                                              ";
						if (game_area.divided)
						{
							gotoxy(0, game_area.orig_cord.cord_y + game_area.matrix_row*(block.height + 1) + 3);
						}
						else gotoxy(0, game_area.orig_cord.cord_y + game_area.matrix_row*block.height + 3);
						setcolor(game_area.warning_color.bg_color, game_area.warning_color.fg_color);
						cout << "[��ǰ���]" << "λ�÷Ƿ�";
						setcolor();
					}

					illegal = 1;

					continue;
				}
			}

			//�������ֻ��Ҫ��������Ĳ���
			switch (maction)
			{
			case MOUSE_LEFT_BUTTON_CLICK:			//�������
				return;
			}
		}

		if (ret == CCT_KEYBOARD_EVENT)
		{
			switch (keycode1)
			{
			case 224:
				switch (keycode2) {
				case KB_ARROW_UP:
					go_cfg(game_area, block, block_color, UP);
					if (game_area.bot_info)
					{
						if (game_area.divided)
						{
							gotoxy(0, game_area.orig_cord.cord_y + game_area.matrix_row*(block.height + 1) + 3);
						}
						else gotoxy(0, game_area.orig_cord.cord_y + game_area.matrix_row*block.height + 3);
						cout << "                                                              ";
						if (game_area.divided)
						{
							gotoxy(0, game_area.orig_cord.cord_y + game_area.matrix_row*(block.height + 1) + 3);
						}
						else gotoxy(0, game_area.orig_cord.cord_y + game_area.matrix_row*block.height + 3);
						setcolor(game_area.norm_info_color.bg_color, game_area.norm_info_color.fg_color);
						cout << "[��ǰ����] " << char(game_area.curr_row + 65) << "��" << game_area.curr_col << "��";
						setcolor();
					}
					break;
				case KB_ARROW_DOWN:
					go_cfg(game_area, block, block_color, DOWN);
					if (game_area.bot_info)
					{
						if (game_area.divided)
						{
							gotoxy(0, game_area.orig_cord.cord_y + game_area.matrix_row*(block.height + 1) + 3);
						}
						else gotoxy(0, game_area.orig_cord.cord_y + game_area.matrix_row*block.height + 3);
						cout << "                                                              ";
						if (game_area.divided)
						{
							gotoxy(0, game_area.orig_cord.cord_y + game_area.matrix_row*(block.height + 1) + 3);
						}
						else gotoxy(0, game_area.orig_cord.cord_y + game_area.matrix_row*block.height + 3);
						setcolor(game_area.norm_info_color.bg_color, game_area.norm_info_color.fg_color);
						cout << "[��ǰ����] " << char(game_area.curr_row + 65) << "��" << game_area.curr_col << "��";
						setcolor();
					}
					break;
				case KB_ARROW_LEFT:
					go_cfg(game_area, block, block_color, LEFT);
					if (game_area.bot_info)
					{
						if (game_area.divided)
						{
							gotoxy(0, game_area.orig_cord.cord_y + game_area.matrix_row*(block.height + 1) + 3);
						}
						else gotoxy(0, game_area.orig_cord.cord_y + game_area.matrix_row*block.height + 3);
						cout << "                                                              ";
						if (game_area.divided)
						{
							gotoxy(0, game_area.orig_cord.cord_y + game_area.matrix_row*(block.height + 1) + 3);
						}
						else gotoxy(0, game_area.orig_cord.cord_y + game_area.matrix_row*block.height + 3);
						setcolor(game_area.norm_info_color.bg_color, game_area.norm_info_color.fg_color);
						cout << "[��ǰ����] " << char(game_area.curr_row + 65) << "��" << game_area.curr_col << "��";
						setcolor();
					}
					break;
				case KB_ARROW_RIGHT:
					go_cfg(game_area, block, block_color, RIGHT);
					if (game_area.bot_info)
					{
						if (game_area.divided)
						{
							gotoxy(0, game_area.orig_cord.cord_y + game_area.matrix_row*(block.height + 1) + 3);
						}
						else gotoxy(0, game_area.orig_cord.cord_y + game_area.matrix_row*block.height + 3);
						cout << "                                                              ";
						if (game_area.divided)
						{
							gotoxy(0, game_area.orig_cord.cord_y + game_area.matrix_row*(block.height + 1) + 3);
						}
						else gotoxy(0, game_area.orig_cord.cord_y + game_area.matrix_row*block.height + 3);
						setcolor(game_area.norm_info_color.bg_color, game_area.norm_info_color.fg_color);
						cout << "[��ǰ����] " << char(game_area.curr_row + 65) << "��" << game_area.curr_col << "��";
						setcolor();
					}
					break;
				}
				//�ƶ��󽫵�ǰ��ѡ��ķ���ָ�
				for (int i = 0; i < game_area.matrix_row; i++)
				{
					for (int j = 0; j < game_area.matrix_col; j++)
					{
						if (game_area.mark_matrix[i][j] == '*' && (i != game_area.curr_row || j != game_area.curr_col))
						{
							if (game_area.divided != 1)
							{
								orig_cord.cord_x = (game_area.orig_cord.cord_x + 4) + j * block.width;
								orig_cord.cord_y = (game_area.orig_cord.cord_y + 2) + i * block.height;
								print_block_cfg(game_area.rand_matrix[i][j], game_area, orig_cord, block, block_color, NORMAL);
							}
							else if (game_area.divided == 1)
							{
								orig_cord.cord_x = (game_area.orig_cord.cord_x + 4) + j * (block.width + 2);
								orig_cord.cord_y = (game_area.orig_cord.cord_y + 2) + i * (block.height + 1);
								print_block_cfg(game_area.rand_matrix[i][j], game_area, orig_cord, block, block_color, NORMAL);
							}
						}
					}
				}

				orig_mark(game_area.mark_matrix, game_area.matrix_row, game_area.matrix_col);
				break;
			case 13:
				return;
			}
		}
	}
}

//�ú������ڽ���������ת��Ϊָ�������У�������µĿɶ�ȡ�����ļ��汾ʹ�ã�
bool cord_to_rc_cfg(Game_area &game_area, Cord cord, Block block)
{
	//����ǰѡ��������Ϊ��һ��ѡ������
	game_area.last_row = game_area.curr_row;
	game_area.last_col = game_area.curr_col;

	//�����жϸ�������λ���Ƿ�Ϸ�
	bool legal_row = 0, legal_col = 0, legal_value = 0;

	if (game_area.divided != 1)
	{
		//�޷ָ��ߵ����
		for (int i = 0; i < game_area.matrix_col; i++)
		{
			int block_cord_x = game_area.orig_cord.cord_x + 4 + i * block.width;

			if (cord.cord_x >= block_cord_x && cord.cord_x <= block_cord_x + block.width)
			{
				game_area.curr_col = i;
				legal_col = 1;
			}
		}

		for (int i = 0; i < game_area.matrix_row; i++)
		{
			int block_cord_y = game_area.orig_cord.cord_y + 2 + i * block.height;

			if (cord.cord_y >= block_cord_y && cord.cord_y <= block_cord_y + block.height)
			{
				game_area.curr_row = i;
				legal_row = 1;
			}
		}
	}

	else if (game_area.divided == 1)
	{
		//�зָ��߰汾
		//�޷ָ��ߵ����
		for (int i = 0; i < game_area.matrix_col; i++)
		{
			int block_cord_x = game_area.orig_cord.cord_x + 4 + i * (block.width + 2);

			if (cord.cord_x >= block_cord_x && cord.cord_x <= block_cord_x + block.width)
			{
				game_area.curr_col = i;
				legal_col = 1;
			}
		}

		for (int i = 0; i < game_area.matrix_row; i++)
		{
			int block_cord_y = game_area.orig_cord.cord_y + 2 + i * (block.height + 1);

			if (cord.cord_y >= block_cord_y && cord.cord_y <= block_cord_y + block.height)
			{
				game_area.curr_row = i;
				legal_row = 1;
			}
		}
	}

	if (game_area.rand_matrix[game_area.curr_row][game_area.curr_col] != 0)
	{
		legal_value = 1;
	}

	return (legal_row && legal_col && legal_value);
}

//���ڼ��̲�����������������ƶ�
void go_cfg(Game_area &game_area, Block block, Block_color block_color, int direction)
{
	if (direction == UP)
	{
		if (game_area.curr_row <= 0) game_area.curr_row = game_area.matrix_row - 1;
		else game_area.curr_row -= 1;

		if (game_area.rand_matrix[game_area.curr_row][game_area.curr_col] == 0)
		{
			game_area.curr_row -= 1;
			go_cfg(game_area, block, block_color, direction);
		}
		else
		{
			if (game_area.divided != 1)
			{
				Cord orig_cord;
				orig_cord.cord_x = (game_area.orig_cord.cord_x + 4) + game_area.curr_col * block.width;
				orig_cord.cord_y = (game_area.orig_cord.cord_y + 2) + game_area.curr_row * block.height;
				print_block_cfg(game_area.rand_matrix[game_area.curr_row][game_area.curr_col], game_area, orig_cord, block, block_color, CHOSEN);

				orig_cord.cord_x = (game_area.orig_cord.cord_x + 4) + game_area.last_col * block.width;
				orig_cord.cord_y = (game_area.orig_cord.cord_y + 2) + game_area.last_row * block.height;
				print_block_cfg(game_area.rand_matrix[game_area.last_row][game_area.last_col], game_area, orig_cord, block, block_color, NORMAL);
			}
			else if (game_area.divided == 1)
			{
				Cord orig_cord;
				orig_cord.cord_x = (game_area.orig_cord.cord_x + 4) + game_area.curr_col * (block.width + 2);
				orig_cord.cord_y = (game_area.orig_cord.cord_y + 2) + game_area.curr_row * (block.height + 1);
				print_block_cfg(game_area.rand_matrix[game_area.curr_row][game_area.curr_col], game_area, orig_cord, block, block_color, CHOSEN);

				orig_cord.cord_x = (game_area.orig_cord.cord_x + 4) + game_area.last_col * (block.width + 2);
				orig_cord.cord_y = (game_area.orig_cord.cord_y + 2) + game_area.last_row * (block.height + 1);
				print_block_cfg(game_area.rand_matrix[game_area.last_row][game_area.last_col], game_area, orig_cord, block, block_color, NORMAL);
			}
		}
	}
	else if (direction == DOWN)
	{
		if (game_area.curr_row >= game_area.matrix_row - 1) game_area.curr_row = 0;
		else game_area.curr_row += 1;

		if (game_area.rand_matrix[game_area.curr_row][game_area.curr_col] == 0)
		{
			game_area.curr_row += 1;
			go_cfg(game_area, block, block_color, direction);
		}
		else
		{
			if (game_area.divided != 1)
			{
				Cord orig_cord;
				orig_cord.cord_x = (game_area.orig_cord.cord_x + 4) + game_area.curr_col * block.width;
				orig_cord.cord_y = (game_area.orig_cord.cord_y + 2) + game_area.curr_row * block.height;
				print_block_cfg(game_area.rand_matrix[game_area.curr_row][game_area.curr_col], game_area, orig_cord, block, block_color, CHOSEN);

				orig_cord.cord_x = (game_area.orig_cord.cord_x + 4) + game_area.last_col * block.width;
				orig_cord.cord_y = (game_area.orig_cord.cord_y + 2) + game_area.last_row * block.height;
				print_block_cfg(game_area.rand_matrix[game_area.last_row][game_area.last_col], game_area, orig_cord, block, block_color, NORMAL);
			}
			else if (game_area.divided == 1)
			{
				Cord orig_cord;
				orig_cord.cord_x = (game_area.orig_cord.cord_x + 4) + game_area.curr_col * (block.width + 2);
				orig_cord.cord_y = (game_area.orig_cord.cord_y + 2) + game_area.curr_row * (block.height + 1);
				print_block_cfg(game_area.rand_matrix[game_area.curr_row][game_area.curr_col], game_area, orig_cord, block, block_color, CHOSEN);

				orig_cord.cord_x = (game_area.orig_cord.cord_x + 4) + game_area.last_col * (block.width + 2);
				orig_cord.cord_y = (game_area.orig_cord.cord_y + 2) + game_area.last_row * (block.height + 1);
				print_block_cfg(game_area.rand_matrix[game_area.last_row][game_area.last_col], game_area, orig_cord, block, block_color, NORMAL);
			}
		}
	}
	else if (direction == LEFT)
	{
		if (game_area.curr_col <= 0) game_area.curr_col = game_area.matrix_col - 1;
		else game_area.curr_col -= 1;

		if (game_area.rand_matrix[game_area.curr_row][game_area.curr_col] == 0)
		{
			go_cfg(game_area, block, block_color, direction);
		}
		else
		{
			if (game_area.divided != 1)
			{
				Cord orig_cord;
				orig_cord.cord_x = (game_area.orig_cord.cord_x + 4) + game_area.curr_col * block.width;
				orig_cord.cord_y = (game_area.orig_cord.cord_y + 2) + game_area.curr_row * block.height;
				print_block_cfg(game_area.rand_matrix[game_area.curr_row][game_area.curr_col], game_area, orig_cord, block, block_color, CHOSEN);

				orig_cord.cord_x = (game_area.orig_cord.cord_x + 4) + game_area.last_col * block.width;
				orig_cord.cord_y = (game_area.orig_cord.cord_y + 2) + game_area.last_row * block.height;
				print_block_cfg(game_area.rand_matrix[game_area.last_row][game_area.last_col], game_area, orig_cord, block, block_color, NORMAL);
			}
			else if (game_area.divided == 1)
			{
				Cord orig_cord;
				orig_cord.cord_x = (game_area.orig_cord.cord_x + 4) + game_area.curr_col * (block.width + 2);
				orig_cord.cord_y = (game_area.orig_cord.cord_y + 2) + game_area.curr_row * (block.height + 1);
				print_block_cfg(game_area.rand_matrix[game_area.curr_row][game_area.curr_col], game_area, orig_cord, block, block_color, CHOSEN);

				orig_cord.cord_x = (game_area.orig_cord.cord_x + 4) + game_area.last_col * (block.width + 2);
				orig_cord.cord_y = (game_area.orig_cord.cord_y + 2) + game_area.last_row * (block.height + 1);
				print_block_cfg(game_area.rand_matrix[game_area.last_row][game_area.last_col], game_area, orig_cord, block, block_color, NORMAL);
			}
		}
	}
	else if (direction == RIGHT)
	{
		if (game_area.curr_col >= game_area.matrix_col - 1) game_area.curr_col = 0;
		else game_area.curr_col += 1;

		if (game_area.rand_matrix[game_area.curr_row][game_area.curr_col] == 0)
		{
			go_cfg(game_area, block, block_color, direction);
		}
		else
		{
			if (game_area.divided != 1)
			{
				Cord orig_cord;
				orig_cord.cord_x = (game_area.orig_cord.cord_x + 4) + game_area.curr_col * block.width;
				orig_cord.cord_y = (game_area.orig_cord.cord_y + 2) + game_area.curr_row * block.height;
				print_block_cfg(game_area.rand_matrix[game_area.curr_row][game_area.curr_col], game_area, orig_cord, block, block_color, CHOSEN);

				orig_cord.cord_x = (game_area.orig_cord.cord_x + 4) + game_area.last_col * block.width;
				orig_cord.cord_y = (game_area.orig_cord.cord_y + 2) + game_area.last_row * block.height;
				print_block_cfg(game_area.rand_matrix[game_area.last_row][game_area.last_col], game_area, orig_cord, block, block_color, NORMAL);
			}
			else if (game_area.divided == 1)
			{
				Cord orig_cord;
				orig_cord.cord_x = (game_area.orig_cord.cord_x + 4) + game_area.curr_col * (block.width + 2);
				orig_cord.cord_y = (game_area.orig_cord.cord_y + 2) + game_area.curr_row * (block.height + 1);
				print_block_cfg(game_area.rand_matrix[game_area.curr_row][game_area.curr_col], game_area, orig_cord, block, block_color, CHOSEN);

				orig_cord.cord_x = (game_area.orig_cord.cord_x + 4) + game_area.last_col * (block.width + 2);
				orig_cord.cord_y = (game_area.orig_cord.cord_y + 2) + game_area.last_row * (block.height + 1);
				print_block_cfg(game_area.rand_matrix[game_area.last_row][game_area.last_col], game_area, orig_cord, block, block_color, NORMAL);
			}
		}
	}

	game_area.last_col = game_area.curr_col;
	game_area.last_row = game_area.curr_row;
}


//�ú������ڻس�/�������ȷ�Ϻϳɣ�������µĿɶ�ȡ�����ļ��汾ʹ�ã�
int cancel_confirm_cfg(Game_area game_area, Block block)
{
	Cord cord;
	int ret, maction;
	int keycode1, keycode2;
	int loop = 1;

	enable_mouse();
	setcursor(CURSOR_INVISIBLE);	//�رչ��

	while (loop)
	{
		/* �����/���̣�����ֵΪ���������е�ĳһ��, ��ǰ���λ����<X,Y>�� */
		ret = read_keyboard_and_mouse(cord.cord_x, cord.cord_y, maction, keycode1, keycode2);

		if (ret == CCT_MOUSE_EVENT)
		{
			if (game_area.divided != 1)
			{
				int block_cord_x = game_area.orig_cord.cord_x + 4 + game_area.curr_col * block.width;
				int block_cord_y = game_area.orig_cord.cord_y + 2 + game_area.curr_row * block.height;

				if ((cord.cord_x >= block_cord_x) && (cord.cord_x < block_cord_x + block.width) && (cord.cord_y >= block_cord_y) && (cord.cord_y < block_cord_y + block.height))
				{
					if (maction == MOUSE_LEFT_BUTTON_CLICK)
					{
						return CLICK;
					}
				}
				else return CANCEL;
			}

			else if (game_area.divided == 1)
			{
				int block_cord_x = game_area.orig_cord.cord_x + 4 + game_area.curr_col * (block.width + 2);
				int block_cord_y = game_area.orig_cord.cord_y + 2 + game_area.curr_row * (block.height + 1);

				if ((cord.cord_x >= block_cord_x) && (cord.cord_x < block_cord_x + block.width) && (cord.cord_y >= block_cord_y) && (cord.cord_y < block_cord_y + block.height))
				{
					if (maction == MOUSE_LEFT_BUTTON_CLICK)
					{
						return CLICK;
					}
				}
				else return CANCEL;
			}
		}

		else if (ret == CCT_KEYBOARD_EVENT)
		{
			if (keycode1 == 13) return CLICK;
			else return CANCEL;
		}
	}

	return 1;
}

//�ú�������������ɫ��ļ������䣨������µĿɶ�ȡ�����ļ��汾ʹ�ã�
void block_fall_cfg(Game_area &game_area, Block block, Block_color block_color)
{
	int temp;

	for (int i = 0; i < game_area.matrix_col; i++)
	{
		bool stat = 1;
		while (stat)
		{
			stat = 0;
			for (int j = game_area.matrix_row - 2; j >= 0; j--)
			{
				if (game_area.rand_matrix[j + 1][i] == 0 && game_area.rand_matrix[j][i] != 0)
				{
					block_move_cfg(game_area, block, block_color, j, i, DOWN);

					temp = game_area.rand_matrix[j + 1][i];
					game_area.rand_matrix[j + 1][i] = game_area.rand_matrix[j][i];
					game_area.rand_matrix[j][i] = temp;

					stat = 1;
				}
			}
		}
	}
}

//�ú������ڴ�ӡ����unicode�ַ�(���Զ�����ɫ�����ӳ�ʱ��������ļ��ж�ȡ��
void print_unicode_cfg(const char *str, const int bg_color, const int fg_color, const int n, int delay_time)
{
	const char *p;

	setcolor(bg_color, fg_color);

	for (int i = 0; i < n; i++)
	{
		for (p = str; *p; p++)
			putchar(*p);

		Sleep(delay_time);
	}
	setcolor();
}