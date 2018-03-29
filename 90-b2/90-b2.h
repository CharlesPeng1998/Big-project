/*1751367 ��2 ����*/
#pragma once

#define MIN_ROW 22
#define MIN_COL 15
#define MAX_ROW 50 //��Ҳ��֪��Ҫ����������Ϊ���ٺã������û��������������޸İ�
#define MAX_COL 50 



//����̨���ڽṹ�壬��¼����̨���ڴ�С
struct Consoleborder
{
	int cols;
	int lines;
};

//cmd�汾��Ϸ����ṹ��
struct Game_area
{
	int **display_matrix;//������ʾ��Ϸ����ľ���
	int matrix_row;
	int matrix_col;
	const char *border[6] = { "��","��","��","��","��","��" };//�߿�����
	int orig_x;//����ʼ������
	int orig_y;
};


void input_row_col_tetris(int &row, int &col, int Max_row, int Min_row, int Max_col, int Min_col);
void print_cmd_game_area(Game_area game_area);




void cmd_tetris();