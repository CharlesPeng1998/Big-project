/*1751367 计2 彭健聪*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <ctime>
#include <cmath>
#include <cstdio>
#include <conio.h>
#include <Windows.h>
#include <fstream>
#include "cmd_console_tools.h"
#include "..\common\common_cfgfile_tools.hpp"
#include "common.h"
using namespace std;

//菜单函数，接收存放菜单项的指针数组，根据用户输入返回一个字符
char menu(const char *items[], int n)
{
	//记录最大菜单项的长度
	int max_len = int(strlen(items[0]));
	for (int i = 1; i < n; i++)
	{
		if (strlen(items[i]) > max_len) max_len = int(strlen(items[i]));
	}

	while (1)
	{
		//根据最长菜单项的长度打印横线
		for (int i = 0; i < max_len; i++)
		{
			cout << "-";
		}
		cout << endl;

		//打印菜单项
		for (int i = 0; i < n; i++)
		{
			cout << items[i] << endl;
		}

		//根据最长菜单项的长度打印横线
		for (int i = 0; i < max_len; i++)
		{
			cout << "-";
		}
		cout << endl;
		
		//接收用户输入选择项
		cout << "[请选择:]";
		char choice = _getch();

		if (choice >= 97) choice -= 32;//若输入小写字母坐标则需要转换为大写字母

		//根据用户输入返回不同字符
		for (int i = 0; i < n; i++)
		{
			if (choice == items[i][0]) return items[i][0];
			else;
		}
		cls();
		continue;
	}
}

//查找指定坐标位置及周围相同项的函数（非递归）
void mark(int(*rand_matrix)[10], char(*mark_matrix)[10], int cord_row, int cord_col, int Max_row, int Max_col)
{
	mark_matrix[cord_row][cord_col] = '*';
	bool stat = 1;//用于存储寻找连续项这一活动的状态
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

//内部数组移动函数(根据传入参数的不同进行不同的移动操作)
void matrix_move(int(*rand_matrix)[10], char(*mark_matrix)[10], int row, int col,int move_type)
{
	switch (move_type)
	{
	case DOWN: //根据冒泡原理使0上浮到每列的顶端
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
		int num_invalid = 0;//用于记录数组右侧的无效列的数量
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

//该函数用于判断本关是否结束
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

/*该函数用于显示初始外框架
  game为游戏的类型
  type为外框架的类型（有分割线/无分割线）
  根据传入的参数不同显示不同的外框架*/
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
			//设置命令行窗口的大小
			setconsoleborder(55 + (col - 8) * 6, 32 + (row - 8) * 3);
			gotoxy(0, 1);

			cout << "      ";
			//打印列号
			for (int i = 0; i < col; i++)
			{
				cout << i << "     ";
			}

			cout << endl << endl << endl;
			//打印英文行号
			for (int i = 0; i < row; i++)
			{
				cout << char(i + 65) << endl << endl << endl;
			}

			gotoxy(2, 2);
			//以下三句打印上边框
			print_unicode("╔", COLOR_HWHITE, COLOR_BLACK, 1);
			print_unicode("═", COLOR_HWHITE, COLOR_BLACK, col * 3);
			print_unicode("╗", COLOR_HWHITE, COLOR_BLACK, 1);

			//打印左右边框
			for (int i = 3; i < row * 3 + 3; i++)
			{
				gotoxy(2, i);
				print_unicode("║", COLOR_HWHITE, COLOR_BLACK, 1);
				for (int j = 0; j < col * 2; j++)
				{
					print_unicode("   ", COLOR_HWHITE, COLOR_BLACK, 1);
				}

				print_unicode("║", COLOR_HWHITE, COLOR_BLACK, 1);
			}

			//打印下边框
			gotoxy(2, row * 3 + 3);
			print_unicode("╚", COLOR_HWHITE, COLOR_BLACK, 1);
			print_unicode("═", COLOR_HWHITE, COLOR_BLACK, col * 3);
			print_unicode("╝", COLOR_HWHITE, COLOR_BLACK, 1);

			break;
		}

		case DIVIDED:
		{
			int curr_x, curr_y;//定义两个坐标，寻找打印位置时需要用到
			
			//设置命令行窗口的大小
			setconsoleborder(69 + (col - 8) * 8, 39 + (row - 8) * 4);
			gotoxy(0, 1);

			cout << "      ";
			//打印列号
			for (int i = 0; i < col; i++)
			{
				cout << i << "       ";
			}

			cout << endl << endl << endl;
			//打印英文行号
			for (int i = 0; i < row; i++)
			{
				cout << char(i + 65) << endl << endl << endl<<endl;
			}

			gotoxy(2, 2);
			//打印上边框
			print_unicode("╔", COLOR_HWHITE, COLOR_BLACK, 1);

			for (int i = 0; i < col - 1; i++)
			{
				print_unicode("═", COLOR_HWHITE, COLOR_BLACK, 3);
				print_unicode("╤", COLOR_HWHITE, COLOR_BLACK, 1);
			}

			print_unicode("═", COLOR_HWHITE, COLOR_BLACK, 3);
			print_unicode("╗", COLOR_HWHITE, COLOR_BLACK, 1);

			for (int i = 0; i < row - 1; i++)
			{
				for (int j = 0; j < 3; j++)
				{		
					cout << endl;
					getxy(curr_x, curr_y);
					gotoxy(curr_x + 2, curr_y);
					print_unicode("║", COLOR_HWHITE, COLOR_BLACK, 1);

					for (int k = 0; k < col - 1; k++)
					{
						print_unicode("      ", COLOR_HWHITE, COLOR_BLACK, 1);
						print_unicode("│", COLOR_HWHITE, COLOR_BLACK, 1);
					}
					print_unicode("      ", COLOR_HWHITE, COLOR_BLACK, 1);

					print_unicode("║", COLOR_HWHITE, COLOR_BLACK, 1);
					//cout << endl;
				}

				cout << endl;
				getxy(curr_x, curr_y);
				gotoxy(curr_x + 2, curr_y);
				print_unicode("╟", COLOR_HWHITE, COLOR_BLACK, 1);
				for (int j = 0; j < col - 1; j++)
				{
					print_unicode("───", COLOR_HWHITE, COLOR_BLACK, 1);
					print_unicode("┼", COLOR_HWHITE, COLOR_BLACK, 1);
				}
				print_unicode("───", COLOR_HWHITE, COLOR_BLACK, 1);
				print_unicode("╢", COLOR_HWHITE, COLOR_BLACK, 1);
				//cout << endl;
			}

			for (int j = 0; j < 3; j++)
			{
				cout << endl;
				getxy(curr_x, curr_y);
				gotoxy(curr_x + 2, curr_y);
				print_unicode("║", COLOR_HWHITE, COLOR_BLACK, 1);

				for (int k = 0; k < col - 1; k++)
				{
					print_unicode("      ", COLOR_HWHITE, COLOR_BLACK, 1);
					print_unicode("│", COLOR_HWHITE, COLOR_BLACK, 1);
				}
				print_unicode("      ", COLOR_HWHITE, COLOR_BLACK, 1);

				print_unicode("║", COLOR_HWHITE, COLOR_BLACK, 1);
				//cout << endl;
			}

			//打印下边框
			cout << endl;
			getxy(curr_x, curr_y);
			gotoxy(curr_x + 2, curr_y);
			print_unicode("╚", COLOR_HWHITE, COLOR_BLACK, 1);

			for (int i = 0; i < col - 1; i++)
			{
				print_unicode("═", COLOR_HWHITE, COLOR_BLACK, 3);
				print_unicode("╧", COLOR_HWHITE, COLOR_BLACK, 1);
			}

			print_unicode("═", COLOR_HWHITE, COLOR_BLACK, 3);
			print_unicode("╝", COLOR_HWHITE, COLOR_BLACK, 1);
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
			//设置命令行窗口的大小
			setconsoleborder(35 + (col - 5) * 6, 22 + (row - 5) * 3);

			gotoxy(0, 1);
			//以下三句打印上边框
			print_unicode("┏", COLOR_HWHITE, COLOR_BLACK, 1);
			print_unicode("━", COLOR_HWHITE, COLOR_BLACK, col * 3);
			print_unicode("┓", COLOR_HWHITE, COLOR_BLACK, 1);

			//打印左右边框
			for (int i = 2; i < row * 3 + 2; i++)
			{
				print_unicode("┃", COLOR_HWHITE, COLOR_BLACK, 1);
				for (int j = 0; j < col * 2; j++)
				{
					print_unicode("   ", COLOR_HWHITE, COLOR_BLACK, 1);
				}

				print_unicode("┃", COLOR_HWHITE, COLOR_BLACK, 1);
				cout << endl;
			}

			//打印下边框
			print_unicode("┗", COLOR_HWHITE, COLOR_BLACK, 1);
			print_unicode("━", COLOR_HWHITE, COLOR_BLACK, col * 3);
			print_unicode("┛", COLOR_HWHITE, COLOR_BLACK, 1);

			break;
		}
		case DIVIDED:
		{
			setconsoleborder(43 + (col - 5) * 8, 26 + (row - 5) * 4);
			
			gotoxy(0, 1);
			//打印上边框
			print_unicode("┏", COLOR_HWHITE, COLOR_BLACK, 1);

			for (int i = 0; i < col - 1; i++)
			{
				print_unicode("━", COLOR_HWHITE, COLOR_BLACK, 3);
				print_unicode("┳", COLOR_HWHITE, COLOR_BLACK, 1);
			}

			print_unicode("━", COLOR_HWHITE, COLOR_BLACK, 3);
			print_unicode("┓", COLOR_HWHITE, COLOR_BLACK, 1);

			//打印左右边框
			for (int i = 0; i < row - 1; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					print_unicode("┃", COLOR_HWHITE, COLOR_BLACK, 1);

					for (int k = 0; k < col - 1; k++)
					{
						print_unicode("      ", COLOR_HWHITE, COLOR_BLACK, 1);
						print_unicode("┃", COLOR_HWHITE, COLOR_BLACK, 1);
					}
					print_unicode("      ", COLOR_HWHITE, COLOR_BLACK, 1);

					print_unicode("┃", COLOR_HWHITE, COLOR_BLACK, 1);
					cout << endl;
				}

				print_unicode("┣", COLOR_HWHITE, COLOR_BLACK, 1);
				for (int j = 0; j < col - 1; j++)
				{
					print_unicode("━━━", COLOR_HWHITE, COLOR_BLACK, 1);
					print_unicode("╋", COLOR_HWHITE, COLOR_BLACK, 1);
				}
				print_unicode("━━━", COLOR_HWHITE, COLOR_BLACK, 1);
				print_unicode("┫", COLOR_HWHITE, COLOR_BLACK, 1);
				cout << endl;

			}

			for (int j = 0; j < 3; j++)
			{
				print_unicode("┃", COLOR_HWHITE, COLOR_BLACK, 1);

				for (int k = 0; k < col - 1; k++)
				{
					print_unicode("      ", COLOR_HWHITE, COLOR_BLACK, 1);
					print_unicode("┃", COLOR_HWHITE, COLOR_BLACK, 1);
				}
				print_unicode("      ", COLOR_HWHITE, COLOR_BLACK, 1);

				print_unicode("┃", COLOR_HWHITE, COLOR_BLACK, 1);
				cout << endl;
			}

			//打印下边框
			print_unicode("┗", COLOR_HWHITE, COLOR_BLACK, 1);

			for (int i = 0; i < col - 1; i++)
			{
				print_unicode("━", COLOR_HWHITE, COLOR_BLACK, 3);
				print_unicode("┻", COLOR_HWHITE, COLOR_BLACK, 1);
			}

			print_unicode("━", COLOR_HWHITE, COLOR_BLACK, 3);
			print_unicode("┛", COLOR_HWHITE, COLOR_BLACK, 1);
		}
		}
	}
	}
}

/*该函数用于打印一个色块
  可自定义色块的长和宽；
  需要色块的游戏；
  以及色块的类型（正常/当前/选中）*/
void print_block(int value, int cord_x, int cord_y,int game,int type)
{
	switch (game)
	{
	case POPSTAR:
	{
		int bg_color=0;//记录色块的背景色
		
		gotoxy(cord_x, cord_y);
		
		//根据内部数组的值选择不同的色块颜色
		switch (value)
		{
		case 1:bg_color = COLOR_HRED; break;
		case 2:bg_color = COLOR_HBLUE; break;
		case 3:bg_color = COLOR_HGREEN; break;
		case 4:bg_color = COLOR_HYELLOW; break;
		case 5:bg_color = COLOR_HPINK; break;
		case 0:type=EMP; break; //若内部数组值为0这打印空块，即框架背景色
		}

		//根据色块的类型打印不同的前景色
		switch (type)
		{
		case NORMAL:
		{	
			setcolor(bg_color, COLOR_BLACK);
			
			cout << "╔" << "═" << "╗";
			getxy(cord_x, cord_y);
			gotoxy(cord_x - 6, cord_y + 1);
			cout << "║" <<"★"<< "║";
			getxy(cord_x, cord_y);
			gotoxy(cord_x - 6, cord_y + 1);
			cout << "╚" << "═" << "╝";

			setcolor();
			break;
		}
		case CHOSEN:
		{
			setcolor(bg_color, COLOR_WHITE);

			cout << "╔" << "═" << "╗";
			getxy(cord_x, cord_y);
			gotoxy(cord_x - 6, cord_y + 1);
			cout << "║" << "★" << "║";
			getxy(cord_x, cord_y);
			gotoxy(cord_x - 6, cord_y + 1);
			cout << "╚" << "═" << "╝";

			setcolor();
			break;
		}
		case EMP:
		{
			setcolor(COLOR_HWHITE, COLOR_HWHITE);

			cout << "╔" << "═" << "╗";
			getxy(cord_x, cord_y);
			gotoxy(cord_x - 6, cord_y + 1);
			cout << "║" << "★" << "║";
			getxy(cord_x, cord_y);
			gotoxy(cord_x - 6, cord_y + 1);
			cout << "╚" << "═" << "╝";

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
			//根据值的不同打印不同颜色方块
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
			cout << "┏" << "━" << "┓";
			getxy(cord_x, cord_y);
			gotoxy(cord_x - 6, cord_y + 1);
			cout << "┃" << ' ' << value << "┃";
			getxy(cord_x, cord_y);
			gotoxy(cord_x - 6, cord_y + 1);
			cout << "┗" << "━" << "┛";
		}
		else
		{
			cout << "┏" << "━" << "┓";
			getxy(cord_x, cord_y);
			gotoxy(cord_x - 6, cord_y + 1);
			cout << "┃" << value << "┃";
			getxy(cord_x, cord_y);
			gotoxy(cord_x - 6, cord_y + 1);
			cout << "┗" << "━" << "┛";
		}

		setcolor();
	}
	}
}

//该函数用于一个色块的下落
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
		cout << "━━━";
		setcolor();
		print_block(target, cord_x, cord_y, MAKE10, NORMAL);
		break;
	}
}

//该函数用于显示游戏区域（配合配置文件使用）
void print_game_area(Game_area game_area, Block block)
{
	//用来临时记录坐标，方便光标的移动
	Cord temp_cord;

	if (game_area.divided != 1)
	{
		//无分割线版本
		
		//屏幕大小先这样吧，后续可能会有扩展
		setconsoleborder(game_area.matrix_col*block.width + 10, game_area.matrix_row*block.height + 10);

		//我打算先把界面显示出来再去考虑显示行列标号
		gotoxy(game_area.orig_cord.cord_x + 2, game_area.orig_cord.cord_y + 1);

		//以下三句打印上边框
		print_unicode(game_area.border[0], game_area.game_area_color.bg_color, game_area.game_area_color.fg_color, 1);
		print_unicode(game_area.border[4], game_area.game_area_color.bg_color, game_area.game_area_color.fg_color, game_area.matrix_col * block.width/2);
		print_unicode(game_area.border[2], game_area.game_area_color.bg_color, game_area.game_area_color.fg_color, 1);

		//打印左右边框
		for (int i = 0; i < game_area.matrix_row * block.height; i++)
		{
			getxy(temp_cord.cord_x, temp_cord.cord_y);
			gotoxy(game_area.orig_cord.cord_x + 2, temp_cord.cord_y + 1);
			
			print_unicode(game_area.border[5], game_area.game_area_color.bg_color, game_area.game_area_color.fg_color, 1);
			for (int j = 0; j < game_area.matrix_col*block.width; j++)
			{
				print_unicode(" ", game_area.game_area_color.bg_color, game_area.game_area_color.fg_color, 1);
			}

			print_unicode(game_area.border[5], game_area.game_area_color.bg_color, game_area.game_area_color.fg_color, 1);
		}

		//打印下边框
		getxy(temp_cord.cord_x, temp_cord.cord_y);
		gotoxy(game_area.orig_cord.cord_x + 2, temp_cord.cord_y + 1);

		print_unicode(game_area.border[1], game_area.game_area_color.bg_color, game_area.game_area_color.fg_color, 1);
		print_unicode(game_area.border[4], game_area.game_area_color.bg_color, game_area.game_area_color.fg_color, game_area.matrix_col * block.width / 2);
		print_unicode(game_area.border[3], game_area.game_area_color.bg_color, game_area.game_area_color.fg_color, 1);

		//然后再考虑要不要打印行列编号
		if (game_area.show_row_col_number == 1)
		{
			setcolor(0, COLOR_HBLUE);
			
			gotoxy(game_area.orig_cord.cord_x, game_area.orig_cord.cord_y);

			cout << "      ";
			//打印列号
			for (int i = 0; i < game_area.matrix_col; i++)
			{
				cout << i;
				for (int j = 0; j < block.width-1; j++)
				{
					cout << ' ';
				}
			}

			for (int i = 0; i < 3; i++)
			{
				getxy(temp_cord.cord_x, temp_cord.cord_y);
				gotoxy(game_area.orig_cord.cord_x, temp_cord.cord_y + 1);
			}

			//打印英文行号
			for (int i = 0; i < game_area.matrix_row; i++)
			{
				cout << char(i + 65);

				for (int j = 0; j < block.height; j++)
				{
					getxy(temp_cord.cord_x, temp_cord.cord_y);
					gotoxy(game_area.orig_cord.cord_x, temp_cord.cord_y + 1);
				}
			}
		}
	}

	else if (game_area.divided == 1)
	{
		//带有分割线版本
		setconsoleborder(game_area.matrix_col*(block.width+2) + 10, game_area.matrix_row*(block.height+1) + 10);

		gotoxy(game_area.orig_cord.cord_x + 2, game_area.orig_cord.cord_y + 1);

		//打印上边框
		print_unicode(game_area.border[0], game_area.game_area_color.bg_color, game_area.game_area_color.fg_color, 1);

		for (int i = 0; i < game_area.matrix_col - 1; i++)
		{
			print_unicode(game_area.border[4], game_area.game_area_color.bg_color, game_area.game_area_color.fg_color, 3);
			print_unicode(game_area.border[6], game_area.game_area_color.bg_color, game_area.game_area_color.fg_color, 1);
		}

		print_unicode(game_area.border[4], game_area.game_area_color.bg_color, game_area.game_area_color.fg_color, 3);
		print_unicode(game_area.border[2], game_area.game_area_color.bg_color, game_area.game_area_color.fg_color, 1);

		for (int i = 0; i < game_area.matrix_row - 1; i++)
		{
			for (int j = 0; j < block.height; j++)
			{
				getxy(temp_cord.cord_x, temp_cord.cord_y);
				gotoxy(game_area.orig_cord.cord_x + 2, temp_cord.cord_y + 1);

				print_unicode(game_area.border[5], game_area.game_area_color.bg_color, game_area.game_area_color.fg_color, 1);

				for (int k = 0; k < game_area.matrix_col - 1; k++)
				{
					print_unicode(" ", game_area.game_area_color.bg_color, game_area.game_area_color.fg_color, block.width);
					print_unicode(game_area.border[5], game_area.game_area_color.bg_color, game_area.game_area_color.fg_color, 1);
				}
				print_unicode(" ", game_area.game_area_color.bg_color, game_area.game_area_color.fg_color, block.width);
				print_unicode(game_area.border[5], game_area.game_area_color.bg_color, game_area.game_area_color.fg_color, 1);
			}

			getxy(temp_cord.cord_x, temp_cord.cord_y);
			gotoxy(game_area.orig_cord.cord_x + 2, temp_cord.cord_y + 1);

			print_unicode(game_area.border[8], game_area.game_area_color.bg_color, game_area.game_area_color.fg_color, 1);
			for (int j = 0; j < game_area.matrix_col - 1; j++)
			{
				print_unicode(game_area.border[4], game_area.game_area_color.bg_color, game_area.game_area_color.fg_color, block.width/2);
				print_unicode(game_area.border[10], game_area.game_area_color.bg_color, game_area.game_area_color.fg_color, 1);
			}
			print_unicode(game_area.border[4], game_area.game_area_color.bg_color, game_area.game_area_color.fg_color, block.width / 2);
			print_unicode(game_area.border[9], game_area.game_area_color.bg_color, game_area.game_area_color.fg_color, 1);
		}

		for (int j = 0; j < block.height; j++)
		{
			getxy(temp_cord.cord_x, temp_cord.cord_y);
			gotoxy(game_area.orig_cord.cord_x + 2, temp_cord.cord_y + 1);

			print_unicode(game_area.border[5], game_area.game_area_color.bg_color, game_area.game_area_color.fg_color, 1);

			for (int k = 0; k < game_area.matrix_col - 1; k++)
			{
				print_unicode(" ", game_area.game_area_color.bg_color, game_area.game_area_color.fg_color, block.width);
				print_unicode(game_area.border[5], game_area.game_area_color.bg_color, game_area.game_area_color.fg_color, 1);
			}
			print_unicode(" ", game_area.game_area_color.bg_color, game_area.game_area_color.fg_color, block.width);
			print_unicode(game_area.border[5], game_area.game_area_color.bg_color, game_area.game_area_color.fg_color, 1);
		}

		//打印下边框
		getxy(temp_cord.cord_x, temp_cord.cord_y);
		gotoxy(game_area.orig_cord.cord_x + 2, temp_cord.cord_y + 1);
		print_unicode(game_area.border[1], game_area.game_area_color.bg_color, game_area.game_area_color.fg_color, 1);

		for (int i = 0; i < game_area.matrix_col - 1; i++)
		{
			print_unicode(game_area.border[4], game_area.game_area_color.bg_color, game_area.game_area_color.fg_color, 3);
			print_unicode(game_area.border[7], game_area.game_area_color.bg_color, game_area.game_area_color.fg_color, 1);
		}

		print_unicode(game_area.border[4], game_area.game_area_color.bg_color, game_area.game_area_color.fg_color, 3);
		print_unicode(game_area.border[3], game_area.game_area_color.bg_color, game_area.game_area_color.fg_color, 1);

		//然后再考虑要不要打印行列编号
		if (game_area.show_row_col_number == 1)
		{
			setcolor(0, COLOR_HBLUE);

			gotoxy(game_area.orig_cord.cord_x, game_area.orig_cord.cord_y);

			cout << "      ";
			//打印列号
			for (int i = 0; i < game_area.matrix_col; i++)
			{
				cout << i;
				for (int j = 0; j < block.width+1; j++)
				{
					cout << ' ';
				}
			}

			for (int i = 0; i < 3; i++)
			{
				getxy(temp_cord.cord_x, temp_cord.cord_y);
				gotoxy(game_area.orig_cord.cord_x, temp_cord.cord_y + 1);
			}

			//打印英文行号
			for (int i = 0; i < game_area.matrix_row; i++)
			{
				cout << char(i + 65);

				for (int j = 0; j < block.height+1; j++)
				{
					getxy(temp_cord.cord_x, temp_cord.cord_y);
					gotoxy(game_area.orig_cord.cord_x, temp_cord.cord_y + 1);
				}
			}
		}
	}

	setcolor();
}

//该函数用于打印一个方块（配合配置文件使用）
void print_block_cfg(int value, Cord cord, Block block, Block_color block_color, int type)
{
	if (block.type == MAKE10)
	{
		//游戏为合成十的情况
		block.value.value_num = value;

		//考虑色块的类型：正常 / 选中 / 空白
		if (type == CHOSEN)
		{
			setcolor(block_color.chosen_block_color.bg_color, block_color.chosen_block_color.fg_color);
		}
		else if (type == EMP)
		{
			setcolor(block_color.eliminated_block_color.bg_color, block_color.eliminated_block_color.fg_color);
		}
		else
		{
			//根据值的不同打印不同颜色方块
			switch (value)
			{
			case 1:setcolor(block_color.block_color_1.bg_color, block_color.block_color_1.fg_color); break;
			case 2:setcolor(block_color.block_color_2.bg_color, block_color.block_color_2.fg_color); break;
			case 3:setcolor(block_color.block_color_3.bg_color, block_color.block_color_3.fg_color); break;
			case 4:setcolor(block_color.block_color_4.bg_color, block_color.block_color_4.fg_color); break;
			case 5:setcolor(block_color.block_color_5.bg_color, block_color.block_color_5.fg_color); break;
			case 6:setcolor(block_color.block_color_6.bg_color, block_color.block_color_6.fg_color); break;
			case 7:setcolor(block_color.block_color_7.bg_color, block_color.block_color_7.fg_color); break;
			case 8:setcolor(block_color.block_color_8.bg_color, block_color.block_color_8.fg_color); break;
			case 9:setcolor(block_color.block_color_9.bg_color, block_color.block_color_9.fg_color); break;
			case 10:setcolor(block_color.block_color_10.bg_color, block_color.block_color_10.fg_color); break;
			case 11:setcolor(block_color.block_color_11.bg_color, block_color.block_color_11.fg_color); break;
			}
		}
	}
	else if (block.type == POPSTAR)
	{
		//游戏为合成十的情况
		strcpy(block.value.value_star,"★");

		//考虑色块的类型：正常 / 选中 / 空白
		if (type == CHOSEN)
		{
			setcolor(block_color.chosen_block_color.bg_color, block_color.chosen_block_color.fg_color);
		}
		else if (type == EMP)
		{
			setcolor(block_color.eliminated_block_color.bg_color, block_color.eliminated_block_color.fg_color);
		}
		else
		{
			//根据值的不同打印不同颜色方块
			switch (value)
			{
			case 1:setcolor(block_color.block_color_1.bg_color, block_color.block_color_1.fg_color); break;
			case 2:setcolor(block_color.block_color_2.bg_color, block_color.block_color_2.fg_color); break;
			case 3:setcolor(block_color.block_color_3.bg_color, block_color.block_color_3.fg_color); break;
			case 4:setcolor(block_color.block_color_4.bg_color, block_color.block_color_4.fg_color); break;
			case 5:setcolor(block_color.block_color_5.bg_color, block_color.block_color_5.fg_color); break;
			}
		}
	}

	//移动到指定起始坐标
	gotoxy(cord.cord_x, cord.cord_y);

	//首先打印一个色块的第一行
	cout << block.frame[0];
	for (int i = 0; i < block.width / 2 - 2; i++)
	{
		cout << block.frame[4];
	}
	cout << block.frame[2];

	//接着我们会在第二行当中打印色块的值
	getxy(cord.cord_x, cord.cord_y);
	gotoxy(cord.cord_x - block.width, cord.cord_y + 1);

	cout << block.frame[5];
	for (int i = 0; i < (block.width - 4) / 4; i++)
	{
		cout << ' ';
	}

	switch (block.type)
	{
	case POPSTAR:cout << block.value.value_star; break;
	case MAKE10:cout << setw(2) << block.value.value_num; break;
	}
	
	for (int i = 0; i < (block.width - 4) / 4; i++)
	{
		cout << ' ';
	}

	cout << block.frame[5];

	//接着打印剩下的除最后一行以外的色块边框
	for (int i = 0; i < block.height - 3; i++)
	{
		getxy(cord.cord_x, cord.cord_y);
		gotoxy(cord.cord_x - block.width, cord.cord_y + 1);

		cout << block.frame[5];
		for (int i = 0; i < block.width / 2 - 2; i++)
		{
			cout << "  ";
		}
		cout << block.frame[5];
	}

	//最后我们打印最后一行
	getxy(cord.cord_x, cord.cord_y);
	gotoxy(cord.cord_x - block.width, cord.cord_y + 1);

	cout << block.frame[1];
	for (int i = 0; i < block.width / 2 - 2; i++)
	{
		cout << block.frame[4];
	}
	cout << block.frame[3];

	setcolor();
}

//该函数用于一个色块的移动（配合配置文件使用）
void block_move_cfg(Game_area game_area, Block block, Block_color block_color, int cord_row, int cord_col, int direction)
{
	//记录所移动色块的值
	int target = game_area.rand_matrix[cord_row][cord_col];
	
	//我们先来写没有分割线游戏界面下的移动吧
	if (game_area.divided != 1)
	{
		//该色块在屏幕中的起始坐标
		Cord orig_cord,curr_cord;
		orig_cord.cord_x = (game_area.orig_cord.cord_x + 4) + cord_row * block.width;
		orig_cord.cord_y = (game_area.orig_cord.cord_y + 2) + cord_row * block.height;

		curr_cord.cord_x = orig_cord.cord_x;
		curr_cord.cord_y = orig_cord.cord_y;

		//当然我们先向下移动
		if (direction == DOWN)
		{
			for (int i = 0; i < block.height + 1; i++)
			{
				//色块原位置打印空白
				print_block_cfg(target, orig_cord, block, block_color, EMP);
				print_block_cfg(target, curr_cord, block, block_color, NORMAL);

				curr_cord.cord_y;
				Sleep(10);
			}
		}

		//接下来是向左移动
		else if (direction == LEFT)
		{
			for (int i = 0; i < block.width + 1; i++)
			{
				//色块原位置打印空白
				print_block_cfg(target, orig_cord, block, block_color, EMP);
				print_block_cfg(target, curr_cord, block, block_color, NORMAL);

				curr_cord.cord_x--;
				Sleep(10);
			}
		
		}
	}

	//下面来写有分割线版本的
	else if (game_area.divided == 1)
	{
		//该色块在屏幕中的起始坐标
		Cord orig_cord, curr_cord;
		orig_cord.cord_x = (game_area.orig_cord.cord_x + 4) + cord_row * (block.width+2);
		orig_cord.cord_y = (game_area.orig_cord.cord_y + 2) + cord_row * (block.height+1);
		
		curr_cord.cord_x = orig_cord.cord_x;
		curr_cord.cord_y = orig_cord.cord_y;

		if (direction == DOWN)
		{
			for (int i = 0; i < block.height + 1; i++)
			{
				//色块原位置打印空白
				print_block_cfg(target, orig_cord, block, block_color, EMP);
				print_block_cfg(target, curr_cord, block, block_color, NORMAL);

				curr_cord.cord_y++;
				Sleep(10);
			}

			print_block_cfg(target, orig_cord, block, block_color, EMP);
			gotoxy(curr_cord.cord_x, curr_cord.cord_y - 1);

			print_unicode(game_area.border[4], game_area.game_area_color.bg_color, game_area.game_area_color.fg_color, block.width / 2);
			print_block_cfg(target, curr_cord, block, block_color, NORMAL);
		}
		else if (direction == LEFT)
		{
			Cord temp_cord; //一会移动光标需要用到的临时坐标

			for (int i = 0; i < block.width + 1; i++)
			{
				//色块原位置打印空白
				print_block_cfg(target, orig_cord, block, block_color, EMP);
				print_block_cfg(target, curr_cord, block, block_color, NORMAL);

				curr_cord.cord_x--;
				Sleep(10);
			}

			print_block_cfg(target, orig_cord, block, block_color, EMP);
			gotoxy(orig_cord.cord_x-2, orig_cord.cord_y);

			for (int i = 0; i < block.height; i++)
			{
				print_unicode(game_area.border[5], game_area.game_area_color.bg_color, game_area.game_area_color.fg_color, 1);

				getxy(temp_cord.cord_x, temp_cord.cord_y);
				gotoxy(temp_cord.cord_x, temp_cord.cord_y + 1);
			}
			print_block_cfg(target, curr_cord, block, block_color, NORMAL);
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
	item_get_value(cfgfile, "色块设置", "边框线-左上角", game_area.border[0], TYPE_STRING);
	item_get_value(cfgfile, "色块设置", "边框线-左下角", game_area.border[1], TYPE_STRING);
	item_get_value(cfgfile, "色块设置", "边框线-右上角", game_area.border[2], TYPE_STRING);
	item_get_value(cfgfile, "色块设置", "边框线-右下角", game_area.border[3], TYPE_STRING);
	item_get_value(cfgfile, "色块设置", "边框线-横线", game_area.border[4], TYPE_STRING);
	item_get_value(cfgfile, "色块设置", "边框线-竖线", game_area.border[5], TYPE_STRING);

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

	else if (block.type == POPSTAR)
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

	item_get_value(cfgfile, "色块设置", "选中色块前景色", &block_color.chosen_block_color.fg_color, TYPE_INT);
	if (block_color.chosen_block_color.fg_color < 0 || block_color.chosen_block_color.fg_color > 15)
	{
		block_color.chosen_block_color.fg_color = 7;
	}
}

