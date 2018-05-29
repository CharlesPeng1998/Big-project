/*1751367 计2 彭健聪*/
#pragma once

#define EXTRA_ROW 5

#define MIN_ROW 22
#define MIN_COL 15
#define MAX_ROW 50 //我也不知道要把上限设置为多少好，根据用户体验再来进行修改吧
#define MAX_COL 50 

//存放方块的矩阵的大小
#define BLOCK_ROW 5
#define BLOCK_COL 5



//消除色块还是绘制色块的参数
#define DRAW 1
#define ELIMINATE_PAST 0
#define ELIMINATE_CURR 2

//方块旋转的方向
#define ANTI_CLOCKWISE 1
#define CLOCKWISE 0

//游戏版本
#define CMD 0
#define GUI 1


//cmd版本游戏区域结构体
struct tGame_area
{
	int display_matrix[53][50] = { 0 };//用于显示游戏区域的矩阵
	int matrix_row;
	int matrix_col;
	const char *border[6] = { "┏","┓","┗","┛","━","┃" };//边框类型
	Cord orig_cord;
};

//表示一个方块当前状态的结构体
struct State
{
	bool move_allowed= 1;
	bool left_allowed = 1;
	bool right_allowed = 1;
	bool rotate_allowed = 1;
};

//方块结构体
struct tBlock
{
	int matrix[BLOCK_ROW][BLOCK_COL]; //将方块存在在一个5*5的矩阵当中
	Position curr_pos; //方块中心当前的位置
	Position last_pos; //方块中心上次所在位置
	int value; //该方块代表的数字
	const char *style[7] = { "┏","┓","┗","┛","━","┃","★" }; //方块样式
	Position central_pos = { 2,2 };
	State state;
};

void draw_block(tBlock block, tGame_area &game_area, int type);
void input_row_col_tetris(int &row, int &col, int Max_row, int Min_row, int Max_col, int Min_col);
void GUI_tetris();
void block_move(tBlock &block, int direction, tGame_area &game_area, int type);
void block_rotate(tBlock &block, tGame_area &game_area, int direction, int type);
bool position_legal(tBlock block, tGame_area game_area);
bool judge_behavior(tBlock block, tGame_area game_area, int type);
void kill_row_fall(tBlock block, tGame_area &game_area, int &total_score, int type);
bool judge_end(tGame_area &game_area);
void print_GUI_game_area(tGame_area game_area);
void draw_GUI_block(tBlock block, int value, int cord_x, int cord_y, int type);
void draw_full_block(tBlock block, tGame_area &game_area, int type);
void side_info(int next_num, int total_score);