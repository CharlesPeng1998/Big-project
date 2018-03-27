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

int main()
{
	//����һ��ָ�����飬��Ŵ���˵������Ĳ˵�ѡ��
	const char *items[10];
	items[0] = "A.�������ҳ����������ʶ";
	items[1] = "B.���������һ���������ֲ�����ʾ��";
	items[2] = "C.���������һ�أ��ֲ�����ʾ��";
	items[3] = "D.αͼ�ν����������ѡ��һ��ɫ�飨�޷ָ��ߣ�";
	items[4] = "E.αͼ�ν����������ѡ��һ��ɫ�飨�зָ��ߣ�";
	items[5] = "F.αͼ�ν������һ���������ֲ��裩";
	items[6] = "G.αͼ�ν���������";
	items[7] = "Q.�˳�";

	while (1)
	{
		char choice = menu(items, 8);

		if (choice == items[0][0])
		{
			//��ʾ�û�����������
			cls();
			int row, col;
			input_row_col(row, col,POPSTAR);

			//�û�����ľ������꣬�к�Ϊ��ĸ��alpha�����к�Ϊ���֣�num��
			char input_alpha;
			int input_num;

			//�����������ͱ�Ǿ���
			int rand_matrix[10][10] = { 0 };
			char mark_matrix[10][10];

			//��ʼ���ڲ�����
			orig_matrix(rand_matrix, row, col,POPSTAR);
			orig_mark(mark_matrix, row, col);

			//ִ�е�һС��ĺ���
			A_find_mark(rand_matrix,mark_matrix,row,col,input_alpha,input_num);
			//�������˵�
			back_to_menu();

			cls();
			continue;
		}

		else if (choice == items[1][0])
		{
			//��ʾ�û�����������
			cls();
			int row, col;
			input_row_col(row, col,POPSTAR);

			//�����������ͱ�Ǿ���
			int rand_matrix[10][10] = { 0 };
			char mark_matrix[10][10];

			//��ʼ���ڲ�����
			orig_matrix(rand_matrix, row, col,POPSTAR);
			orig_mark(mark_matrix, row, col);

			//�û�����ľ������꣬�к�Ϊ��ĸ��alpha�����к�Ϊ���֣�num��
			char input_alpha;
			int input_num;

			int score, total_score = 0;//��¼���һ�������ķ����͵�ǰ�ܷ���
			
			//ִ�е�һС��ĺ���
			A_find_mark(rand_matrix, mark_matrix, row, col, input_alpha, input_num);
			
			switch (confirm_combine("ȷ���Ƿ��", "����Χ����ֵͬ����", input_alpha, input_num))
			{
			//ִ�еڶ�С��ĺ���
			case 'y':B_eliminate(rand_matrix, mark_matrix, row, col, input_alpha, input_num, score, total_score); break;
			case 'n':break;
			case 'q':break;
			}

			//�������˵�
			back_to_menu();

			cls();
			continue;
		}

		else if (choice == items[2][0])
		{
			//��ʾ�û�����������
			cls();
			int row, col;
			input_row_col(row, col,POPSTAR);

			//�����������ͱ�Ǿ���
			int rand_matrix[10][10] = { 0 };
			char mark_matrix[10][10];

			//�û�����ľ������꣬�к�Ϊ��ĸ��alpha�����к�Ϊ���֣�num��
			char input_alpha;
			int input_num;

			int score, total_score = 0;//��¼���һ�������ķ����͵�ǰ�ܷ���

			//ִ�е���С�������������溯��
			C_cmd_complete(rand_matrix, mark_matrix, row, col, input_alpha, input_num, score, total_score);

			//�������˵�
			back_to_menu();

			cls();
			continue;
		}

		else if (choice == items[3][0])
		{
			//��ʾ�û�����������
			cls();
			int row, col;
			input_row_col(row, col,POPSTAR);

			int rand_matrix[10][10] = { 0 };
			char mark_matrix[10][10];
			
			int score, total_score = 0;//��¼���һ�������ķ����͵�ǰ�ܷ���

			//ִ�е���С��ĺ���
			D_GUI_choose_undvd(rand_matrix, mark_matrix, row, col, score, total_score);
			
			back_to_menu();

			cls();
			continue;
		}

		else if (choice == items[4][0])
		{
			//��ʾ�û�����������
			cls();
			int row, col;
			input_row_col(row, col,POPSTAR);

			//�����������ͱ�Ǿ���
			int rand_matrix[10][10] = { 0 };
			char mark_matrix[10][10];

			int score, total_score = 0;//��¼���һ�������ķ����͵�ǰ�ܷ���

	        //ִ�е���С��ĺ���
			E_GUI_choose_dvd(rand_matrix, mark_matrix, row, col, score, total_score);

			back_to_menu();

			cls();
			continue;
		}

		else if (choice == items[5][0])
		{
			//��ʾ�û�����������
			cls();
			int row, col;
			input_row_col(row, col,POPSTAR);

			//�����������ͱ�Ǿ���
			int rand_matrix[10][10] = { 0 };
			char mark_matrix[10][10];

			int score, total_score = 0;//��¼���һ�������ķ����͵�ǰ�ܷ���

			F_GUI_eliminate(rand_matrix, mark_matrix, row, col, score, total_score,F);

			back_to_menu();

			cls();
			continue;
		}

		else if (choice == items[6][0])
		{
			//��ʾ�û�����������
			cls();
			int row, col;
			input_row_col(row, col,POPSTAR);

			//�����������ͱ�Ǿ���
			int rand_matrix[10][10] = { 0 };
			char mark_matrix[10][10];

			int score, total_score = 0;//��¼���һ�������ķ����͵�ǰ�ܷ���

			while (1)
			{
				G_GUI_complete(rand_matrix, mark_matrix, row, col, score, total_score);
			}
		}

		else if (choice == items[7][0])
		{
			cout << endl << endl;
			return 0;
		}
	}
}