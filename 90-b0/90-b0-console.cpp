/*1751367 计2 彭健聪*/
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

//该函数用于从配置文件中读取配置信息
int read_game_cfg(const char *cfg_name, Game_area &game_area, Block &block, Block_color &block_color)
{
	fstream cfgfile;

	if (!open_cfgfile(cfgfile, cfg_name, OPEN_OPT_RDONLY))
	{
		cout << "打开配置文件失败";
		return 0;
	}

	//首先确定游戏界面是否需要分割线
	char value;
	item_get_value(cfgfile, "边框设置", "需要分隔线", &value, TYPE_CHARACTER);

	if (value == 'y' || value == 'Y')
	{
		game_area.divided = 1;
	}
	else if (value == 'n' || value == 'N')
	{
		game_area.divided = 0;
	}
	else game_area.divided = 1;

	//确定是否需要显示行列号
	item_get_value(cfgfile, "边框设置", "行号列标显示", &value, TYPE_CHARACTER);
	if (value == 'y' || value == 'Y')
	{
		game_area.show_row_col_number = 1;
	}
	else if (value == 'n' || value == 'N')
	{
		game_area.show_row_col_number = 0;
	}
	else game_area.show_row_col_number = 1;

	//是否显示上下状态栏
	item_get_value(cfgfile, "状态栏设置", "上状态栏", &value, TYPE_CHARACTER);
	if (value == 'y' || value == 'Y')
	{
		game_area.top_info = 1;
	}
	else if (value == 'n' || value == 'N')
	{
		game_area.top_info = 0;
	}
	else game_area.top_info = 1;

	item_get_value(cfgfile, "状态栏设置", "下状态栏", &value, TYPE_CHARACTER);
	if (value == 'y' || value == 'Y')
	{
		game_area.bot_info = 1;
	}
	else if (value == 'n' || value == 'N')
	{
		game_area.bot_info = 0;
	}
	else game_area.bot_info = 1;

	//读取游戏区域的行列大小
	item_get_value(cfgfile, "区域设置", "行数", &game_area.matrix_row, TYPE_INT);
	if (game_area.matrix_row < 5 || game_area.matrix_row > 8)
	{
		//超出范围取缺省值
		game_area.matrix_row = 5;
	}

	item_get_value(cfgfile, "区域设置", "列数", &game_area.matrix_col, TYPE_INT);
	if (game_area.matrix_col < 5 || game_area.matrix_col > 10)
	{
		//超出范围取缺省值
		game_area.matrix_col = 5;
	}

	//读取下方空行和右侧空行
	item_get_value(cfgfile, "区域设置", "下方空行", &game_area.extra_line, TYPE_INT);
	if (game_area.extra_line < 0 || game_area.extra_line>15)
	{
		game_area.extra_line = 0;
	}

	item_get_value(cfgfile, "区域设置", "右侧空列", &game_area.extra_col, TYPE_INT);
	if (game_area.extra_col < 0 || game_area.extra_col>15)
	{
		game_area.extra_col = 0;
	}

	//读取游戏界面打印延迟时间
	item_get_value(cfgfile, "区域设置", "画边框延时", &game_area.delay_time, TYPE_INT);
	{
		if (game_area.delay_time < 0 || game_area.delay_time>100)
		{
			game_area.delay_time = 0;
		}
	}

	//读取色块下落延迟时间
	item_get_value(cfgfile, "区域设置", "色块移动延时", &block.move_delay_time, TYPE_INT);
	{
		if (block.move_delay_time < 0 || block.move_delay_time>100)
		{
			block.move_delay_time = 0;
		}
	}

	//读取游戏目标(合成十需要)
	if (block.type == MAKE10)
	{
		item_get_value(cfgfile, "区域设置", "合成目标", &game_area.goal, TYPE_INT);

		if (game_area.goal < 5 || game_area.goal>99)
		{
			game_area.goal = 5;
		}
	}

	//读取游戏区域边框的字符
	item_get_value(cfgfile, "边框设置", "边框线-左上角", game_area.border[0], TYPE_STRING);
	item_get_value(cfgfile, "边框设置", "边框线-左下角", game_area.border[1], TYPE_STRING);
	item_get_value(cfgfile, "边框设置", "边框线-右上角", game_area.border[2], TYPE_STRING);
	item_get_value(cfgfile, "边框设置", "边框线-右下角", game_area.border[3], TYPE_STRING);
	item_get_value(cfgfile, "边框设置", "边框线-横线", game_area.border[4], TYPE_STRING);
	item_get_value(cfgfile, "边框设置", "边框线-竖线", game_area.border[5], TYPE_STRING);
	item_get_value(cfgfile, "边框设置", "边框线-上分隔线", game_area.border[6], TYPE_STRING);
	item_get_value(cfgfile, "边框设置", "边框线-下分隔线", game_area.border[7], TYPE_STRING);
	item_get_value(cfgfile, "边框设置", "边框线-左分隔线", game_area.border[8], TYPE_STRING);
	item_get_value(cfgfile, "边框设置", "边框线-右分隔线角", game_area.border[9], TYPE_STRING);
	item_get_value(cfgfile, "边框设置", "边框线-中分隔线", game_area.border[10], TYPE_STRING);

	//读取游戏区域颜色
	item_get_value(cfgfile, "边框设置", "背景色", &game_area.game_area_color.bg_color, TYPE_INT);
	if (game_area.game_area_color.bg_color < 0 || game_area.game_area_color.bg_color>15)
	{
		//背景色超出范围则取缺省值
		game_area.game_area_color.bg_color = 15;
	}

	item_get_value(cfgfile, "边框设置", "前景色", &game_area.game_area_color.fg_color, TYPE_INT);
	if (game_area.game_area_color.fg_color < 0 || game_area.game_area_color.fg_color>15)
	{
		//前景色超出范围则取缺省值
		game_area.game_area_color.fg_color = 0;
	}

	//读取显示信息的颜色
	item_get_value(cfgfile, "状态栏设置", "正常文字背景色", &game_area.norm_info_color.bg_color, TYPE_INT);
	if (game_area.norm_info_color.bg_color < -1 || game_area.norm_info_color.bg_color>15)
	{
		//背景色超出范围则取缺省值
		game_area.game_area_color.bg_color = -1;
	}

	item_get_value(cfgfile, "状态栏设置", "正常文字前景色", &game_area.norm_info_color.fg_color, TYPE_INT);
	if (game_area.norm_info_color.fg_color < -1 || game_area.norm_info_color.fg_color>15)
	{
		//背景色超出范围则取缺省值
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

	item_get_value(cfgfile, "状态栏设置", "错误文字背景色", &game_area.warning_color.bg_color, TYPE_INT);
	if (game_area.warning_color.bg_color < -1 || game_area.warning_color.bg_color>15)
	{
		//背景色超出范围则取缺省值
		game_area.warning_color.bg_color = -1;
	}

	item_get_value(cfgfile, "状态栏设置", "错误文字前景色", &game_area.warning_color.fg_color, TYPE_INT);
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



	//读取游戏区域的起始坐标
	item_get_value(cfgfile, "区域设置", "起始列号", &game_area.orig_cord.cord_x, TYPE_INT);
	if (game_area.orig_cord.cord_x < 0 || game_area.orig_cord.cord_x>15)
	{
		game_area.orig_cord.cord_x = 0;
	}

	item_get_value(cfgfile, "区域设置", "起始行号", &game_area.orig_cord.cord_y, TYPE_INT);
	if (game_area.orig_cord.cord_y < 0 || game_area.orig_cord.cord_y > 15)
	{
		game_area.orig_cord.cord_y = 0;
	}

	//读取色块的长和宽
	item_get_value(cfgfile, "色块设置", "宽度", &block.width, TYPE_INT);

	if (block.width % 2 != 0)
	{
		//色块宽度读取到奇数则自动+1
		block.width++;
	}

	if (block.width < 6 || block.width>16)
	{
		block.width = 6;
	}

	item_get_value(cfgfile, "色块设置", "高度", &block.height, TYPE_INT);

	if (block.height < 3 || block.height > 6)
	{
		block.height = 6;
	}

	//读取色块的边框字符
	item_get_value(cfgfile, "色块设置", "边框线-左上角", block.frame[0], TYPE_STRING);
	item_get_value(cfgfile, "色块设置", "边框线-左下角", block.frame[1], TYPE_STRING);
	item_get_value(cfgfile, "色块设置", "边框线-右上角", block.frame[2], TYPE_STRING);
	item_get_value(cfgfile, "色块设置", "边框线-右下角", block.frame[3], TYPE_STRING);
	item_get_value(cfgfile, "色块设置", "边框线-横线", block.frame[4], TYPE_STRING);
	item_get_value(cfgfile, "色块设置", "边框线-竖线", block.frame[5], TYPE_STRING);

	/*在读取色块颜色的时候需要考虑实际的游戏类型，合成十需要用到十一个色块颜色
	而消灭星星只需要用到前五个*/
	if (block.type == MAKE10)
	{
		item_get_value(cfgfile, "色块设置", "色块1-前景色", &block_color.block_color_1.fg_color, TYPE_INT);
		if (block_color.block_color_1.fg_color < 0 || block_color.block_color_1.fg_color>15)
		{
			block_color.block_color_1.fg_color = 0;
		}

		item_get_value(cfgfile, "色块设置", "色块1-背景色", &block_color.block_color_1.bg_color, TYPE_INT);
		if (block_color.block_color_1.bg_color < 0 || block_color.block_color_1.bg_color>15)
		{
			block_color.block_color_1.bg_color = 1;
		}

		item_get_value(cfgfile, "色块设置", "色块2-前景色", &block_color.block_color_2.fg_color, TYPE_INT);
		if (block_color.block_color_2.fg_color < 0 || block_color.block_color_2.fg_color>15)
		{
			block_color.block_color_2.fg_color = 0;
		}

		item_get_value(cfgfile, "色块设置", "色块2-背景色", &block_color.block_color_2.bg_color, TYPE_INT);
		if (block_color.block_color_2.bg_color < 0 || block_color.block_color_2.bg_color>15)
		{
			block_color.block_color_2.bg_color = 2;
		}

		item_get_value(cfgfile, "色块设置", "色块3-前景色", &block_color.block_color_3.fg_color, TYPE_INT);
		if (block_color.block_color_3.fg_color < 0 || block_color.block_color_3.fg_color>15)
		{
			block_color.block_color_3.fg_color = 0;
		}

		item_get_value(cfgfile, "色块设置", "色块3-背景色", &block_color.block_color_3.bg_color, TYPE_INT);
		if (block_color.block_color_3.bg_color < 0 || block_color.block_color_3.bg_color>15)
		{
			block_color.block_color_2.bg_color = 3;
		}

		item_get_value(cfgfile, "色块设置", "色块4-前景色", &block_color.block_color_4.fg_color, TYPE_INT);
		if (block_color.block_color_4.fg_color < 0 || block_color.block_color_4.fg_color>15)
		{
			block_color.block_color_4.fg_color = 0;
		}

		item_get_value(cfgfile, "色块设置", "色块4-背景色", &block_color.block_color_4.bg_color, TYPE_INT);
		if (block_color.block_color_4.bg_color < 0 || block_color.block_color_4.bg_color>15)
		{
			block_color.block_color_4.bg_color = 4;
		}

		item_get_value(cfgfile, "色块设置", "色块5-前景色", &block_color.block_color_5.fg_color, TYPE_INT);
		if (block_color.block_color_5.fg_color < 0 || block_color.block_color_5.fg_color>15)
		{
			block_color.block_color_5.fg_color = 0;
		}

		item_get_value(cfgfile, "色块设置", "色块5-背景色", &block_color.block_color_5.bg_color, TYPE_INT);
		if (block_color.block_color_5.bg_color < 0 || block_color.block_color_5.bg_color>15)
		{
			block_color.block_color_5.bg_color = 5;
		}

		item_get_value(cfgfile, "色块设置", "色块6-前景色", &block_color.block_color_6.fg_color, TYPE_INT);
		if (block_color.block_color_6.fg_color < 0 || block_color.block_color_6.fg_color>15)
		{
			block_color.block_color_6.fg_color = 0;
		}

		item_get_value(cfgfile, "色块设置", "色块6-背景色", &block_color.block_color_6.bg_color, TYPE_INT);
		if (block_color.block_color_6.bg_color < 0 || block_color.block_color_6.bg_color>15)
		{
			block_color.block_color_6.bg_color = 9;
		}

		item_get_value(cfgfile, "色块设置", "色块7-前景色", &block_color.block_color_7.fg_color, TYPE_INT);
		if (block_color.block_color_7.fg_color < 0 || block_color.block_color_7.fg_color>15)
		{
			block_color.block_color_7.fg_color = 0;
		}

		item_get_value(cfgfile, "色块设置", "色块7-背景色", &block_color.block_color_7.bg_color, TYPE_INT);
		if (block_color.block_color_7.bg_color < 0 || block_color.block_color_7.bg_color>15)
		{
			block_color.block_color_7.bg_color = 10;
		}

		item_get_value(cfgfile, "色块设置", "色块8-前景色", &block_color.block_color_8.fg_color, TYPE_INT);
		if (block_color.block_color_8.fg_color < 0 || block_color.block_color_8.fg_color>15)
		{
			block_color.block_color_8.fg_color = 0;
		}

		item_get_value(cfgfile, "色块设置", "色块8-背景色", &block_color.block_color_8.bg_color, TYPE_INT);
		if (block_color.block_color_8.bg_color < 0 || block_color.block_color_8.bg_color>15)
		{
			block_color.block_color_8.bg_color = 11;
		}

		item_get_value(cfgfile, "色块设置", "色块9-前景色", &block_color.block_color_9.fg_color, TYPE_INT);
		if (block_color.block_color_9.fg_color < 0 || block_color.block_color_9.fg_color>15)
		{
			block_color.block_color_9.fg_color = 0;
		}

		item_get_value(cfgfile, "色块设置", "色块9-背景色", &block_color.block_color_9.bg_color, TYPE_INT);
		if (block_color.block_color_9.bg_color < 0 || block_color.block_color_9.bg_color>15)
		{
			block_color.block_color_9.bg_color = 12;
		}

		item_get_value(cfgfile, "色块设置", "色块10-前景色", &block_color.block_color_10.fg_color, TYPE_INT);
		if (block_color.block_color_10.fg_color < 0 || block_color.block_color_10.fg_color>15)
		{
			block_color.block_color_10.fg_color = 0;
		}

		item_get_value(cfgfile, "色块设置", "色块10-背景色", &block_color.block_color_10.bg_color, TYPE_INT);
		if (block_color.block_color_10.bg_color < 0 || block_color.block_color_10.bg_color>15)
		{
			block_color.block_color_10.bg_color = 13;
		}

		item_get_value(cfgfile, "色块设置", "色块1-前景色", &block_color.block_color_11.fg_color, TYPE_INT);
		if (block_color.block_color_11.fg_color < 0 || block_color.block_color_11.fg_color>15)
		{
			block_color.block_color_11.fg_color = 0;
		}

		item_get_value(cfgfile, "色块设置", "色块1-背景色", &block_color.block_color_11.bg_color, TYPE_INT);
		if (block_color.block_color_11.bg_color < 0 || block_color.block_color_11.bg_color>15)
		{
			block_color.block_color_11.bg_color = 1;
		}
	}


	//读取选中色块颜色
	item_get_value(cfgfile, "色块设置", "选中色块背景色", &block_color.chosen_block_color.bg_color, TYPE_INT);
	if (block_color.chosen_block_color.bg_color < 0 || block_color.chosen_block_color.bg_color > 15)
	{
		block_color.chosen_block_color.bg_color = 5;
	}

	item_get_value(cfgfile, "色块设置", "选中色块前景色", &block_color.chosen_block_color.fg_color, TYPE_INT);
	if (block_color.chosen_block_color.fg_color < 0 || block_color.chosen_block_color.fg_color > 15)
	{
		block_color.chosen_block_color.fg_color = 7;
	}

	close_cfgfile(cfgfile);

	return 1;
}

//可读取配置文件版本的伪图形界面完整游戏版本
void GUI_full_cfg(char *cfgfile_name)
{
	Cord orig_cord; //这个东西在打印色块的时候进行坐标定位的时候需要

	int score; //记录分数用的

	//定义游戏区域结构体变量
	Game_area game_area;
	//色块结构体变量
	Block make10_block;

	make10_block.type = MAKE10;
	//色块颜色信息变量
	Block_color block_color;

	//从配置文件中读取信息
	read_game_cfg(cfgfile_name, game_area, make10_block, block_color);

	//初始化内部数组
	orig_matrix(game_area.rand_matrix, game_area.matrix_row, game_area.matrix_col, MAKE10);
	orig_mark(game_area.mark_matrix, game_area.matrix_row, game_area.matrix_col);

	//打印游戏界面
	print_game_area(game_area, make10_block);

#if 1
	//打印色块
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
			cout << "箭头键/鼠标移动，回车键/单机左键选择并结束";
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
				cout << "周围无相同值!";
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
			cout << "箭头键/鼠标移动取消当前选择，回车键/单击左键合成";
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
			cout << "本次得分:" << score << ' ' << "总得分:" << game_area.total_score << ' ' << "合成目标:" << game_area.goal;
			setcolor();
		}

		//被消除的色块填空白
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

		//填充内部数组
		fill_rmatrix(game_area.rand_matrix, game_area.mark_matrix, game_area.matrix_row, game_area.matrix_col);

		//打印填充色块
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
				cout << "无可合成色块!按回车结束游戏...";
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
				cout << "以合成到目标" << game_area.goal << ",按回车键向更高目标进发";
				setcolor();
			}

			while (_getch() != '\r');
			game_area.goal++;

			if (game_area.top_info)
			{
				gotoxy(0, 0);
				setcolor(game_area.norm_info_color.bg_color, game_area.norm_info_color.fg_color);
				cout << "本次得分:" << score << ' ' << "总得分:" << game_area.total_score << ' ' << "合成目标:" << game_area.goal;
				setcolor();
			}
			continue;
		}
	}
#endif 
}