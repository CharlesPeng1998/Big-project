/*1751367 ��2 ����*/
#pragma once
//�ƶ��ķ���
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define UP 4
#define ROTATE 4

/*��ʾ��߿�������ѡ����Ϸ���ͺͱ߿����͵Ĳ���*/
#define MAKE10 1
#define POPSTAR 0
#define TETRIS 2

#define DIVIDED 1
#define UNDIVIDED 0

/*��ӡһ��ɫ�麯����ɫ�����͵Ĳ���*/
#define NORMAL 1
#define CURR 2
#define CHOSEN 3
#define EMP 4

//ѡ�������ȡ����ǰѡ���Ǽ�������
#define CANCEL 0
#define CLICK 1

//enter_click������ȷ��ʹ�õļ��̰���
#define C 1
#define ENTER 0

//elmn_fall��������Ų���
#define F 0
#define G 1

//��Ļ����ṹ��
struct Cord
{
	int cord_x;
	int cord_y;
};

//��������ṹ��
struct Position
{
	int cord_row;
	int cord_col;
};

//����̨���ڽṹ�壬��¼����̨���ڴ�С
struct Consoleborder
{
	int cols;
	int lines;
};

//��ɫ�ṹ��
struct Color
{
	int bg_color;
	int fg_color;
};

//cmd�汾��Ϸ����ṹ��
struct Game_area
{
	//�����������ͱ���þ���
	int total_score=0; //��¼��ǰ�ܷ�
	int goal=5; //��ϷĿ��
	int rand_matrix[8][10] = { 0 };
	char mark_matrix[8][10];
	bool divided = 1; //�Ƿ���Ҫ�ָ���
	bool show_row_col_number = 1; //�Ƿ���ʾ�к��б�
	int matrix_row=5;
	int matrix_col=5;
	char border[11][3] = { "��","��","��","��","��","��", "��","��","��","��","��" };//�߿�����
	Color game_area_color = {15,0};
	Cord orig_cord = { 0,0 };

	int curr_row, curr_col; //��¼��ǰѡ��ɫ�����ڵ�����
	int last_row, last_col; //�ϴ�ѡ��ɫ�����ڵ�����

	int extra_line = 0; //�·�����
	int extra_col = 0; //�Ҳ����

	int delay_time = 0;

	int top_info=1;
	int bot_info=1;

	Color norm_info_color = {15,0};
	Color warning_color = { 15,14 };
};

//�����壺ɫ�鵱�е���ʾֵ������Ϊ����������Ϊ�����ַ���
union value_in_block
{
	int value_num;
	char value_star[3];
};

//ɫ��ṹ��
struct Block
{
	int type=MAKE10; //����ɫ������ͣ�MAKE10 / POPSTAR
	int width = 6; //�������Ϊ�������Զ���1
	int height = 3;
	value_in_block value;

	//ɫ��ı߿���ʽ
	char frame[6][3] = { "��","��","��","��","��","��" };
	int move_delay_time=10;
};

//�������ļ��ж�ȡ����ɫ��Ϣ
struct Block_color
{
	//һ����11����ɫ��Ϣ,������Ϸ����ǰ5��
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
	Color chosen_block_color; //��ѡ��ɫ����ɫ
};



//����Ϊ���Ҫ�󲿷�
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

//����Ϊ������ȡ����
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