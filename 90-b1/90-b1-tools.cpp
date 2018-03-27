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

//该函数用于根据标记矩阵对内部数组进行消除操作，即置0
void eliminate(int(*rand_matrix)[10], char(*mark_matrix)[10], int row, int col)
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (mark_matrix[i][j] == '*') rand_matrix[i][j] = 0;
		}
	}
}

//该函数用于计算一次消除的得分
int elmn_score(char(*mark_matrix)[10], int row, int col)
{
	//记录消除方块的个数
	int elnm_num = 0;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (mark_matrix[i][j] == '*') elnm_num++;
		}
	}

	return elnm_num * elnm_num * 5;
}

//该函数用于某关结束后统计剩余不可消除项
int remain_num(int(*rand_matrix)[10], int row, int col)
{
	int num = 0;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (rand_matrix[i][j] != 0) num++;
		}
	}
	return num;
}