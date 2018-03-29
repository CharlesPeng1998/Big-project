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

//打印命令行版本的游戏区域
void print_cmd_game_area(Game_area game_area)
{
	setcolor(0, COLOR_HYELLOW);
	
	//将光标移动到指定起始位置
	gotoxy(game_area.orig_x,game_area.orig_y);
	
	//首先打印边框
	cout << game_area.border[0];
	for (int i = 0; i < game_area.matrix_col; i++)
	{
		cout << game_area.border[4];
	}
	cout << game_area.border[1];

	for (int i = 0; i < game_area.matrix_row; i++)
	{
		game_area.orig_y++;
		gotoxy(game_area.orig_x, game_area.orig_y);
		
		cout << game_area.border[5];
		
		setcolor();
		for (int j = 0; j < game_area.matrix_col; j++)
		{
			cout <<' '<< game_area.display_matrix[i][j];
		}
		setcolor(0, COLOR_HYELLOW);
		
		cout << game_area.border[5];
	}

	game_area.orig_y++;
	gotoxy(game_area.orig_x, game_area.orig_y);

	cout << game_area.border[2];
	for (int i = 0; i < game_area.matrix_col; i++)
	{
		cout << game_area.border[4];
	}
	cout << game_area.border[3];

	setcolor();
}
