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