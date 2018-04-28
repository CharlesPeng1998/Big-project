/*1751367 计2 彭健聪*/
#pragma once
//移动的方向
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define UP 4
#define ROTATE 4

/*显示外边框函数当中选择游戏类型和边框类型的参数*/
#define MAKE10 1
#define POPSTAR 0
#define TETRIS 2

#define DIVIDED 1
#define UNDIVIDED 0

/*打印一个色块函数总色块类型的参数*/
#define NORMAL 1
#define CURR 2
#define CHOSEN 3
#define EMP 4

//选定方块后取消当前选择还是继续消除
#define CANCEL 0
#define CLICK 1

//enter_click函数中确认使用的键盘按键
#define C 1
#define ENTER 0

//elmn_fall函数的题号参数
#define F 0
#define G 1

//屏幕坐标结构体
struct Cord
{
	int cord_x;
	int cord_y;
};

//矩阵坐标结构体
struct Position
{
	int cord_row;
	int cord_col;
};

//控制台窗口结构体，记录控制台窗口大小
struct Consoleborder
{
	int cols;
	int lines;
};

//颜色结构体
struct Color
{
	int bg_color;
	int fg_color;
};

//cmd版本游戏区域结构体
struct Game_area
{
	//定义随机矩阵和标记用矩阵
	int total_score=0; //记录当前总分
	int goal=5; //游戏目标
	int rand_matrix[8][10] = { 0 };
	char mark_matrix[8][10];
	bool divided = 1; //是否需要分割线
	bool show_row_col_number = 1; //是否显示行号列标
	int matrix_row=5;
	int matrix_col=5;
	char border[11][3] = { "┏","┗","┓","┛","━","┃", "┳","┻","┣","┫","╋" };//边框类型
	Color game_area_color = {15,0};
	Cord orig_cord = { 0,0 };

	int curr_row, curr_col; //记录当前选定色块所在的行列
	int last_row, last_col; //上次选定色块所在的行列

	int extra_line = 0; //下方空行
	int extra_col = 0; //右侧空行

	int delay_time = 0;

	int top_info=1;
	int bot_info=1;

	Color norm_info_color = {15,0};
	Color warning_color = { 15,14 };
};

//共用体：色块当中的显示值（可能为整数，可能为星星字符）
union value_in_block
{
	int value_num;
	char value_star[3];
};

//色块结构体
struct Block
{
	int type=MAKE10; //代表色块的类型：MAKE10 / POPSTAR
	int width = 6; //如果设置为奇数则自动加1
	int height = 3;
	value_in_block value;

	//色块的边框样式
	char frame[6][3] = { "┏","┗","┓","┛","━","┃" };
	int move_delay_time=10;
};

//从配置文件中读取的颜色信息
struct Block_color
{
	//一共有11组颜色信息,两个游戏共用前5组
	Color block_color_1 = { 1,0 };
	Color block_color_2 = { 2,0 };
	Color block_color_3 = { 3,0 };
	Color block_color_4 = { 4,0 };
	Color block_color_5 = { 5,0 };
	Color block_color_6 = { 9,0 };
	Color block_color_7 = { 10,0 };
	Color block_color_8 = { 11,0 };
	Color block_color_9 = { 12,0 };
	Color block_color_10 = { 13,0 };
	Color block_color_11 = { 1,0 };
	Color chosen_block_color; //被选中色块颜色
};



//以下为沈坚要求部分
char menu(const char *items[], int n);
void mark(int(*rand_matrix)[10], char(*mark_matrix)[10], int cord_row, int cord_col, int Max_row, int Max_col);
void matrix_move(int(*rand_matrix)[10], char(*mark_matrix)[10], int row, int col,int move_type);
bool end_judge(int(*rand_matrix)[10], int row, int col);
void print_frame(int row, int col, int game, int type);
void print_block(int value, int cord_x, int cord_y, int game, int type);
void block_move(int(*rand_matrix)[10], int cord_row, int cord_col, int game, int direction);
void print_game_area(Game_area game_area, Block block);
void print_block_cfg(int value, Game_area game_area, Cord cord, Block block, Block_color block_color, int type);
void block_move_cfg(Game_area game_area, Block block, Block_color block_color, int cord_row, int cord_col, int direction);
int read_game_cfg(const char *cfg_name, Game_area &game_area, Block &block, Block_color &block_color);
void print_game_cfg(Game_area game_area, Block block, Block_color block_color);
void kb_move_cfg(Game_area &game_area, Block block, Block_color block_color);
bool cord_to_rc_cfg(Game_area &game_area, Cord cord, Block block);
void go_cfg(Game_area &game_area, Block block, Block_color block_color, int direction);
void GUI_full_cfg();
int cancel_confirm_cfg(Game_area game_area, Block block);
void block_fall_cfg(Game_area &game_area, Block block, Block_color block_color);
void print_unicode_cfg(const char *str, const int bg_color, const int fg_color, const int n, int delay_time);

//以下为个人提取部分
void input_row_col(int &row, int &col,int game);
void orig_matrix(int(*rand_matrix)[10], int row, int col, int game);
void orig_mark(char(*mark_matrix)[10], int row, int col);
void input_cord(int(*rand_matrix)[10], int row, int col, char &alpha, int &num);
int judge_cord(int(*rand_matrix)[10], int row, int col, int curr_row, int curr_col);
void print_matirx(int(*rand_matrix)[10], int row, int col);
void print_mark(char(*mark_matrix)[10], int row, int col);
void print_color_matrix(int(*rand_matrix)[10], char(*mark_matrix)[10], int row, int col);
void back_to_menu();
void print_unicode(const char *str, const int bg_color, const int fg_color, const int n);
char confirm_combine(const char *enquire1, const char *enquire2, char input_alpha, int input_num);
void go_up(int(*rand_matrix)[10], int row, int col, int &curr_row, int &curr_col, int &last_row, int &last_col, int type, int game = POPSTAR);
void go_down(int(*rand_matrix)[10], int row, int col, int &curr_row, int &curr_col, int &last_row, int &last_col, int type, int game = POPSTAR);
void go_left(int(*rand_matrix)[10], int row, int col, int &curr_row, int &curr_col, int &last_row, int &last_col, int type, int game = POPSTAR);
void go_right(int(*rand_matrix)[10], int row, int col, int &curr_row, int &curr_col, int &last_row, int &last_col, int type, int game = POPSTAR);
int cancel_confirm(int curr_row, int curr_col,int game=POPSTAR);
void block_fall(int(*rand_matrix)[10], int row, int col, int game = POPSTAR);
bool cord_to_rc(int(*rand_matrix)[10], int row, int col, int cord_x, int cord_y, int &curr_row, int &curr_col, int &last_row, int &last_col, int game, int type);