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

//该函数用于用户输入行列数以及目标值
void input_rcg(int &row, int &col, int &goal)
{
	bool judge_row = 0, judge_col = 0, judge_goal = 0;

	int curr_x;
	int curr_y; //用来记录当前光标的位置

	getxy(curr_x, curr_y);//获取当前光标位置，以便于输入错误时光标返回至原输入位置

	while (!judge_row)
	{
		gotoxy(curr_x, curr_y);
		cout << "请输入行数<5-8>: ";
		cin >> row;

		//检验输入是否合法，下同
		if (cin.fail() || row < 5 || row > 8)
		{
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail(), '\n');
			cout << "输入不合法，请重新输入     ";
			continue;
		}
		else judge_row = 1;
	}

	getxy(curr_x, curr_y);
	cout << "                      ";
	gotoxy(curr_x, curr_y);//这三句用于清除上次留下的错误提示，下同

	while (!judge_col)
	{
		gotoxy(curr_x, curr_y);
		cout << "请输入列数<5-10>: ";
		cin >> col;

		if (cin.fail() || col < 5 || col > 10)
		{
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail(), '\n');
			cout << "输入不合法，请重新输入     ";
			continue;
		}
		else judge_col = 1;
	}

	getxy(curr_x, curr_y);
	cout << "                      ";
	gotoxy(curr_x, curr_y);

	while (!judge_goal)
	{
		gotoxy(curr_x, curr_y);
		cout << "请输入合成目标<5-20>: ";
		cin >> goal;

		if (cin.fail() || goal < 5 || goal > 20)
		{
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail(), '\n');
			cout << "输入不合法，请重新输入     ";
			continue;
		}
		else judge_goal = 1;
	}

	getxy(curr_x, curr_y);
	cout << "                      ";
	gotoxy(curr_x, curr_y);
}

//该函数用于合并，消零，计分
int combine(int(*rand_matrix)[10], char(*mark_matrix)[10], int row, int col, char input_alpha, int input_num)
{
	int score = 0;//记录用户得分
	int target = rand_matrix[int(input_alpha - 65)][input_num];

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
	rand_matrix[int(input_alpha - 65)][input_num] = target + 1;

	print_color_matrix(rand_matrix, mark_matrix, row, col);

	return score;
}

//该函数用于填充矩阵（仅填充随机矩阵，用于每次消0后使用） （更新了标记填充位置的功能，以便于为填充位置上色）
void fill_rmatrix(int(*rand_matrix)[10], char(*mark_matrix)[10], int row, int col)
{
	int random;//用于记录随机数

			   //遍历矩阵寻找最大值
	int max = rand_matrix[0][0];
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (rand_matrix[i][j] > max) max = rand_matrix[i][j];
		}
	}

	//根据最大值设置填充数字的概率
	if (max == 3 || max == 0)
	{
		srand((unsigned int)(time(0)));//生成随机种子

									   //1-3等概率填充矩阵
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				if (rand_matrix[i][j] == 0)
				{
					switch (rand() % 3)
					{
					case 0:rand_matrix[i][j] = 1; break;
					case 1:rand_matrix[i][j] = 2; break;
					case 2:rand_matrix[i][j] = 3; break;
					}

					mark_matrix[i][j] = '*';
				}
			}
		}
	}

	else if (max == 4)
	{
		srand((unsigned int)(time(0)));//生成随机种子

		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				if (rand_matrix[i][j] == 0)
				{
					random = rand() % 10;

					if (random >= 0 && random <= 2) rand_matrix[i][j] = 1;
					else if (random >= 3 && random <= 5) rand_matrix[i][j] = 2;
					else if (random >= 6 && random <= 8) rand_matrix[i][j] = 3;
					else rand_matrix[i][j] = 4;

					mark_matrix[i][j] = '*';
				}
			}
		}

	}

	else if (max == 5)
	{
		srand((unsigned int)(time(0)));//生成随机种子

		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				if (rand_matrix[i][j] == 0)
				{
					random = rand() % 20;

					if (random >= 0 && random <= 4) rand_matrix[i][j] = 1;
					else if (random >= 5 && random <= 9) rand_matrix[i][j] = 2;
					else if (random >= 10 && random <= 14) rand_matrix[i][j] = 3;
					else if (random >= 15 && random <= 17) rand_matrix[i][j] = 4;
					else rand_matrix[i][j] = 5;

					mark_matrix[i][j] = '*';
				}
			}
		}
	}

	else if (max == 6)
	{
		srand((unsigned int)(time(0)));//生成随机种子

		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				if (rand_matrix[i][j] == 0)
				{
					random = rand() % 20;

					if (random >= 0 && random <= 3) rand_matrix[i][j] = 1;
					else if (random >= 4 && random <= 7) rand_matrix[i][j] = 2;
					else if (random >= 8 && random <= 11) rand_matrix[i][j] = 3;
					else if (random >= 12 && random <= 15) rand_matrix[i][j] = 4;
					else if (random >= 16 && random <= 18) rand_matrix[i][j] = 5;
					else rand_matrix[i][j] = 6;

					mark_matrix[i][j] = '*';
				}
			}
		}
	}

	else
	{
		srand((unsigned int)(time(0)));//生成随机种子

		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				if (rand_matrix[i][j] == 0)
				{
					random = rand() % 20;

					if (random >= 0 && random <= 15)
					{
						rand_matrix[i][j] = (rand() % (max - 3)) + 1;
					}
					else if (random >= 16 && random <= 17) rand_matrix[i][j] = max - 2;
					else if (random == 18) rand_matrix[i][j] = max - 1;
					else rand_matrix[i][j] = max;

					mark_matrix[i][j] = '*';
				}
			}
		}
	}
}

//该函数用于判断是否达到合成目标
bool win_check(int(*rand_matrix)[10], int row, int col, int &goal)
{
	bool win = false;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (rand_matrix[i][j] == goal) win = true;
		}
	}

	return win;
}