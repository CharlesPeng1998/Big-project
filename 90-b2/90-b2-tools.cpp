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
#include "90-b2.h"
using namespace std;

//该函数用于接收用户输入行列数
void input_row_col_tetris(int &row, int &col, int Max_row, int Min_row, int Max_col, int Min_col)
{
	cls();
	
	bool judge_row = 0, judge_col = 0;

	int curr_x;
	int curr_y; //用来记录当前光标的位置

	getxy(curr_x, curr_y);//获取当前光标位置，以便于输入错误时光标返回至原输入位置

	while (!judge_row)
	{
		gotoxy(curr_x, curr_y);

		cout << "请输入行数<" << Min_row << '-' << Max_row << ">: ";

		cin >> row;

		//检验输入是否合法，下同
		if (cin.fail() || row < Min_row || row > Max_row)
		{
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail(), '\n');
			cout << "输入不合法，请重新输入     ";
			continue;
		}
		else judge_row = 1;
		break;
	}

	getxy(curr_x, curr_y);
	cout << "                      ";
	gotoxy(curr_x, curr_y);//这三句用于清除上次留下的错误提示，下同

	while (!judge_col)
	{
		gotoxy(curr_x, curr_y);

		cout << "请输入列数<" << Min_col << '-' << Max_col << ">: ";

		cin >> col;

		//检验输入是否合法，下同
		if (cin.fail() || col < Min_col || col > Max_col)
		{
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail(), '\n');
			cout << "输入不合法，请重新输入     ";
			continue;
		}
		else judge_col = 1;
		break;
	}

	cls();
}