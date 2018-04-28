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
#include "..\common\common_cfgfile_tools.hpp"
#include "90-b0.h"

#define TEST
//#define TEST1
using namespace std;

int main()
{
#ifndef TEST	
	//����һ��ָ�����飬��Ŵ���˵������Ĳ˵�ѡ��
	const char *items[10];
	items[0] = "1.�������ҳ��ɺϲ����ʶ���ǵݹ飩";
	items[1] = "2.�������ҳ��ɺϲ����ʶ���ݹ飩";
	items[2] = "3.���������һ�κϳɣ��ֲ�����ʾ��";
	items[3] = "4.�����������棨�ֲ�����ʾ��";
	items[4] = "5.αͼ�ν�����ʾ��ʼ���飨�޷ָ��ߣ�";
	items[5] = "6.αͼ�ν�����ʾ��ʼ���飨�зָ��ߣ�";
	items[6] = "7.αͼ�ν������ü�ͷ��ѡ��ǰɫ��";
	items[7] = "8.αͼ�ν������һ�κϳɣ��ֲ��裩";
	items[8] = "9.αͼ�ν���������";
	items[9] = "0.�˳�";

	while (1)
	{
		char choice = menu(items, 10);

		if (choice == items[0][0])
		{
			int col, row;
			system("cls");
			input_row_col(row, col, MAKE10);

			//�����������ͱ���þ���
			int rand_matrix[8][10] = { 0 };
			char mark_matrix[8][10];

			//�û�����ľ������꣬�к�Ϊ��ĸ��alpha�����к�Ϊ���֣�num��
			char input_alpha;
			int input_num;

			//��ʼ���ڲ�����
			orig_matrix(rand_matrix, row, col, MAKE10);
			orig_mark(mark_matrix, row, col);

			//ִ�е�һС��ĺ���
			one_check_mark(rand_matrix, mark_matrix, row, col, input_alpha, input_num);

			//�������˵�
			back_to_menu();

			cls();
			continue;
		}

		else if (choice == items[1][0])
		{
			int col, row;
			system("cls");
			input_row_col(row, col, MAKE10);

			//�����������ͱ���þ���
			int rand_matrix[8][10] = { 0 };
			char mark_matrix[8][10];

			//�û�����ľ������꣬�к�Ϊ��ĸ��alpha�����к�Ϊ���֣�num��
			char input_alpha;
			int input_num;

			//��ʼ���ڲ�����
			orig_matrix(rand_matrix, row, col, MAKE10);
			orig_mark(mark_matrix, row, col);

			//ִ�еڶ�С��ĺ���
			two_check_mark(rand_matrix, mark_matrix, row, col, input_alpha, input_num);

			//�������˵�
			back_to_menu();

			cls();
			continue;
		}

		else if (choice == items[2][0])
		{
			int col, row, goal;

			system("cls");
			input_rcg(row, col, goal);

			//�����������ͱ���þ���
			int rand_matrix[8][10] = { 0 };
			char mark_matrix[8][10];

			//�û�����ľ������꣬�к�Ϊ��ĸ��alpha�����к�Ϊ���֣�num��
			char input_alpha;
			int input_num, score,total_score=0;

			//��ʼ���ڲ�����
			orig_matrix(rand_matrix, row, col, MAKE10);
			orig_mark(mark_matrix, row, col);

			//ִ�е�һС��ĺ���
			one_check_mark(rand_matrix, mark_matrix, row, col, input_alpha, input_num);

			switch (confirm_combine("��ȷ���Ƿ�����ڵ���ֵͬ�ϲ���", "��", input_alpha, input_num))
			{
				//ִ�е���С��ĺ���
			case 'y':three_cmd_combine(rand_matrix, mark_matrix, row, col, input_alpha, input_num, score, total_score, goal); break;
			case 'n':break;
			case 'q':break;
			}

			//�������˵�
			back_to_menu();

			cls();
			continue;

		}

		else if (choice == items[3][0])
		{
			int col, row, goal;

			system("cls");
			input_rcg(row, col, goal);

			//�����������ͱ���þ���
			int rand_matrix[8][10] = { 0 };
			char mark_matrix[8][10];

			//�û�����ľ������꣬�к�Ϊ��ĸ��alpha�����к�Ϊ���֣�num��
			char input_alpha;
			int input_num, score, total_score = 0;

			four_cmd_complete(rand_matrix, mark_matrix, row, col, input_alpha, input_num, score, total_score, goal);

			//�������˵�
			back_to_menu();

			cls();
			continue;
		}

		else if (choice == items[4][0])
		{
			int col, row;
			system("cls");
			input_row_col(row, col, MAKE10);

			//�����������ͱ���þ���
			int rand_matrix[8][10] = { 0 };

			five_GUI_dsp_undvd(rand_matrix, row, col);

			//�������˵�
			back_to_menu();

			cls();
			continue;
		}

		else if (choice == items[5][0])
		{
			int col, row;
			system("cls");
			input_row_col(row, col, MAKE10);

			//�����������ͱ���þ���
			int rand_matrix[8][10] = { 0 };

			six_GUI_dsp_dvd(rand_matrix, row, col);

			//�������˵�
			back_to_menu();

			cls();
			continue;
		}

		else if (choice == items[6][0])
		{
			int col, row;
			system("cls");
			input_row_col(row, col, MAKE10);

			//�����������ͱ���þ���
			int rand_matrix[8][10] = { 0 };
			char mark_matrix[8][10];

			six_GUI_dsp_dvd(rand_matrix, row, col);

			seven_kb_choose(rand_matrix,mark_matrix, row, col);

			//�������˵�
			back_to_menu();

			cls();
			continue;
		}

		else if (choice == items[7][0])
		{
			int col, row, score = 0, total_score = 0,goal=5;
			system("cls");
			input_row_col(row, col, MAKE10);

			//�����������ͱ���þ���
			int rand_matrix[8][10] = { 0 };
			char mark_matrix[8][10];

			//��ʼ���ڲ�����
			orig_matrix(rand_matrix, row, col, MAKE10);
			orig_mark(mark_matrix, row, col);

			six_GUI_dsp_dvd(rand_matrix, row, col);

			eight_GUI_combine(rand_matrix, mark_matrix, row, col,goal,score,total_score);

			//�������˵�
			back_to_menu();

			cls();
			continue;
		}

		else if (choice == items[8][0])
		{
			int col, row, goal, score = 0, total_score = 0;

			system("cls");
			input_rcg(row, col, goal);

			//�����������ͱ���þ���
			int rand_matrix[8][10] = { 0 };
			char mark_matrix[8][10];

			//��ʼ���ڲ�����
			orig_matrix(rand_matrix, row, col, MAKE10);
			orig_mark(mark_matrix, row, col);

			six_GUI_dsp_dvd(rand_matrix, row, col);

			nine_GUI_complete(rand_matrix, mark_matrix, row, col, goal, score, total_score);

			//�������˵�
			back_to_menu();

			cls();
			continue;
		}

		else if (choice == items[9][0])
		{
			cout << endl << endl;
			return 0;
		}
	}

	
#endif	
	
#ifdef TEST1	
	fstream cfgfile;
	open_cfgfile(cfgfile, "test.cfg", OPEN_OPT_RDWR);

	//Group *group_head = read_cfg(cfgfile);

	//print_cfg(group_head);

	//delete_cfg(group_head);
	
	Block popstar_block;
	popstar_block.type = POPSTAR;

	Block_color block_color;

	item_get_value(cfgfile, "ɫ������", "ɫ��1-ǰ��ɫ", &block_color.block_color_1.fg_color, TYPE_INT);
	item_get_value(cfgfile, "ɫ������", "ɫ��1-����ɫ", &block_color.block_color_1.bg_color, TYPE_INT);

	Cord test_cord;
	test_cord.cord_x = 0;
	test_cord.cord_y = 0;

	popstar_block.width = 6;
	popstar_block.height = 3;

	Game_area game_area;
	game_area.orig_cord.cord_x = 0;
	game_area.orig_cord.cord_y = 0;

	game_area.game_area_color.bg_color = COLOR_HWHITE;
	game_area.game_area_color.fg_color = 0;

	print_game_area(game_area, popstar_block);
#endif 

	//������Ϸ����ṹ�����
	Game_area game_area;
	//ɫ��ṹ�����
	Block block;

	//�������ļ��ж�ȡ��Ϣ





	system("cls");
	input_rcg(game_area.matrix_row, game_area.matrix_row, game_area.goal);

	//��ʼ���ڲ�����
	orig_matrix(game_area.rand_matrix, game_area.matrix_row, game_area.matrix_col, MAKE10);
	orig_mark(game_area.mark_matrix, game_area.matrix_row, game_area.matrix_col);

	print_game_area(game_area, block);




	return 0;

}