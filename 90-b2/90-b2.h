/*1751367 计2 彭健聪*/
#pragma once

#define MIN_ROW 22
#define MIN_COL 15
#define MAX_ROW 50 //我也不知道要把上限设置为多少好，根据用户体验再来进行修改吧
#define MAX_COL 50 



//控制台窗口结构体，记录控制台窗口大小
struct Consoleborder
{
	int cols;
	int lines;
};

//cmd版本游戏区域结构体
struct Game_area
{
	int **display_matrix;//用于显示游戏区域的矩阵
	int matrix_row;
	int matrix_col;
	const char *border[6] = { "┏","┓","┗","┛","━","┃" };//边框类型
	int orig_x;//区域开始的坐标
	int orig_y;
};


void input_row_col_tetris(int &row, int &col, int Max_row, int Min_row, int Max_col, int Min_col);
void print_cmd_game_area(Game_area game_area);




void cmd_tetris();