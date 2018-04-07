/*1751367 计2 彭健聪*/
#include <iostream>
#include <iomanip>
#include <ctime>
#include <cmath>
#include <cstdio>
#include <conio.h>
#include <Windows.h>
#include "cmd_console_tools.h"
#include "common.h"
using namespace std;

//该函数用于用户输入行列数(可以共用）
void input_row_col(int &row, int &col,int game)
{
	bool judge_row = 0, judge_col = 0;

	int curr_x;
	int curr_y; //用来记录当前光标的位置

	getxy(curr_x, curr_y);//获取当前光标位置，以便于输入错误时光标返回至原输入位置

	while (!judge_row)
	{
		gotoxy(curr_x, curr_y);
		
		switch (game)
		{
		case POPSTAR:cout << "请输入行数<8-10>: "; break;
		case MAKE10:cout << "请输入行数<5-8>: "; break;
		}
		
		cin >> row;

		switch (game)
		{
		case POPSTAR:
		{
			//检验输入是否合法，下同
			if (cin.fail() || row < 8 || row > 10)
			{
				cin.clear();
				cin.ignore(cin.rdbuf()->in_avail(), '\n');
				cout << "输入不合法，请重新输入     ";
				continue;
			}
			else judge_row = 1;
			break;
		}

		case MAKE10:
		{
			//检验输入是否合法，下同
			if (cin.fail() || row < 5 || row > 8)
			{
				cin.clear();
				cin.ignore(cin.rdbuf()->in_avail(), '\n');
				cout << "输入不合法，请重新输入     ";
				continue;
			}
			else judge_row = 1;
			break;
		}
		}
	}

	getxy(curr_x, curr_y);
	cout << "                      ";
	gotoxy(curr_x, curr_y);//这三句用于清除上次留下的错误提示，下同

	while (!judge_col)
	{
		gotoxy(curr_x, curr_y);
		switch (game)
		{
		case POPSTAR:cout << "请输入行数<8-10>: "; break;
		case MAKE10:cout << "请输入行数<5-10>: "; break;
		}
		cin >> col;

		switch (game)
		{
		case POPSTAR:
		{
			//检验输入是否合法，下同
			if (cin.fail() || row < 8 || row > 10)
			{
				cin.clear();
				cin.ignore(cin.rdbuf()->in_avail(), '\n');
				cout << "输入不合法，请重新输入     ";
				continue;
			}
			else judge_col = 1;
			break;
		}

		case MAKE10:
		{
			//检验输入是否合法，下同
			if (cin.fail() || row < 5 || row > 10)
			{
				cin.clear();
				cin.ignore(cin.rdbuf()->in_avail(), '\n');
				cout << "输入不合法，请重新输入     ";
				continue;
			}
			else judge_col = 1;
			break;
		}
		}
	}

	getxy(curr_x, curr_y);
	cout << "                      ";
	gotoxy(curr_x, curr_y);
}

//该函数用于每关游戏开始前对数组进行随机填充
void orig_matrix(int(*rand_matrix)[10], int row, int col, int game)
{
	switch (game)
	{
	case POPSTAR:
	{
		srand((unsigned int)(time(0)));//生成随机种子

		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				switch (rand() % 5)
				{
				case 0:rand_matrix[i][j] = 1; break;
				case 1:rand_matrix[i][j] = 2; break;
				case 2:rand_matrix[i][j] = 3; break;
				case 3:rand_matrix[i][j] = 4; break;
				case 4:rand_matrix[i][j] = 5; break;
				}
			}
		}
		break;
	}

	case MAKE10:
	{
		srand((unsigned int)(time(0)));//生成随机种子

									   //1-3等概率填充矩阵
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				switch (rand() % 3)
				{
				case 0:rand_matrix[i][j] = 1; break;
				case 1:rand_matrix[i][j] = 2; break;
				case 2:rand_matrix[i][j] = 3; break;
				}
			}
		}
		break;
	}
	}
}

//该函数用于初始化标记数组，即清零(可以共用）
void orig_mark(char(*mark_matrix)[10], int row, int col)
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			mark_matrix[i][j] = '0';
		}
	}
}

//该函数用于命令行版本的字母+数字坐标输入，并判断输入是否合法(可以共用）
void input_cord(int(*rand_matrix)[10], int row, int col, char &alpha, int &num)
{
	int curr_x, curr_y;//用于后面用户输入非法时光标位置的返回

	while (1)
	{
		cout << endl << "请以字母+数字形式[例: c2]输入矩阵坐标: ";
		getxy(curr_x, curr_y);//得到当前光标的位置

		while (1)
		{
			gotoxy(curr_x, curr_y);
			cin >> alpha;
			cin >> num;

			if (alpha >= 97) alpha -= 32;//若输入小写字母坐标则需要转换为大写字母

			if (cin.fail() || int(alpha - 65) < 0 || int(alpha - 65) > row - 1 || num<0 || num>col - 1)
			{
				cin.clear();
				cin.ignore(cin.rdbuf()->in_avail(), '\n');
				cout << "输入错误，请重新输入       ";
				continue;
			}
			else break;
		}

		cout << "输入为" << alpha << "行" << num << "列                    " << endl;

		//判断输入位置是否合法，即是否为0值
		if (!rand_matrix[alpha - 65][num])
		{
			cout << "输入的矩阵坐标位置为0（非法位置），请重新输入" << endl;
			continue;
		}

		//判断选定坐标周围是否存在相同值
		if (!judge_cord(rand_matrix, row, col, alpha - 65, num))
		{
			cout << "输入的矩阵坐标处无相同值，请重新输入" << endl;
			continue;
		}
		else break;
	}
}

//该函数用于判断用户选定坐标周围是否存在连续相同值(可以共用）
int judge_cord(int(*rand_matrix)[10], int row, int col, int curr_row, int curr_col)
{
	bool judge_cord = 0;

	if (rand_matrix[curr_row][curr_col] == 0) return 2;

	//以下四个if语句用于判断选定坐标周围是否存在相同值
	if (curr_row > 0 && rand_matrix[curr_row - 1][curr_col] == rand_matrix[curr_row][curr_col] && rand_matrix[curr_row][curr_col] != 0)
	{
		judge_cord = 1;
	}
	else if (curr_row < row - 1 && rand_matrix[curr_row + 1][curr_col] == rand_matrix[curr_row][curr_col] && rand_matrix[curr_row][curr_col] != 0)
	{
		judge_cord = 1;
	}
	else if (curr_col > 0 && rand_matrix[curr_row][curr_col - 1] == rand_matrix[curr_row][curr_col] && rand_matrix[curr_row][curr_col] != 0)
	{
		judge_cord = 1;
	}
	else if (curr_col < col - 1 && rand_matrix[curr_row][curr_col + 1] == rand_matrix[curr_row][curr_col] && rand_matrix[curr_row][curr_col] != 0)
	{
		judge_cord = 1;
	}

	return judge_cord;
}

//该函数用于打印内部数组（可以共用）
void print_matirx(int(*rand_matrix)[10], int row, int col)
{
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
			cout << "  ";
			if (rand_matrix[i][j] == 0)
			{
				setcolor(COLOR_HPINK, 0);
				cout << rand_matrix[i][j];
				setcolor();
			}
			else cout << rand_matrix[i][j];
		}
		cout << endl;
	}
}

//该函数用于打印标记矩阵（可以共用）
void print_mark(char(*mark_matrix)[10], int row, int col)
{
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
			cout << "  " << mark_matrix[i][j];
		}
		cout << endl;
	}
}

//该函数用于打印内部数组（不同色标识）(可以共用）
void print_color_matrix(int(*rand_matrix)[10], char(*mark_matrix)[10], int row, int col)
{
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
			cout << "  ";
			if (mark_matrix[i][j] == '*')
			{
				setcolor(COLOR_HPINK, 0);
				cout << rand_matrix[i][j];
				setcolor();
			}
			else cout << rand_matrix[i][j];
		}
		cout << endl;
	}
}

//该函数用于输入end结束小题返回主菜单
void back_to_menu()
{
	int x, y;//用于输入错误时光标返回原输入位置
	char btm[4];//back-to-menu

	cout << endl << "本小题结束，请输入End继续...";
	getxy(x, y);
	cin >> btm;

	while ((btm[0] != 'e' && btm[0] != 'E') || (btm[1] != 'n' && btm[1] != 'N') || (btm[2] != 'd' && btm[2] != 'D'))
	{
		cout << "输入错误，请重新输入";
		gotoxy(x, y);
		cin >> btm;
	}
}

//该函数用于打印单个unicode字符(可自定义颜色）
void print_unicode(const char *str, const int bg_color, const int fg_color, const int n)
{
	const char *p;

	setcolor(bg_color, fg_color);

	for (int i = 0; i < n; i++)
	{
		for (p = str; *p; p++)
			putchar(*p);

		Sleep(1);
	}
	setcolor();
}

/*该函数用于用户确认是否消除相同项（可以共用)
enquire1和enquire2分别是询问语句的两段，根据不同游戏的询问传入不同的参数*/
char confirm_combine(const char *enquire1, const char *enquire2, char input_alpha, int input_num)
{
	char confirm;
	cout << enquire1 << input_alpha << input_num << enquire2 << "<Y/N/Q>: ";

	while (confirm = _getch())
	{
		if (confirm == 'y' || confirm == 'Y') return 'y';

		else if (confirm == 'n' || confirm == 'N') return 'n';

		else if (confirm == 'q' || confirm == 'Q') return 'q';

		else continue;
	}

	return 1;
}

/*以下四个函数分别用于键盘操作方块的上下左右移动*/
void go_up(int(*rand_matrix)[10], int row, int col, int &curr_row, int &curr_col, int &last_row, int &last_col, int type,int game)
{
	if (game == POPSTAR)
	{
		//若当前色块位于最上列则需要从最下列绕回
		if (curr_row <= 0) curr_row = row - 1;
		else curr_row -= 1;

		if (rand_matrix[curr_row][curr_col] == 0)
		{
			curr_row -= 1;
			switch (type)
			{
			case UNDIVIDED:go_up(rand_matrix, row, col, curr_row, curr_col, last_row, last_col, UNDIVIDED); break;
			case DIVIDED:go_up(rand_matrix, row, col, curr_row, curr_col, last_row, last_col, DIVIDED); break;
			}
		}
		else
		{
			switch (type)
			{
			case UNDIVIDED:
				print_block(rand_matrix[curr_row][curr_col], 4 + curr_col * 6, 3 + curr_row * 3, POPSTAR, CHOSEN);
				print_block(rand_matrix[last_row][last_col], 4 + last_col * 6, 3 + last_row * 3, POPSTAR, NORMAL);
				break;
			case DIVIDED:
				print_block(rand_matrix[curr_row][curr_col], 4 + curr_col * 8, 3 + curr_row * 4, POPSTAR, CHOSEN);
				print_block(rand_matrix[last_row][last_col], 4 + last_col * 8, 3 + last_row * 4, POPSTAR, NORMAL);
				break;
			}

		}

		last_row = curr_row; last_col = curr_col;
	}
	else if (game == MAKE10)
	{
		//往上一个方格打印异色
		if (curr_row == 0) curr_row = row - 1;
		else curr_row -= 1;

		print_block(rand_matrix[curr_row][curr_col], 2 + curr_col * 8, 2 + curr_row * 4, MAKE10, CHOSEN);
		//原方格打印原色
		print_block(rand_matrix[last_row][last_col], 2 + last_col * 8, 2 + last_row * 4, MAKE10, NORMAL);

		last_row = curr_row; last_col = curr_col;
	}
}

void go_down(int(*rand_matrix)[10], int row, int col, int &curr_row, int &curr_col, int &last_row, int &last_col, int type, int game)
{
	if (game == POPSTAR)
	{
		//若当前色块位于最上列则需要从最下列绕回
		if (curr_row >= row - 1) curr_row = 0;
		else curr_row += 1;

		if (rand_matrix[curr_row][curr_col] == 0)
		{
			curr_row += 1;
			switch (type)
			{
			case UNDIVIDED:go_down(rand_matrix, row, col, curr_row, curr_col, last_row, last_col, UNDIVIDED); break;
			case DIVIDED:go_down(rand_matrix, row, col, curr_row, curr_col, last_row, last_col, DIVIDED); break;
			}
		}
		else
		{
			switch (type)
			{
			case UNDIVIDED:
				print_block(rand_matrix[curr_row][curr_col], 4 + curr_col * 6, 3 + curr_row * 3, POPSTAR, CHOSEN);
				print_block(rand_matrix[last_row][last_col], 4 + last_col * 6, 3 + last_row * 3, POPSTAR, NORMAL);
				break;
			case DIVIDED:
				print_block(rand_matrix[curr_row][curr_col], 4 + curr_col * 8, 3 + curr_row * 4, POPSTAR, CHOSEN);
				print_block(rand_matrix[last_row][last_col], 4 + last_col * 8, 3 + last_row * 4, POPSTAR, NORMAL);
				break;
			}
		}

		last_row = curr_row; last_col = curr_col;
	}
	else if (game == MAKE10)
	{
		//往下一个方格打印异色
		if (curr_row == row - 1) curr_row = 0;
		else curr_row += 1;

		print_block(rand_matrix[curr_row][curr_col], 2 + curr_col * 8, 2 + curr_row * 4, MAKE10, CHOSEN);
		//原方格打印原色
		print_block(rand_matrix[last_row][last_col], 2 + last_col * 8, 2 + last_row * 4, MAKE10, NORMAL);

		last_row = curr_row; last_col = curr_col;
	}
}

void go_right(int(*rand_matrix)[10], int row, int col, int &curr_row, int &curr_col, int &last_row, int &last_col, int type, int game)
{
	if (game == POPSTAR)
	{
		//若当前色块位于最上列则需要从最下列绕回
		if (curr_col >= col - 1) curr_col = 0;
		else curr_col += 1;

		if (rand_matrix[curr_row][curr_col] == 0)
		{
			switch (type)
			{
			case UNDIVIDED:go_right(rand_matrix, row, col, curr_row, curr_col, last_row, last_col, UNDIVIDED); break;
			case DIVIDED:go_right(rand_matrix, row, col, curr_row, curr_col, last_row, last_col, DIVIDED); break;
			}
		}
		else
		{
			switch (type)
			{
			case UNDIVIDED:
				print_block(rand_matrix[curr_row][curr_col], 4 + curr_col * 6, 3 + curr_row * 3, POPSTAR, CHOSEN);
				print_block(rand_matrix[last_row][last_col], 4 + last_col * 6, 3 + last_row * 3, POPSTAR, NORMAL);
				break;
			case DIVIDED:
				print_block(rand_matrix[curr_row][curr_col], 4 + curr_col * 8, 3 + curr_row * 4, POPSTAR, CHOSEN);
				print_block(rand_matrix[last_row][last_col], 4 + last_col * 8, 3 + last_row * 4, POPSTAR, NORMAL);
				break;
			}
		}

		last_row = curr_row; last_col = curr_col;
	}
	else if (game == MAKE10)
	{
		//往右一个方格打印异色
		if (curr_col == col - 1) curr_col = 0;
		else curr_col += 1;

		print_block(rand_matrix[curr_row][curr_col], 2 + curr_col * 8, 2 + curr_row * 4, MAKE10, CHOSEN);
		//原方格打印原色
		print_block(rand_matrix[last_row][last_col], 2 + last_col * 8, 2 + last_row * 4, MAKE10, NORMAL);

		last_row = curr_row; last_col = curr_col;
	}
}

void go_left(int(*rand_matrix)[10], int row, int col, int &curr_row, int &curr_col, int &last_row, int &last_col, int type, int game)
{
	if (game == POPSTAR)
	{
		//若当前色块位于最上列则需要从最下列绕回
		if (curr_col <= 0) curr_col = col - 1;
		else curr_col -= 1;

		if (rand_matrix[curr_row][curr_col] == 0)
		{
			switch (type)
			{
			case UNDIVIDED:go_left(rand_matrix, row, col, curr_row, curr_col, last_row, last_col, UNDIVIDED); break;
			case DIVIDED:go_left(rand_matrix, row, col, curr_row, curr_col, last_row, last_col, DIVIDED); break;
			}
		}
		else
		{
			switch (type)
			{
			case UNDIVIDED:
				print_block(rand_matrix[curr_row][curr_col], 4 + curr_col * 6, 3 + curr_row * 3, POPSTAR, CHOSEN);
				print_block(rand_matrix[last_row][last_col], 4 + last_col * 6, 3 + last_row * 3, POPSTAR, NORMAL);
				break;
			case DIVIDED:
				print_block(rand_matrix[curr_row][curr_col], 4 + curr_col * 8, 3 + curr_row * 4, POPSTAR, CHOSEN);
				print_block(rand_matrix[last_row][last_col], 4 + last_col * 8, 3 + last_row * 4, POPSTAR, NORMAL);
				break;
			}
		}

		last_row = curr_row; last_col = curr_col;
	}
	else if (game == MAKE10)
	{
		//往左一个方格打印异色
		if (curr_col == 0) curr_col = col - 1;
		else curr_col -= 1;

		print_block(rand_matrix[curr_row][curr_col], 2 + curr_col * 8, 2 + curr_row * 4, MAKE10, CHOSEN);
		//原方格打印原色
		print_block(rand_matrix[last_row][last_col], 2 + last_col * 8, 2 + last_row * 4, MAKE10, NORMAL);

		last_row = curr_row; last_col = curr_col;
	}
}

//该函数用于回车/单击左键确认合成
int cancel_confirm(int curr_row, int curr_col,int game)
{
	int X = 0, Y = 0;
	int ret, maction;
	int keycode1, keycode2;
	int loop = 1;

	enable_mouse();
	setcursor(CURSOR_INVISIBLE);	//关闭光标

	while (loop)
	{
		/* 读鼠标/键盘，返回值为下述操作中的某一种, 当前鼠标位置在<X,Y>处 */
		ret = read_keyboard_and_mouse(X, Y, maction, keycode1, keycode2);

		if (ret == CCT_MOUSE_EVENT)
		{
			if (game == POPSTAR)
			{
				if ((X >= (4 + curr_col * 6) && X < (10 + curr_col * 6)) && (Y >= (3 + curr_row * 3) && Y < (6 + curr_row * 3)))
				{
					if (maction == MOUSE_LEFT_BUTTON_CLICK)
					{
						return CLICK;
					}
				}
				else return CANCEL;
			}
			else if (game == MAKE10)
			{
				if ((X >= (2 + curr_col * 8) && X < (10 + curr_col * 8)) && (Y >= (2 + curr_row * 4) && Y < (6 + curr_row * 4)))
				{
					if (maction == MOUSE_LEFT_BUTTON_CLICK)
					{
						return CLICK;
					}
				}
				else return CANCEL;
			}
		}

		else if (ret == CCT_KEYBOARD_EVENT)
		{
			if (keycode1 == 13) return CLICK;
			else return CANCEL;
		}
	}

	return 1;
}

//该函数用于消除后色块的集体下落
void block_fall(int(*rand_matrix)[10], int row, int col, int game)
{
	int temp;

	for (int i = 0; i < col; i++)
	{
		bool stat = 1;
		while (stat)
		{
			stat = 0;
			for (int j = row - 2; j >= 0; j--)
			{
				if (rand_matrix[j + 1][i] == 0 && rand_matrix[j][i] != 0)
				{
					if (game == POPSTAR) block_move(rand_matrix, j, i, POPSTAR, DOWN);
					else if (game == MAKE10) block_move(rand_matrix, j, i, MAKE10, DOWN);

					temp = rand_matrix[j + 1][i];
					rand_matrix[j + 1][i] = rand_matrix[j][i];
					rand_matrix[j][i] = temp;

					stat = 1;
				}
			}
		}
	}

}

//该函数用于将给定坐标转化为指定的行列
bool cord_to_rc(int(*rand_matrix)[10], int row, int col, int cord_x, int cord_y, int &curr_row, int &curr_col, int &last_row, int &last_col, int game, int type)
{
	//将当前选择行列视为上一次选择行列
	last_row = curr_row;
	last_col = curr_col;

	//用于判断给定坐标位置是否合法
	bool legal_row = 0, legal_col = 0, legal_value = 0;

	switch (game)
	{
	case POPSTAR:
	{
		switch (type)
		{
		case UNDIVIDED:
			for (int i = 0; i < col; i++)
			{
				if (cord_x >= (4 + i * 6) && cord_x < (10 + i * 6))
				{
					curr_col = i;
					legal_col = 1;
				}
			}
			for (int i = 0; i < row; i++)
			{
				if (cord_y >= (3 + i * 3) && cord_y < (6 + i * 3))
				{
					curr_row = i;
					legal_row = 1;
				}
			}

			if (rand_matrix[curr_row][curr_col] != 0) legal_value = 1;

			return (legal_row && legal_col && legal_value);

		case DIVIDED:
			for (int i = 0; i < col; i++)
			{
				if (cord_x >= (4 + i * 8) && cord_x < (12 + i * 8))
				{
					curr_col = i;
					legal_col = 1;
				}
			}
			for (int i = 0; i < row; i++)
			{
				if (cord_y >= (3 + i * 4) && cord_y < (7 + i * 4))
				{
					curr_row = i;
					legal_row = 1;
				}
			}

			if (rand_matrix[curr_row][curr_col] != 0) legal_value = 1;

			return (legal_row && legal_col && legal_value);
		}
	}
	case MAKE10:
	{
		for (int i = 0; i < col; i++)
		{
			if (cord_x >= (2 + i * 8) && cord_x < (10 + i * 8))
			{
				curr_col = i;
				legal_col = 1;
			}
		}
		for (int i = 0; i < row; i++)
		{
			if (cord_y >= (2 + i * 4) && cord_y < (6 + i * 4))
			{
				curr_row = i;
				legal_row = 1;
			}
		}

		if (rand_matrix[curr_row][curr_col] != 0) legal_value = 1;

		return (legal_row && legal_col && legal_value);
	}
	}

	return 1;
}