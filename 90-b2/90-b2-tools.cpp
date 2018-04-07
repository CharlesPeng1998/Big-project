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

//�ú������ڽ����û�����������
void input_row_col_tetris(int &row, int &col, int Max_row, int Min_row, int Max_col, int Min_col)
{
	cls();
	
	bool judge_row = 0, judge_col = 0;

	int curr_x;
	int curr_y; //������¼��ǰ����λ��

	getxy(curr_x, curr_y);//��ȡ��ǰ���λ�ã��Ա����������ʱ��귵����ԭ����λ��

	while (!judge_row)
	{
		gotoxy(curr_x, curr_y);

		cout << "����������<" << Min_row << '-' << Max_row << ">: ";

		cin >> row;

		//���������Ƿ�Ϸ�����ͬ
		if (cin.fail() || row < Min_row || row > Max_row)
		{
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail(), '\n');
			cout << "���벻�Ϸ�������������     ";
			continue;
		}
		else judge_row = 1;
		break;
	}

	getxy(curr_x, curr_y);
	cout << "                      ";
	gotoxy(curr_x, curr_y);//��������������ϴ����µĴ�����ʾ����ͬ

	while (!judge_col)
	{
		gotoxy(curr_x, curr_y);

		cout << "����������<" << Min_col << '-' << Max_col << ">: ";

		cin >> col;

		//���������Ƿ�Ϸ�����ͬ
		if (cin.fail() || col < Min_col || col > Max_col)
		{
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail(), '\n');
			cout << "���벻�Ϸ�������������     ";
			continue;
		}
		else judge_col = 1;
		break;
	}

	cls();
}

//�жϼٶ������λ���Ƿ�Ϸ�
bool position_legal(Block block, Game_area game_area)
{
	int dis_row, dis_col; //������ĳ�㵽���ĵ����о���

	for (int i = 0; i < BLOCK_ROW; i++)
	{
		for (int j = 0; j < BLOCK_COL; j++)
		{
			if (block.matrix[i][j] == 1)
			{
				dis_row = i - block.central_pos.cord_row;
				dis_col = j - block.central_pos.cord_col;

				if (block.curr_pos.cord_row + dis_row >= game_area.matrix_row) return 0;
				else if (block.curr_pos.cord_col + dis_col >= game_area.matrix_col || block.curr_pos.cord_col + dis_col < 0) return 0;
				else if (game_area.display_matrix[block.curr_pos.cord_row + dis_row][block.curr_pos.cord_col + dis_col] != 0) return 0;
			}
		}
	}

	return 1;
}

//�ж���ǰ�����ܷ����ĳ����Ϊ��״̬
bool judge_behavior(Block block, Game_area game_area, int type)
{
	switch (type)
	{
	case DOWN:
		draw_block(block, game_area, ELIMINATE_CURR);
		block.curr_pos.cord_row++;
		return position_legal(block, game_area);
	case LEFT:
		draw_block(block, game_area, ELIMINATE_CURR);
		block.curr_pos.cord_col--;
		return position_legal(block, game_area);
	case RIGHT:
		draw_block(block, game_area, ELIMINATE_CURR);
		block.curr_pos.cord_col++;
		return position_legal(block, game_area);
	case ROTATE:
		draw_block(block, game_area, ELIMINATE_CURR);
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
		return position_legal(block, game_area);
	}

	return 0;
}