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
#include "90-b0.h"
#include "../90-b1/90-b1.h"
using namespace std;

//�ú�����������ϲ�ʱƵ����Ч
void print_shiny(int value, int cord_x, int cord_y)
{
	for (int i = 0; i < 3; i++)

	{
		int X = cord_x, Y = cord_y;
		print_block(value, cord_x, cord_y, MAKE10, CHOSEN);
		Sleep(100);
		//����ֵ�Ĳ�ͬ��ӡ��ͬ��ɫ����
		print_block(value, cord_x, cord_y, MAKE10, NORMAL);
		Sleep(100);

	}
	setcolor();
}

//�ú������ںϳ�ʮ�����ƶ�ѡ��ɫ��
void kb_move(int(*rand_matrix)[10], char(*mark_matrix)[10], int row, int col, int &curr_row, int &curr_col, int &last_row, int &last_col)
{
	int X = 0, Y = 0;
	int ret, maction;
	int keycode1, keycode2;
	int loop = 1;

	setcursor(CURSOR_INVISIBLE);

	while (loop)
	{
		ret = read_keyboard_and_mouse(X, Y, maction, keycode1, keycode2);

		if (ret == CCT_KEYBOARD_EVENT)
		{
			switch (keycode1)
			{
			case 224:
				switch (keycode2) {
				case KB_ARROW_UP:
					go_up(rand_matrix, row, col, curr_row, curr_col, last_row, last_col, UNDIVIDED, MAKE10);
					gotoxy(0, row * 4 + 2);
					cout << "                                                  ";
					gotoxy(0, row * 4 + 2);
					cout << "[��ǰ����] " << char(curr_row + 65) << "��" << curr_col << "��";
					break;
				case KB_ARROW_DOWN:
					go_down(rand_matrix, row, col, curr_row, curr_col, last_row, last_col, UNDIVIDED, MAKE10);
					gotoxy(0, row * 4 + 2);
					cout << "                                                  ";
					gotoxy(0, row * 4 + 2);
					cout << "[��ǰ����] " << char(curr_row + 65) << "��" << curr_col << "��";
					break;
				case KB_ARROW_LEFT:
					go_left(rand_matrix, row, col, curr_row, curr_col, last_row, last_col, UNDIVIDED, MAKE10);
					gotoxy(0, row * 4 + 2);
					cout << "                                                  ";
					gotoxy(0, row * 4 + 2);
					cout << "[��ǰ����] " << char(curr_row + 65) << "��" << curr_col << "��";
					break;
				case KB_ARROW_RIGHT:
					go_right(rand_matrix, row, col, curr_row, curr_col, last_row, last_col, UNDIVIDED, MAKE10);
					gotoxy(0, row * 4 + 2);
					cout << "                                                  ";
					gotoxy(0, row * 4 + 2);
					cout << "[��ǰ����] " << char(curr_row + 65) << "��" << curr_col << "��";
					break;
				}
				//�ƶ��󽫵�ǰ��ѡ��ķ���ָ�
				for (int i = 0; i < row; i++)
				{
					for (int j = 0; j < col; j++)
					{
						if (mark_matrix[i][j] == '*' && (i != curr_row || j != curr_col)) print_block(rand_matrix[i][j], 2 + j * 8, 2 + i * 4, MAKE10, NORMAL);
					}
				}

				orig_mark(mark_matrix, row, col);
				break;
			case 13:
				return;
			}
		}
	}
}

//�ú������ڼ���ȷ�ϼ���
int kb_confirm()
{
	int X = 0, Y = 0;
	int ret, maction;
	int keycode1, keycode2;
	int loop = 1;

	enable_mouse();
	setcursor(CURSOR_INVISIBLE);	//�رչ��

	while (loop)
	{
		ret = read_keyboard_and_mouse(X, Y, maction, keycode1, keycode2);

		if (ret == CCT_KEYBOARD_EVENT)
		{
			if (keycode1 == 13) return CLICK;
			else return CANCEL;
		}
	}

	return 1;
}

//�ú�������αͼ�ν����¶��ڲ�������кϳɼ�һ����
int GUI_combine(int(*rand_matrix)[10], char(*mark_matrix)[10], int row, int col, int curr_row, int curr_col)
{
	int score = 0;//��¼�û��÷�
	int target = rand_matrix[curr_row][curr_col];

	//�������������㲢��Ŀ������һ
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (mark_matrix[i][j] == '*')
			{
				rand_matrix[i][j] = 0;
				score += target * 3;
			}
		}
	}
	rand_matrix[curr_row][curr_col] = target + 1;

	return score;
}

//�ú������ںϳ�ʮ���+�����ƶ�ѡ��ɫ��
void kb_mouse_move(int(*rand_matrix)[10], char(*mark_matrix)[10], int row, int col, int &curr_row, int &curr_col, int &last_row, int &last_col)
{
	int X = 0, Y = 0;
	int ret, maction;
	int keycode1, keycode2;
	int loop = 1;

	bool illegal = 0;

	enable_mouse();
	setcursor(CURSOR_INVISIBLE);	//�رչ��

	while (loop)
	{
		ret = read_keyboard_and_mouse(X, Y, maction, keycode1, keycode2);

		if (ret == CCT_MOUSE_EVENT) {
			//����ǰ���λ�õ�����ת��Ϊ��Ӧ�������ˣ����ж�λ�õ�ǰλ���Ƿ�Ϸ�
			if (cord_to_rc(rand_matrix, row, col, X, Y, curr_row, curr_col, last_row, last_col, MAKE10, UNDIVIDED))
			{
				//�����ǰ������ڷ�������һ�����ڷ��鲻ͬ�Ŵ�ӡλ����Ϣ������������ӡ������Ƶ��
				if ((curr_row != last_row) || (curr_col != last_col) || illegal)
				{
					//�ƶ��󽫵�ǰ��ѡ��ķ���ָ�
					for (int i = 0; i < row; i++)
					{
						for (int j = 0; j < col; j++)
						{
							if (mark_matrix[i][j] == '*') print_block(rand_matrix[i][j], 2 + j * 8, 2 + i * 4, MAKE10, NORMAL);
						}
					}

					orig_mark(mark_matrix, row, col);

					print_block(rand_matrix[last_row][last_col], 2 + last_col * 8, 2 + last_row * 4, MAKE10, NORMAL);
					print_block(rand_matrix[curr_row][curr_col], 2 + curr_col * 8, 2 + curr_row * 4, MAKE10, CHOSEN);

					//��ӡ�����������λ��
					gotoxy(0, row * 4 + 2);
					cout << "                                                              ";
					gotoxy(0, row * 4 + 2);
					cout << "[��ǰ���] " << char(curr_row + 65) << "��" << curr_col << "��";

					illegal = 0;

				}
			}
			else //λ�÷Ƿ�
			{
				if (!illegal)
				{
					print_block(rand_matrix[last_row][last_col], 2 + last_col * 8, 2 + last_row * 4, MAKE10, NORMAL);

					gotoxy(0, row * 4 + 2);
					cout << "                                                                             ";
					gotoxy(0, row * 4 + 2);
					cout << "[��ǰ���]" << "λ�÷Ƿ�";

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
					go_up(rand_matrix, row, col, curr_row, curr_col, last_row, last_col, UNDIVIDED, MAKE10);
					gotoxy(0, row * 4 + 2);
					cout << "                                                  ";
					gotoxy(0, row * 4 + 2);
					cout << "[��ǰ����] " << char(curr_row + 65) << "��" << curr_col << "��";
					break;
				case KB_ARROW_DOWN:
					go_down(rand_matrix, row, col, curr_row, curr_col, last_row, last_col, UNDIVIDED, MAKE10);
					gotoxy(0, row * 4 + 2);
					cout << "                                                  ";
					gotoxy(0, row * 4 + 2);
					cout << "[��ǰ����] " << char(curr_row + 65) << "��" << curr_col << "��";
					break;
				case KB_ARROW_LEFT:
					go_left(rand_matrix, row, col, curr_row, curr_col, last_row, last_col, UNDIVIDED, MAKE10);
					gotoxy(0, row * 4 + 2);
					cout << "                                                  ";
					gotoxy(0, row * 4 + 2);
					cout << "[��ǰ����] " << char(curr_row + 65) << "��" << curr_col << "��";
					break;
				case KB_ARROW_RIGHT:
					go_right(rand_matrix, row, col, curr_row, curr_col, last_row, last_col, UNDIVIDED, MAKE10);
					gotoxy(0, row * 4 + 2);
					cout << "                                                  ";
					gotoxy(0, row * 4 + 2);
					cout << "[��ǰ����] " << char(curr_row + 65) << "��" << curr_col << "��";
					break;
				}
				//�ƶ��󽫵�ǰ��ѡ��ķ���ָ�
				for (int i = 0; i < row; i++)
				{
					for (int j = 0; j < col; j++)
					{
						if (mark_matrix[i][j] == '*' && (i != curr_row || j != curr_col)) print_block(rand_matrix[i][j], 2 + j * 8, 2 + i * 4, MAKE10, NORMAL);
					}
				}

				orig_mark(mark_matrix, row, col);
				break;
			case 13:
				return;
			}
		}
	}
}

//����Ŀ�壺αͼ�ν�����ʾ��ʼ���飨�޷ָ��ߣ�
void five_GUI_dsp_undvd(int(*rand_matrix)[10], int row, int col)
{
	orig_matrix(rand_matrix, row, col, MAKE10);
	print_frame(row, col, MAKE10, UNDIVIDED);

	//��ӡɫ��
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			print_block(rand_matrix[i][j], 2 + j * 6, 2 + i * 3, MAKE10, NORMAL);
		}
	}

	gotoxy(0, 0);
	cout << "��Ļ��ǰ����Ϊ: " << 22 + (row - 5) * 3 << "��" << 35 + (col - 5) * 6 << "��";

	gotoxy(0, row * 3 + 4);
	cout << endl;
}

//����Ŀ����αͼ�ν�����ʾ��ʼ���飨�зָ��ߣ�
void six_GUI_dsp_dvd(int(*rand_matrix)[10], int row, int col)
{
	orig_matrix(rand_matrix, row, col, MAKE10);
	print_frame(row, col, MAKE10, DIVIDED);

	//��ӡɫ��
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			print_block(rand_matrix[i][j], 2 + j * 8, 2 + i * 4, MAKE10, NORMAL);
		}
	}

	gotoxy(0, 0);
	cout << "��Ļ��ǰ����Ϊ: " << 26 + (row - 5) * 4 << "��" << 43 + (col - 5) * 8 << "��";

	gotoxy(0, row * 4 + 2);

}

//����Ŀ�ߣ�αͼ�ν������ü�ͷ��ѡ��ǰɫ��
void seven_kb_choose(int(*rand_matrix)[10], char(*mark_matrix)[10], int row, int col)
{
	int curr_row = 0, curr_col = 0;
	int last_row = 0, last_col = 0;

	print_block(rand_matrix[0][0], 2, 2, MAKE10, CHOSEN);

	gotoxy(0, row * 4 + 2);
	cout << "��ͷ��/����ƶ����س���/�������ѡ�񲢽���";

	kb_move(rand_matrix, mark_matrix, row, col, curr_row, curr_col, last_row, last_col);

	gotoxy(0, row * 4 + 2);
	cout << "                                                  ";
	gotoxy(0, row * 4 + 2);
	cout << "ѡ����" << char(curr_row + 65) << "��" << curr_col << "��" << endl;

	setcursor(CURSOR_VISIBLE_NORMAL);
}

//����Ŀ�ˣ�αͼ�ν������һ�κϳɣ��ֲ��裩
void eight_GUI_combine(int(*rand_matrix)[10], char(*mark_matrix)[10], int row, int col, int &goal, int &score, int &total_score)
{
	int curr_row = 0, curr_col = 0;
	int last_row = 0, last_col = 0;

	print_block(rand_matrix[0][0], 2, 2, MAKE10, CHOSEN);

	gotoxy(0, row * 4 + 2);
	cout << "��ͷ��/����ƶ����س���/�������ѡ�񲢽���";

	while (1)
	{
		kb_move(rand_matrix, mark_matrix, row, col, curr_row, curr_col, last_row, last_col);

		if (!judge_cord(rand_matrix, row, col, curr_row, curr_col))
		{
			gotoxy(0, row * 4 + 2);
			cout << "                                           ";
			setcolor(0, COLOR_HYELLOW);
			gotoxy(0, row * 4 + 2);
			cout << "��Χ����ֵͬ!";
			setcolor();
			cout << "��ͷ��/����ƶ����س���/�������ѡ��";
			continue;
		}

		mark(rand_matrix, mark_matrix, curr_row, curr_col, row, col);

		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				if (mark_matrix[i][j] == '*') print_block(rand_matrix[i][j], 2 + j * 8, 2 + i * 4, MAKE10, CHOSEN);
			}
		}

		gotoxy(0, row * 4 + 2);
		cout << "                                           ";
		gotoxy(0, row * 4 + 2);
		cout << "��ͷ��/����ƶ�ȡ����ǰѡ�񣬻س���/��������ϳ�";

		if (!kb_confirm()) continue;

		score = GUI_combine(rand_matrix, mark_matrix, row, col, curr_row, curr_col);
		total_score += score;

		gotoxy(0, 0);
		cout << "���ε÷�:" << score << ' ' << "�ܵ÷�:" << total_score << ' ' << "�ϳ�Ŀ��:" << goal;

		//��������ɫ����հ�
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				if (rand_matrix[i][j] == 0) print_block(rand_matrix[i][j], 2 + j * 8, 2 + i * 4, MAKE10, EMP);
			}
		}
		//ԭ��ѡɫ���ӡƵ����Ч
		print_shiny(rand_matrix[curr_row][curr_col], 2 + curr_col * 8, 2 + curr_row * 4);

		gotoxy(0, row * 4 + 2);
		cout << "                                                    ";
		gotoxy(0, row * 4 + 2);
		cout << "�ϳ���ɣ��س���/�����������0";

		while (_getch() != '\r');

		//���鼯������
		block_fall(rand_matrix, row, col, MAKE10);

		gotoxy(0, row * 4 + 2);
		cout << "                                                    ";
		gotoxy(0, row * 4 + 2);
		cout << "������ɣ��س���/������������ֵ";

		while (_getch() != '\r');

		//����ڲ�����
		fill_rmatrix(rand_matrix, mark_matrix, row, col);
		//��ӡ���ɫ��
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				if (mark_matrix[i][j] == '*') print_block(rand_matrix[i][j], 2 + j * 8, 2 + i * 4, MAKE10, NORMAL);
			}
		}

		setcursor(CURSOR_VISIBLE_NORMAL);

		gotoxy(0, row * 4 + 2);
		cout << "                                                    ";
		gotoxy(0, row * 4 + 2);
		cout << "���κϳɽ�������C/������������µ�һ�κϳ�";

		while (_getch() != 'c' && _getch() != 'C');

		return;


	}
}

//����Ŀ�ţ�αͼ�ν���������
void nine_GUI_complete(int(*rand_matrix)[10], char(*mark_matrix)[10], int row, int col, int &goal, int &score, int &total_score)
{
	while (1)
	{
		print_block(rand_matrix[0][0], 2, 2, MAKE10, CHOSEN);
		int curr_row = 0, curr_col = 0;
		int last_row = 0, last_col = 0;

		gotoxy(0, row * 4 + 2);
		cout << "��ͷ��/����ƶ����س���/�������ѡ�񲢽���";

		kb_mouse_move(rand_matrix, mark_matrix, row, col, curr_row, curr_col, last_row, last_col);

		if (!judge_cord(rand_matrix, row, col, curr_row, curr_col))
		{
			gotoxy(0, row * 4 + 2);
			cout << "                                           ";
			setcolor(0, COLOR_HYELLOW);
			gotoxy(0, row * 4 + 2);
			cout << "��Χ����ֵͬ!";
			setcolor();
			cout << "��ͷ��/����ƶ����س���/�������ѡ��";
			continue;
		}

		mark(rand_matrix, mark_matrix, curr_row, curr_col, row, col);

		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				if (mark_matrix[i][j] == '*') print_block(rand_matrix[i][j], 2 + j * 8, 2 + i * 4, MAKE10, CHOSEN);
			}
		}

		gotoxy(0, row * 4 + 2);
		cout << "                                           ";
		gotoxy(0, row * 4 + 2);
		cout << "��ͷ��/����ƶ�ȡ����ǰѡ�񣬻س���/��������ϳ�";

		if (!cancel_confirm(curr_row, curr_col, MAKE10)) continue;

		score = GUI_combine(rand_matrix, mark_matrix, row, col, curr_row, curr_col);
		total_score += score;

		gotoxy(0, 0);
		cout << "���ε÷�:" << score << ' ' << "�ܵ÷�:" << total_score << ' ' << "�ϳ�Ŀ��:" << goal;

		//��������ɫ����հ�
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				if (rand_matrix[i][j] == 0) print_block(rand_matrix[i][j], 2 + j * 8, 2 + i * 4, MAKE10, EMP);
			}
		}
		//ԭ��ѡɫ���ӡƵ����Ч
		print_shiny(rand_matrix[curr_row][curr_col], 2 + curr_col * 8, 2 + curr_row * 4);

		//���鼯������
		block_fall(rand_matrix, row, col, MAKE10);

		//����ڲ�����
		fill_rmatrix(rand_matrix, mark_matrix, row, col);
		//��ӡ���ɫ��
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				Sleep(20);
				if (mark_matrix[i][j] == '*') print_block(rand_matrix[i][j], 2 + j * 8, 2 + i * 4, MAKE10, NORMAL);
			}
		}

		if (end_judge(rand_matrix, row, col))
		{
			gotoxy(0, row * 4 + 2);
			cout << "                                                             ";
			setcolor(0, COLOR_HRED);
			gotoxy(0, row * 4 + 2);
			cout << "�޿ɺϳ�ɫ��!���س�������Ϸ...";
			setcolor();

			while (_getch() != '\r');
			return;
		}

		if (win_check(rand_matrix, row, col, goal))
		{
			gotoxy(0, row * 4 + 2);
			cout << "                                                             ";
			setcolor(0, COLOR_HRED);
			gotoxy(0, row * 4 + 2);
			cout << "�Ժϳɵ�Ŀ��" << goal << ",���س��������Ŀ�����";
			setcolor();

			while (_getch() != '\r');
			goal++;
			gotoxy(0, 0);
			cout << "���ε÷�:" << score << ' ' << "�ܵ÷�:" << total_score << ' ' << "�ϳ�Ŀ��:" << goal;
			continue;
		}
	}
}