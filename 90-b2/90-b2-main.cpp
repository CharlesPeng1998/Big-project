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

int main()
{
	char choice;
	const char *items[4] = { "��ӭ��������˹���飬������û�������ȫ�°汾\n\n","1.�������������ǰ汾(���������룬��Ϸ���鼫��Ų�����","2.����αͼ�ν���߼��汾","3.�˳�" };

	while (1)
	{
		cls();
		//��ʾ���˵���Ϣ�������û������ѡ��
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