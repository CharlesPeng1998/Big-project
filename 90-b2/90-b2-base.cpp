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
#include "90-b2.h"
using namespace std;

//俄罗斯方块命令行弱智版本
void cmd_tetris()
{
	//定义一个游戏区域结构体变量
	Game_area game_area;

	//定义一个控制台大小结构体变量
	Consoleborder consoleborder;

	//接收用户自定义行列数
	input_row_col_tetris(game_area.matrix_row, game_area.matrix_col, MAX_ROW, MIN_ROW, MAX_COL, MIN_COL);

	//为显示矩阵动态申请空间
	game_area.display_matrix = new int *[game_area.matrix_row];
	for (int i = 0; i < game_area.matrix_row; i++)
	{
		game_area.display_matrix[i] = new int[game_area.matrix_col];
	}

	//将初始显示矩阵全部置为0
	for (int i = 0; i < game_area.matrix_row; i++)
	{
		for (int j = 0; j < game_area.matrix_col; j++)
		{
			game_area.display_matrix[i][j] = 0;
		}
	}

	//初始化游戏区域的起始坐标
	game_area.orig_x = 25;
	game_area.orig_y = 1;

	//调整适应游戏区域的控制台窗口大小
	consoleborder.cols = game_area.orig_x+(game_area.matrix_col+2)*2;
	consoleborder.lines = game_area.orig_y+game_area.matrix_row+5;

	setconsoleborder(consoleborder.cols, consoleborder.lines);

	//打印显示矩阵（即游戏区域）
	print_cmd_game_area(game_area);

	back_to_menu();

	//首先回收低一级的动态数组
	for (int i = 0; i < game_area.matrix_col; i++)
	{
		delete[] game_area.display_matrix[i];
	}
	//回收高一级的动态数组
	delete[] game_area.display_matrix;
}