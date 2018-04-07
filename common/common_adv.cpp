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

//�ú��������û�����������(���Թ��ã�
void input_row_col(int &row, int &col,int game)
{
	bool judge_row = 0, judge_col = 0;

	int curr_x;
	int curr_y; //������¼��ǰ����λ��

	getxy(curr_x, curr_y);//��ȡ��ǰ���λ�ã��Ա����������ʱ��귵����ԭ����λ��

	while (!judge_row)
	{
		gotoxy(curr_x, curr_y);
		
		switch (game)
		{
		case POPSTAR:cout << "����������<8-10>: "; break;
		case MAKE10:cout << "����������<5-8>: "; break;
		}
		
		cin >> row;

		switch (game)
		{
		case POPSTAR:
		{
			//���������Ƿ�Ϸ�����ͬ
			if (cin.fail() || row < 8 || row > 10)
			{
				cin.clear();
				cin.ignore(cin.rdbuf()->in_avail(), '\n');
				cout << "���벻�Ϸ�������������     ";
				continue;
			}
			else judge_row = 1;
			break;
		}

		case MAKE10:
		{
			//���������Ƿ�Ϸ�����ͬ
			if (cin.fail() || row < 5 || row > 8)
			{
				cin.clear();
				cin.ignore(cin.rdbuf()->in_avail(), '\n');
				cout << "���벻�Ϸ�������������     ";
				continue;
			}
			else judge_row = 1;
			break;
		}
		}
	}

	getxy(curr_x, curr_y);
	cout << "                      ";
	gotoxy(curr_x, curr_y);//��������������ϴ����µĴ�����ʾ����ͬ

	while (!judge_col)
	{
		gotoxy(curr_x, curr_y);
		switch (game)
		{
		case POPSTAR:cout << "����������<8-10>: "; break;
		case MAKE10:cout << "����������<5-10>: "; break;
		}
		cin >> col;

		switch (game)
		{
		case POPSTAR:
		{
			//���������Ƿ�Ϸ�����ͬ
			if (cin.fail() || row < 8 || row > 10)
			{
				cin.clear();
				cin.ignore(cin.rdbuf()->in_avail(), '\n');
				cout << "���벻�Ϸ�������������     ";
				continue;
			}
			else judge_col = 1;
			break;
		}

		case MAKE10:
		{
			//���������Ƿ�Ϸ�����ͬ
			if (cin.fail() || row < 5 || row > 10)
			{
				cin.clear();
				cin.ignore(cin.rdbuf()->in_avail(), '\n');
				cout << "���벻�Ϸ�������������     ";
				continue;
			}
			else judge_col = 1;
			break;
		}
		}
	}

	getxy(curr_x, curr_y);
	cout << "                      ";
	gotoxy(curr_x, curr_y);
}

//�ú�������ÿ����Ϸ��ʼǰ���������������
void orig_matrix(int(*rand_matrix)[10], int row, int col, int game)
{
	switch (game)
	{
	case POPSTAR:
	{
		srand((unsigned int)(time(0)));//�����������

		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				switch (rand() % 5)
				{
				case 0:rand_matrix[i][j] = 1; break;
				case 1:rand_matrix[i][j] = 2; break;
				case 2:rand_matrix[i][j] = 3; break;
				case 3:rand_matrix[i][j] = 4; break;
				case 4:rand_matrix[i][j] = 5; break;
				}
			}
		}
		break;
	}

	case MAKE10:
	{
		srand((unsigned int)(time(0)));//�����������

									   //1-3�ȸ���������
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				switch (rand() % 3)
				{
				case 0:rand_matrix[i][j] = 1; break;
				case 1:rand_matrix[i][j] = 2; break;
				case 2:rand_matrix[i][j] = 3; break;
				}
			}
		}
		break;
	}
	}
}

//�ú������ڳ�ʼ��������飬������(���Թ��ã�
void orig_mark(char(*mark_matrix)[10], int row, int col)
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			mark_matrix[i][j] = '0';
		}
	}
}

//�ú������������а汾����ĸ+�����������룬���ж������Ƿ�Ϸ�(���Թ��ã�
void input_cord(int(*rand_matrix)[10], int row, int col, char &alpha, int &num)
{
	int curr_x, curr_y;//���ں����û�����Ƿ�ʱ���λ�õķ���

	while (1)
	{
		cout << endl << "������ĸ+������ʽ[��: c2]�����������: ";
		getxy(curr_x, curr_y);//�õ���ǰ����λ��

		while (1)
		{
			gotoxy(curr_x, curr_y);
			cin >> alpha;
			cin >> num;

			if (alpha >= 97) alpha -= 32;//������Сд��ĸ��������Ҫת��Ϊ��д��ĸ

			if (cin.fail() || int(alpha - 65) < 0 || int(alpha - 65) > row - 1 || num<0 || num>col - 1)
			{
				cin.clear();
				cin.ignore(cin.rdbuf()->in_avail(), '\n');
				cout << "�����������������       ";
				continue;
			}
			else break;
		}

		cout << "����Ϊ" << alpha << "��" << num << "��                    " << endl;

		//�ж�����λ���Ƿ�Ϸ������Ƿ�Ϊ0ֵ
		if (!rand_matrix[alpha - 65][num])
		{
			cout << "����ľ�������λ��Ϊ0���Ƿ�λ�ã�������������" << endl;
			continue;
		}

		//�ж�ѡ��������Χ�Ƿ������ֵͬ
		if (!judge_cord(rand_matrix, row, col, alpha - 65, num))
		{
			cout << "����ľ������괦����ֵͬ������������" << endl;
			continue;
		}
		else break;
	}
}

//�ú��������ж��û�ѡ��������Χ�Ƿ����������ֵͬ(���Թ��ã�
int judge_cord(int(*rand_matrix)[10], int row, int col, int curr_row, int curr_col)
{
	bool judge_cord = 0;

	if (rand_matrix[curr_row][curr_col] == 0) return 2;

	//�����ĸ�if��������ж�ѡ��������Χ�Ƿ������ֵͬ
	if (curr_row > 0 && rand_matrix[curr_row - 1][curr_col] == rand_matrix[curr_row][curr_col] && rand_matrix[curr_row][curr_col] != 0)
	{
		judge_cord = 1;
	}
	else if (curr_row < row - 1 && rand_matrix[curr_row + 1][curr_col] == rand_matrix[curr_row][curr_col] && rand_matrix[curr_row][curr_col] != 0)
	{
		judge_cord = 1;
	}
	else if (curr_col > 0 && rand_matrix[curr_row][curr_col - 1] == rand_matrix[curr_row][curr_col] && rand_matrix[curr_row][curr_col] != 0)
	{
		judge_cord = 1;
	}
	else if (curr_col < col - 1 && rand_matrix[curr_row][curr_col + 1] == rand_matrix[curr_row][curr_col] && rand_matrix[curr_row][curr_col] != 0)
	{
		judge_cord = 1;
	}

	return judge_cord;
}

//�ú������ڴ�ӡ�ڲ����飨���Թ��ã�
void print_matirx(int(*rand_matrix)[10], int row, int col)
{
	cout << "  |";
	for (int i = 0; i < col; i++)
	{
		cout << "  " << i;
	}
	cout << endl;
	cout << "--+";
	for (int i = 0; i < col; i++)
	{
		cout << "---";
	}
	cout << endl;

	for (int i = 0; i < row; i++)
	{
		cout << char(i + 65) << " |";
		for (int j = 0; j < col; j++)
		{
			cout << "  ";
			if (rand_matrix[i][j] == 0)
			{
				setcolor(COLOR_HPINK, 0);
				cout << rand_matrix[i][j];
				setcolor();
			}
			else cout << rand_matrix[i][j];
		}
		cout << endl;
	}
}

//�ú������ڴ�ӡ��Ǿ��󣨿��Թ��ã�
void print_mark(char(*mark_matrix)[10], int row, int col)
{
	cout << "  |";
	for (int i = 0; i < col; i++)
	{
		cout << "  " << i;
	}
	cout << endl;
	cout << "--+";
	for (int i = 0; i < col; i++)
	{
		cout << "---";
	}
	cout << endl;

	for (int i = 0; i < row; i++)
	{
		cout << char(i + 65) << " |";
		for (int j = 0; j < col; j++)
		{
			cout << "  " << mark_matrix[i][j];
		}
		cout << endl;
	}
}

//�ú������ڴ�ӡ�ڲ����飨��ͬɫ��ʶ��(���Թ��ã�
void print_color_matrix(int(*rand_matrix)[10], char(*mark_matrix)[10], int row, int col)
{
	cout << "  |";
	for (int i = 0; i < col; i++)
	{
		cout << "  " << i;
	}
	cout << endl;
	cout << "--+";
	for (int i = 0; i < col; i++)
	{
		cout << "---";
	}
	cout << endl;

	for (int i = 0; i < row; i++)
	{
		cout << char(i + 65) << " |";
		for (int j = 0; j < col; j++)
		{
			cout << "  ";
			if (mark_matrix[i][j] == '*')
			{
				setcolor(COLOR_HPINK, 0);
				cout << rand_matrix[i][j];
				setcolor();
			}
			else cout << rand_matrix[i][j];
		}
		cout << endl;
	}
}

//�ú�����������end����С�ⷵ�����˵�
void back_to_menu()
{
	int x, y;//�����������ʱ��귵��ԭ����λ��
	char btm[4];//back-to-menu

	cout << endl << "��С�������������End����...";
	getxy(x, y);
	cin >> btm;

	while ((btm[0] != 'e' && btm[0] != 'E') || (btm[1] != 'n' && btm[1] != 'N') || (btm[2] != 'd' && btm[2] != 'D'))
	{
		cout << "�����������������";
		gotoxy(x, y);
		cin >> btm;
	}
}

//�ú������ڴ�ӡ����unicode�ַ�(���Զ�����ɫ��
void print_unicode(const char *str, const int bg_color, const int fg_color, const int n)
{
	const char *p;

	setcolor(bg_color, fg_color);

	for (int i = 0; i < n; i++)
	{
		for (p = str; *p; p++)
			putchar(*p);

		Sleep(1);
	}
	setcolor();
}

/*�ú��������û�ȷ���Ƿ�������ͬ����Թ���)
enquire1��enquire2�ֱ���ѯ���������Σ����ݲ�ͬ��Ϸ��ѯ�ʴ��벻ͬ�Ĳ���*/
char confirm_combine(const char *enquire1, const char *enquire2, char input_alpha, int input_num)
{
	char confirm;
	cout << enquire1 << input_alpha << input_num << enquire2 << "<Y/N/Q>: ";

	while (confirm = _getch())
	{
		if (confirm == 'y' || confirm == 'Y') return 'y';

		else if (confirm == 'n' || confirm == 'N') return 'n';

		else if (confirm == 'q' || confirm == 'Q') return 'q';

		else continue;
	}

	return 1;
}

/*�����ĸ������ֱ����ڼ��̲�����������������ƶ�*/
void go_up(int(*rand_matrix)[10], int row, int col, int &curr_row, int &curr_col, int &last_row, int &last_col, int type,int game)
{
	if (game == POPSTAR)
	{
		//����ǰɫ��λ������������Ҫ���������ƻ�
		if (curr_row <= 0) curr_row = row - 1;
		else curr_row -= 1;

		if (rand_matrix[curr_row][curr_col] == 0)
		{
			curr_row -= 1;
			switch (type)
			{
			case UNDIVIDED:go_up(rand_matrix, row, col, curr_row, curr_col, last_row, last_col, UNDIVIDED); break;
			case DIVIDED:go_up(rand_matrix, row, col, curr_row, curr_col, last_row, last_col, DIVIDED); break;
			}
		}
		else
		{
			switch (type)
			{
			case UNDIVIDED:
				print_block(rand_matrix[curr_row][curr_col], 4 + curr_col * 6, 3 + curr_row * 3, POPSTAR, CHOSEN);
				print_block(rand_matrix[last_row][last_col], 4 + last_col * 6, 3 + last_row * 3, POPSTAR, NORMAL);
				break;
			case DIVIDED:
				print_block(rand_matrix[curr_row][curr_col], 4 + curr_col * 8, 3 + curr_row * 4, POPSTAR, CHOSEN);
				print_block(rand_matrix[last_row][last_col], 4 + last_col * 8, 3 + last_row * 4, POPSTAR, NORMAL);
				break;
			}

		}

		last_row = curr_row; last_col = curr_col;
	}
	else if (game == MAKE10)
	{
		//����һ�������ӡ��ɫ
		if (curr_row == 0) curr_row = row - 1;
		else curr_row -= 1;

		print_block(rand_matrix[curr_row][curr_col], 2 + curr_col * 8, 2 + curr_row * 4, MAKE10, CHOSEN);
		//ԭ�����ӡԭɫ
		print_block(rand_matrix[last_row][last_col], 2 + last_col * 8, 2 + last_row * 4, MAKE10, NORMAL);

		last_row = curr_row; last_col = curr_col;
	}
}

void go_down(int(*rand_matrix)[10], int row, int col, int &curr_row, int &curr_col, int &last_row, int &last_col, int type, int game)
{
	if (game == POPSTAR)
	{
		//����ǰɫ��λ������������Ҫ���������ƻ�
		if (curr_row >= row - 1) curr_row = 0;
		else curr_row += 1;

		if (rand_matrix[curr_row][curr_col] == 0)
		{
			curr_row += 1;
			switch (type)
			{
			case UNDIVIDED:go_down(rand_matrix, row, col, curr_row, curr_col, last_row, last_col, UNDIVIDED); break;
			case DIVIDED:go_down(rand_matrix, row, col, curr_row, curr_col, last_row, last_col, DIVIDED); break;
			}
		}
		else
		{
			switch (type)
			{
			case UNDIVIDED:
				print_block(rand_matrix[curr_row][curr_col], 4 + curr_col * 6, 3 + curr_row * 3, POPSTAR, CHOSEN);
				print_block(rand_matrix[last_row][last_col], 4 + last_col * 6, 3 + last_row * 3, POPSTAR, NORMAL);
				break;
			case DIVIDED:
				print_block(rand_matrix[curr_row][curr_col], 4 + curr_col * 8, 3 + curr_row * 4, POPSTAR, CHOSEN);
				print_block(rand_matrix[last_row][last_col], 4 + last_col * 8, 3 + last_row * 4, POPSTAR, NORMAL);
				break;
			}
		}

		last_row = curr_row; last_col = curr_col;
	}
	else if (game == MAKE10)
	{
		//����һ�������ӡ��ɫ
		if (curr_row == row - 1) curr_row = 0;
		else curr_row += 1;

		print_block(rand_matrix[curr_row][curr_col], 2 + curr_col * 8, 2 + curr_row * 4, MAKE10, CHOSEN);
		//ԭ�����ӡԭɫ
		print_block(rand_matrix[last_row][last_col], 2 + last_col * 8, 2 + last_row * 4, MAKE10, NORMAL);

		last_row = curr_row; last_col = curr_col;
	}
}

void go_right(int(*rand_matrix)[10], int row, int col, int &curr_row, int &curr_col, int &last_row, int &last_col, int type, int game)
{
	if (game == POPSTAR)
	{
		//����ǰɫ��λ������������Ҫ���������ƻ�
		if (curr_col >= col - 1) curr_col = 0;
		else curr_col += 1;

		if (rand_matrix[curr_row][curr_col] == 0)
		{
			switch (type)
			{
			case UNDIVIDED:go_right(rand_matrix, row, col, curr_row, curr_col, last_row, last_col, UNDIVIDED); break;
			case DIVIDED:go_right(rand_matrix, row, col, curr_row, curr_col, last_row, last_col, DIVIDED); break;
			}
		}
		else
		{
			switch (type)
			{
			case UNDIVIDED:
				print_block(rand_matrix[curr_row][curr_col], 4 + curr_col * 6, 3 + curr_row * 3, POPSTAR, CHOSEN);
				print_block(rand_matrix[last_row][last_col], 4 + last_col * 6, 3 + last_row * 3, POPSTAR, NORMAL);
				break;
			case DIVIDED:
				print_block(rand_matrix[curr_row][curr_col], 4 + curr_col * 8, 3 + curr_row * 4, POPSTAR, CHOSEN);
				print_block(rand_matrix[last_row][last_col], 4 + last_col * 8, 3 + last_row * 4, POPSTAR, NORMAL);
				break;
			}
		}

		last_row = curr_row; last_col = curr_col;
	}
	else if (game == MAKE10)
	{
		//����һ�������ӡ��ɫ
		if (curr_col == col - 1) curr_col = 0;
		else curr_col += 1;

		print_block(rand_matrix[curr_row][curr_col], 2 + curr_col * 8, 2 + curr_row * 4, MAKE10, CHOSEN);
		//ԭ�����ӡԭɫ
		print_block(rand_matrix[last_row][last_col], 2 + last_col * 8, 2 + last_row * 4, MAKE10, NORMAL);

		last_row = curr_row; last_col = curr_col;
	}
}

void go_left(int(*rand_matrix)[10], int row, int col, int &curr_row, int &curr_col, int &last_row, int &last_col, int type, int game)
{
	if (game == POPSTAR)
	{
		//����ǰɫ��λ������������Ҫ���������ƻ�
		if (curr_col <= 0) curr_col = col - 1;
		else curr_col -= 1;

		if (rand_matrix[curr_row][curr_col] == 0)
		{
			switch (type)
			{
			case UNDIVIDED:go_left(rand_matrix, row, col, curr_row, curr_col, last_row, last_col, UNDIVIDED); break;
			case DIVIDED:go_left(rand_matrix, row, col, curr_row, curr_col, last_row, last_col, DIVIDED); break;
			}
		}
		else
		{
			switch (type)
			{
			case UNDIVIDED:
				print_block(rand_matrix[curr_row][curr_col], 4 + curr_col * 6, 3 + curr_row * 3, POPSTAR, CHOSEN);
				print_block(rand_matrix[last_row][last_col], 4 + last_col * 6, 3 + last_row * 3, POPSTAR, NORMAL);
				break;
			case DIVIDED:
				print_block(rand_matrix[curr_row][curr_col], 4 + curr_col * 8, 3 + curr_row * 4, POPSTAR, CHOSEN);
				print_block(rand_matrix[last_row][last_col], 4 + last_col * 8, 3 + last_row * 4, POPSTAR, NORMAL);
				break;
			}
		}

		last_row = curr_row; last_col = curr_col;
	}
	else if (game == MAKE10)
	{
		//����һ�������ӡ��ɫ
		if (curr_col == 0) curr_col = col - 1;
		else curr_col -= 1;

		print_block(rand_matrix[curr_row][curr_col], 2 + curr_col * 8, 2 + curr_row * 4, MAKE10, CHOSEN);
		//ԭ�����ӡԭɫ
		print_block(rand_matrix[last_row][last_col], 2 + last_col * 8, 2 + last_row * 4, MAKE10, NORMAL);

		last_row = curr_row; last_col = curr_col;
	}
}

//�ú������ڻس�/�������ȷ�Ϻϳ�
int cancel_confirm(int curr_row, int curr_col,int game)
{
	int X = 0, Y = 0;
	int ret, maction;
	int keycode1, keycode2;
	int loop = 1;

	enable_mouse();
	setcursor(CURSOR_INVISIBLE);	//�رչ��

	while (loop)
	{
		/* �����/���̣�����ֵΪ���������е�ĳһ��, ��ǰ���λ����<X,Y>�� */
		ret = read_keyboard_and_mouse(X, Y, maction, keycode1, keycode2);

		if (ret == CCT_MOUSE_EVENT)
		{
			if (game == POPSTAR)
			{
				if ((X >= (4 + curr_col * 6) && X < (10 + curr_col * 6)) && (Y >= (3 + curr_row * 3) && Y < (6 + curr_row * 3)))
				{
					if (maction == MOUSE_LEFT_BUTTON_CLICK)
					{
						return CLICK;
					}
				}
				else return CANCEL;
			}
			else if (game == MAKE10)
			{
				if ((X >= (2 + curr_col * 8) && X < (10 + curr_col * 8)) && (Y >= (2 + curr_row * 4) && Y < (6 + curr_row * 4)))
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

//�ú�������������ɫ��ļ�������
void block_fall(int(*rand_matrix)[10], int row, int col, int game)
{
	int temp;

	for (int i = 0; i < col; i++)
	{
		bool stat = 1;
		while (stat)
		{
			stat = 0;
			for (int j = row - 2; j >= 0; j--)
			{
				if (rand_matrix[j + 1][i] == 0 && rand_matrix[j][i] != 0)
				{
					if (game == POPSTAR) block_move(rand_matrix, j, i, POPSTAR, DOWN);
					else if (game == MAKE10) block_move(rand_matrix, j, i, MAKE10, DOWN);

					temp = rand_matrix[j + 1][i];
					rand_matrix[j + 1][i] = rand_matrix[j][i];
					rand_matrix[j][i] = temp;

					stat = 1;
				}
			}
		}
	}

}

//�ú������ڽ���������ת��Ϊָ��������
bool cord_to_rc(int(*rand_matrix)[10], int row, int col, int cord_x, int cord_y, int &curr_row, int &curr_col, int &last_row, int &last_col, int game, int type)
{
	//����ǰѡ��������Ϊ��һ��ѡ������
	last_row = curr_row;
	last_col = curr_col;

	//�����жϸ�������λ���Ƿ�Ϸ�
	bool legal_row = 0, legal_col = 0, legal_value = 0;

	switch (game)
	{
	case POPSTAR:
	{
		switch (type)
		{
		case UNDIVIDED:
			for (int i = 0; i < col; i++)
			{
				if (cord_x >= (4 + i * 6) && cord_x < (10 + i * 6))
				{
					curr_col = i;
					legal_col = 1;
				}
			}
			for (int i = 0; i < row; i++)
			{
				if (cord_y >= (3 + i * 3) && cord_y < (6 + i * 3))
				{
					curr_row = i;
					legal_row = 1;
				}
			}

			if (rand_matrix[curr_row][curr_col] != 0) legal_value = 1;

			return (legal_row && legal_col && legal_value);

		case DIVIDED:
			for (int i = 0; i < col; i++)
			{
				if (cord_x >= (4 + i * 8) && cord_x < (12 + i * 8))
				{
					curr_col = i;
					legal_col = 1;
				}
			}
			for (int i = 0; i < row; i++)
			{
				if (cord_y >= (3 + i * 4) && cord_y < (7 + i * 4))
				{
					curr_row = i;
					legal_row = 1;
				}
			}

			if (rand_matrix[curr_row][curr_col] != 0) legal_value = 1;

			return (legal_row && legal_col && legal_value);
		}
	}
	case MAKE10:
	{
		for (int i = 0; i < col; i++)
		{
			if (cord_x >= (2 + i * 8) && cord_x < (10 + i * 8))
			{
				curr_col = i;
				legal_col = 1;
			}
		}
		for (int i = 0; i < row; i++)
		{
			if (cord_y >= (2 + i * 4) && cord_y < (6 + i * 4))
			{
				curr_row = i;
				legal_row = 1;
			}
		}

		if (rand_matrix[curr_row][curr_col] != 0) legal_value = 1;

		return (legal_row && legal_col && legal_value);
	}
	}

	return 1;
}