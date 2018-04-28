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
#include "..\common\common_cfgfile_tools.hpp"
#include "../90-b1/90-b1.h"
using namespace std;

//连续区域标记函数（递归版本）
void mark2(int matrix1[][10], char matrix2[][10], int cord_row, int cord_col, int Max_row, int Max_col)
{
	matrix2[cord_row][cord_col] = '*';

	if (cord_row > 0 && matrix1[cord_row - 1][cord_col] == matrix1[cord_row][cord_col] && matrix2[cord_row - 1][cord_col] != '*')
	{
		matrix2[cord_row - 1][cord_col] = '*';
		mark2(matrix1, matrix2, cord_row - 1, cord_col, Max_row, Max_col);
	}

	if (cord_row < Max_row - 1 && matrix1[cord_row + 1][cord_col] == matrix1[cord_row][cord_col] && matrix2[cord_row + 1][cord_col] != '*')
	{
		matrix2[cord_row + 1][cord_col] = '*';
		mark2(matrix1, matrix2, cord_row + 1, cord_col, Max_row, Max_col);
	}

	if (cord_col > 0 && matrix1[cord_row][cord_col - 1] == matrix1[cord_row][cord_col] && matrix2[cord_row][cord_col - 1] != '*')
	{
		matrix2[cord_row][cord_col - 1] = '*';
		mark2(matrix1, matrix2, cord_row, cord_col - 1, Max_row, Max_col);
	}

	if (cord_row <Max_col - 1 && matrix1[cord_row][cord_col + 1] == matrix1[cord_row][cord_col] && matrix2[cord_row][cord_col + 1] != '*')
	{
		matrix2[cord_row][cord_col + 1] = '*';
		mark2(matrix1, matrix2, cord_row, cord_col + 1, Max_row, Max_col);
	}
}

//该函数用于打印数组下落后不同色标识的零
void print_color_zero(int(*rand_matrix)[10], int row, int col)
{
	cout << "除0后的数组<不同色标识>: " << endl;
	cout << "  |";
	for (int i = 0; i < col; i++)
	{
		cout << "  " << i;
	}
	cout << endl;
	cout << "--+";
	for (int i = 0; i < col; i++)
	{
		cout << "---";
	}
	cout << endl;

	for (int i = 0; i < row; i++)
	{
		cout << char(i + 65) << " |";
		for (int j = 0; j < col; j++)
		{
			if (rand_matrix[i][j] == 0)
			{
				setcolor(COLOR_BLACK, COLOR_HPINK);
				cout << "  " << rand_matrix[i][j];
				setcolor();
			}
			else
			{
				cout << "  " << rand_matrix[i][j];
			}
		}
		cout << endl;
	}
}

//子题目一：命令行找出可合成项并标识（非递归）
void one_check_mark(int(*rand_matrix)[10], char(*mark_matrix)[10], int row, int col, char &input_alpha, int &input_num)
{
	//打印完整数组
	cout << endl;
	cout << "当前数组:" << endl;
	print_matirx(rand_matrix, row, col);

	input_cord(rand_matrix, row, col, input_alpha, input_num);

	//在标记矩阵上标记连续同项区域
	mark(rand_matrix, mark_matrix, int(input_alpha - 65), input_num, row, col);

	//打印查找结果数组
	cout << endl << "查找结果数组:" << endl;
	print_mark(mark_matrix, row, col);

	//打印不同色标识的内部数组
	cout << endl << "当前数组<不同色标识>:" << endl;
	print_color_matrix(rand_matrix, mark_matrix, row, col);
	cout << endl;
}

//子题目二：命令行找出可合成项并标识（递归）
void two_check_mark(int(*rand_matrix)[10], char(*mark_matrix)[10], int row, int col, char &input_alpha, int &input_num)
{
	//打印完整数组
	cout << endl;
	cout << "当前数组:" << endl;
	print_matirx(rand_matrix, row, col);

	input_cord(rand_matrix, row, col, input_alpha, input_num);

	//在标记矩阵上标记连续同项区域
	mark2(rand_matrix, mark_matrix, int(input_alpha - 65), input_num, row, col);

	//打印查找结果数组
	cout << endl << "查找结果数组:" << endl;
	print_mark(mark_matrix, row, col);

	//打印不同色标识的内部数组
	cout << endl << "当前数组<不同色标识>:" << endl;
	print_color_matrix(rand_matrix, mark_matrix, row, col);
	cout << endl;
}

//子题目三：命令行完成一次合成（分步骤显示）
void three_cmd_combine(int(*rand_matrix)[10], char(*mark_matrix)[10], int &row, int &col, char &input_alpha, int &input_num, int &score, int &total_score,int goal)
{
	cout << endl;
	score = combine(rand_matrix, mark_matrix, row, col, input_alpha, input_num);
	total_score += score;

	cout << "本次得分: " << score << "  " << "总得分: " << total_score << "  " << "合成目标: " << goal << endl << endl;
	cout << "按回车键进行数组下落除0操作...";
	//忽略除回车以外所有输入
	while (_getch() != '\r')
		;

	matrix_move(rand_matrix, mark_matrix, row, col, DOWN);
	orig_mark(mark_matrix, row, col);
	cout << endl;
	print_color_zero(rand_matrix, row, col);

	
	cout <<endl<< "按回车键进行新值填充...";
	while (_getch() != '\r')
		;

	fill_rmatrix(rand_matrix, mark_matrix, row, col);
	
	cout << endl << "新值填充后的数组<不同色标识>: " << endl;
	print_color_matrix(rand_matrix, mark_matrix, row, col);

	if (end_judge(rand_matrix, row, col))
	{
		setcolor(COLOR_HYELLOW, COLOR_HRED);
		cout << endl << "无可合成项，游戏结束..." << endl;
		setcolor();
	}
}

//子题目四：命令行完整版（分步骤显示）
void four_cmd_complete(int(*rand_matrix)[10], char(*mark_matrix)[10], int &row, int &col, char &input_alpha, int &input_num, int &score, int &total_score, int goal)
{
	//初始化内部数组
	orig_matrix(rand_matrix, row, col, MAKE10);
	
	while (!end_judge(rand_matrix, row, col))
	{
		//初始化标记数组
		orig_mark(mark_matrix, row, col);

		//执行第一小题的函数
		one_check_mark(rand_matrix, mark_matrix, row, col, input_alpha, input_num);

		switch (confirm_combine("请确认是否把相邻的相同值合并到", "中", input_alpha, input_num))
		{
			//执行第三小题的函数
		case 'y':three_cmd_combine(rand_matrix, mark_matrix, row, col, input_alpha, input_num, score, total_score, goal); break;
		case 'n':continue;
		case 'q':return;
		}

		cout << "本次消除结束，按回车键继续新一次的消除...";

		if (win_check(rand_matrix, row, col,goal))
		{
			setcolor(COLOR_HYELLOW, COLOR_HRED);
			cout << endl << "已经合成到" << goal << "!!" << endl;
			setcolor();
			cout << "按回车键向更高目标进发...";

			while (_getch() != '\r');

			goal++;
			continue;
		}

		while (_getch() != '\r');
		continue;
	}

	if (end_judge(rand_matrix, row, col))
	{
		setcolor(COLOR_HYELLOW, COLOR_HRED);
		cout << endl << "无可合成项，按回车结束游戏..." << endl;
		setcolor();

		while (_getch() != '\r');
		return;
	}
}

