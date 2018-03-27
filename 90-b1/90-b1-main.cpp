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

int main()
{
	//定义一个指针数组，存放传入菜单函数的菜单选项
	const char *items[10];
	items[0] = "A.命令行找出可消除项并标识";
	items[1] = "B.命令行完成一次消除（分步骤显示）";
	items[2] = "C.命令行完成一关（分步骤显示）";
	items[3] = "D.伪图形界面下用鼠标选择一个色块（无分隔线）";
	items[4] = "E.伪图形界面下用鼠标选择一个色块（有分隔线）";
	items[5] = "F.伪图形界面完成一次消除（分步骤）";
	items[6] = "G.伪图形界面完整版";
	items[7] = "Q.退出";

	while (1)
	{
		char choice = menu(items, 8);

		if (choice == items[0][0])
		{
			//提示用户输入行列数
			cls();
			int row, col;
			input_row_col(row, col,POPSTAR);

			//用户输入的矩阵坐标，行号为字母（alpha），列号为数字（num）
			char input_alpha;
			int input_num;

			//定义随机矩阵和标记矩阵
			int rand_matrix[10][10] = { 0 };
			char mark_matrix[10][10];

			//初始化内部数组
			orig_matrix(rand_matrix, row, col,POPSTAR);
			orig_mark(mark_matrix, row, col);

			//执行第一小题的函数
			A_find_mark(rand_matrix,mark_matrix,row,col,input_alpha,input_num);
			//返回主菜单
			back_to_menu();

			cls();
			continue;
		}

		else if (choice == items[1][0])
		{
			//提示用户输入行列数
			cls();
			int row, col;
			input_row_col(row, col,POPSTAR);

			//定义随机矩阵和标记矩阵
			int rand_matrix[10][10] = { 0 };
			char mark_matrix[10][10];

			//初始化内部数组
			orig_matrix(rand_matrix, row, col,POPSTAR);
			orig_mark(mark_matrix, row, col);

			//用户输入的矩阵坐标，行号为字母（alpha），列号为数字（num）
			char input_alpha;
			int input_num;

			int score, total_score = 0;//记录完成一次消除的分数和当前总分数
			
			//执行第一小题的函数
			A_find_mark(rand_matrix, mark_matrix, row, col, input_alpha, input_num);
			
			switch (confirm_combine("确认是否把", "及周围的相同值消除", input_alpha, input_num))
			{
			//执行第二小题的函数
			case 'y':B_eliminate(rand_matrix, mark_matrix, row, col, input_alpha, input_num, score, total_score); break;
			case 'n':break;
			case 'q':break;
			}

			//返回主菜单
			back_to_menu();

			cls();
			continue;
		}

		else if (choice == items[2][0])
		{
			//提示用户输入行列数
			cls();
			int row, col;
			input_row_col(row, col,POPSTAR);

			//定义随机矩阵和标记矩阵
			int rand_matrix[10][10] = { 0 };
			char mark_matrix[10][10];

			//用户输入的矩阵坐标，行号为字母（alpha），列号为数字（num）
			char input_alpha;
			int input_num;

			int score, total_score = 0;//记录完成一次消除的分数和当前总分数

			//执行第三小题命令行完整版函数
			C_cmd_complete(rand_matrix, mark_matrix, row, col, input_alpha, input_num, score, total_score);

			//返回主菜单
			back_to_menu();

			cls();
			continue;
		}

		else if (choice == items[3][0])
		{
			//提示用户输入行列数
			cls();
			int row, col;
			input_row_col(row, col,POPSTAR);

			int rand_matrix[10][10] = { 0 };
			char mark_matrix[10][10];
			
			int score, total_score = 0;//记录完成一次消除的分数和当前总分数

			//执行第四小题的函数
			D_GUI_choose_undvd(rand_matrix, mark_matrix, row, col, score, total_score);
			
			back_to_menu();

			cls();
			continue;
		}

		else if (choice == items[4][0])
		{
			//提示用户输入行列数
			cls();
			int row, col;
			input_row_col(row, col,POPSTAR);

			//定义随机矩阵和标记矩阵
			int rand_matrix[10][10] = { 0 };
			char mark_matrix[10][10];

			int score, total_score = 0;//记录完成一次消除的分数和当前总分数

	        //执行第五小题的函数
			E_GUI_choose_dvd(rand_matrix, mark_matrix, row, col, score, total_score);

			back_to_menu();

			cls();
			continue;
		}

		else if (choice == items[5][0])
		{
			//提示用户输入行列数
			cls();
			int row, col;
			input_row_col(row, col,POPSTAR);

			//定义随机矩阵和标记矩阵
			int rand_matrix[10][10] = { 0 };
			char mark_matrix[10][10];

			int score, total_score = 0;//记录完成一次消除的分数和当前总分数

			F_GUI_eliminate(rand_matrix, mark_matrix, row, col, score, total_score,F);

			back_to_menu();

			cls();
			continue;
		}

		else if (choice == items[6][0])
		{
			//提示用户输入行列数
			cls();
			int row, col;
			input_row_col(row, col,POPSTAR);

			//定义随机矩阵和标记矩阵
			int rand_matrix[10][10] = { 0 };
			char mark_matrix[10][10];

			int score, total_score = 0;//记录完成一次消除的分数和当前总分数

			while (1)
			{
				G_GUI_complete(rand_matrix, mark_matrix, row, col, score, total_score);
			}
		}

		else if (choice == items[7][0])
		{
			cout << endl << endl;
			return 0;
		}
	}
}