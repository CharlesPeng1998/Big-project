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
#include "90-b1.h"
using namespace std;

extern "C"
{
#include "../common/common_cfgfile_tools.h"
}


//该函数用于回车/单击左键确认继续
int enter_click(int btn)
{
	int X, Y;
	int ret, maction;
	int keycode1, keycode2;
	int loop = 1;

	enable_mouse();
	setcursor(CURSOR_INVISIBLE);	//关闭光标

	while (loop)
	{
		/* 读鼠标/键盘，返回值为下述操作中的某一种, 当前鼠标位置在<X,Y>处 */
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

//该函数用于移动和选择色块
void move(int(*rand_matrix)[10], char(*mark_matrix)[10], int row, int col, int &curr_row, int &curr_col, int &last_row, int &last_col, int type)
{
	int X = 0, Y = 0;
	int ret, maction;
	int keycode1, keycode2;
	int loop = 1;

	/*解释一下这个变量的作用：
	在改进前版本中，若将鼠标移动到非法位置后再次移动到边界上的方块，
	则此时的方块并没有被选中。原因是在非法位置移动时curr_和last_是
	一直保持相等。为解决这个问题，设置一个判断是否在非法位置的变量，
	当从非法位置回到合法位置时仍进行方块的打印。*/
	bool illegal = 0;


	enable_mouse();
	setcursor(CURSOR_INVISIBLE);	//关闭光标

	if (type == UNDIVIDED)
	{
		while (loop) {
			/* 读鼠标/键盘，返回值为下述操作中的某一种, 当前鼠标位置在<X,Y>处 */
			ret = read_keyboard_and_mouse(X, Y, maction, keycode1, keycode2);

			if (ret == CCT_MOUSE_EVENT) {
				//将当前鼠标位置的坐标转化为对应的行列了，并判断位置当前位置是否合法
				if (cord_to_rc(rand_matrix, row, col, X, Y, curr_row, curr_col, last_row, last_col, POPSTAR, UNDIVIDED))
				{
					//如果当前鼠标所在方块与上一次所在方块不同才打印位置信息，否则会持续打印，产生频闪
					if ((curr_row != last_row) || (curr_col != last_col) || illegal)
					{
						//移动后将当前已选择的方块恢复
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

						//打印鼠标所在行列位置
						gotoxy(0, row * 3 + 4);
						cout << "                                          ";
						gotoxy(0, row * 3 + 4);
						cout << "[当前鼠标] " << char(curr_row + 65) << "行" << curr_col << "列";

						illegal = 0;

					}
				}
				else //位置非法
				{
					if (!illegal)
					{
						print_block(rand_matrix[last_row][last_col], 4 + last_col * 6, 3 + last_row * 3, POPSTAR, NORMAL);

						gotoxy(0, row * 3 + 4);
						cout << "                                                                             ";
						gotoxy(0, row * 3 + 4);
						cout << "[当前鼠标]" << "位置非法";

						illegal = 1;

						continue;
					}
				}

				//对于鼠标只需要单击左键的操作
				switch (maction)
				{
				case MOUSE_LEFT_BUTTON_CLICK:			//按下左键
					gotoxy(0, row * 3 + 4);
					cout << "                                       ";
					gotoxy(0, row * 3 + 4);
					cout << "选中了" << char(curr_row + 65) << "行" << curr_col << "列";
					setcursor(CURSOR_VISIBLE_NORMAL);//恢复光标
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
						cout << "[当前键盘] " << char(curr_row + 65) << "行" << curr_col << "列";
						break;
					case KB_ARROW_DOWN:
						go_down(rand_matrix, row, col, curr_row, curr_col, last_row, last_col, UNDIVIDED);
						gotoxy(0, row * 3 + 4);
						cout << "[当前键盘] " << char(curr_row + 65) << "行" << curr_col << "列";
						break;
					case KB_ARROW_LEFT:
						go_left(rand_matrix, row, col, curr_row, curr_col, last_row, last_col, UNDIVIDED);
						gotoxy(0, row * 3 + 4);
						cout << "[当前键盘] " << char(curr_row + 65) << "行" << curr_col << "列";
						break;
					case KB_ARROW_RIGHT:
						go_right(rand_matrix, row, col, curr_row, curr_col, last_row, last_col, UNDIVIDED);
						gotoxy(0, row * 3 + 4);
						cout << "[当前键盘] " << char(curr_row + 65) << "行" << curr_col << "列";
						break;
					}

					//移动后将当前已选择的方块恢复
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
					cout << "选中了" << char(curr_row + 65) << "行" << curr_col << "列";
					setcursor(CURSOR_VISIBLE_NORMAL);//恢复光标
					return;
				}
			}
		}
	}
	else if (type == DIVIDED)
	{
		while (loop) {
			/* 读鼠标/键盘，返回值为下述操作中的某一种, 当前鼠标位置在<X,Y>处 */
			ret = read_keyboard_and_mouse(X, Y, maction, keycode1, keycode2);

			if (ret == CCT_MOUSE_EVENT) {
				//将当前鼠标位置的坐标转化为对应的行列了，并判断位置当前位置是否合法
				if (cord_to_rc(rand_matrix, row, col, X, Y, curr_row, curr_col, last_row, last_col, POPSTAR, DIVIDED))
				{
					//如果当前鼠标所在方块与上一次所在方块不同才打印位置信息，否则会持续打印，产生频闪
					if ((curr_row != last_row) || (curr_col != last_col) || illegal)
					{
						print_block(rand_matrix[last_row][last_col], 4 + last_col * 8, 3 + last_row * 4, POPSTAR, NORMAL);
						print_block(rand_matrix[curr_row][curr_col], 4 + curr_col * 8, 3 + curr_row * 4, POPSTAR, CHOSEN);

						//打印鼠标所在行列位置
						gotoxy(0, row * 4 + 3);
						cout << "                                          ";
						gotoxy(0, row * 4 + 3);
						cout << "[当前鼠标] " << char(curr_row + 65) << "行" << curr_col << "列";

						illegal = 0;
					}
				}
				else //位置非法
				{
					print_block(rand_matrix[last_row][last_col], 4 + last_col * 8, 3 + last_row * 4, POPSTAR, NORMAL);

					gotoxy(0, row * 4 + 3);
					cout << "[当前鼠标]" << "位置非法";

					illegal = 1;
				}

				//对于鼠标只需要单击左键的操作
				switch (maction)
				{
				case MOUSE_LEFT_BUTTON_CLICK:			//按下左键
					gotoxy(0, row * 4 + 3);
					cout << "                                       ";
					gotoxy(0, row * 4 + 3);
					cout << "选中了" << char(curr_row + 65) << "行" << curr_col << "列";
					setcursor(CURSOR_VISIBLE_NORMAL);//恢复光标
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
						cout << "[当前键盘] " << char(curr_row + 65) << "行" << curr_col << "列";
						break;
					case KB_ARROW_DOWN:
						go_down(rand_matrix, row, col, curr_row, curr_col, last_row, last_col, DIVIDED);
						gotoxy(0, row * 4 + 3);
						cout << "[当前键盘] " << char(curr_row + 65) << "行" << curr_col << "列";
						break;
					case KB_ARROW_LEFT:
						go_left(rand_matrix, row, col, curr_row, curr_col, last_row, last_col, DIVIDED);
						gotoxy(0, row * 4 + 3);
						cout << "[当前键盘] " << char(curr_row + 65) << "行" << curr_col << "列";
						break;
					case KB_ARROW_RIGHT:
						go_right(rand_matrix, row, col, curr_row, curr_col, last_row, last_col, DIVIDED);
						gotoxy(0, row * 4 + 3);
						cout << "[当前键盘] " << char(curr_row + 65) << "行" << curr_col << "列";
						break;
					}
					break;

				case 13:
					gotoxy(0, row * 4 + 3);
					cout << "                                       ";
					gotoxy(0, row * 4 + 3);
					cout << "选中了" << char(curr_row + 65) << "行" << curr_col << "列";
					setcursor(CURSOR_VISIBLE_NORMAL);//恢复光标
					return;
				}
			}
		}

		setcursor(CURSOR_VISIBLE_NORMAL);	//打开光标
	}
}

//该函数用于伪图形界面下的一次消除
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

//该函数用于整列左移
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

//该函数用于执行选定方块之后的操作
int elmn_fall(int(*rand_matrix)[10], char(*mark_matrix)[10], int &row, int &col, int &curr_row, int &curr_col, int &score, int &total_score, int question)
{
	gotoxy(0, row * 3 + 4);
	cout << "                                                ";
	gotoxy(0, row * 3 + 4);
	cout << "箭头键/鼠标移动取消当前选择，回车键/单击左键合成";

	mark(rand_matrix, mark_matrix, curr_row, curr_col, row, col);

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (mark_matrix[i][j] == '*') print_block(rand_matrix[i][j], 4 + j * 6, 3 + i * 3, POPSTAR, CHOSEN);
		}
	}

	//用户第一次选择后确认消除或取消
	if (cancel_confirm(curr_row, curr_col))
	{
		//将选择项进行消除
		GUI_eliminate(rand_matrix, mark_matrix, row, col);

		if (question == F)
		{
			gotoxy(0, row * 3 + 4);
			cout << "                                                ";
			gotoxy(0, row * 3 + 4);
			cout << "合成完成，回车键/单机左键下落0";

			while (!enter_click(ENTER));
		}

		block_fall(rand_matrix, row, col);
		block_left(rand_matrix, row, col);
		score = elmn_score(mark_matrix, row, col);
		total_score += score;

		gotoxy(0, 0);
		cout << "                                                ";
		gotoxy(0, 0);
		cout << "本次得分:" << score << ' ' << "总分:" << total_score;

		if (question == F)
		{
			gotoxy(0, row * 3 + 4);
			cout << "                                                ";
			gotoxy(0, row * 3 + 4);
			setcolor(0, COLOR_HRED);
			cout << "本次合成结束，按C/单机左键继续一次新的合成";
			setcolor();

			while (!enter_click(C));
		}

		setcursor(CURSOR_VISIBLE_NORMAL);
		return 1;
	}
	else return 0;
}

//子题目D：伪图形界面下用鼠标选择一个色块（无分隔线）
void D_GUI_choose_undvd(int(*rand_matrix)[10], char(*mark_matrix)[10], int &row, int &col, int &score, int &total_score)
{
	//当前所原则方块的行列
	int curr_row = 0, curr_col = 0;
	//选择方块上一次所在的方块行列
	int last_row = 0, last_col = 0;

	//初始化内部数组
	orig_matrix(rand_matrix, row, col, POPSTAR);
	orig_mark(mark_matrix, row, col);

	//打印外部框架
	print_frame(row, col, POPSTAR, UNDIVIDED);

	//打印色块
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			print_block(rand_matrix[i][j], 4 + j * 6, 3 + i * 3, POPSTAR, NORMAL);
		}
	}

	gotoxy(0, 0);
	cout << "屏幕当前设置为：" << 32 + (row - 8) * 3 << "行" << 55 + (col - 8) * 6 << "列";

	gotoxy(0, row * 3 + 4);
	cout << "箭头键/鼠标移动，回车键/单击左键选择并结束";

	//初始状态下第一个方块为选定状态
	print_block(rand_matrix[0][0], 4, 3, POPSTAR, CHOSEN);

	move(rand_matrix, mark_matrix, row, col, curr_row, curr_col, last_row, last_col, UNDIVIDED);
}

//子题目E：伪图形界面下用鼠标选择一个色块（有分隔线）
void E_GUI_choose_dvd(int(*rand_matrix)[10], char(*mark_matrix)[10], int &row, int &col, int &score, int &total_score)
{
	//当前所原则方块的行列
	int curr_row = 0, curr_col = 0;
	//选择方块上一次所在的方块行列
	int last_row = 0, last_col = 0;

	//初始化内部数组
	orig_matrix(rand_matrix, row, col, POPSTAR);
	orig_mark(mark_matrix, row, col);

	//打印外部框架
	print_frame(row, col, POPSTAR, DIVIDED);

	//打印色块
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			print_block(rand_matrix[i][j], 4 + j * 8, 3 + i * 4, POPSTAR, NORMAL);
		}
	}

	gotoxy(0, 0);
	cout << "屏幕当前设置为：" << 39 + (row - 8) * 4 << "行" << 69 + (col - 8) * 8 << "列";

	gotoxy(0, row * 4 + 3);
	cout << "箭头键/鼠标移动，回车键/单击左键选择并结束";

	//初始状态下第一个方块为选定状态
	print_block(rand_matrix[0][0], 4, 3, POPSTAR, CHOSEN);

	move(rand_matrix, mark_matrix, row, col, curr_row, curr_col, last_row, last_col, DIVIDED);
}

//子题目F：伪图形界面完成一次消除（分步骤）
void F_GUI_eliminate(int(*rand_matrix)[10], char(*mark_matrix)[10], int &row, int &col, int &score, int &total_score, int question)
{
	//当前所选择方块的行列
	int curr_row = 0, curr_col = 0;
	//选择方块上一次所在的方块行列
	int last_row = 0, last_col = 0;

	if (question == F)
	{
		//初始化内部数组
		orig_matrix(rand_matrix, row, col, POPSTAR);
		orig_mark(mark_matrix, row, col);

		//打印外部框架
		print_frame(row, col, POPSTAR, UNDIVIDED);

		//打印色块
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				print_block(rand_matrix[i][j], 4 + j * 6, 3 + i * 3, POPSTAR, NORMAL);
			}
		}

		gotoxy(0, 0);
		cout << "屏幕当前设置为：" << 32 + (row - 8) * 3 << "行" << 55 + (col - 8) * 6 << "列";
	}

	gotoxy(0, row * 3 + 4);
	cout << "箭头键/鼠标移动，回车键/单击左键选择并结束";


	//初始时第一列的第一个色块为选中状态
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
	setcursor(CURSOR_INVISIBLE);	//关闭光标

	while (loop) {
		/* 读鼠标/键盘，返回值为下述操作中的某一种, 当前鼠标位置在<X,Y>处 */
		ret = read_keyboard_and_mouse(X, Y, maction, keycode1, keycode2);

		if (ret == CCT_MOUSE_EVENT) {
			//将当前鼠标位置的坐标转化为对应的行列了，并判断位置当前位置是否合法
			if (cord_to_rc(rand_matrix, row, col, X, Y, curr_row, curr_col, last_row, last_col, POPSTAR, UNDIVIDED))
			{
				//如果当前鼠标所在方块与上一次所在方块不同才打印位置信息，否则会持续打印，产生频闪
				if ((curr_row != last_row) || (curr_col != last_col) || illegal)
				{
					//移动后将当前已选择的方块恢复
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

					//打印鼠标所在行列位置
					gotoxy(0, row * 3 + 4);
					cout << "                                                                             ";
					gotoxy(0, row * 3 + 4);
					cout << "[当前鼠标] " << char(curr_row + 65) << "行" << curr_col << "列";

					illegal = 0;
				}
			}
			else //位置非法
			{
				if (!illegal)
				{
					print_block(rand_matrix[last_row][last_col], 4 + last_col * 6, 3 + last_row * 3, POPSTAR, NORMAL);

					gotoxy(0, row * 3 + 4);
					cout << "                                                                             ";
					gotoxy(0, row * 3 + 4);
					cout << "[当前鼠标]" << "位置非法";

					illegal = 1;

					continue;
				}
			}

			//对于鼠标只需要单击左键的操作
			switch (maction)
			{
			case MOUSE_LEFT_BUTTON_CLICK:			//按下左键
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
					cout << "周围无相同值，";
					setcolor();
					cout << "箭头键/鼠标移动，回车键/单击左键选择";
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
					cout << "[当前键盘] " << char(curr_row + 65) << "行" << curr_col << "列";
					break;
				case KB_ARROW_DOWN:
					go_down(rand_matrix, row, col, curr_row, curr_col, last_row, last_col, UNDIVIDED);
					gotoxy(0, row * 3 + 4);
					cout << "                                                                             ";
					gotoxy(0, row * 3 + 4);
					cout << "[当前键盘] " << char(curr_row + 65) << "行" << curr_col << "列";
					break;
				case KB_ARROW_LEFT:
					go_left(rand_matrix, row, col, curr_row, curr_col, last_row, last_col, UNDIVIDED);
					gotoxy(0, row * 3 + 4);
					cout << "                                                                             ";
					gotoxy(0, row * 3 + 4);
					cout << "[当前键盘] " << char(curr_row + 65) << "行" << curr_col << "列";
					break;
				case KB_ARROW_RIGHT:
					go_right(rand_matrix, row, col, curr_row, curr_col, last_row, last_col, UNDIVIDED);
					gotoxy(0, row * 3 + 4);
					cout << "                                                                             ";
					gotoxy(0, row * 3 + 4);
					cout << "[当前键盘] " << char(curr_row + 65) << "行" << curr_col << "列";
					break;
				}

				//移动后将当前已选择的方块恢复
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
					cout << "周围无相同值，";
					setcolor();
					cout << "箭头键/鼠标移动，回车键/单击左键选择";
					continue;
				}
			}
		}
	}
}

//子题目G：伪图形界面完整版
void G_GUI_complete(int(*rand_matrix)[10], char(*mark_matrix)[10], int &row, int &col, int &score, int &total_score)
{
	//当前所选择方块的行列
	int curr_row = 0, curr_col = 0;
	//选择方块上一次所在的方块行列
	int last_row = 0, last_col = 0;

	//初始化内部数组
	orig_matrix(rand_matrix, row, col, POPSTAR);
	orig_mark(mark_matrix, row, col);

	//打印外部框架
	print_frame(row, col, POPSTAR, UNDIVIDED);

	//打印色块
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			print_block(rand_matrix[i][j], 4 + j * 6, 3 + i * 3, POPSTAR, NORMAL);
		}
	}

	gotoxy(0, 0);
	cout << "屏幕当前设置为：" << 32 + (row - 8) * 3 << "行" << 55 + (col - 8) * 6 << "列";

	while (1)
	{
		F_GUI_eliminate(rand_matrix, mark_matrix, row, col, score, total_score, G);

		if (end_judge(rand_matrix, row, col))
		{
			gotoxy(0, row * 3 + 4);
			cout << "                                                         ";
			gotoxy(0, row * 3 + 4);
			setcolor(0, COLOR_HRED);
			cout << "本关结束！剩余" << remain_num(rand_matrix, row, col) << "项！按回车键继续下一关！";
			setcolor();

			while (_getch() != '\r');

			return;
		}
		else continue;
	}
}

//可读取配置文件的伪图形界面完整版
void GUI_full_cfg(const char *cfgfile_name)
{
	Cord orig_cord; //这个东西在打印色块的时候进行坐标定位的时候需要

	int score; //记录分数用的

	//定义游戏区域结构体变量
	Game_area game_area;
	//色块结构体变量
	Block popstar_block;

	popstar_block.type = POPSTAR;
	//色块颜色信息变量
	Block_color block_color;

	//从配置文件中读取信息
	read_game_cfg(cfgfile_name, game_area, popstar_block, block_color);

	//print_game_cfg(game_area, popstar_block, block_color);
	//return;

	//初始化内部数组
	orig_matrix(game_area.rand_matrix, game_area.matrix_row, game_area.matrix_col, POPSTAR);
	orig_mark(game_area.mark_matrix, game_area.matrix_row, game_area.matrix_col);

	//打印游戏界面
	print_game_area(game_area, popstar_block);

	//打印色块
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
		//初始时第一列的第一个色块为选中状态
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
			cout << "箭头键/鼠标移动，回车键/单机左键选择并结束";
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
				cout << "周围无相同值!";
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
				cout << "本关结束！剩余" << remain_num(game_area.rand_matrix, game_area.matrix_row, game_area.matrix_col) << "项！按回车键继续下一关！";
				setcolor();
			}

			while (_getch() != '\r');

			return;
		}
		else continue;
	}
}

//该函数用于执行选定方块之后的操作(配合可读取配置文件版本使用）
int elmn_fall_cfg(Game_area &game_area, Block block,Block_color block_color,int &score)
{
	Cord orig_cord; //定位用
	
	if (game_area.bot_info)
	{
		gotoxy(0, game_area.orig_cord.cord_y + game_area.matrix_row*(block.height + 1) + 3);
		setcolor(game_area.norm_info_color.bg_color, game_area.norm_info_color.fg_color);
		cout << "箭头键/鼠标移动，回车键/单机左键选择并结束";
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
		//将选择项删除
		GUI_eliminate_cfg(game_area, block, block_color);

		block_fall_cfg(game_area, block, block_color);
		block_left_cfg(game_area, block, block_color);

		score = elmn_score(game_area.mark_matrix, game_area.matrix_row, game_area.matrix_col);
		game_area.total_score += score;

		if (game_area.top_info)
		{
			gotoxy(0, 0);
			setcolor(game_area.norm_info_color.bg_color, game_area.norm_info_color.fg_color);
			cout << "本次得分:" << score << ' ' << "总得分:" << game_area.total_score;
			setcolor();
		}

		setcursor(CURSOR_VISIBLE_NORMAL);
		return 1;
	}
	else return 0;
}

//该函数用于伪图形界面下的一次消除(配合可读取配置文件版本使用）
void GUI_eliminate_cfg(Game_area &game_area, Block block, Block_color block_color)
{
	Cord orig_cord; //定位用的
	
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

//该函数用于整列左移
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

//从配置文件中读取配置信息（使用C语言的工具函数集）
int read_game_cfg(const char *cfg_name, Game_area &game_area, Block &block, Block_color &block_color)
{
	FILE *cfgfile;
	
	cfgfile = open_cfgfile(cfg_name, OPEN_OPT_RDONLY);

	if (cfgfile == NULL)
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
	if (item_get_value(cfgfile, "区域设置", "行数", &game_area.matrix_row, TYPE_INT))
	{
		if (game_area.matrix_row < 8 || game_area.matrix_row > 10)
		{
			//超出范围取缺省值
			game_area.matrix_row = 10;
		}
	}
	else game_area.matrix_row = 10;

	if (item_get_value(cfgfile, "区域设置", "列数", &game_area.matrix_col, TYPE_INT))
	{
		if (game_area.matrix_col < 8 || game_area.matrix_col > 10)
		{
			//超出范围取缺省值
			game_area.matrix_col = 10;
		}
	}
	else game_area.matrix_col = 10;

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
		if (block.move_delay_time < 3 || block.move_delay_time>100)
		{
			block.move_delay_time = 10;
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
	if (block.type == POPSTAR)
	{
		item_get_value(cfgfile, "色块设置", "色块1-前景色", &block_color.block_color_1.fg_color, TYPE_INT);
		if (block_color.block_color_1.fg_color < 0 || block_color.block_color_1.fg_color>15)
		{
			block_color.block_color_1.fg_color = 0;
		}

		item_get_value(cfgfile, "色块设置", "色块1-背景色", &block_color.block_color_1.bg_color, TYPE_INT);
		if (block_color.block_color_1.bg_color < 0 || block_color.block_color_1.bg_color>15)
		{
			block_color.block_color_1.bg_color = 9;
		}

		item_get_value(cfgfile, "色块设置", "色块2-前景色", &block_color.block_color_2.fg_color, TYPE_INT);
		if (block_color.block_color_2.fg_color < 0 || block_color.block_color_2.fg_color>15)
		{
			block_color.block_color_2.fg_color = 0;
		}

		item_get_value(cfgfile, "色块设置", "色块2-背景色", &block_color.block_color_2.bg_color, TYPE_INT);
		if (block_color.block_color_2.bg_color < 0 || block_color.block_color_2.bg_color>15)
		{
			block_color.block_color_2.bg_color = 10;
		}

		item_get_value(cfgfile, "色块设置", "色块3-前景色", &block_color.block_color_3.fg_color, TYPE_INT);
		if (block_color.block_color_3.fg_color < 0 || block_color.block_color_3.fg_color>15)
		{
			block_color.block_color_3.fg_color = 0;
		}

		item_get_value(cfgfile, "色块设置", "色块3-背景色", &block_color.block_color_3.bg_color, TYPE_INT);
		if (block_color.block_color_3.bg_color < 0 || block_color.block_color_3.bg_color>15)
		{
			block_color.block_color_2.bg_color = 11;
		}

		item_get_value(cfgfile, "色块设置", "色块4-前景色", &block_color.block_color_4.fg_color, TYPE_INT);
		if (block_color.block_color_4.fg_color < 0 || block_color.block_color_4.fg_color>15)
		{
			block_color.block_color_4.fg_color = 12;
		}

		item_get_value(cfgfile, "色块设置", "色块4-背景色", &block_color.block_color_4.bg_color, TYPE_INT);
		if (block_color.block_color_4.bg_color < 0 || block_color.block_color_4.bg_color>15)
		{
			block_color.block_color_4.bg_color = 12;
		}

		item_get_value(cfgfile, "色块设置", "色块5-前景色", &block_color.block_color_5.fg_color, TYPE_INT);
		if (block_color.block_color_5.fg_color < 0 || block_color.block_color_5.fg_color>15)
		{
			block_color.block_color_5.fg_color = 0;
		}

		item_get_value(cfgfile, "色块设置", "色块5-背景色", &block_color.block_color_5.bg_color, TYPE_INT);
		if (block_color.block_color_5.bg_color < 0 || block_color.block_color_5.bg_color>15)
		{
			block_color.block_color_5.bg_color = 13;
		}
	}

	//读取选中色块颜色
	item_get_value(cfgfile, "色块设置", "选中色块背景色", &block_color.chosen_block_color.bg_color, TYPE_INT);
	if (block_color.chosen_block_color.bg_color < 0 || block_color.chosen_block_color.bg_color > 15)
	{
		block_color.chosen_block_color.bg_color = 5;
	}

	if (item_get_value(cfgfile, "色块设置", "选中色块前景色", &block_color.chosen_block_color.fg_color, TYPE_INT))
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