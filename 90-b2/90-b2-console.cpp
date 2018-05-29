/*1751367 ��2 ����*/
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

//��Ϸ�����ڲ����鵱�д�ӡһ������
void draw_block(tBlock block, tGame_area &game_area, int type)
{
	int dis_row, dis_col; //������ĳ�㵽���ĵ����о���
	for (int i = 0; i < BLOCK_ROW; i++)
	{
		for (int j = 0; j < BLOCK_COL; j++)
		{
			if (block.matrix[i][j] != 0)
			{
				dis_row = i - block.central_pos.cord_row;
				dis_col = j - block.central_pos.cord_col;

				switch (type)
				{
				case DRAW:game_area.display_matrix[block.curr_pos.cord_row + dis_row][block.curr_pos.cord_col + dis_col] = block.value; break;
					//�����ϴ�����λ�õķ��飬�ڷ����ƶ�ʱʹ��
				case ELIMINATE_PAST:game_area.display_matrix[block.last_pos.cord_row + dis_row][block.last_pos.cord_col + dis_col] = 0; break;
					//������ǰλ�õķ��飬����ת����ʱʹ��
				case ELIMINATE_CURR:game_area.display_matrix[block.curr_pos.cord_row + dis_row][block.curr_pos.cord_col + dis_col] = 0; break;
				}
			}
		}
	}

	//print_cmd_game_area(game_area);
}

//������ƶ�
void block_move(tBlock &block, int direction, tGame_area &game_area, int type)
{
	block.last_pos = block.curr_pos;

	switch (direction)
	{
	case DOWN:block.curr_pos.cord_row++; break;
	case LEFT:block.curr_pos.cord_col--; break;
	case RIGHT:block.curr_pos.cord_col++; break;
	}

	draw_full_block(block, game_area, ELIMINATE_PAST);
	draw_full_block(block, game_area, DRAW);
}

//�������ת
void block_rotate(tBlock &block, tGame_area &game_area, int direction, int type)
{
	draw_full_block(block, game_area, ELIMINATE_CURR);
	
	//��һ����ʱ�ľ�����ÿ����ת֮��ĵ㣬����ٽ������Ƶ�ԭ����
	int copy_matrix[BLOCK_ROW][BLOCK_COL] = { 0 };

	for (int i = 0; i < BLOCK_ROW; i++)
	{
		for (int j = 0; j < BLOCK_COL; j++)
		{
			if (block.matrix[i][j] != 0)
			{
				copy_matrix[4 - j][i] = block.matrix[i][j];
			}
		}
	}

	for (int i = 0; i < BLOCK_ROW; i++)
	{
		for (int j = 0; j < BLOCK_COL; j++)
		{
			block.matrix[i][j] = copy_matrix[i][j];
		}
	}

	draw_full_block(block, game_area, DRAW);
}

//�ú��������ж��Ƿ����һ�в�������������
void kill_row_fall(tBlock block, tGame_area &game_area, int &total_score, int type)
{
	bool finished;
	int target_row;
	int kill_num = 0;
	int temp;

	for (target_row = EXTRA_ROW + 1; target_row < game_area.matrix_row; target_row++)
	{
		finished = 1;

		for (int j = 0; j < game_area.matrix_col; j++)
		{
			if (game_area.display_matrix[target_row][j] == 0)
			{
				finished = 0;
				break;
			}
		}

		if (finished)
		{
			kill_num++;

			for (int i = 0; i < game_area.matrix_col; i++)
				game_area.display_matrix[target_row][i] = 0;

			if (type == GUI)
			{
				for (int i = 0; i<game_area.matrix_col; i++)
					draw_GUI_block(block, block.value, game_area.orig_cord.cord_x + 2 + i * 6, game_area.orig_cord.cord_y + 1 + (target_row - EXTRA_ROW) * 3, EMP);
			}

			for (int i = target_row - 1; i >= EXTRA_ROW; i--)
			{
				for (int j = 0; j < game_area.matrix_col; j++)
				{
					if (type == GUI)
					{
						draw_GUI_block(block, game_area.display_matrix[i][j], game_area.orig_cord.cord_x + 2 + j * 6, game_area.orig_cord.cord_y + 1 + (i - EXTRA_ROW) * 3, EMP);
						draw_GUI_block(block, game_area.display_matrix[i][j], game_area.orig_cord.cord_x + 2 + j * 6, game_area.orig_cord.cord_y + 1 + (i - EXTRA_ROW + 1) * 3, NORMAL);
					}

					temp = game_area.display_matrix[i][j];
					game_area.display_matrix[i][j] = game_area.display_matrix[i + 1][j];
					game_area.display_matrix[i + 1][j] = temp;
				}
			}
		}
	}

	total_score += (kill_num*kill_num + kill_num) / 2;
}

//�ú��������ж���Ϸ�Ƿ����
bool judge_end(tGame_area &game_area)
{
	for (int i = 0; i < game_area.matrix_col; i++)
	{
		if (game_area.display_matrix[3][i] != 0)
		{
			gotoxy(10, 3);
			setcolor(0, COLOR_RED);
			cout << "��Ϸ�������밴�س��������˵�...";
			setcursor(CURSOR_INVISIBLE);
			setcolor();

			while (_getch() != '\r');
			setcursor(CURSOR_VISIBLE_NORMAL);

			return 1;
		}
	}

	return 0;
}

//αͼ�ν����»��Ʊ߿�ͱ���
void print_GUI_game_area(tGame_area game_area)
{
	setcolor(COLOR_HWHITE, 0);

	//������ƶ���ָ����ʼλ��
	gotoxy(game_area.orig_cord.cord_x, game_area.orig_cord.cord_y);

	//���ȴ�ӡ�߿�
	cout << game_area.border[0];
	for (int i = 0; i < game_area.matrix_col * 3; i++)
	{
		cout << game_area.border[4];
	}
	cout << game_area.border[1];

	for (int i = EXTRA_ROW * 3; i < game_area.matrix_row * 3; i++)
	{
		game_area.orig_cord.cord_y++;
		gotoxy(game_area.orig_cord.cord_x, game_area.orig_cord.cord_y);

		cout << game_area.border[5];

		for (int j = 0; j < game_area.matrix_col * 3; j++)
		{
			setcolor(COLOR_HWHITE, COLOR_HWHITE);
			cout << "  ";
			setcolor(COLOR_HWHITE, 0);
		}
		cout << game_area.border[5];
	}

	game_area.orig_cord.cord_y++;
	gotoxy(game_area.orig_cord.cord_x, game_area.orig_cord.cord_y);

	cout << game_area.border[2];
	for (int i = 0; i < game_area.matrix_col * 3; i++)
	{
		cout << game_area.border[4];
	}
	cout << game_area.border[3];

	setcolor();
}

//αͼ�ν����»���һ������
void draw_GUI_block(tBlock block, int value, int cord_x, int cord_y, int type)
{
	int bg_color = 0;//��¼ɫ��ı���ɫ

	gotoxy(cord_x, cord_y);

	//�����ڲ������ֵѡ��ͬ��ɫ����ɫ
	switch (value)
	{
	case 1:bg_color = COLOR_HRED; break;
	case 2:bg_color = COLOR_HBLUE; break;
	case 3:bg_color = COLOR_HGREEN; break;
	case 4:bg_color = COLOR_HYELLOW; break;
	case 5:bg_color = COLOR_HPINK; break;
	case 6:bg_color = COLOR_BLUE; break;
	case 7:bg_color = COLOR_HCYAN; break;
	case 8:bg_color = COLOR_PINK; break;
	case 9:bg_color = COLOR_GREEN; break;
	case 10:bg_color = COLOR_RED; break;
	}

	if (type == EMP || value == 0) setcolor(COLOR_HWHITE, COLOR_HWHITE);
	else setcolor(bg_color, 0);

	cout << block.style[0] << block.style[4] << block.style[1];
	getxy(cord_x, cord_y);
	gotoxy(cord_x - 6, cord_y + 1);
	cout << block.style[5] << block.style[6] << block.style[5];
	getxy(cord_x, cord_y);
	gotoxy(cord_x - 6, cord_y + 1);
	cout << block.style[2] << block.style[4] << block.style[3];

	setcolor();
}

//αͼ�ν����»����������ַ���
void draw_full_block(tBlock block, tGame_area &game_area, int type)
{
	int dis_row, dis_col; //������ĳ�㵽���ĵ����о���
	int draw_row, draw_col;
	for (int i = 0; i < BLOCK_ROW; i++)
	{
		for (int j = 0; j < BLOCK_COL; j++)
		{
			if (block.matrix[i][j] != 0)
			{
				dis_row = i - block.central_pos.cord_row;
				dis_col = j - block.central_pos.cord_col;

				switch (type)
				{
				case DRAW:
					draw_row = block.curr_pos.cord_row + dis_row - EXTRA_ROW;
					draw_col = block.curr_pos.cord_col + dis_col;

					game_area.display_matrix[block.curr_pos.cord_row + dis_row][block.curr_pos.cord_col + dis_col] = block.value;
					if (draw_row >= 0)
						draw_GUI_block(block, block.value, game_area.orig_cord.cord_x + 2 + (draw_col) * 6, game_area.orig_cord.cord_y + 1 + (draw_row) * 3, NORMAL);
					break;

					//�����ϴ�����λ�õķ��飬�ڷ����ƶ�ʱʹ��
				case ELIMINATE_PAST:
					draw_row = block.last_pos.cord_row + dis_row - EXTRA_ROW;
					draw_col = block.last_pos.cord_col + dis_col;

					game_area.display_matrix[block.last_pos.cord_row + dis_row][block.last_pos.cord_col + dis_col] = 0;
					if (draw_row >= 0)
						draw_GUI_block(block, block.value, game_area.orig_cord.cord_x + 2 + (draw_col) * 6, game_area.orig_cord.cord_y + 1 + (draw_row) * 3, EMP);
					break;
					//������ǰλ�õķ��飬����ת����ʱʹ��
				case ELIMINATE_CURR:
					draw_row = block.curr_pos.cord_row + dis_row - EXTRA_ROW;
					draw_col = block.curr_pos.cord_col + dis_col;

					game_area.display_matrix[block.curr_pos.cord_row + dis_row][block.curr_pos.cord_col + dis_col] = 0;
					if (draw_row >= 0)
						draw_GUI_block(block, block.value, game_area.orig_cord.cord_x + 2 + (draw_col) * 6, game_area.orig_cord.cord_y + 1 + (draw_row) * 3, EMP);
					break;
				}
			}
		}
	}
}