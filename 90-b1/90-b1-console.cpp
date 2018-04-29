/*1751367 ��2 ����*/
#include <iostream>
#include <iomanip>
#include <ctime>
#include <cmath>
#include <cstdio>
#include <conio.h>
#include <Windows.h>
#include "..\common\cmd_console_tools.h"
#include "..\common\common.h"
#include "90-b1.h"
using namespace std;

extern "C"
{
#include "../common/common_cfgfile_tools.h"
}


//�ú������ڻس�/�������ȷ�ϼ���
int enter_click(int btn)
{
	int X, Y;
	int ret, maction;
	int keycode1, keycode2;
	int loop = 1;

	enable_mouse();
	setcursor(CURSOR_INVISIBLE);	//�رչ��

	while (loop)
	{
		/* �����/���̣�����ֵΪ���������е�ĳһ��, ��ǰ���λ����<X,Y>�� */
		ret = read_keyboard_and_mouse(X, Y, maction, keycode1, keycode2);

		if (btn == ENTER)
		{
			if (ret == CCT_MOUSE_EVENT)
			{
				if (maction == MOUSE_LEFT_BUTTON_CLICK)
				{
					return 1;
				}
			}
			else if (ret == CCT_KEYBOARD_EVENT)
			{
				if (keycode1 == 13)
				{
					return 1;
				}
			}
		}
		else if (btn == C)
		{
			if (ret == CCT_MOUSE_EVENT)
			{
				if (maction == MOUSE_LEFT_BUTTON_CLICK)
				{
					return 1;
				}
			}
			else if (ret == CCT_KEYBOARD_EVENT)
			{
				if (keycode1 == 'c' || keycode1 == 'C')
				{
					return 1;
				}
			}
		}
	}

	return 1;
}

//�ú��������ƶ���ѡ��ɫ��
void move(int(*rand_matrix)[10], char(*mark_matrix)[10], int row, int col, int &curr_row, int &curr_col, int &last_row, int &last_col, int type)
{
	int X = 0, Y = 0;
	int ret, maction;
	int keycode1, keycode2;
	int loop = 1;

	/*����һ��������������ã�
	�ڸĽ�ǰ�汾�У���������ƶ����Ƿ�λ�ú��ٴ��ƶ����߽��ϵķ��飬
	���ʱ�ķ��鲢û�б�ѡ�С�ԭ�����ڷǷ�λ���ƶ�ʱcurr_��last_��
	һֱ������ȡ�Ϊ���������⣬����һ���ж��Ƿ��ڷǷ�λ�õı�����
	���ӷǷ�λ�ûص��Ϸ�λ��ʱ�Խ��з���Ĵ�ӡ��*/
	bool illegal = 0;


	enable_mouse();
	setcursor(CURSOR_INVISIBLE);	//�رչ��

	if (type == UNDIVIDED)
	{
		while (loop) {
			/* �����/���̣�����ֵΪ���������е�ĳһ��, ��ǰ���λ����<X,Y>�� */
			ret = read_keyboard_and_mouse(X, Y, maction, keycode1, keycode2);

			if (ret == CCT_MOUSE_EVENT) {
				//����ǰ���λ�õ�����ת��Ϊ��Ӧ�������ˣ����ж�λ�õ�ǰλ���Ƿ�Ϸ�
				if (cord_to_rc(rand_matrix, row, col, X, Y, curr_row, curr_col, last_row, last_col, POPSTAR, UNDIVIDED))
				{
					//�����ǰ������ڷ�������һ�����ڷ��鲻ͬ�Ŵ�ӡλ����Ϣ������������ӡ������Ƶ��
					if ((curr_row != last_row) || (curr_col != last_col) || illegal)
					{
						//�ƶ��󽫵�ǰ��ѡ��ķ���ָ�
						for (int i = 0; i < row; i++)
						{
							for (int j = 0; j < col; j++)
							{
								if (mark_matrix[i][j] == '*') print_block(rand_matrix[i][j], 4 + j * 6, 3 + i * 3, POPSTAR, NORMAL);
							}
						}

						orig_mark(mark_matrix, row, col);

						print_block(rand_matrix[last_row][last_col], 4 + last_col * 6, 3 + last_row * 3, POPSTAR, NORMAL);
						print_block(rand_matrix[curr_row][curr_col], 4 + curr_col * 6, 3 + curr_row * 3, POPSTAR, CHOSEN);

						//��ӡ�����������λ��
						gotoxy(0, row * 3 + 4);
						cout << "                                          ";
						gotoxy(0, row * 3 + 4);
						cout << "[��ǰ���] " << char(curr_row + 65) << "��" << curr_col << "��";

						illegal = 0;

					}
				}
				else //λ�÷Ƿ�
				{
					if (!illegal)
					{
						print_block(rand_matrix[last_row][last_col], 4 + last_col * 6, 3 + last_row * 3, POPSTAR, NORMAL);

						gotoxy(0, row * 3 + 4);
						cout << "                                                                             ";
						gotoxy(0, row * 3 + 4);
						cout << "[��ǰ���]" << "λ�÷Ƿ�";

						illegal = 1;

						continue;
					}
				}

				//�������ֻ��Ҫ��������Ĳ���
				switch (maction)
				{
				case MOUSE_LEFT_BUTTON_CLICK:			//�������
					gotoxy(0, row * 3 + 4);
					cout << "                                       ";
					gotoxy(0, row * 3 + 4);
					cout << "ѡ����" << char(curr_row + 65) << "��" << curr_col << "��";
					setcursor(CURSOR_VISIBLE_NORMAL);//�ָ����
					return;
				}
			}

			else if (ret == CCT_KEYBOARD_EVENT)
			{
				switch (keycode1)
				{
				case 224:
					switch (keycode2) {
					case KB_ARROW_UP:
						go_up(rand_matrix, row, col, curr_row, curr_col, last_row, last_col, UNDIVIDED);
						gotoxy(0, row * 3 + 4);
						cout << "[��ǰ����] " << char(curr_row + 65) << "��" << curr_col << "��";
						break;
					case KB_ARROW_DOWN:
						go_down(rand_matrix, row, col, curr_row, curr_col, last_row, last_col, UNDIVIDED);
						gotoxy(0, row * 3 + 4);
						cout << "[��ǰ����] " << char(curr_row + 65) << "��" << curr_col << "��";
						break;
					case KB_ARROW_LEFT:
						go_left(rand_matrix, row, col, curr_row, curr_col, last_row, last_col, UNDIVIDED);
						gotoxy(0, row * 3 + 4);
						cout << "[��ǰ����] " << char(curr_row + 65) << "��" << curr_col << "��";
						break;
					case KB_ARROW_RIGHT:
						go_right(rand_matrix, row, col, curr_row, curr_col, last_row, last_col, UNDIVIDED);
						gotoxy(0, row * 3 + 4);
						cout << "[��ǰ����] " << char(curr_row + 65) << "��" << curr_col << "��";
						break;
					}

					//�ƶ��󽫵�ǰ��ѡ��ķ���ָ�
					for (int i = 0; i < row; i++)
					{
						for (int j = 0; j < col; j++)
						{
							if (mark_matrix[i][j] == '*' && (i != curr_row || j != curr_col)) print_block(rand_matrix[i][j], 4 + j * 6, 3 + i * 3, POPSTAR, NORMAL);
						}
					}

					orig_mark(mark_matrix, row, col);


					break;

				case 13:
					gotoxy(0, row * 3 + 4);
					cout << "                                       ";
					gotoxy(0, row * 3 + 4);
					cout << "ѡ����" << char(curr_row + 65) << "��" << curr_col << "��";
					setcursor(CURSOR_VISIBLE_NORMAL);//�ָ����
					return;
				}
			}
		}
	}
	else if (type == DIVIDED)
	{
		while (loop) {
			/* �����/���̣�����ֵΪ���������е�ĳһ��, ��ǰ���λ����<X,Y>�� */
			ret = read_keyboard_and_mouse(X, Y, maction, keycode1, keycode2);

			if (ret == CCT_MOUSE_EVENT) {
				//����ǰ���λ�õ�����ת��Ϊ��Ӧ�������ˣ����ж�λ�õ�ǰλ���Ƿ�Ϸ�
				if (cord_to_rc(rand_matrix, row, col, X, Y, curr_row, curr_col, last_row, last_col, POPSTAR, DIVIDED))
				{
					//�����ǰ������ڷ�������һ�����ڷ��鲻ͬ�Ŵ�ӡλ����Ϣ������������ӡ������Ƶ��
					if ((curr_row != last_row) || (curr_col != last_col) || illegal)
					{
						print_block(rand_matrix[last_row][last_col], 4 + last_col * 8, 3 + last_row * 4, POPSTAR, NORMAL);
						print_block(rand_matrix[curr_row][curr_col], 4 + curr_col * 8, 3 + curr_row * 4, POPSTAR, CHOSEN);

						//��ӡ�����������λ��
						gotoxy(0, row * 4 + 3);
						cout << "                                          ";
						gotoxy(0, row * 4 + 3);
						cout << "[��ǰ���] " << char(curr_row + 65) << "��" << curr_col << "��";

						illegal = 0;
					}
				}
				else //λ�÷Ƿ�
				{
					print_block(rand_matrix[last_row][last_col], 4 + last_col * 8, 3 + last_row * 4, POPSTAR, NORMAL);

					gotoxy(0, row * 4 + 3);
					cout << "[��ǰ���]" << "λ�÷Ƿ�";

					illegal = 1;
				}

				//�������ֻ��Ҫ��������Ĳ���
				switch (maction)
				{
				case MOUSE_LEFT_BUTTON_CLICK:			//�������
					gotoxy(0, row * 4 + 3);
					cout << "                                       ";
					gotoxy(0, row * 4 + 3);
					cout << "ѡ����" << char(curr_row + 65) << "��" << curr_col << "��";
					setcursor(CURSOR_VISIBLE_NORMAL);//�ָ����
					return;
				}
			}

			else if (ret == CCT_KEYBOARD_EVENT)
			{
				switch (keycode1)
				{
				case 224:
					switch (keycode2) {
					case KB_ARROW_UP:
						go_up(rand_matrix, row, col, curr_row, curr_col, last_row, last_col, DIVIDED);
						gotoxy(0, row * 4 + 3);
						cout << "[��ǰ����] " << char(curr_row + 65) << "��" << curr_col << "��";
						break;
					case KB_ARROW_DOWN:
						go_down(rand_matrix, row, col, curr_row, curr_col, last_row, last_col, DIVIDED);
						gotoxy(0, row * 4 + 3);
						cout << "[��ǰ����] " << char(curr_row + 65) << "��" << curr_col << "��";
						break;
					case KB_ARROW_LEFT:
						go_left(rand_matrix, row, col, curr_row, curr_col, last_row, last_col, DIVIDED);
						gotoxy(0, row * 4 + 3);
						cout << "[��ǰ����] " << char(curr_row + 65) << "��" << curr_col << "��";
						break;
					case KB_ARROW_RIGHT:
						go_right(rand_matrix, row, col, curr_row, curr_col, last_row, last_col, DIVIDED);
						gotoxy(0, row * 4 + 3);
						cout << "[��ǰ����] " << char(curr_row + 65) << "��" << curr_col << "��";
						break;
					}
					break;

				case 13:
					gotoxy(0, row * 4 + 3);
					cout << "                                       ";
					gotoxy(0, row * 4 + 3);
					cout << "ѡ����" << char(curr_row + 65) << "��" << curr_col << "��";
					setcursor(CURSOR_VISIBLE_NORMAL);//�ָ����
					return;
				}
			}
		}

		setcursor(CURSOR_VISIBLE_NORMAL);	//�򿪹��
	}
}

//�ú�������αͼ�ν����µ�һ������
void GUI_eliminate(int(*rand_matrix)[10], char(*mark_matrix)[10], int row, int col)
{
	eliminate(rand_matrix, mark_matrix, row, col);
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (mark_matrix[i][j] == '*') print_block(rand_matrix[i][j], 4 + j * 6, 3 + i * 3, POPSTAR, EMP);
		}
	}

}

//�ú���������������
void block_left(int(*rand_matrix)[10], int row, int col)
{
	int temp;
	bool stat = 1;

	while (stat)
	{
		stat = 0;
		for (int i = 1; i < col; i++)
		{
			if (rand_matrix[row - 1][i] != 0 && rand_matrix[row - 1][i - 1] == 0)
			{
				for (int j = row - 1; j >= 0; j--)
				{
					block_move(rand_matrix, j, i, POPSTAR, LEFT);

					temp = rand_matrix[j][i];
					rand_matrix[j][i] = rand_matrix[j][i - 1];
					rand_matrix[j][i - 1] = temp;
				}
				stat = 1;
			}
		}
	}
}

//�ú�������ִ��ѡ������֮��Ĳ���
int elmn_fall(int(*rand_matrix)[10], char(*mark_matrix)[10], int &row, int &col, int &curr_row, int &curr_col, int &score, int &total_score, int question)
{
	gotoxy(0, row * 3 + 4);
	cout << "                                                ";
	gotoxy(0, row * 3 + 4);
	cout << "��ͷ��/����ƶ�ȡ����ǰѡ�񣬻س���/��������ϳ�";

	mark(rand_matrix, mark_matrix, curr_row, curr_col, row, col);

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (mark_matrix[i][j] == '*') print_block(rand_matrix[i][j], 4 + j * 6, 3 + i * 3, POPSTAR, CHOSEN);
		}
	}

	//�û���һ��ѡ���ȷ��������ȡ��
	if (cancel_confirm(curr_row, curr_col))
	{
		//��ѡ�����������
		GUI_eliminate(rand_matrix, mark_matrix, row, col);

		if (question == F)
		{
			gotoxy(0, row * 3 + 4);
			cout << "                                                ";
			gotoxy(0, row * 3 + 4);
			cout << "�ϳ���ɣ��س���/�����������0";

			while (!enter_click(ENTER));
		}

		block_fall(rand_matrix, row, col);
		block_left(rand_matrix, row, col);
		score = elmn_score(mark_matrix, row, col);
		total_score += score;

		gotoxy(0, 0);
		cout << "                                                ";
		gotoxy(0, 0);
		cout << "���ε÷�:" << score << ' ' << "�ܷ�:" << total_score;

		if (question == F)
		{
			gotoxy(0, row * 3 + 4);
			cout << "                                                ";
			gotoxy(0, row * 3 + 4);
			setcolor(0, COLOR_HRED);
			cout << "���κϳɽ�������C/�����������һ���µĺϳ�";
			setcolor();

			while (!enter_click(C));
		}

		setcursor(CURSOR_VISIBLE_NORMAL);
		return 1;
	}
	else return 0;
}

//����ĿD��αͼ�ν����������ѡ��һ��ɫ�飨�޷ָ��ߣ�
void D_GUI_choose_undvd(int(*rand_matrix)[10], char(*mark_matrix)[10], int &row, int &col, int &score, int &total_score)
{
	//��ǰ��ԭ�򷽿������
	int curr_row = 0, curr_col = 0;
	//ѡ�񷽿���һ�����ڵķ�������
	int last_row = 0, last_col = 0;

	//��ʼ���ڲ�����
	orig_matrix(rand_matrix, row, col, POPSTAR);
	orig_mark(mark_matrix, row, col);

	//��ӡ�ⲿ���
	print_frame(row, col, POPSTAR, UNDIVIDED);

	//��ӡɫ��
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			print_block(rand_matrix[i][j], 4 + j * 6, 3 + i * 3, POPSTAR, NORMAL);
		}
	}

	gotoxy(0, 0);
	cout << "��Ļ��ǰ����Ϊ��" << 32 + (row - 8) * 3 << "��" << 55 + (col - 8) * 6 << "��";

	gotoxy(0, row * 3 + 4);
	cout << "��ͷ��/����ƶ����س���/�������ѡ�񲢽���";

	//��ʼ״̬�µ�һ������Ϊѡ��״̬
	print_block(rand_matrix[0][0], 4, 3, POPSTAR, CHOSEN);

	move(rand_matrix, mark_matrix, row, col, curr_row, curr_col, last_row, last_col, UNDIVIDED);
}

//����ĿE��αͼ�ν����������ѡ��һ��ɫ�飨�зָ��ߣ�
void E_GUI_choose_dvd(int(*rand_matrix)[10], char(*mark_matrix)[10], int &row, int &col, int &score, int &total_score)
{
	//��ǰ��ԭ�򷽿������
	int curr_row = 0, curr_col = 0;
	//ѡ�񷽿���һ�����ڵķ�������
	int last_row = 0, last_col = 0;

	//��ʼ���ڲ�����
	orig_matrix(rand_matrix, row, col, POPSTAR);
	orig_mark(mark_matrix, row, col);

	//��ӡ�ⲿ���
	print_frame(row, col, POPSTAR, DIVIDED);

	//��ӡɫ��
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			print_block(rand_matrix[i][j], 4 + j * 8, 3 + i * 4, POPSTAR, NORMAL);
		}
	}

	gotoxy(0, 0);
	cout << "��Ļ��ǰ����Ϊ��" << 39 + (row - 8) * 4 << "��" << 69 + (col - 8) * 8 << "��";

	gotoxy(0, row * 4 + 3);
	cout << "��ͷ��/����ƶ����س���/�������ѡ�񲢽���";

	//��ʼ״̬�µ�һ������Ϊѡ��״̬
	print_block(rand_matrix[0][0], 4, 3, POPSTAR, CHOSEN);

	move(rand_matrix, mark_matrix, row, col, curr_row, curr_col, last_row, last_col, DIVIDED);
}

//����ĿF��αͼ�ν������һ���������ֲ��裩
void F_GUI_eliminate(int(*rand_matrix)[10], char(*mark_matrix)[10], int &row, int &col, int &score, int &total_score, int question)
{
	//��ǰ��ѡ�񷽿������
	int curr_row = 0, curr_col = 0;
	//ѡ�񷽿���һ�����ڵķ�������
	int last_row = 0, last_col = 0;

	if (question == F)
	{
		//��ʼ���ڲ�����
		orig_matrix(rand_matrix, row, col, POPSTAR);
		orig_mark(mark_matrix, row, col);

		//��ӡ�ⲿ���
		print_frame(row, col, POPSTAR, UNDIVIDED);

		//��ӡɫ��
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				print_block(rand_matrix[i][j], 4 + j * 6, 3 + i * 3, POPSTAR, NORMAL);
			}
		}

		gotoxy(0, 0);
		cout << "��Ļ��ǰ����Ϊ��" << 32 + (row - 8) * 3 << "��" << 55 + (col - 8) * 6 << "��";
	}

	gotoxy(0, row * 3 + 4);
	cout << "��ͷ��/����ƶ����س���/�������ѡ�񲢽���";


	//��ʼʱ��һ�еĵ�һ��ɫ��Ϊѡ��״̬
	for (int i = 0; i < row; i++)
	{
		if (rand_matrix[i][0] != 0)
		{
			print_block(rand_matrix[i][0], 4, 3 + i * 3, POPSTAR, CHOSEN);
			curr_row = i;
			curr_col = 0;

			last_row = i;
			last_col = 0;
			break;
		}
	}

	int X = 0, Y = 0;
	int ret, maction;
	int keycode1, keycode2;
	int loop = 1;

	bool illegal = 0;

	enable_mouse();
	setcursor(CURSOR_INVISIBLE);	//�رչ��

	while (loop) {
		/* �����/���̣�����ֵΪ���������е�ĳһ��, ��ǰ���λ����<X,Y>�� */
		ret = read_keyboard_and_mouse(X, Y, maction, keycode1, keycode2);

		if (ret == CCT_MOUSE_EVENT) {
			//����ǰ���λ�õ�����ת��Ϊ��Ӧ�������ˣ����ж�λ�õ�ǰλ���Ƿ�Ϸ�
			if (cord_to_rc(rand_matrix, row, col, X, Y, curr_row, curr_col, last_row, last_col, POPSTAR, UNDIVIDED))
			{
				//�����ǰ������ڷ�������һ�����ڷ��鲻ͬ�Ŵ�ӡλ����Ϣ������������ӡ������Ƶ��
				if ((curr_row != last_row) || (curr_col != last_col) || illegal)
				{
					//�ƶ��󽫵�ǰ��ѡ��ķ���ָ�
					for (int i = 0; i < row; i++)
					{
						for (int j = 0; j < col; j++)
						{
							if (mark_matrix[i][j] == '*') print_block(rand_matrix[i][j], 4 + j * 6, 3 + i * 3, POPSTAR, NORMAL);
						}
					}

					orig_mark(mark_matrix, row, col);

					print_block(rand_matrix[last_row][last_col], 4 + last_col * 6, 3 + last_row * 3, POPSTAR, NORMAL);
					print_block(rand_matrix[curr_row][curr_col], 4 + curr_col * 6, 3 + curr_row * 3, POPSTAR, CHOSEN);

					//��ӡ�����������λ��
					gotoxy(0, row * 3 + 4);
					cout << "                                                                             ";
					gotoxy(0, row * 3 + 4);
					cout << "[��ǰ���] " << char(curr_row + 65) << "��" << curr_col << "��";

					illegal = 0;
				}
			}
			else //λ�÷Ƿ�
			{
				if (!illegal)
				{
					print_block(rand_matrix[last_row][last_col], 4 + last_col * 6, 3 + last_row * 3, POPSTAR, NORMAL);

					gotoxy(0, row * 3 + 4);
					cout << "                                                                             ";
					gotoxy(0, row * 3 + 4);
					cout << "[��ǰ���]" << "λ�÷Ƿ�";

					illegal = 1;

					continue;
				}
			}

			//�������ֻ��Ҫ��������Ĳ���
			switch (maction)
			{
			case MOUSE_LEFT_BUTTON_CLICK:			//�������
				if (judge_cord(rand_matrix, row, col, curr_row, curr_col) == 1)
				{
					if (question == F)
					{
						if (!elmn_fall(rand_matrix, mark_matrix, row, col, curr_row, curr_col, score, total_score, F)) continue;
						else return;
					}
					else if (question == G)
					{
						if (!elmn_fall(rand_matrix, mark_matrix, row, col, curr_row, curr_col, score, total_score, G)) continue;
						else return;
					}
				}
				else if (judge_cord(rand_matrix, row, col, curr_row, curr_col) == 0)
				{
					gotoxy(0, row * 3 + 4);
					cout << "                                       ";
					gotoxy(0, row * 3 + 4);
					setcolor(0, COLOR_HRED);
					cout << "��Χ����ֵͬ��";
					setcolor();
					cout << "��ͷ��/����ƶ����س���/�������ѡ��";
					continue;
				}
				else continue;
			}
		}

		else if (ret == CCT_KEYBOARD_EVENT)
		{
			switch (keycode1)
			{
			case 224:
				switch (keycode2) {
				case KB_ARROW_UP:
					go_up(rand_matrix, row, col, curr_row, curr_col, last_row, last_col, UNDIVIDED);
					gotoxy(0, row * 3 + 4);
					cout << "                                                                             ";
					gotoxy(0, row * 3 + 4);
					cout << "[��ǰ����] " << char(curr_row + 65) << "��" << curr_col << "��";
					break;
				case KB_ARROW_DOWN:
					go_down(rand_matrix, row, col, curr_row, curr_col, last_row, last_col, UNDIVIDED);
					gotoxy(0, row * 3 + 4);
					cout << "                                                                             ";
					gotoxy(0, row * 3 + 4);
					cout << "[��ǰ����] " << char(curr_row + 65) << "��" << curr_col << "��";
					break;
				case KB_ARROW_LEFT:
					go_left(rand_matrix, row, col, curr_row, curr_col, last_row, last_col, UNDIVIDED);
					gotoxy(0, row * 3 + 4);
					cout << "                                                                             ";
					gotoxy(0, row * 3 + 4);
					cout << "[��ǰ����] " << char(curr_row + 65) << "��" << curr_col << "��";
					break;
				case KB_ARROW_RIGHT:
					go_right(rand_matrix, row, col, curr_row, curr_col, last_row, last_col, UNDIVIDED);
					gotoxy(0, row * 3 + 4);
					cout << "                                                                             ";
					gotoxy(0, row * 3 + 4);
					cout << "[��ǰ����] " << char(curr_row + 65) << "��" << curr_col << "��";
					break;
				}

				//�ƶ��󽫵�ǰ��ѡ��ķ���ָ�
				for (int i = 0; i < row; i++)
				{
					for (int j = 0; j < col; j++)
					{
						if (mark_matrix[i][j] == '*' && (i != curr_row || j != curr_col)) print_block(rand_matrix[i][j], 4 + j * 6, 3 + i * 3, POPSTAR, NORMAL);
					}
				}

				orig_mark(mark_matrix, row, col);
				break;

			case 13:
				if (judge_cord(rand_matrix, row, col, curr_row, curr_col))
				{
					if (question == F)
					{
						if (!elmn_fall(rand_matrix, mark_matrix, row, col, curr_row, curr_col, score, total_score, F)) continue;
						else return;
					}
					else if (question == G)
					{
						if (!elmn_fall(rand_matrix, mark_matrix, row, col, curr_row, curr_col, score, total_score, G)) continue;
						else return;
					}
				}
				else
				{
					gotoxy(0, row * 3 + 4);
					cout << "                                       ";
					gotoxy(0, row * 3 + 4);
					setcolor(0, COLOR_HRED);
					cout << "��Χ����ֵͬ��";
					setcolor();
					cout << "��ͷ��/����ƶ����س���/�������ѡ��";
					continue;
				}
			}
		}
	}
}

//����ĿG��αͼ�ν���������
void G_GUI_complete(int(*rand_matrix)[10], char(*mark_matrix)[10], int &row, int &col, int &score, int &total_score)
{
	//��ǰ��ѡ�񷽿������
	int curr_row = 0, curr_col = 0;
	//ѡ�񷽿���һ�����ڵķ�������
	int last_row = 0, last_col = 0;

	//��ʼ���ڲ�����
	orig_matrix(rand_matrix, row, col, POPSTAR);
	orig_mark(mark_matrix, row, col);

	//��ӡ�ⲿ���
	print_frame(row, col, POPSTAR, UNDIVIDED);

	//��ӡɫ��
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			print_block(rand_matrix[i][j], 4 + j * 6, 3 + i * 3, POPSTAR, NORMAL);
		}
	}

	gotoxy(0, 0);
	cout << "��Ļ��ǰ����Ϊ��" << 32 + (row - 8) * 3 << "��" << 55 + (col - 8) * 6 << "��";

	while (1)
	{
		F_GUI_eliminate(rand_matrix, mark_matrix, row, col, score, total_score, G);

		if (end_judge(rand_matrix, row, col))
		{
			gotoxy(0, row * 3 + 4);
			cout << "                                                         ";
			gotoxy(0, row * 3 + 4);
			setcolor(0, COLOR_HRED);
			cout << "���ؽ�����ʣ��" << remain_num(rand_matrix, row, col) << "����س���������һ�أ�";
			setcolor();

			while (_getch() != '\r');

			return;
		}
		else continue;
	}
}

//�ɶ�ȡ�����ļ���αͼ�ν���������
void GUI_full_cfg(const char *cfgfile_name)
{
	Cord orig_cord; //��������ڴ�ӡɫ���ʱ��������궨λ��ʱ����Ҫ

	int score; //��¼�����õ�

	//������Ϸ����ṹ�����
	Game_area game_area;
	//ɫ��ṹ�����
	Block popstar_block;

	popstar_block.type = POPSTAR;
	//ɫ����ɫ��Ϣ����
	Block_color block_color;

	//�������ļ��ж�ȡ��Ϣ
	read_game_cfg(cfgfile_name, game_area, popstar_block, block_color);

	//print_game_cfg(game_area, popstar_block, block_color);
	//return;

	//��ʼ���ڲ�����
	orig_matrix(game_area.rand_matrix, game_area.matrix_row, game_area.matrix_col, POPSTAR);
	orig_mark(game_area.mark_matrix, game_area.matrix_row, game_area.matrix_col);

	//��ӡ��Ϸ����
	print_game_area(game_area, popstar_block);

	//��ӡɫ��
	for (int i = 0; i < game_area.matrix_row; i++)
	{
		for (int j = 0; j < game_area.matrix_col; j++)
		{
			switch (game_area.divided)
			{
			case 1:
				orig_cord.cord_x = (game_area.orig_cord.cord_x + 4) + j * (popstar_block.width + 2);
				orig_cord.cord_y = (game_area.orig_cord.cord_y + 2) + i * (popstar_block.height + 1);
				break;

			case 0:
				orig_cord.cord_x = (game_area.orig_cord.cord_x + 4) + j * popstar_block.width;
				orig_cord.cord_y = (game_area.orig_cord.cord_y + 2) + i * popstar_block.height;
				break;
			}

			print_block_cfg(game_area.rand_matrix[i][j], game_area, orig_cord, popstar_block, block_color, NORMAL);
		}
	}

	while (1)
	{
		//��ʼʱ��һ�еĵ�һ��ɫ��Ϊѡ��״̬
		for (int i = 0; i < game_area.matrix_row; i++)
		{
			if (game_area.rand_matrix[i][0] != 0)
			{
				game_area.curr_row = i;
				game_area.curr_col = 0;

				game_area.last_row = i;
				game_area.last_col = 0;

				switch (game_area.divided)
				{
				case 1:
					orig_cord.cord_x = (game_area.orig_cord.cord_x + 4) + game_area.curr_col * (popstar_block.width + 2);
					orig_cord.cord_y = (game_area.orig_cord.cord_y + 2) + game_area.curr_row * (popstar_block.height + 1);
					break;

				case 0:
					orig_cord.cord_x = (game_area.orig_cord.cord_x + 4) + game_area.curr_col * popstar_block.width;
					orig_cord.cord_y = (game_area.orig_cord.cord_y + 2) + game_area.curr_row * popstar_block.height;
					break;
				}

				print_block_cfg(game_area.rand_matrix[game_area.curr_row][game_area.curr_col], game_area, orig_cord, popstar_block, block_color, CHOSEN);

				break;
			}
		}

		if (game_area.bot_info)
		{
			if (game_area.divided)
			{
				gotoxy(0, game_area.orig_cord.cord_y + game_area.matrix_row*(popstar_block.height + 1) + 3);
			}
			else gotoxy(0, game_area.orig_cord.cord_y + game_area.matrix_row*popstar_block.height + 3);
			
			setcolor(game_area.norm_info_color.bg_color, game_area.norm_info_color.fg_color);
			cout << "��ͷ��/����ƶ����س���/�������ѡ�񲢽���";
			setcolor();
		}

		kb_move_cfg(game_area, popstar_block, block_color);

		if (!judge_cord(game_area.rand_matrix, game_area.matrix_row, game_area.matrix_col, game_area.curr_row, game_area.curr_col))
		{
			if (game_area.bot_info)
			{
				if (game_area.divided)
				{
					gotoxy(0, game_area.orig_cord.cord_y + game_area.matrix_row*(popstar_block.height + 1) + 3);
				}
				else gotoxy(0, game_area.orig_cord.cord_y + game_area.matrix_row*popstar_block.height + 3);
				cout << "                                                              ";
				setcolor(game_area.warning_color.bg_color, game_area.warning_color.fg_color);

				if (game_area.divided)
				{
					gotoxy(42, game_area.orig_cord.cord_y + game_area.matrix_row*(popstar_block.height + 1) + 3);
				}
				else gotoxy(42, game_area.orig_cord.cord_y + game_area.matrix_row*popstar_block.height + 3);
				cout << "��Χ����ֵͬ!";
				setcolor();
			}

			switch (game_area.divided)
			{
			case 1:
				orig_cord.cord_x = (game_area.orig_cord.cord_x + 4) + game_area.curr_col * (popstar_block.width + 2);
				orig_cord.cord_y = (game_area.orig_cord.cord_y + 2) + game_area.curr_row * (popstar_block.height + 1);
				break;

			case 0:
				orig_cord.cord_x = (game_area.orig_cord.cord_x + 4) + game_area.curr_col * popstar_block.width;
				orig_cord.cord_y = (game_area.orig_cord.cord_y + 2) + game_area.curr_row * popstar_block.height;
				break;
			}

			print_block_cfg(game_area.rand_matrix[game_area.curr_row][game_area.curr_col], game_area, orig_cord, popstar_block, block_color, NORMAL);
			continue;
		}

		elmn_fall_cfg(game_area, popstar_block, block_color, score);

		if (end_judge(game_area.rand_matrix, game_area.matrix_row, game_area.matrix_col))
		{
			if (game_area.bot_info)
			{
				if (game_area.divided)
				{
					gotoxy(0, game_area.orig_cord.cord_y + game_area.matrix_row*(popstar_block.height + 1) + 3);
				}
				else gotoxy(0, game_area.orig_cord.cord_y + game_area.matrix_row*popstar_block.height + 3);
				cout << "                                                              ";
				if (game_area.divided)
				{
					gotoxy(0, game_area.orig_cord.cord_y + game_area.matrix_row*(popstar_block.height + 1) + 3);
				}
				else gotoxy(0, game_area.orig_cord.cord_y + game_area.matrix_row*popstar_block.height + 3);
				setcolor(game_area.warning_color.bg_color, game_area.warning_color.fg_color);
				cout << "���ؽ�����ʣ��" << remain_num(game_area.rand_matrix, game_area.matrix_row, game_area.matrix_col) << "����س���������һ�أ�";
				setcolor();
			}

			while (_getch() != '\r');

			return;
		}
		else continue;
	}
}

//�ú�������ִ��ѡ������֮��Ĳ���(��Ͽɶ�ȡ�����ļ��汾ʹ�ã�
int elmn_fall_cfg(Game_area &game_area, Block block,Block_color block_color,int &score)
{
	Cord orig_cord; //��λ��
	
	if (game_area.bot_info)
	{
		gotoxy(0, game_area.orig_cord.cord_y + game_area.matrix_row*(block.height + 1) + 3);
		setcolor(game_area.norm_info_color.bg_color, game_area.norm_info_color.fg_color);
		cout << "��ͷ��/����ƶ����س���/�������ѡ�񲢽���";
		setcolor();
	}

	mark(game_area.rand_matrix, game_area.mark_matrix, game_area.curr_row, game_area.curr_col, game_area.matrix_row, game_area.matrix_col);

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

				print_block_cfg(game_area.rand_matrix[i][j], game_area, orig_cord, block, block_color, CHOSEN);
			}
		}
	}

	if (cancel_confirm_cfg(game_area, block))
	{
		//��ѡ����ɾ��
		GUI_eliminate_cfg(game_area, block, block_color);

		block_fall_cfg(game_area, block, block_color);
		block_left_cfg(game_area, block, block_color);

		score = elmn_score(game_area.mark_matrix, game_area.matrix_row, game_area.matrix_col);
		game_area.total_score += score;

		if (game_area.top_info)
		{
			gotoxy(0, 0);
			setcolor(game_area.norm_info_color.bg_color, game_area.norm_info_color.fg_color);
			cout << "���ε÷�:" << score << ' ' << "�ܵ÷�:" << game_area.total_score;
			setcolor();
		}

		setcursor(CURSOR_VISIBLE_NORMAL);
		return 1;
	}
	else return 0;
}

//�ú�������αͼ�ν����µ�һ������(��Ͽɶ�ȡ�����ļ��汾ʹ�ã�
void GUI_eliminate_cfg(Game_area &game_area, Block block, Block_color block_color)
{
	Cord orig_cord; //��λ�õ�
	
	eliminate(game_area.rand_matrix, game_area.mark_matrix, game_area.matrix_row, game_area.matrix_col);
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

				print_block_cfg(game_area.rand_matrix[i][j], game_area, orig_cord, block, block_color, EMP);
			}
		}
	}
}

//�ú���������������
void block_left_cfg(Game_area &game_area, Block block, Block_color block_color)
{
	int temp;
	bool stat = 1;

	while (stat)
	{
		stat = 0;
		for (int i = 1; i < game_area.matrix_col; i++)
		{
			if (game_area.rand_matrix[game_area.matrix_row - 1][i] != 0 && game_area.rand_matrix[game_area.matrix_row - 1][i - 1] == 0)
			{
				for (int j = game_area.matrix_row - 1; j >= 0; j--)
				{
					block_move_cfg(game_area, block, block_color, j, i, LEFT);

					temp = game_area.rand_matrix[j][i];
					game_area.rand_matrix[j][i] = game_area.rand_matrix[j][i - 1];
					game_area.rand_matrix[j][i - 1] = temp;
				}
				stat = 1;
			}
		}
	}
}

//�������ļ��ж�ȡ������Ϣ��ʹ��C���ԵĹ��ߺ�������
int read_game_cfg(const char *cfg_name, Game_area &game_area, Block &block, Block_color &block_color)
{
	FILE *cfgfile;
	
	cfgfile = open_cfgfile(cfg_name, OPEN_OPT_RDONLY);

	if (cfgfile == NULL)
	{
		cout << "�������ļ�ʧ��";
		return 0;
	}

	//����ȷ����Ϸ�����Ƿ���Ҫ�ָ���
	char value;
	item_get_value(cfgfile, "�߿�����", "��Ҫ�ָ���", &value, TYPE_CHARACTER);

	if (value == 'y' || value == 'Y')
	{
		game_area.divided = 1;
	}
	else if (value == 'n' || value == 'N')
	{
		game_area.divided = 0;
	}
	else game_area.divided = 1;


	//ȷ���Ƿ���Ҫ��ʾ���к�
	item_get_value(cfgfile, "�߿�����", "�к��б���ʾ", &value, TYPE_CHARACTER);
	if (value == 'y' || value == 'Y')
	{
		game_area.show_row_col_number = 1;
	}
	else if (value == 'n' || value == 'N')
	{
		game_area.show_row_col_number = 0;
	}
	else game_area.show_row_col_number = 1;

	//�Ƿ���ʾ����״̬��
	item_get_value(cfgfile, "״̬������", "��״̬��", &value, TYPE_CHARACTER);
	if (value == 'y' || value == 'Y')
	{
		game_area.top_info = 1;
	}
	else if (value == 'n' || value == 'N')
	{
		game_area.top_info = 0;
	}
	else game_area.top_info = 1;

	item_get_value(cfgfile, "״̬������", "��״̬��", &value, TYPE_CHARACTER);
	if (value == 'y' || value == 'Y')
	{
		game_area.bot_info = 1;
	}
	else if (value == 'n' || value == 'N')
	{
		game_area.bot_info = 0;
	}
	else game_area.bot_info = 1;

	//��ȡ��Ϸ��������д�С
	if (item_get_value(cfgfile, "��������", "����", &game_area.matrix_row, TYPE_INT))
	{
		if (game_area.matrix_row < 8 || game_area.matrix_row > 10)
		{
			//������Χȡȱʡֵ
			game_area.matrix_row = 10;
		}
	}
	else game_area.matrix_row = 10;

	if (item_get_value(cfgfile, "��������", "����", &game_area.matrix_col, TYPE_INT))
	{
		if (game_area.matrix_col < 8 || game_area.matrix_col > 10)
		{
			//������Χȡȱʡֵ
			game_area.matrix_col = 10;
		}
	}
	else game_area.matrix_col = 10;

	//��ȡ�·����к��Ҳ����
	item_get_value(cfgfile, "��������", "�·�����", &game_area.extra_line, TYPE_INT);
	if (game_area.extra_line < 0 || game_area.extra_line>15)
	{
		game_area.extra_line = 0;
	}

	item_get_value(cfgfile, "��������", "�Ҳ����", &game_area.extra_col, TYPE_INT);
	if (game_area.extra_col < 0 || game_area.extra_col>15)
	{
		game_area.extra_col = 0;
	}

	//��ȡ��Ϸ�����ӡ�ӳ�ʱ��
	item_get_value(cfgfile, "��������", "���߿���ʱ", &game_area.delay_time, TYPE_INT);
	{
		if (game_area.delay_time < 0 || game_area.delay_time>100)
		{
			game_area.delay_time = 0;
		}
	}

	//��ȡɫ�������ӳ�ʱ��
	item_get_value(cfgfile, "��������", "ɫ���ƶ���ʱ", &block.move_delay_time, TYPE_INT);
	{
		if (block.move_delay_time < 3 || block.move_delay_time>100)
		{
			block.move_delay_time = 10;
		}
	}

	//��ȡ��Ϸ����߿���ַ�
	item_get_value(cfgfile, "�߿�����", "�߿���-���Ͻ�", game_area.border[0], TYPE_STRING);
	item_get_value(cfgfile, "�߿�����", "�߿���-���½�", game_area.border[1], TYPE_STRING);
	item_get_value(cfgfile, "�߿�����", "�߿���-���Ͻ�", game_area.border[2], TYPE_STRING);
	item_get_value(cfgfile, "�߿�����", "�߿���-���½�", game_area.border[3], TYPE_STRING);
	item_get_value(cfgfile, "�߿�����", "�߿���-����", game_area.border[4], TYPE_STRING);
	item_get_value(cfgfile, "�߿�����", "�߿���-����", game_area.border[5], TYPE_STRING);
	item_get_value(cfgfile, "�߿�����", "�߿���-�Ϸָ���", game_area.border[6], TYPE_STRING);
	item_get_value(cfgfile, "�߿�����", "�߿���-�·ָ���", game_area.border[7], TYPE_STRING);
	item_get_value(cfgfile, "�߿�����", "�߿���-��ָ���", game_area.border[8], TYPE_STRING);
	item_get_value(cfgfile, "�߿�����", "�߿���-�ҷָ��߽�", game_area.border[9], TYPE_STRING);
	item_get_value(cfgfile, "�߿�����", "�߿���-�зָ���", game_area.border[10], TYPE_STRING);

	//��ȡ��Ϸ������ɫ
	item_get_value(cfgfile, "�߿�����", "����ɫ", &game_area.game_area_color.bg_color, TYPE_INT);
	if (game_area.game_area_color.bg_color < 0 || game_area.game_area_color.bg_color>15)
	{
		//����ɫ������Χ��ȡȱʡֵ
		game_area.game_area_color.bg_color = 15;
	}

	item_get_value(cfgfile, "�߿�����", "ǰ��ɫ", &game_area.game_area_color.fg_color, TYPE_INT);
	if (game_area.game_area_color.fg_color < 0 || game_area.game_area_color.fg_color>15)
	{
		//ǰ��ɫ������Χ��ȡȱʡֵ
		game_area.game_area_color.fg_color = 0;
	}

	//��ȡ��ʾ��Ϣ����ɫ
	item_get_value(cfgfile, "״̬������", "�������ֱ���ɫ", &game_area.norm_info_color.bg_color, TYPE_INT);
	if (game_area.norm_info_color.bg_color < -1 || game_area.norm_info_color.bg_color>15)
	{
		//����ɫ������Χ��ȡȱʡֵ
		game_area.game_area_color.bg_color = -1;
	}

	item_get_value(cfgfile, "״̬������", "��������ǰ��ɫ", &game_area.norm_info_color.fg_color, TYPE_INT);
	if (game_area.norm_info_color.fg_color < -1 || game_area.norm_info_color.fg_color>15)
	{
		//����ɫ������Χ��ȡȱʡֵ
		game_area.game_area_color.fg_color = -1;
	}

	if (game_area.game_area_color.bg_color == -1)
	{
		game_area.game_area_color.bg_color = game_area.game_area_color.bg_color;
	}
	if (game_area.game_area_color.fg_color == -1)
	{
		game_area.game_area_color.fg_color = game_area.game_area_color.fg_color;
	}

	/***************************************************************/

	item_get_value(cfgfile, "״̬������", "�������ֱ���ɫ", &game_area.warning_color.bg_color, TYPE_INT);
	if (game_area.warning_color.bg_color < -1 || game_area.warning_color.bg_color>15)
	{
		//����ɫ������Χ��ȡȱʡֵ
		game_area.warning_color.bg_color = -1;
	}

	item_get_value(cfgfile, "״̬������", "��������ǰ��ɫ", &game_area.warning_color.fg_color, TYPE_INT);
	if (game_area.warning_color.fg_color < -1 || game_area.warning_color.fg_color>15)
	{
		game_area.warning_color.fg_color = -1;
	}

	if (game_area.warning_color.bg_color == -1)
	{
		game_area.warning_color.bg_color = game_area.game_area_color.bg_color;
	}
	if (game_area.warning_color.fg_color == -1)
	{
		game_area.warning_color.fg_color = game_area.game_area_color.fg_color;
	}

	//��ȡ��Ϸ�������ʼ����
	item_get_value(cfgfile, "��������", "��ʼ�к�", &game_area.orig_cord.cord_x, TYPE_INT);
	if (game_area.orig_cord.cord_x < 0 || game_area.orig_cord.cord_x>15)
	{
		game_area.orig_cord.cord_x = 0;
	}

	item_get_value(cfgfile, "��������", "��ʼ�к�", &game_area.orig_cord.cord_y, TYPE_INT);
	if (game_area.orig_cord.cord_y < 0 || game_area.orig_cord.cord_y > 15)
	{
		game_area.orig_cord.cord_y = 0;
	}

	//��ȡɫ��ĳ��Ϳ�
	item_get_value(cfgfile, "ɫ������", "���", &block.width, TYPE_INT);

	if (block.width % 2 != 0)
	{
		//ɫ���ȶ�ȡ���������Զ�+1
		block.width++;
	}

	if (block.width < 6 || block.width>16)
	{
		block.width = 6;
	}

	item_get_value(cfgfile, "ɫ������", "�߶�", &block.height, TYPE_INT);

	if (block.height < 3 || block.height > 6)
	{
		block.height = 6;
	}

	//��ȡɫ��ı߿��ַ�
	item_get_value(cfgfile, "ɫ������", "�߿���-���Ͻ�", block.frame[0], TYPE_STRING);
	item_get_value(cfgfile, "ɫ������", "�߿���-���½�", block.frame[1], TYPE_STRING);
	item_get_value(cfgfile, "ɫ������", "�߿���-���Ͻ�", block.frame[2], TYPE_STRING);
	item_get_value(cfgfile, "ɫ������", "�߿���-���½�", block.frame[3], TYPE_STRING);
	item_get_value(cfgfile, "ɫ������", "�߿���-����", block.frame[4], TYPE_STRING);
	item_get_value(cfgfile, "ɫ������", "�߿���-����", block.frame[5], TYPE_STRING);

	/*�ڶ�ȡɫ����ɫ��ʱ����Ҫ����ʵ�ʵ���Ϸ���ͣ��ϳ�ʮ��Ҫ�õ�ʮһ��ɫ����ɫ
	����������ֻ��Ҫ�õ�ǰ���*/
	if (block.type == POPSTAR)
	{
		item_get_value(cfgfile, "ɫ������", "ɫ��1-ǰ��ɫ", &block_color.block_color_1.fg_color, TYPE_INT);
		if (block_color.block_color_1.fg_color < 0 || block_color.block_color_1.fg_color>15)
		{
			block_color.block_color_1.fg_color = 0;
		}

		item_get_value(cfgfile, "ɫ������", "ɫ��1-����ɫ", &block_color.block_color_1.bg_color, TYPE_INT);
		if (block_color.block_color_1.bg_color < 0 || block_color.block_color_1.bg_color>15)
		{
			block_color.block_color_1.bg_color = 9;
		}

		item_get_value(cfgfile, "ɫ������", "ɫ��2-ǰ��ɫ", &block_color.block_color_2.fg_color, TYPE_INT);
		if (block_color.block_color_2.fg_color < 0 || block_color.block_color_2.fg_color>15)
		{
			block_color.block_color_2.fg_color = 0;
		}

		item_get_value(cfgfile, "ɫ������", "ɫ��2-����ɫ", &block_color.block_color_2.bg_color, TYPE_INT);
		if (block_color.block_color_2.bg_color < 0 || block_color.block_color_2.bg_color>15)
		{
			block_color.block_color_2.bg_color = 10;
		}

		item_get_value(cfgfile, "ɫ������", "ɫ��3-ǰ��ɫ", &block_color.block_color_3.fg_color, TYPE_INT);
		if (block_color.block_color_3.fg_color < 0 || block_color.block_color_3.fg_color>15)
		{
			block_color.block_color_3.fg_color = 0;
		}

		item_get_value(cfgfile, "ɫ������", "ɫ��3-����ɫ", &block_color.block_color_3.bg_color, TYPE_INT);
		if (block_color.block_color_3.bg_color < 0 || block_color.block_color_3.bg_color>15)
		{
			block_color.block_color_2.bg_color = 11;
		}

		item_get_value(cfgfile, "ɫ������", "ɫ��4-ǰ��ɫ", &block_color.block_color_4.fg_color, TYPE_INT);
		if (block_color.block_color_4.fg_color < 0 || block_color.block_color_4.fg_color>15)
		{
			block_color.block_color_4.fg_color = 12;
		}

		item_get_value(cfgfile, "ɫ������", "ɫ��4-����ɫ", &block_color.block_color_4.bg_color, TYPE_INT);
		if (block_color.block_color_4.bg_color < 0 || block_color.block_color_4.bg_color>15)
		{
			block_color.block_color_4.bg_color = 12;
		}

		item_get_value(cfgfile, "ɫ������", "ɫ��5-ǰ��ɫ", &block_color.block_color_5.fg_color, TYPE_INT);
		if (block_color.block_color_5.fg_color < 0 || block_color.block_color_5.fg_color>15)
		{
			block_color.block_color_5.fg_color = 0;
		}

		item_get_value(cfgfile, "ɫ������", "ɫ��5-����ɫ", &block_color.block_color_5.bg_color, TYPE_INT);
		if (block_color.block_color_5.bg_color < 0 || block_color.block_color_5.bg_color>15)
		{
			block_color.block_color_5.bg_color = 13;
		}
	}

	//��ȡѡ��ɫ����ɫ
	item_get_value(cfgfile, "ɫ������", "ѡ��ɫ�鱳��ɫ", &block_color.chosen_block_color.bg_color, TYPE_INT);
	if (block_color.chosen_block_color.bg_color < 0 || block_color.chosen_block_color.bg_color > 15)
	{
		block_color.chosen_block_color.bg_color = 5;
	}

	if (item_get_value(cfgfile, "ɫ������", "ѡ��ɫ��ǰ��ɫ", &block_color.chosen_block_color.fg_color, TYPE_INT))
	{
		if (block_color.chosen_block_color.fg_color < 0 || block_color.chosen_block_color.fg_color > 15)
		{
			block_color.chosen_block_color.fg_color = 15;
		}
	}
	else block_color.chosen_block_color.fg_color = 15;

	close_cfgfile(cfgfile);

	return 1;
}