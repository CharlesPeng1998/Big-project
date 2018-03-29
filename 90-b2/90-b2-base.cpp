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

//����˹�������������ǰ汾
void cmd_tetris()
{
	//����һ����Ϸ����ṹ�����
	Game_area game_area;

	//����һ������̨��С�ṹ�����
	Consoleborder consoleborder;

	//�����û��Զ���������
	input_row_col_tetris(game_area.matrix_row, game_area.matrix_col, MAX_ROW, MIN_ROW, MAX_COL, MIN_COL);

	//Ϊ��ʾ����̬����ռ�
	game_area.display_matrix = new int *[game_area.matrix_row];
	for (int i = 0; i < game_area.matrix_row; i++)
	{
		game_area.display_matrix[i] = new int[game_area.matrix_col];
	}

	//����ʼ��ʾ����ȫ����Ϊ0
	for (int i = 0; i < game_area.matrix_row; i++)
	{
		for (int j = 0; j < game_area.matrix_col; j++)
		{
			game_area.display_matrix[i][j] = 0;
		}
	}

	//��ʼ����Ϸ�������ʼ����
	game_area.orig_x = 25;
	game_area.orig_y = 1;

	//������Ӧ��Ϸ����Ŀ���̨���ڴ�С
	consoleborder.cols = game_area.orig_x+(game_area.matrix_col+2)*2;
	consoleborder.lines = game_area.orig_y+game_area.matrix_row+5;

	setconsoleborder(consoleborder.cols, consoleborder.lines);

	//��ӡ��ʾ���󣨼���Ϸ����
	print_cmd_game_area(game_area);

	back_to_menu();

	//���Ȼ��յ�һ���Ķ�̬����
	for (int i = 0; i < game_area.matrix_col; i++)
	{
		delete[] game_area.display_matrix[i];
	}
	//���ո�һ���Ķ�̬����
	delete[] game_area.display_matrix;
}