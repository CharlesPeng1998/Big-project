/*1751367 计2 彭健聪*/
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

//子题目A：命令行方式找出可消除项并标识
void A_find_mark(int(*rand_matrix)[10], char(*mark_matrix)[10], int &row, int &col,char &input_alpha,int &input_num)
{
	//打印完整数组
	cout << endl;
	cout << "当前数组:" << endl;
	print_matirx(rand_matrix, row, col);

	input_cord(rand_matrix, row, col, input_alpha, input_num);

	//在标记矩阵上标记连续同项区域
	mark(rand_matrix, mark_matrix, int(input_alpha - 65), input_num, row, col);

	//打印查找结果数组
	cout << endl << "查找结果数组:" << endl;
	print_mark(mark_matrix, row, col);

	//打印不同色标识的内部数组
	cout << endl << "当前数组<不同色标识>:" << endl;
	print_color_matrix(rand_matrix, mark_matrix, row, col);
	cout << endl;
}

//子题目B：命令行完成一次消除（分步骤显示）
void B_eliminate(int(*rand_matrix)[10], char(*mark_matrix)[10], int &row, int &col,char &input_alpha, int &input_num,int &score,int &total_score)
{
	//将选择的相同项在内部数组当中置0
	eliminate(rand_matrix, mark_matrix, row, col);

	//打印消除后的内部数组
	cout <<endl<< "相同值归并后的数据<不同色标识>:" << endl;
	print_color_matrix(rand_matrix, mark_matrix, row, col);
	cout << endl;
		
	//计算本次得分
	score = elmn_score(mark_matrix, row, col);
	total_score += score;
	cout << endl << "本次得分：" << score << " 总得分：" << total_score << endl;

	cout << "按回车键进行数组下落操作...";
	while (_getch() != '\r');
	cout << endl;

	//进行数组下落和左移的操作
	matrix_move(rand_matrix, mark_matrix, row, col, DOWN);
	
	cout << "下落后的数组:" << endl;
	print_color_matrix(rand_matrix, mark_matrix, row, col);

	matrix_move(rand_matrix, mark_matrix, row, col, LEFT);
}

//子题目C：命令行完成一关（分步骤显示）
void C_cmd_complete(int(*rand_matrix)[10], char(*mark_matrix)[10], int &row, int &col, char &input_alpha, int &input_num, int &score, int &total_score)
{
	//初始化内部数组
	orig_matrix(rand_matrix, row, col,POPSTAR);

	while (!end_judge(rand_matrix, row, col))
	{
		//初始化标记数组
		orig_mark(mark_matrix, row, col);
		//执行第一小题的函数
		A_find_mark(rand_matrix, mark_matrix, row, col, input_alpha, input_num);

		switch (confirm_combine("确认是否把", "及周围的相同值消除", input_alpha, input_num))
		{
			//执行第二小题的函数
		case 'y':B_eliminate(rand_matrix, mark_matrix, row, col, input_alpha, input_num, score, total_score); break;
		case 'n':continue;
		case 'q':return;
		}

		cout << "本次消除结束，按回车键继续新一次的消除...";

		while (_getch() != '\r');
		continue;
	}

	if (end_judge(rand_matrix, row, col))
	{
		cout << endl;
		cout << "当前数组:" << endl;
		print_matirx(rand_matrix, row, col);
		cout << endl;

		setcolor(COLOR_YELLOW, COLOR_RED);
		cout << "剩余" << remain_num(rand_matrix, row, col) << "个不可消除项，本关结束" << endl;
		setcolor();
	}
}

