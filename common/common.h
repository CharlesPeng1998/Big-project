/*1751367 ��2 ����*/
#pragma once
/*�ڲ������ƶ���������ѡ���ƶ���ʽ�Ĳ���*/
#define DOWN 0
#define LEFT 1

/*��ʾ��߿�������ѡ����Ϸ���ͺͱ߿����͵Ĳ���*/
#define MAKE10 1
#define POPSTAR 0

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

//����Ϊ���Ҫ�󲿷�
char menu(const char *items[], int n);
void mark(int(*rand_matrix)[10], char(*mark_matrix)[10], int cord_row, int cord_col, int Max_row, int Max_col);
void matrix_move(int(*rand_matrix)[10], char(*mark_matrix)[10], int row, int col,int move_type);
bool end_judge(int(*rand_matrix)[10], int row, int col);
void print_frame(int row, int col, int game, int type);
void print_block(int value, int cord_x, int cord_y, int game, int type);
void block_move(int(*rand_matrix)[10], int cord_row, int cord_col, int game, int direction);

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