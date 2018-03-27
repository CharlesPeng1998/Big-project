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
#include "90-b1.h"
using namespace std;

//�ú������ڸ��ݱ�Ǿ�����ڲ����������������������0
void eliminate(int(*rand_matrix)[10], char(*mark_matrix)[10], int row, int col)
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (mark_matrix[i][j] == '*') rand_matrix[i][j] = 0;
		}
	}
}

//�ú������ڼ���һ�������ĵ÷�
int elmn_score(char(*mark_matrix)[10], int row, int col)
{
	//��¼��������ĸ���
	int elnm_num = 0;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (mark_matrix[i][j] == '*') elnm_num++;
		}
	}

	return elnm_num * elnm_num * 5;
}

//�ú�������ĳ�ؽ�����ͳ��ʣ�಻��������
int remain_num(int(*rand_matrix)[10], int row, int col)
{
	int num = 0;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (rand_matrix[i][j] != 0) num++;
		}
	}
	return num;
}