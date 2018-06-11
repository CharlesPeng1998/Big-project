#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <sstream>
#include <stdio.h>
#include <iomanip>
using namespace std;

int main()
{
#if 1
	unsigned char incode[3] = "聪"; // 要读出的汉字 
	unsigned char qh, wh;
	unsigned long offset;
	// 占两个字节, 取其区位号 
	qh = incode[0] - 0xa0; //获得区码
	wh = incode[1] - 0xa0; //获得位码
	offset = (94 * (qh - 1) + (wh - 1)) * 32; /*得到偏移位置*/

	FILE *HZK;
	unsigned char mat[32];
	if ((HZK = fopen("HZK16F", "rb")) == NULL)
	{
		printf("Can't open hzk16\n");
		exit(0);
	}

	fseek(HZK, offset, SEEK_SET);
	fread(mat, sizeof(unsigned char), 32, HZK);


	for (int i = 0; i < 32; i++)
	{
		cout <<setw(2)<<setfill('0')<< hex<<int(mat[i]) << ' ';
	}
#endif 
	return 0;
}