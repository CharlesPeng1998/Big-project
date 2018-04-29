/*1751367 ��2 ����*/
#define _CRT_SECURE_NO_WARNINGS
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
#include "..\common\common_cfgfile_tools.hpp"
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

//�ú������ڴ������ļ��ж�ȡ������Ϣ
int read_game_cfg(const char *cfg_name, Game_area &game_area, Block &block, Block_color &block_color)
{
	fstream cfgfile;

	if (!open_cfgfile(cfgfile, cfg_name, OPEN_OPT_RDONLY))
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
	item_get_value(cfgfile, "��������", "����", &game_area.matrix_row, TYPE_INT);
	if (game_area.matrix_row < 5 || game_area.matrix_row > 8)
	{
		//������Χȡȱʡֵ
		game_area.matrix_row = 5;
	}

	item_get_value(cfgfile, "��������", "����", &game_area.matrix_col, TYPE_INT);
	if (game_area.matrix_col < 5 || game_area.matrix_col > 10)
	{
		//������Χȡȱʡֵ
		game_area.matrix_col = 5;
	}

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
		if (block.move_delay_time < 0 || block.move_delay_time>100)
		{
			block.move_delay_time = 0;
		}
	}

	//��ȡ��ϷĿ��(�ϳ�ʮ��Ҫ)
	if (block.type == MAKE10)
	{
		item_get_value(cfgfile, "��������", "�ϳ�Ŀ��", &game_area.goal, TYPE_INT);

		if (game_area.goal < 5 || game_area.goal>99)
		{
			game_area.goal = 5;
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
	if (block.type == MAKE10)
	{
		item_get_value(cfgfile, "ɫ������", "ɫ��1-ǰ��ɫ", &block_color.block_color_1.fg_color, TYPE_INT);
		if (block_color.block_color_1.fg_color < 0 || block_color.block_color_1.fg_color>15)
		{
			block_color.block_color_1.fg_color = 0;
		}

		item_get_value(cfgfile, "ɫ������", "ɫ��1-����ɫ", &block_color.block_color_1.bg_color, TYPE_INT);
		if (block_color.block_color_1.bg_color < 0 || block_color.block_color_1.bg_color>15)
		{
			block_color.block_color_1.bg_color = 1;
		}

		item_get_value(cfgfile, "ɫ������", "ɫ��2-ǰ��ɫ", &block_color.block_color_2.fg_color, TYPE_INT);
		if (block_color.block_color_2.fg_color < 0 || block_color.block_color_2.fg_color>15)
		{
			block_color.block_color_2.fg_color = 0;
		}

		item_get_value(cfgfile, "ɫ������", "ɫ��2-����ɫ", &block_color.block_color_2.bg_color, TYPE_INT);
		if (block_color.block_color_2.bg_color < 0 || block_color.block_color_2.bg_color>15)
		{
			block_color.block_color_2.bg_color = 2;
		}

		item_get_value(cfgfile, "ɫ������", "ɫ��3-ǰ��ɫ", &block_color.block_color_3.fg_color, TYPE_INT);
		if (block_color.block_color_3.fg_color < 0 || block_color.block_color_3.fg_color>15)
		{
			block_color.block_color_3.fg_color = 0;
		}

		item_get_value(cfgfile, "ɫ������", "ɫ��3-����ɫ", &block_color.block_color_3.bg_color, TYPE_INT);
		if (block_color.block_color_3.bg_color < 0 || block_color.block_color_3.bg_color>15)
		{
			block_color.block_color_2.bg_color = 3;
		}

		item_get_value(cfgfile, "ɫ������", "ɫ��4-ǰ��ɫ", &block_color.block_color_4.fg_color, TYPE_INT);
		if (block_color.block_color_4.fg_color < 0 || block_color.block_color_4.fg_color>15)
		{
			block_color.block_color_4.fg_color = 0;
		}

		item_get_value(cfgfile, "ɫ������", "ɫ��4-����ɫ", &block_color.block_color_4.bg_color, TYPE_INT);
		if (block_color.block_color_4.bg_color < 0 || block_color.block_color_4.bg_color>15)
		{
			block_color.block_color_4.bg_color = 4;
		}

		item_get_value(cfgfile, "ɫ������", "ɫ��5-ǰ��ɫ", &block_color.block_color_5.fg_color, TYPE_INT);
		if (block_color.block_color_5.fg_color < 0 || block_color.block_color_5.fg_color>15)
		{
			block_color.block_color_5.fg_color = 0;
		}

		item_get_value(cfgfile, "ɫ������", "ɫ��5-����ɫ", &block_color.block_color_5.bg_color, TYPE_INT);
		if (block_color.block_color_5.bg_color < 0 || block_color.block_color_5.bg_color>15)
		{
			block_color.block_color_5.bg_color = 5;
		}

		item_get_value(cfgfile, "ɫ������", "ɫ��6-ǰ��ɫ", &block_color.block_color_6.fg_color, TYPE_INT);
		if (block_color.block_color_6.fg_color < 0 || block_color.block_color_6.fg_color>15)
		{
			block_color.block_color_6.fg_color = 0;
		}

		item_get_value(cfgfile, "ɫ������", "ɫ��6-����ɫ", &block_color.block_color_6.bg_color, TYPE_INT);
		if (block_color.block_color_6.bg_color < 0 || block_color.block_color_6.bg_color>15)
		{
			block_color.block_color_6.bg_color = 9;
		}

		item_get_value(cfgfile, "ɫ������", "ɫ��7-ǰ��ɫ", &block_color.block_color_7.fg_color, TYPE_INT);
		if (block_color.block_color_7.fg_color < 0 || block_color.block_color_7.fg_color>15)
		{
			block_color.block_color_7.fg_color = 0;
		}

		item_get_value(cfgfile, "ɫ������", "ɫ��7-����ɫ", &block_color.block_color_7.bg_color, TYPE_INT);
		if (block_color.block_color_7.bg_color < 0 || block_color.block_color_7.bg_color>15)
		{
			block_color.block_color_7.bg_color = 10;
		}

		item_get_value(cfgfile, "ɫ������", "ɫ��8-ǰ��ɫ", &block_color.block_color_8.fg_color, TYPE_INT);
		if (block_color.block_color_8.fg_color < 0 || block_color.block_color_8.fg_color>15)
		{
			block_color.block_color_8.fg_color = 0;
		}

		item_get_value(cfgfile, "ɫ������", "ɫ��8-����ɫ", &block_color.block_color_8.bg_color, TYPE_INT);
		if (block_color.block_color_8.bg_color < 0 || block_color.block_color_8.bg_color>15)
		{
			block_color.block_color_8.bg_color = 11;
		}

		item_get_value(cfgfile, "ɫ������", "ɫ��9-ǰ��ɫ", &block_color.block_color_9.fg_color, TYPE_INT);
		if (block_color.block_color_9.fg_color < 0 || block_color.block_color_9.fg_color>15)
		{
			block_color.block_color_9.fg_color = 0;
		}

		item_get_value(cfgfile, "ɫ������", "ɫ��9-����ɫ", &block_color.block_color_9.bg_color, TYPE_INT);
		if (block_color.block_color_9.bg_color < 0 || block_color.block_color_9.bg_color>15)
		{
			block_color.block_color_9.bg_color = 12;
		}

		item_get_value(cfgfile, "ɫ������", "ɫ��10-ǰ��ɫ", &block_color.block_color_10.fg_color, TYPE_INT);
		if (block_color.block_color_10.fg_color < 0 || block_color.block_color_10.fg_color>15)
		{
			block_color.block_color_10.fg_color = 0;
		}

		item_get_value(cfgfile, "ɫ������", "ɫ��10-����ɫ", &block_color.block_color_10.bg_color, TYPE_INT);
		if (block_color.block_color_10.bg_color < 0 || block_color.block_color_10.bg_color>15)
		{
			block_color.block_color_10.bg_color = 13;
		}

		item_get_value(cfgfile, "ɫ������", "ɫ��1-ǰ��ɫ", &block_color.block_color_11.fg_color, TYPE_INT);
		if (block_color.block_color_11.fg_color < 0 || block_color.block_color_11.fg_color>15)
		{
			block_color.block_color_11.fg_color = 0;
		}

		item_get_value(cfgfile, "ɫ������", "ɫ��1-����ɫ", &block_color.block_color_11.bg_color, TYPE_INT);
		if (block_color.block_color_11.bg_color < 0 || block_color.block_color_11.bg_color>15)
		{
			block_color.block_color_11.bg_color = 1;
		}
	}


	//��ȡѡ��ɫ����ɫ
	item_get_value(cfgfile, "ɫ������", "ѡ��ɫ�鱳��ɫ", &block_color.chosen_block_color.bg_color, TYPE_INT);
	if (block_color.chosen_block_color.bg_color < 0 || block_color.chosen_block_color.bg_color > 15)
	{
		block_color.chosen_block_color.bg_color = 5;
	}

	item_get_value(cfgfile, "ɫ������", "ѡ��ɫ��ǰ��ɫ", &block_color.chosen_block_color.fg_color, TYPE_INT);
	if (block_color.chosen_block_color.fg_color < 0 || block_color.chosen_block_color.fg_color > 15)
	{
		block_color.chosen_block_color.fg_color = 7;
	}

	close_cfgfile(cfgfile);

	return 1;
}

//�ɶ�ȡ�����ļ��汾��αͼ�ν���������Ϸ�汾
void GUI_full_cfg(char *cfgfile_name)
{
	Cord orig_cord; //��������ڴ�ӡɫ���ʱ��������궨λ��ʱ����Ҫ

	int score; //��¼�����õ�

	//������Ϸ����ṹ�����
	Game_area game_area;
	//ɫ��ṹ�����
	Block make10_block;

	make10_block.type = MAKE10;
	//ɫ����ɫ��Ϣ����
	Block_color block_color;

	//�������ļ��ж�ȡ��Ϣ
	read_game_cfg(cfgfile_name, game_area, make10_block, block_color);

	//��ʼ���ڲ�����
	orig_matrix(game_area.rand_matrix, game_area.matrix_row, game_area.matrix_col, MAKE10);
	orig_mark(game_area.mark_matrix, game_area.matrix_row, game_area.matrix_col);

	//��ӡ��Ϸ����
	print_game_area(game_area, make10_block);

#if 1
	//��ӡɫ��
	for (int i = 0; i < game_area.matrix_row; i++)
	{
		for (int j = 0; j < game_area.matrix_col; j++)
		{
			switch (game_area.divided)
			{
			case 1:
				orig_cord.cord_x = (game_area.orig_cord.cord_x + 4) + j * (make10_block.width + 2);
				orig_cord.cord_y = (game_area.orig_cord.cord_y + 2) + i * (make10_block.height + 1);
				break;

			case 0:
				orig_cord.cord_x = (game_area.orig_cord.cord_x + 4) + j * make10_block.width;
				orig_cord.cord_y = (game_area.orig_cord.cord_y + 2) + i * make10_block.height;
				break;
			}

			print_block_cfg(game_area.rand_matrix[i][j], game_area, orig_cord, make10_block, block_color, NORMAL);

		}
	}

	while (1)
	{
		game_area.curr_col = game_area.last_col = 0;
		game_area.curr_row = game_area.last_row = 0;

		orig_cord.cord_x = game_area.orig_cord.cord_x + 4;
		orig_cord.cord_y = game_area.orig_cord.cord_y + 2;

		print_block_cfg(game_area.rand_matrix[0][0], game_area, orig_cord, make10_block, block_color, CHOSEN);

		if (game_area.bot_info)
		{          
			gotoxy(0, game_area.orig_cord.cord_y + game_area.matrix_row*(make10_block.height + 1) + 3);
			setcolor(game_area.norm_info_color.bg_color, game_area.norm_info_color.fg_color);
			cout << "��ͷ��/����ƶ����س���/�������ѡ�񲢽���";
			setcolor();
		}

		kb_move_cfg(game_area, make10_block, block_color);

		if (!judge_cord(game_area.rand_matrix, game_area.matrix_row, game_area.matrix_col, game_area.curr_row, game_area.curr_col))
		{
			if (game_area.bot_info)
			{
				gotoxy(0, game_area.orig_cord.cord_y + game_area.matrix_row*(make10_block.height + 1) + 3);
				cout << "                                                              ";
				setcolor(game_area.warning_color.bg_color, game_area.warning_color.fg_color);

				gotoxy(42, game_area.orig_cord.cord_y + game_area.matrix_row*(make10_block.height + 1) + 3);
				cout << "��Χ����ֵͬ!";
				setcolor();
			}

			switch (game_area.divided)
			{
			case 1:
				orig_cord.cord_x = (game_area.orig_cord.cord_x + 4) + game_area.curr_col * (make10_block.width + 2);
				orig_cord.cord_y = (game_area.orig_cord.cord_y + 2) + game_area.curr_row * (make10_block.height + 1);
				break;

			case 0:
				orig_cord.cord_x = (game_area.orig_cord.cord_x + 4) + game_area.curr_col * make10_block.width;
				orig_cord.cord_y = (game_area.orig_cord.cord_y + 2) + game_area.curr_row * make10_block.height;
				break;
			}

			print_block_cfg(game_area.rand_matrix[game_area.curr_row][game_area.curr_col], game_area, orig_cord, make10_block, block_color, NORMAL);
			continue;
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
						orig_cord.cord_x = (game_area.orig_cord.cord_x + 4) + j * (make10_block.width + 2);
						orig_cord.cord_y = (game_area.orig_cord.cord_y + 2) + i * (make10_block.height + 1);
						break;

					case 0:
						orig_cord.cord_x = (game_area.orig_cord.cord_x + 4) + j * make10_block.width;
						orig_cord.cord_y = (game_area.orig_cord.cord_y + 2) + i * make10_block.height;
						break;
					}

					print_block_cfg(game_area.rand_matrix[i][j], game_area, orig_cord, make10_block, block_color, CHOSEN);
				}
			}
		}

		if (game_area.bot_info)
		{
			gotoxy(0, game_area.orig_cord.cord_y + game_area.matrix_row*(make10_block.height + 1) + 3);
			cout << "                                                              ";
			gotoxy(0, game_area.orig_cord.cord_y + game_area.matrix_row*(make10_block.height + 1) + 3);
			setcolor(game_area.norm_info_color.bg_color, game_area.norm_info_color.fg_color);
			cout << "��ͷ��/����ƶ�ȡ����ǰѡ�񣬻س���/��������ϳ�";
			setcolor();
		}

		if (!cancel_confirm_cfg(game_area, make10_block))
		{
			continue;
		}

		score = GUI_combine(game_area.rand_matrix, game_area.mark_matrix, game_area.matrix_row, game_area.matrix_col, game_area.curr_row, game_area.curr_col);
		game_area.total_score += score;

		if (game_area.top_info)
		{
			gotoxy(0, 0);
			setcolor(game_area.norm_info_color.bg_color, game_area.norm_info_color.fg_color);
			cout << "���ε÷�:" << score << ' ' << "�ܵ÷�:" << game_area.total_score << ' ' << "�ϳ�Ŀ��:" << game_area.goal;
			setcolor();
		}

		//��������ɫ����հ�
		for (int i = 0; i < game_area.matrix_row; i++)
		{
			for (int j = 0; j < game_area.matrix_col; j++)
			{
				if (game_area.rand_matrix[i][j] == 0)
				{
					switch (game_area.divided)
					{
					case 1:
						orig_cord.cord_x = (game_area.orig_cord.cord_x + 4) + j * (make10_block.width + 2);
						orig_cord.cord_y = (game_area.orig_cord.cord_y + 2) + i * (make10_block.height + 1);
						break;

					case 0:
						orig_cord.cord_x = (game_area.orig_cord.cord_x + 4) + j * make10_block.width;
						orig_cord.cord_y = (game_area.orig_cord.cord_y + 2) + i * make10_block.height;
						break;
					}

					print_block_cfg(game_area.rand_matrix[i][j], game_area, orig_cord, make10_block, block_color, EMP);
				}
			}
		}

		block_fall_cfg(game_area, make10_block, block_color);

		//����ڲ�����
		fill_rmatrix(game_area.rand_matrix, game_area.mark_matrix, game_area.matrix_row, game_area.matrix_col);

		//��ӡ���ɫ��
		for (int i = 0; i < game_area.matrix_row; i++)
		{
			for (int j = 0; j < game_area.matrix_col; j++)
			{
				Sleep(20);
				switch (game_area.divided)
				{
				case 1:
					orig_cord.cord_x = (game_area.orig_cord.cord_x + 4) + j * (make10_block.width + 2);
					orig_cord.cord_y = (game_area.orig_cord.cord_y + 2) + i * (make10_block.height + 1);
					break;

				case 0:
					orig_cord.cord_x = (game_area.orig_cord.cord_x + 4) + j * make10_block.width;
					orig_cord.cord_y = (game_area.orig_cord.cord_y + 2) + i * make10_block.height;
					break;
				}

				print_block_cfg(game_area.rand_matrix[i][j], game_area, orig_cord, make10_block, block_color, NORMAL);
			}
		}

		if (end_judge(game_area.rand_matrix, game_area.matrix_row, game_area.matrix_col))
		{
			if (game_area.bot_info)
			{
				gotoxy(0, game_area.orig_cord.cord_y + game_area.matrix_row*(make10_block.height + 1) + 3);
				cout << "                                                              ";
				setcolor(game_area.warning_color.bg_color, game_area.warning_color.fg_color);
				gotoxy(0, game_area.orig_cord.cord_y + game_area.matrix_row*(make10_block.height + 1) + 3);
				cout << "�޿ɺϳ�ɫ��!���س�������Ϸ...";
				setcolor();
			}

			while (_getch() != '\r');
			return;
		}

		if (win_check(game_area.rand_matrix, game_area.matrix_row, game_area.matrix_col, game_area.goal))
		{
			if (game_area.bot_info)
			{
				gotoxy(0, game_area.orig_cord.cord_y + game_area.matrix_row*(make10_block.height + 1) + 3);
				cout << "                                                             ";
				setcolor(game_area.warning_color.bg_color, game_area.warning_color.fg_color);
				gotoxy(0, game_area.orig_cord.cord_y + game_area.matrix_row*(make10_block.height + 1) + 3);
				cout << "�Ժϳɵ�Ŀ��" << game_area.goal << ",���س��������Ŀ�����";
				setcolor();
			}

			while (_getch() != '\r');
			game_area.goal++;

			if (game_area.top_info)
			{
				gotoxy(0, 0);
				setcolor(game_area.norm_info_color.bg_color, game_area.norm_info_color.fg_color);
				cout << "���ε÷�:" << score << ' ' << "�ܵ÷�:" << game_area.total_score << ' ' << "�ϳ�Ŀ��:" << game_area.goal;
				setcolor();
			}
			continue;
		}
	}
#endif 
}