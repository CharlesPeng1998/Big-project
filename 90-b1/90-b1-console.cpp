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