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
#include "..\common\common_cfgfile_tools.hpp"
#include "90-b0.h"

using namespace std;

int main()
{
#ifndef TEST	
	//定义一个指针数组，存放传入菜单函数的菜单选项
	const char *items[10];
	items[0] = "1.命令行找出可合并项并标识（非递归）";
	items[1] = "2.命令行找出可合并项并标识（递归）";
	items[2] = "3.命令行完成一次合成（分步骤显示）";
	items[3] = "4.命令行完整版（分步骤显示）";
	items[4] = "5.伪图形界面显示初始数组（无分隔线）";
	items[5] = "6.伪图形界面显示初始数组（有分隔线）";
	items[6] = "7.伪图形界面下用箭头键选择当前色块";
	items[7] = "8.伪图形界面完成一次合成（分步骤）";
	items[8] = "9.伪图形界面完整版";
	items[9] = "0.退出";

	while (1)
	{
		char choice = menu(items, 10);

		if (choice == items[0][0])
		{
			int col, row;
			system("cls");
			input_row_col(row, col, MAKE10);

			//定义随机矩阵和标记用矩阵
			int rand_matrix[8][10] = { 0 };
			char mark_matrix[8][10];

			//用户输入的矩阵坐标，行号为字母（alpha），列号为数字（num）
			char input_alpha;
			int input_num;

			//初始化内部数组
			orig_matrix(rand_matrix, row, col, MAKE10);
			orig_mark(mark_matrix, row, col);

			//执行第一小题的函数
			one_check_mark(rand_matrix, mark_matrix, row, col, input_alpha, input_num);

			//返回主菜单
			back_to_menu();

			cls();
			continue;
		}

		else if (choice == items[1][0])
		{
			int col, row;
			system("cls");
			input_row_col(row, col, MAKE10);

			//定义随机矩阵和标记用矩阵
			int rand_matrix[8][10] = { 0 };
			char mark_matrix[8][10];

			//用户输入的矩阵坐标，行号为字母（alpha），列号为数字（num）
			char input_alpha;
			int input_num;

			//初始化内部数组
			orig_matrix(rand_matrix, row, col, MAKE10);
			orig_mark(mark_matrix, row, col);

			//执行第二小题的函数
			two_check_mark(rand_matrix, mark_matrix, row, col, input_alpha, input_num);

			//返回主菜单
			back_to_menu();

			cls();
			continue;
		}

		else if (choice == items[2][0])
		{
			int col, row, goal;

			system("cls");
			input_rcg(row, col, goal);

			//定义随机矩阵和标记用矩阵
			int rand_matrix[8][10] = { 0 };
			char mark_matrix[8][10];

			//用户输入的矩阵坐标，行号为字母（alpha），列号为数字（num）
			char input_alpha;
			int input_num, score,total_score=0;

			//初始化内部数组
			orig_matrix(rand_matrix, row, col, MAKE10);
			orig_mark(mark_matrix, row, col);

			//执行第一小题的函数
			one_check_mark(rand_matrix, mark_matrix, row, col, input_alpha, input_num);

			switch (confirm_combine("请确认是否把相邻的相同值合并到", "中", input_alpha, input_num))
			{
				//执行第三小题的函数
			case 'y':three_cmd_combine(rand_matrix, mark_matrix, row, col, input_alpha, input_num, score, total_score, goal); break;
			case 'n':break;
			case 'q':break;
			}

			//返回主菜单
			back_to_menu();

			cls();
			continue;

		}

		else if (choice == items[3][0])
		{
			int col, row, goal;

			system("cls");
			input_rcg(row, col, goal);

			//定义随机矩阵和标记用矩阵
			int rand_matrix[8][10] = { 0 };
			char mark_matrix[8][10];

			//用户输入的矩阵坐标，行号为字母（alpha），列号为数字（num）
			char input_alpha;
			int input_num, score, total_score = 0;

			four_cmd_complete(rand_matrix, mark_matrix, row, col, input_alpha, input_num, score, total_score, goal);

			//返回主菜单
			back_to_menu();

			cls();
			continue;
		}

		else if (choice == items[4][0])
		{
			int col, row;
			system("cls");
			input_row_col(row, col, MAKE10);

			//定义随机矩阵和标记用矩阵
			int rand_matrix[8][10] = { 0 };

			five_GUI_dsp_undvd(rand_matrix, row, col);

			//返回主菜单
			back_to_menu();

			cls();
			continue;
		}

		else if (choice == items[5][0])
		{
			int col, row;
			system("cls");
			input_row_col(row, col, MAKE10);

			//定义随机矩阵和标记用矩阵
			int rand_matrix[8][10] = { 0 };

			six_GUI_dsp_dvd(rand_matrix, row, col);

			//返回主菜单
			back_to_menu();

			cls();
			continue;
		}

		else if (choice == items[6][0])
		{
			int col, row;
			system("cls");
			input_row_col(row, col, MAKE10);

			//定义随机矩阵和标记用矩阵
			int rand_matrix[8][10] = { 0 };
			char mark_matrix[8][10];

			six_GUI_dsp_dvd(rand_matrix, row, col);

			seven_kb_choose(rand_matrix,mark_matrix, row, col);

			//返回主菜单
			back_to_menu();

			cls();
			continue;
		}

		else if (choice == items[7][0])
		{
			int col, row, score = 0, total_score = 0,goal=5;
			system("cls");
			input_row_col(row, col, MAKE10);

			//定义随机矩阵和标记用矩阵
			int rand_matrix[8][10] = { 0 };
			char mark_matrix[8][10];

			//初始化内部数组
			orig_matrix(rand_matrix, row, col, MAKE10);
			orig_mark(mark_matrix, row, col);

			six_GUI_dsp_dvd(rand_matrix, row, col);

			eight_GUI_combine(rand_matrix, mark_matrix, row, col,goal,score,total_score);

			//返回主菜单
			back_to_menu();

			cls();
			continue;
		}

		else if (choice == items[8][0])
		{
			int col, row, goal, score = 0, total_score = 0;

			system("cls");
			input_rcg(row, col, goal);

			//定义随机矩阵和标记用矩阵
			int rand_matrix[8][10] = { 0 };
			char mark_matrix[8][10];

			//初始化内部数组
			orig_matrix(rand_matrix, row, col, MAKE10);
			orig_mark(mark_matrix, row, col);

			six_GUI_dsp_dvd(rand_matrix, row, col);

			nine_GUI_complete(rand_matrix, mark_matrix, row, col, goal, score, total_score);

			//返回主菜单
			back_to_menu();

			cls();
			continue;
		}

		else if (choice == items[9][0])
		{
			cout << endl << endl;
			return 0;
		}
	}

	
#endif	
	
	//GUI_full_cfg();

	return 0;
}