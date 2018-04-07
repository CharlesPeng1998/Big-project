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

int main()
{
	char choice;
	const char *items[4] = { "欢迎来到俄罗斯方块，这是你没有玩过的全新版本\n\n","1.进入命令行弱智版本(测试用勿入，游戏体验极差概不负责）","2.进入伪图形界面高级版本","3.退出" };

	while (1)
	{
		cls();
		//显示主菜单信息并接收用户输入的选择
		choice = menu(items, 4);

		if (choice == items[1][0])
		{
			cmd_tetris();
		}
		else if (choice == items[2][0])
		{
			GUI_tetris();
		}
		else if (choice == items[3][0]) break;
	}

	return 0;
}