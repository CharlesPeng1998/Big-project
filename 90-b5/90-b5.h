/*1751367 ��2 ����*/
#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <ctime>
#include <cmath>
#include <cstdio>
#include <conio.h>
#include <Windows.h>
#include "..\common\cmd_console_tools.h"
#include "../common/common_cfgfile_tools.hpp"
using namespace std;

#define CHAR_WIDTH 32
#define CHAR_HEIGHT 16

#define EFFECT_1 0
#define EFFECT_2 1
#define EFFECT_3 2
#define EFFECT_4 3

class LED_CONTENT;
class LED_SETUP
{
private:
	int row; //1-5
	int col; //8-10
	int bg_color;

	//��Ч�Ƿ�����
	bool effect[4];

	//��Ļ��ʱ(s) 0-10
	int screen_delay;  
	//��Ŀ��ʱ(s) 0-10
	int item_delay;

	//�ֿ�
	char char_lib[7];

public:
	friend LED_CONTENT;
	friend void display_char(unsigned char mat[32], int cord_x, int cord_y, LED_SETUP led_setup,int color,int effect);
	friend void display_effect_1(int dot_matrix[16][16], int cord_x, int cord_y, LED_SETUP led_setup,int color);
	friend void display_effect_2(int dot_matrix[16][16], int cord_x, int cord_y, LED_SETUP led_setup, int color);
	friend void display_effect_3(int dot_matrix[16][16], int cord_x, int cord_y, LED_SETUP led_setup, int color);
	friend void display_effect_4(int dot_matrix[16][16], int cord_x, int cord_y, LED_SETUP led_setup, int color);
	LED_SETUP();
	void read_cfg();
	void print_cfg();
};

class LED_CONTENT
{
private:
	//����ʮ����ʾ��
	int color[20]; //ǰ��ɫ,0-15,-1�������
	char *content[20]; //��ʾ����

public:
	LED_CONTENT();
	void read_cfg();
	void print_cfg();
	~LED_CONTENT();
	void display_content(LED_SETUP led_setup);
};

/********ȫ�ֺ���ԭ��********/
int random(int start, int end);

/***************************/

