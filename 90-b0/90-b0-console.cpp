/*1751367 计2 彭健聪*/
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

//该函数用于制造合并时频闪特效
void print_shiny(int value, int cord_x, int cord_y)
{
	for (int i = 0; i < 3; i++)

	{
		int X = cord_x, Y = cord_y;
		print_block(value, cord_x, cord_y, MAKE10, CHOSEN);
		Sleep(100);
		//根据值的不同打印不同颜色方块
		print_block(value, cord_x, cord_y, MAKE10, NORMAL);
		Sleep(100);

	}
	setcolor();
}

//该函数用于合成十键盘移动选择色块
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
					cout << "[当前键盘] " << char(curr_row + 65) << "行" << curr_col << "列";
					break;
				case KB_ARROW_DOWN:
					go_down(rand_matrix, row, col, curr_row, curr_col, last_row, last_col, UNDIVIDED, MAKE10);
					gotoxy(0, row * 4 + 2);
					cout << "                                                  ";
					gotoxy(0, row * 4 + 2);
					cout << "[当前键盘] " << char(curr_row + 65) << "行" << curr_col << "列";
					break;
				case KB_ARROW_LEFT:
					go_left(rand_matrix, row, col, curr_row, curr_col, last_row, last_col, UNDIVIDED, MAKE10);
					gotoxy(0, row * 4 + 2);
					cout << "                                                  ";
					gotoxy(0, row * 4 + 2);
					cout << "[当前键盘] " << char(curr_row + 65) << "行" << curr_col << "列";
					break;
				case KB_ARROW_RIGHT:
					go_right(rand_matrix, row, col, curr_row, curr_col, last_row, last_col, UNDIVIDED, MAKE10);
					gotoxy(0, row * 4 + 2);
					cout << "                                                  ";
					gotoxy(0, row * 4 + 2);
					cout << "[当前键盘] " << char(curr_row + 65) << "行" << curr_col << "列";
					break;
				}
				//移动后将当前已选择的方块恢复
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

//该函数用于键盘确认继续
int kb_confirm()
{
	int X = 0, Y = 0;
	int ret, maction;
	int keycode1, keycode2;
	int loop = 1;

	enable_mouse();
	setcursor(CURSOR_INVISIBLE);	//关闭光标

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

//该函数用于伪图形界面下对内部数组进行合成加一操作
int GUI_combine(int(*rand_matrix)[10], char(*mark_matrix)[10], int row, int col, int curr_row, int curr_col)
{
	int score = 0;//记录用户得分
	int target = rand_matrix[curr_row][curr_col];

	//将连续区域清零并将目标数加一
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

//该函数用于合成十鼠标+键盘移动选择色块
void kb_mouse_move(int(*rand_matrix)[10], char(*mark_matrix)[10], int row, int col, int &curr_row, int &curr_col, int &last_row, int &last_col)
{
	int X = 0, Y = 0;
	int ret, maction;
	int keycode1, keycode2;
	int loop = 1;

	bool illegal = 0;

	enable_mouse();
	setcursor(CURSOR_INVISIBLE);	//关闭光标

	while (loop)
	{
		ret = read_keyboard_and_mouse(X, Y, maction, keycode1, keycode2);

		if (ret == CCT_MOUSE_EVENT) {
			//将当前鼠标位置的坐标转化为对应的行列了，并判断位置当前位置是否合法
			if (cord_to_rc(rand_matrix, row, col, X, Y, curr_row, curr_col, last_row, last_col, MAKE10, UNDIVIDED))
			{
				//如果当前鼠标所在方块与上一次所在方块不同才打印位置信息，否则会持续打印，产生频闪
				if ((curr_row != last_row) || (curr_col != last_col) || illegal)
				{
					//移动后将当前已选择的方块恢复
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

					//打印鼠标所在行列位置
					gotoxy(0, row * 4 + 2);
					cout << "                                                              ";
					gotoxy(0, row * 4 + 2);
					cout << "[当前鼠标] " << char(curr_row + 65) << "行" << curr_col << "列";

					illegal = 0;

				}
			}
			else //位置非法
			{
				if (!illegal)
				{
					print_block(rand_matrix[last_row][last_col], 2 + last_col * 8, 2 + last_row * 4, MAKE10, NORMAL);

					gotoxy(0, row * 4 + 2);
					cout << "                                                                             ";
					gotoxy(0, row * 4 + 2);
					cout << "[当前鼠标]" << "位置非法";

					illegal = 1;

					continue;
				}
			}

			//对于鼠标只需要单击左键的操作
			switch (maction)
			{
			case MOUSE_LEFT_BUTTON_CLICK:			//按下左键
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
					cout << "[当前键盘] " << char(curr_row + 65) << "行" << curr_col << "列";
					break;
				case KB_ARROW_DOWN:
					go_down(rand_matrix, row, col, curr_row, curr_col, last_row, last_col, UNDIVIDED, MAKE10);
					gotoxy(0, row * 4 + 2);
					cout << "                                                  ";
					gotoxy(0, row * 4 + 2);
					cout << "[当前键盘] " << char(curr_row + 65) << "行" << curr_col << "列";
					break;
				case KB_ARROW_LEFT:
					go_left(rand_matrix, row, col, curr_row, curr_col, last_row, last_col, UNDIVIDED, MAKE10);
					gotoxy(0, row * 4 + 2);
					cout << "                                                  ";
					gotoxy(0, row * 4 + 2);
					cout << "[当前键盘] " << char(curr_row + 65) << "行" << curr_col << "列";
					break;
				case KB_ARROW_RIGHT:
					go_right(rand_matrix, row, col, curr_row, curr_col, last_row, last_col, UNDIVIDED, MAKE10);
					gotoxy(0, row * 4 + 2);
					cout << "                                                  ";
					gotoxy(0, row * 4 + 2);
					cout << "[当前键盘] " << char(curr_row + 65) << "行" << curr_col << "列";
					break;
				}
				//移动后将当前已选择的方块恢复
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

//子题目五：伪图形界面显示初始数组（无分隔线）
void five_GUI_dsp_undvd(int(*rand_matrix)[10], int row, int col)
{
	orig_matrix(rand_matrix, row, col, MAKE10);
	print_frame(row, col, MAKE10, UNDIVIDED);

	//打印色块
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			print_block(rand_matrix[i][j], 2 + j * 6, 2 + i * 3, MAKE10, NORMAL);
		}
	}

	gotoxy(0, 0);
	cout << "屏幕当前设置为: " << 22 + (row - 5) * 3 << "行" << 35 + (col - 5) * 6 << "列";

	gotoxy(0, row * 3 + 4);
	cout << endl;
}

//子题目六：伪图形界面显示初始数组（有分隔线）
void six_GUI_dsp_dvd(int(*rand_matrix)[10], int row, int col)
{
	orig_matrix(rand_matrix, row, col, MAKE10);
	print_frame(row, col, MAKE10, DIVIDED);

	//打印色块
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			print_block(rand_matrix[i][j], 2 + j * 8, 2 + i * 4, MAKE10, NORMAL);
		}
	}

	gotoxy(0, 0);
	cout << "屏幕当前设置为: " << 26 + (row - 5) * 4 << "行" << 43 + (col - 5) * 8 << "列";

	gotoxy(0, row * 4 + 2);

}

//子题目七：伪图形界面下用箭头键选择当前色块
void seven_kb_choose(int(*rand_matrix)[10], char(*mark_matrix)[10], int row, int col)
{
	int curr_row = 0, curr_col = 0;
	int last_row = 0, last_col = 0;

	print_block(rand_matrix[0][0], 2, 2, MAKE10, CHOSEN);

	gotoxy(0, row * 4 + 2);
	cout << "箭头键/鼠标移动，回车键/单机左键选择并结束";

	kb_move(rand_matrix, mark_matrix, row, col, curr_row, curr_col, last_row, last_col);

	gotoxy(0, row * 4 + 2);
	cout << "                                                  ";
	gotoxy(0, row * 4 + 2);
	cout << "选中了" << char(curr_row + 65) << "行" << curr_col << "列" << endl;

	setcursor(CURSOR_VISIBLE_NORMAL);
}

//子题目八：伪图形界面完成一次合成（分步骤）
void eight_GUI_combine(int(*rand_matrix)[10], char(*mark_matrix)[10], int row, int col, int &goal, int &score, int &total_score)
{
	int curr_row = 0, curr_col = 0;
	int last_row = 0, last_col = 0;

	print_block(rand_matrix[0][0], 2, 2, MAKE10, CHOSEN);

	gotoxy(0, row * 4 + 2);
	cout << "箭头键/鼠标移动，回车键/单机左键选择并结束";

	while (1)
	{
		kb_move(rand_matrix, mark_matrix, row, col, curr_row, curr_col, last_row, last_col);

		if (!judge_cord(rand_matrix, row, col, curr_row, curr_col))
		{
			gotoxy(0, row * 4 + 2);
			cout << "                                           ";
			setcolor(0, COLOR_HYELLOW);
			gotoxy(0, row * 4 + 2);
			cout << "周围无相同值!";
			setcolor();
			cout << "箭头键/鼠标移动，回车键/单击左键选择";
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
		cout << "箭头键/鼠标移动取消当前选择，回车键/单机左键合成";

		if (!kb_confirm()) continue;

		score = GUI_combine(rand_matrix, mark_matrix, row, col, curr_row, curr_col);
		total_score += score;

		gotoxy(0, 0);
		cout << "本次得分:" << score << ' ' << "总得分:" << total_score << ' ' << "合成目标:" << goal;

		//被消除的色块填空白
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				if (rand_matrix[i][j] == 0) print_block(rand_matrix[i][j], 2 + j * 8, 2 + i * 4, MAKE10, EMP);
			}
		}
		//原被选色块打印频闪特效
		print_shiny(rand_matrix[curr_row][curr_col], 2 + curr_col * 8, 2 + curr_row * 4);

		gotoxy(0, row * 4 + 2);
		cout << "                                                    ";
		gotoxy(0, row * 4 + 2);
		cout << "合成完成，回车键/单击左键下落0";

		while (_getch() != '\r');

		//方块集体下落
		block_fall(rand_matrix, row, col, MAKE10);

		gotoxy(0, row * 4 + 2);
		cout << "                                                    ";
		gotoxy(0, row * 4 + 2);
		cout << "下落完成，回车键/单击左键填充新值";

		while (_getch() != '\r');

		//填充内部数组
		fill_rmatrix(rand_matrix, mark_matrix, row, col);
		//打印填充色块
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
		cout << "本次合成结束，按C/单击左键继续新的一次合成";

		while (_getch() != 'c' && _getch() != 'C');

		return;


	}
}

//子题目九：伪图形界面完整版
void nine_GUI_complete(int(*rand_matrix)[10], char(*mark_matrix)[10], int row, int col, int &goal, int &score, int &total_score)
{
	while (1)
	{
		print_block(rand_matrix[0][0], 2, 2, MAKE10, CHOSEN);
		int curr_row = 0, curr_col = 0;
		int last_row = 0, last_col = 0;

		gotoxy(0, row * 4 + 2);
		cout << "箭头键/鼠标移动，回车键/单机左键选择并结束";

		kb_mouse_move(rand_matrix, mark_matrix, row, col, curr_row, curr_col, last_row, last_col);

		if (!judge_cord(rand_matrix, row, col, curr_row, curr_col))
		{
			gotoxy(0, row * 4 + 2);
			cout << "                                           ";
			setcolor(0, COLOR_HYELLOW);
			gotoxy(0, row * 4 + 2);
			cout << "周围无相同值!";
			setcolor();
			cout << "箭头键/鼠标移动，回车键/单击左键选择";
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
		cout << "箭头键/鼠标移动取消当前选择，回车键/单击左键合成";

		if (!cancel_confirm(curr_row, curr_col, MAKE10)) continue;

		score = GUI_combine(rand_matrix, mark_matrix, row, col, curr_row, curr_col);
		total_score += score;

		gotoxy(0, 0);
		cout << "本次得分:" << score << ' ' << "总得分:" << total_score << ' ' << "合成目标:" << goal;

		//被消除的色块填空白
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				if (rand_matrix[i][j] == 0) print_block(rand_matrix[i][j], 2 + j * 8, 2 + i * 4, MAKE10, EMP);
			}
		}
		//原被选色块打印频闪特效
		print_shiny(rand_matrix[curr_row][curr_col], 2 + curr_col * 8, 2 + curr_row * 4);

		//方块集体下落
		block_fall(rand_matrix, row, col, MAKE10);

		//填充内部数组
		fill_rmatrix(rand_matrix, mark_matrix, row, col);
		//打印填充色块
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
			cout << "无可合成色块!按回车结束游戏...";
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
			cout << "以合成到目标" << goal << ",按回车键向更高目标进发";
			setcolor();

			while (_getch() != '\r');
			goal++;
			gotoxy(0, 0);
			cout << "本次得分:" << score << ' ' << "总得分:" << total_score << ' ' << "合成目标:" << goal;
			continue;
		}
	}
}