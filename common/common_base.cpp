/*1751367 ��2 ����*/
#include <iostream>
#include <iomanip>
#include <ctime>
#include <cmath>
#include <cstdio>
#include <conio.h>
#include <Windows.h>
#include "cmd_console_tools.h"
#include "common.h"
using namespace std;

//�˵����������մ�Ų˵����ָ�����飬�����û����뷵��һ���ַ�
char menu(const char *items[], int n)
{
	//��¼���˵���ĳ���
	int max_len = int(strlen(items[0]));
	for (int i = 1; i < n; i++)
	{
		if (strlen(items[i]) > max_len) max_len = int(strlen(items[i]));
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



