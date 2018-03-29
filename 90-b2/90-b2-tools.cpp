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