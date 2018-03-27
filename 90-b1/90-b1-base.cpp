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

//����ĿA�������з�ʽ�ҳ����������ʶ
void A_find_mark(int(*rand_matrix)[10], char(*mark_matrix)[10], int &row, int &col,char &input_alpha,int &input_num)
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

//����ĿB�����������һ���������ֲ�����ʾ��
void B_eliminate(int(*rand_matrix)[10], char(*mark_matrix)[10], int &row, int &col,char &input_alpha, int &input_num,int &score,int &total_score)
{
	//��ѡ�����ͬ�����ڲ����鵱����0
	eliminate(rand_matrix, mark_matrix, row, col);

	//��ӡ��������ڲ�����
	cout <<endl<< "��ֵͬ�鲢�������<��ͬɫ��ʶ>:" << endl;
	print_color_matrix(rand_matrix, mark_matrix, row, col);
	cout << endl;
		
	//���㱾�ε÷�
	score = elmn_score(mark_matrix, row, col);
	total_score += score;
	cout << endl << "���ε÷֣�" << score << " �ܵ÷֣�" << total_score << endl;

	cout << "���س������������������...";
	while (_getch() != '\r');
	cout << endl;

	//����������������ƵĲ���
	matrix_move(rand_matrix, mark_matrix, row, col, DOWN);
	
	cout << "����������:" << endl;
	print_color_matrix(rand_matrix, mark_matrix, row, col);

	matrix_move(rand_matrix, mark_matrix, row, col, LEFT);
}

//����ĿC�����������һ�أ��ֲ�����ʾ��
void C_cmd_complete(int(*rand_matrix)[10], char(*mark_matrix)[10], int &row, int &col, char &input_alpha, int &input_num, int &score, int &total_score)
{
	//��ʼ���ڲ�����
	orig_matrix(rand_matrix, row, col,POPSTAR);

	while (!end_judge(rand_matrix, row, col))
	{
		//��ʼ���������
		orig_mark(mark_matrix, row, col);
		//ִ�е�һС��ĺ���
		A_find_mark(rand_matrix, mark_matrix, row, col, input_alpha, input_num);

		switch (confirm_combine("ȷ���Ƿ��", "����Χ����ֵͬ����", input_alpha, input_num))
		{
			//ִ�еڶ�С��ĺ���
		case 'y':B_eliminate(rand_matrix, mark_matrix, row, col, input_alpha, input_num, score, total_score); break;
		case 'n':continue;
		case 'q':return;
		}

		cout << "�����������������س���������һ�ε�����...";

		while (_getch() != '\r');
		continue;
	}

	if (end_judge(rand_matrix, row, col))
	{
		cout << endl;
		cout << "��ǰ����:" << endl;
		print_matirx(rand_matrix, row, col);
		cout << endl;

		setcolor(COLOR_YELLOW, COLOR_RED);
		cout << "ʣ��" << remain_num(rand_matrix, row, col) << "��������������ؽ���" << endl;
		setcolor();
	}
}

