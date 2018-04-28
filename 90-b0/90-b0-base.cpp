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
#include "90-b0.h"
#include "..\common\common_cfgfile_tools.hpp"
#include "../90-b1/90-b1.h"
using namespace std;

//���������Ǻ������ݹ�汾��
void mark2(int matrix1[][10], char matrix2[][10], int cord_row, int cord_col, int Max_row, int Max_col)
{
	matrix2[cord_row][cord_col] = '*';

	if (cord_row > 0 && matrix1[cord_row - 1][cord_col] == matrix1[cord_row][cord_col] && matrix2[cord_row - 1][cord_col] != '*')
	{
		matrix2[cord_row - 1][cord_col] = '*';
		mark2(matrix1, matrix2, cord_row - 1, cord_col, Max_row, Max_col);
	}

	if (cord_row < Max_row - 1 && matrix1[cord_row + 1][cord_col] == matrix1[cord_row][cord_col] && matrix2[cord_row + 1][cord_col] != '*')
	{
		matrix2[cord_row + 1][cord_col] = '*';
		mark2(matrix1, matrix2, cord_row + 1, cord_col, Max_row, Max_col);
	}

	if (cord_col > 0 && matrix1[cord_row][cord_col - 1] == matrix1[cord_row][cord_col] && matrix2[cord_row][cord_col - 1] != '*')
	{
		matrix2[cord_row][cord_col - 1] = '*';
		mark2(matrix1, matrix2, cord_row, cord_col - 1, Max_row, Max_col);
	}

	if (cord_row <Max_col - 1 && matrix1[cord_row][cord_col + 1] == matrix1[cord_row][cord_col] && matrix2[cord_row][cord_col + 1] != '*')
	{
		matrix2[cord_row][cord_col + 1] = '*';
		mark2(matrix1, matrix2, cord_row, cord_col + 1, Max_row, Max_col);
	}
}

//�ú������ڴ�ӡ���������ͬɫ��ʶ����
void print_color_zero(int(*rand_matrix)[10], int row, int col)
{
	cout << "��0�������<��ͬɫ��ʶ>: " << endl;
	cout << "  |";
	for (int i = 0; i < col; i++)
	{
		cout << "  " << i;
	}
	cout << endl;
	cout << "--+";
	for (int i = 0; i < col; i++)
	{
		cout << "---";
	}
	cout << endl;

	for (int i = 0; i < row; i++)
	{
		cout << char(i + 65) << " |";
		for (int j = 0; j < col; j++)
		{
			if (rand_matrix[i][j] == 0)
			{
				setcolor(COLOR_BLACK, COLOR_HPINK);
				cout << "  " << rand_matrix[i][j];
				setcolor();
			}
			else
			{
				cout << "  " << rand_matrix[i][j];
			}
		}
		cout << endl;
	}
}

//����Ŀһ���������ҳ��ɺϳ����ʶ���ǵݹ飩
void one_check_mark(int(*rand_matrix)[10], char(*mark_matrix)[10], int row, int col, char &input_alpha, int &input_num)
{
	//��ӡ��������
	cout << endl;
	cout << "��ǰ����:" << endl;
	print_matirx(rand_matrix, row, col);

	input_cord(rand_matrix, row, col, input_alpha, input_num);

	//�ڱ�Ǿ����ϱ������ͬ������
	mark(rand_matrix, mark_matrix, int(input_alpha - 65), input_num, row, col);

	//��ӡ���ҽ������
	cout << endl << "���ҽ������:" << endl;
	print_mark(mark_matrix, row, col);

	//��ӡ��ͬɫ��ʶ���ڲ�����
	cout << endl << "��ǰ����<��ͬɫ��ʶ>:" << endl;
	print_color_matrix(rand_matrix, mark_matrix, row, col);
	cout << endl;
}

//����Ŀ�����������ҳ��ɺϳ����ʶ���ݹ飩
void two_check_mark(int(*rand_matrix)[10], char(*mark_matrix)[10], int row, int col, char &input_alpha, int &input_num)
{
	//��ӡ��������
	cout << endl;
	cout << "��ǰ����:" << endl;
	print_matirx(rand_matrix, row, col);

	input_cord(rand_matrix, row, col, input_alpha, input_num);

	//�ڱ�Ǿ����ϱ������ͬ������
	mark2(rand_matrix, mark_matrix, int(input_alpha - 65), input_num, row, col);

	//��ӡ���ҽ������
	cout << endl << "���ҽ������:" << endl;
	print_mark(mark_matrix, row, col);

	//��ӡ��ͬɫ��ʶ���ڲ�����
	cout << endl << "��ǰ����<��ͬɫ��ʶ>:" << endl;
	print_color_matrix(rand_matrix, mark_matrix, row, col);
	cout << endl;
}

//����Ŀ�������������һ�κϳɣ��ֲ�����ʾ��
void three_cmd_combine(int(*rand_matrix)[10], char(*mark_matrix)[10], int &row, int &col, char &input_alpha, int &input_num, int &score, int &total_score,int goal)
{
	cout << endl;
	score = combine(rand_matrix, mark_matrix, row, col, input_alpha, input_num);
	total_score += score;

	cout << "���ε÷�: " << score << "  " << "�ܵ÷�: " << total_score << "  " << "�ϳ�Ŀ��: " << goal << endl << endl;
	cout << "���س����������������0����...";
	//���Գ��س�������������
	while (_getch() != '\r')
		;

	matrix_move(rand_matrix, mark_matrix, row, col, DOWN);
	orig_mark(mark_matrix, row, col);
	cout << endl;
	print_color_zero(rand_matrix, row, col);

	
	cout <<endl<< "���س���������ֵ���...";
	while (_getch() != '\r')
		;

	fill_rmatrix(rand_matrix, mark_matrix, row, col);
	
	cout << endl << "��ֵ���������<��ͬɫ��ʶ>: " << endl;
	print_color_matrix(rand_matrix, mark_matrix, row, col);

	if (end_judge(rand_matrix, row, col))
	{
		setcolor(COLOR_HYELLOW, COLOR_HRED);
		cout << endl << "�޿ɺϳ����Ϸ����..." << endl;
		setcolor();
	}
}

//����Ŀ�ģ������������棨�ֲ�����ʾ��
void four_cmd_complete(int(*rand_matrix)[10], char(*mark_matrix)[10], int &row, int &col, char &input_alpha, int &input_num, int &score, int &total_score, int goal)
{
	//��ʼ���ڲ�����
	orig_matrix(rand_matrix, row, col, MAKE10);
	
	while (!end_judge(rand_matrix, row, col))
	{
		//��ʼ���������
		orig_mark(mark_matrix, row, col);

		//ִ�е�һС��ĺ���
		one_check_mark(rand_matrix, mark_matrix, row, col, input_alpha, input_num);

		switch (confirm_combine("��ȷ���Ƿ�����ڵ���ֵͬ�ϲ���", "��", input_alpha, input_num))
		{
			//ִ�е���С��ĺ���
		case 'y':three_cmd_combine(rand_matrix, mark_matrix, row, col, input_alpha, input_num, score, total_score, goal); break;
		case 'n':continue;
		case 'q':return;
		}

		cout << "�����������������س���������һ�ε�����...";

		if (win_check(rand_matrix, row, col,goal))
		{
			setcolor(COLOR_HYELLOW, COLOR_HRED);
			cout << endl << "�Ѿ��ϳɵ�" << goal << "!!" << endl;
			setcolor();
			cout << "���س��������Ŀ�����...";

			while (_getch() != '\r');

			goal++;
			continue;
		}

		while (_getch() != '\r');
		continue;
	}

	if (end_judge(rand_matrix, row, col))
	{
		setcolor(COLOR_HYELLOW, COLOR_HRED);
		cout << endl << "�޿ɺϳ�����س�������Ϸ..." << endl;
		setcolor();

		while (_getch() != '\r');
		return;
	}
}

