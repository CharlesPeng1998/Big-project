/*1751367 计2 彭健聪*/
#include <iostream>
#include <iomanip>
#include <fstream>
#include <ctime>
#include <cmath>
#include <cstdio>
#include <conio.h>
#include <Windows.h>
#include "..\common\cmd_console_tools.h"
#include "..\common\common.h"
#include "90-b2.h"
using namespace std;

const Block block_1 = { {
		0,0,1,0,0,
		0,0,1,0,0,
		0,0,1,0,0,
		0,0,1,0,0,
		0,0,1,0,0
	},{ 2,5 },{ 2,5 },1 };

const Block block_2 = { {
		0,1,1,1,0,
		0,0,0,1,0,
		0,1,1,1,0,
		0,1,0,0,0,
		0,1,1,1,0
	},{ 2,5 },{ 2,5 },2 };

const Block block_3 = { {
		0,1,1,1,0,
		0,0,0,1,0,
		0,1,1,1,0,
		0,0,0,1,0,
		0,1,1,1,0
	},{ 2,5 },{ 2,5 },3 };

const Block block_4 = { {
		0,1,0,1,0,
		0,1,0,1,0,
		0,1,1,1,0,
		0,0,0,1,0,
		0,0,0,1,0
	},{ 2,5 },{ 2,5 },4 };

const Block block_5 = { {
		0,1,1,1,0,
		0,1,0,0,0,
		0,1,1,1,0,
		0,0,0,1,0,
		0,1,1,1,0
	},{ 2,5 },{ 2,5 },5 };

const Block block_6 = { {
		0,1,1,1,0,
		0,1,0,0,0,
		0,1,1,1,0,
		0,1,0,1,0,
		0,1,1,1,0
	},{ 2,5 },{ 2,5 },6 };

const Block block_7 = { {
		0,1,1,1,0,
		0,0,0,1,0,
		0,0,0,1,0,
		0,0,0,1,0,
		0,0,0,1,0
	},{ 2,5 },{ 2,5 },7 };

const Block block_8 = { {
		0,1,1,1,0,
		0,1,0,1,0,
		0,1,1,1,0,
		0,1,0,1,0,
		0,1,1,1,0
	},{ 2,5 },{ 2,5 },8 };

const Block block_9 = { {
		0,1,1,1,0,
		0,1,0,1,0,
		0,1,1,1,0,
		0,0,0,1,0,
		0,1,1,1,0
	},{ 2,5 },{ 2,5 },9 };

const Block block_0 = { {
		0,1,1,1,0,
		0,1,0,1,0,
		0,1,0,1,0,
		0,1,0,1,0,
		0,1,1,1,0
	},{ 2,5 },{ 2,5 },10 };

//#define TEST

//俄罗斯方块命令行弱智版本
void cmd_tetris()
{
	//定义一个游戏区域结构体变量
	Game_area game_area;

	//定义一个控制台大小结构体变量
	Consoleborder consoleborder;

	//记录总分
	int total_score = 0;

	//接收用户自定义行列数
	input_row_col_tetris(game_area.matrix_row, game_area.matrix_col, MAX_ROW, MIN_ROW, MAX_COL, MIN_COL);

	//为游戏区域矩阵额外添加三行，因为初始时方块从区域外进入游戏区域
	game_area.matrix_row += EXTRA_ROW;

	//将初始显示矩阵全部置为0
	for (int i = 0; i < game_area.matrix_row; i++)
	{
		for (int j = 0; j < game_area.matrix_col; j++)
		{
			game_area.display_matrix[i][j] = 0;
		}
	}

	//初始化游戏区域的起始坐标
	game_area.orig_cord.cord_x = 25;
	game_area.orig_cord.cord_y = 1;

	//调整适应游戏区域的控制台窗口大小
	consoleborder.cols = game_area.orig_cord.cord_x+(game_area.matrix_col+2)*2;
	consoleborder.lines = game_area.orig_cord.cord_y+game_area.matrix_row+2;

	setconsoleborder(consoleborder.cols, consoleborder.lines);

	//打印显示矩阵（即游戏区域）
	print_cmd_game_area(game_area);

	//读取数字文件
	ifstream infile("tetris.dat", ios::in);
	if (!infile.is_open())
	{
		cerr << "open error!" << endl;
		exit(1);
	}

	Block curr_block;
	int curr_num;
	char curr_char;
	char keycode1, keycode2;
	
	while (!infile.eof())
	{
		infile.get(curr_char);
		
		//读取文件中的数字
		if (curr_char >= 48 && curr_char <= 57)
		{
			curr_num = curr_char - '0';
		}
		else continue;
			 
		switch (curr_num)
		{
		case 0:curr_block = block_0; break;
		case 1:curr_block = block_1; break;
		case 2:curr_block = block_2; break;
		case 3:curr_block = block_3; break;
		case 4:curr_block = block_4; break;
		case 5:curr_block = block_5; break;
		case 6:curr_block = block_6; break;
		case 7:curr_block = block_7; break;
		case 8:curr_block = block_8; break;
		case 9:curr_block = block_9; break;
		}

		while (curr_block.state.move_allowed)
		{
			block_move(curr_block, DOWN, game_area,CMD);

			if (_kbhit())
			{
				keycode1 = _getch();
				keycode2 = _getch();

				if ((int)keycode1 == -32)
				{
					switch ((int)keycode2)
					{
					case KB_ARROW_UP:
						if (judge_behavior(curr_block, game_area, ROTATE))
						{
							block_rotate(curr_block, game_area, ANTI_CLOCKWISE,CMD);
						}
						break;
					case KB_ARROW_LEFT:
						if (judge_behavior(curr_block, game_area, LEFT))
						{
							block_move(curr_block, LEFT, game_area,CMD);
						}
						break;
					case KB_ARROW_RIGHT:
						if (judge_behavior(curr_block, game_area, RIGHT))
						{
							block_move(curr_block, RIGHT, game_area,CMD);
						}
						break;
					case KB_ARROW_DOWN:
						if (judge_behavior(curr_block, game_area, DOWN))
						{
							block_move(curr_block, DOWN, game_area,CMD);
						}
						break;
					}
				}
			}
			Sleep(200);
		}

		kill_row_fall(curr_block,game_area,total_score,CMD);
		if (judge_end(game_area)) break;
	}

	back_to_menu();
	infile.close();
}

//俄罗斯方块伪图形界面完整版
void GUI_tetris()
{
	//定义一个游戏区域结构体变量
	Game_area game_area;

	//定义一个控制台大小结构体变量
	Consoleborder consoleborder;

	//记录总分
	int total_score = 0;

	//接收用户自定义行列数
	input_row_col_tetris(game_area.matrix_row, game_area.matrix_col, MAX_ROW, MIN_ROW, MAX_COL, MIN_COL);

	//为游戏区域矩阵额外添加三行，因为初始时方块从区域外进入游戏区域
	game_area.matrix_row += EXTRA_ROW;

	//将初始显示矩阵全部置为0
	for (int i = 0; i < game_area.matrix_row; i++)
	{
		for (int j = 0; j < game_area.matrix_col; j++)
		{
			game_area.display_matrix[i][j] = 0;
		}
	}

	//初始化游戏区域的起始坐标
	game_area.orig_cord.cord_x = 60;
	game_area.orig_cord.cord_y = 1;

	//调整适应游戏区域的控制台窗口大小
	consoleborder.cols = game_area.orig_cord.cord_x + (game_area.matrix_col *6)+4;
	consoleborder.lines = game_area.orig_cord.cord_y + (game_area.matrix_row-1)*3;

	setconsoleborder(consoleborder.cols, consoleborder.lines);

	print_GUI_game_area(game_area);


	//读取数字文件
	ifstream infile("tetris.dat", ios::in);
	if (!infile.is_open())
	{
		cerr << "open error!" << endl;
		exit(1);
	}

	Block curr_block;
	int curr_num;
	int next_num;
	int next_copy=-1;
	char next_char;
	char keycode1, keycode2;

	infile.get(next_char);
	next_num = next_char - '0';

	while (!infile.eof())
	{
		curr_num = next_num;
		
		while (!infile.eof())
		{
			infile.get(next_char);
			//读取文件中的数字
			if (next_char >= 48 && next_char <= 57)
			{
				next_num = next_char - '0';
				break;
			}
			else continue;
		}

		switch (curr_num)
		{
		case 0:curr_block = block_0; break;
		case 1:curr_block = block_1; break;
		case 2:curr_block = block_2; break;
		case 3:curr_block = block_3; break;
		case 4:curr_block = block_4; break;
		case 5:curr_block = block_5; break;
		case 6:curr_block = block_6; break;
		case 7:curr_block = block_7; break;
		case 8:curr_block = block_8; break;
		case 9:curr_block = block_9; break;
		}

		//使方块的起始位置位于区域的中线上
		curr_block.curr_pos.cord_col = curr_block.last_pos.cord_col = game_area.matrix_col / 2;

		while (judge_behavior(curr_block, game_area, DOWN))
		{
			if (next_copy != next_num)
			{
				side_info(next_num, total_score);
				next_copy = next_num;
			}
			
			block_move(curr_block, DOWN, game_area, GUI);

			if (_kbhit())
			{
				keycode1 = _getch();
				keycode2 = _getch();

				if ((int)keycode1 == -32)
				{
					switch ((int)keycode2)
					{
					case KB_ARROW_UP:
						if (judge_behavior(curr_block, game_area, ROTATE))
						{
							block_rotate(curr_block, game_area, ANTI_CLOCKWISE,GUI);
						}
						break;
					case KB_ARROW_LEFT:
						if (judge_behavior(curr_block, game_area, LEFT))
						{
							block_move(curr_block, LEFT, game_area, GUI);
						}
						break;
					case KB_ARROW_RIGHT:
						if (judge_behavior(curr_block, game_area, RIGHT))
						{
							block_move(curr_block, RIGHT, game_area, GUI);
						}
						break;
					case KB_ARROW_DOWN:
						if (judge_behavior(curr_block, game_area, DOWN))
						{
							block_move(curr_block, DOWN, game_area, GUI);
						}
						break;
					}
				}
			}
			Sleep(200);
		}

		kill_row_fall(curr_block, game_area, total_score, GUI);
		if (judge_end(game_area)) break;
	}

	infile.close();
}

/*侧边信息栏：下一个方块，当前分数*/
void side_info(int next_num,int total_score)
{
	Block next_block;
	switch (next_num)
	{
	case 0:next_block = block_0; break;
	case 1:next_block = block_1; break;
	case 2:next_block = block_2; break;
	case 3:next_block = block_3; break;
	case 4:next_block = block_4; break;
	case 5:next_block = block_5; break;
	case 6:next_block = block_6; break;
	case 7:next_block = block_7; break;
	case 8:next_block = block_8; break;
	case 9:next_block = block_9; break;
	}

	Game_area info_area;
	info_area.matrix_col = 3;
	info_area.matrix_row = 5+EXTRA_ROW;

	info_area.orig_cord.cord_x = 16;
	info_area.orig_cord.cord_y = 15;

	print_GUI_game_area(info_area);

	next_block.curr_pos.cord_row = 2 + EXTRA_ROW;
	next_block.curr_pos.cord_col = 1;

	draw_full_block(next_block, info_area, DRAW);

	Game_area score_area; //显示当前分数的区域
	score_area.matrix_col = 7;
	score_area.matrix_row = 5 + EXTRA_ROW;

	score_area.orig_cord.cord_x = 8;
	score_area.orig_cord.cord_y = 50;

	print_GUI_game_area(score_area);

	Block score_first_num; //分数十位上的数
	Block score_second_num; //分数个位上的数

	int first_num = total_score / 10;
	int second_num = total_score % 10;

	switch (first_num)
	{
	case 0:score_first_num = block_0; break;
	case 1:score_first_num = block_1; break;
	case 2:score_first_num = block_2; break;
	case 3:score_first_num = block_3; break;
	case 4:score_first_num = block_4; break;
	case 5:score_first_num = block_5; break;
	case 6:score_first_num = block_6; break;
	case 7:score_first_num = block_7; break;
	case 8:score_first_num = block_8; break;
	case 9:score_first_num = block_9; break;
	}

	switch (second_num)
	{
	case 0:score_second_num = block_0; break;
	case 1:score_second_num = block_1; break;
	case 2:score_second_num = block_2; break;
	case 3:score_second_num = block_3; break;
	case 4:score_second_num = block_4; break;
	case 5:score_second_num = block_5; break;
	case 6:score_second_num = block_6; break;
	case 7:score_second_num = block_7; break;
	case 8:score_second_num = block_8; break;
	case 9:score_second_num = block_9; break;
	}

	score_first_num.curr_pos.cord_row = 2 + EXTRA_ROW;
	score_first_num.curr_pos.cord_col = 1;

	score_second_num.curr_pos.cord_row = 2 + EXTRA_ROW;
	score_second_num.curr_pos.cord_col = 5;

	draw_full_block(score_first_num, score_area, DRAW);
	draw_full_block(score_second_num, score_area, DRAW);
}

