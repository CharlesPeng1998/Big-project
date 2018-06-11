/*1751367 计2 彭健聪*/
#include "90-b5.h"

/*****************半角字符--->全角字符转换表*****************/
//十进制ASCII码33-126需要进行转换
const char *Halfw_To_Fullw[127] =
{
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	NULL, "！", "＂", "＃", "￥", "％", "＆", "＇",
	"（", "）", "＊", "＋", "，", "－", "．", "／",
	"０", "１", "２", "３", "４", "５", "６", "７",
	"８", "９", "：", "；", "＜", "＝", "＞", "？",
	"＠", "Ａ", "Ｂ", "Ｃ", "Ｄ", "Ｅ", "Ｆ", "Ｇ",
	"Ｈ", "Ｉ", "Ｊ", "Ｋ", "Ｌ", "Ｍ", "Ｎ", "Ｏ",
	"Ｐ", "Ｑ", "Ｒ", "Ｓ", "Ｔ", "Ｕ", "Ｖ", "Ｗ",
	"Ｘ", "Ｙ", "Ｚ", "［", "＼", "］", "＾", "＿",
	"｀", "ａ", "ｂ", "ｃ", "ｄ", "ｅ", "ｆ", "ｇ",
	"ｈ", "ｉ", "ｊ", "ｋ", "ｌ", "ｍ", "ｎ", "ｏ",
	"ｐ", "ｑ", "ｒ", "ｓ", "ｔ", "ｕ", "ｖ", "ｗ",
	"ｘ", "ｙ", "ｚ", "｛", "｜", "｝", "￣"
};

/****************LED_SETUP类的成员函数定义***************/

/*构造函数*/
LED_SETUP::LED_SETUP()
{
	row = 4;
	col = 8;
	bg_color = 0;
	
	for (int i = 0; i < 4; i++)
	{
		effect[i] = 1;
	}

	screen_delay = 2;
	item_delay = 3;
	strcpy(char_lib, "HZK16");
}

//从配置文件中读取设置项
void LED_SETUP::read_cfg()
{
	fstream cfgfile;

	if (open_cfgfile(cfgfile, "led.cfg", OPEN_OPT_RDWR) == 0)
	{
		setcolor(0, COLOR_HBLUE);
		cout << "无法打开配置文件，将采用默认配置" << endl;
		setcolor();
		Sleep(3000);
		cls();
		return ;
	}

	//获取行数
	item_get_value(cfgfile, "setup", "行数", &row, TYPE_INT);
	if (row < 1 || row>5)
		row = 4;

	//获取列数
	item_get_value(cfgfile, "setup", "列数", &col, TYPE_INT);
	if (col < 8 || col>10)
		col = 8;

	//获取背景色
	item_get_value(cfgfile, "setup", "背景色", &bg_color, TYPE_INT);
	if (bg_color < 0 || bg_color>15)
		bg_color = 0;

	//是否启动特效
	char effect_on;
	for (int i = 0; i < 4; i++)
	{
		if (item_get_value(cfgfile, "setup", "特效1", &effect_on, TYPE_CHARACTER))
		{
			if (effect_on == 'Y')
				effect[i] = 1;
			else if (effect_on == 'N')
				effect[i] = 0;
		}
	}

	//屏延时
	item_get_value(cfgfile, "setup", "屏延时", &screen_delay, TYPE_INT);
	if (screen_delay < 0 || screen_delay>10)
		screen_delay = 2;

	//条延时
	item_get_value(cfgfile, "setup", "条延时", &item_delay, TYPE_INT);
	if (item_delay < 0 || item_delay>10)
		item_delay = 3;


	//字库
	item_get_value(cfgfile, "setup", "字库", char_lib, TYPE_STRING);
	if (strcmp(char_lib, "HZK16F") && strcmp(char_lib, "HZK16"))
	{
		strcpy(char_lib, "HZK16");
	}

}

//打印配置信息：调试用
void LED_SETUP::print_cfg()
{
	cout << "行数:" << row << endl;
	cout << "列数:" << col << endl;
	cout << "背景色:" << bg_color << endl;
	for (int i = 0; i < 4; i++)
	{
		cout << "特效" << i + 1 << ':' << effect[i] << endl;
	}
	cout << "屏延时:" << screen_delay << endl;
	cout << "条延时:" << item_delay << endl;
	cout << "字库:" << char_lib << endl;
}

/**********LED_CONTENT类的成员行数定义**********/

/*构造函数*/
LED_CONTENT::LED_CONTENT()
{
	//前景色设置默认为随机
	for (int i = 0; i < 20; i++)
	{
		color[i] = -1;
	}

	for (int i = 0; i < 20; i++)
	{
		content[i] = NULL;
	}
}

//从配置文件中读取LED内容
void LED_CONTENT::read_cfg()
{
	fstream cfgfile;

	if (open_cfgfile(cfgfile, "led.cfg", OPEN_OPT_RDWR) == 0)
	{
		setcolor(0, COLOR_HBLUE);
		cout << "无法打开配置文件，将采用默认配置" << endl;
		setcolor();
		Sleep(3000);
		cls();
		return;
	}
	//读取前景色设置
	char cfg_item_color[12] = "itemx_color";

	for (int i = 0; i < 20; i++)
	{
		cfg_item_color[4] = '1' + i;

		if (item_get_value(cfgfile, "content", cfg_item_color, &color[i], TYPE_INT))
		{
			if (color[i] < -1 || color[i]>15)
				color[i] = -1;
		}
	}

	//读取item内容
	char cfg_item_content[6] = "itemx";

	for (int i = 0; i < 20; i++)
	{	
		cfg_item_content[4] = '1' + i;
		char temp[257]; //临时存储 因为文本中可能存在待转换的半角字符

		if (item_get_value(cfgfile, "content", cfg_item_content, temp, TYPE_STRING))
		{
			content[i] = new char[257];

			//将临时文本转移到content当中
			char *p = content[i];

			for (int j = 0; j <= strlen(temp); j++)
			{
				if (unsigned(temp[j]) < 33 || unsigned(temp[j]) > 126)
				{
					*(p++) = temp[j];
				}
				else
				{
					*(p++) = Halfw_To_Fullw[unsigned(temp[j])][0];
					*(p++) = Halfw_To_Fullw[unsigned(temp[j])][1];
				}
			}

			content[i][256] = '\0';
		}
	}
}

//打印配置信息,调试用
void LED_CONTENT::print_cfg()
{
	for (int i = 0; i < 20; i++)
	{
		if (content[i])
		{
			cout << "前景色:" << color[i] << endl;
			cout << "内容:" << content[i] << endl;
		}
	}
}

//析构函数
LED_CONTENT::~LED_CONTENT()
{
	for (int i = 0; i < 20; i++)
	{
		if (content[i])
		{
			delete[] content[i];
		}
	}
}

//显示LED内容
void LED_CONTENT::display_content(LED_SETUP led_setup)
{
	setcursor(CURSOR_INVISIBLE);
	setconsoleborder(led_setup.col * 32, led_setup.row * 16, led_setup.col * 32, led_setup.row * 16);
	setfontsize("点阵字体", 3, 3);
	unsigned char qh; //区码
	unsigned char wh; //位码
	unsigned long offset;

	//指定打印文字的坐标
	int cord_x = 0;
	int cord_y = 0;

	int display_col_count = 0; //当前一行已经显示的字符数量
	int display_row_count = 0; //当前显示的行数

	while (1)
	{
		for (int i = 0; i < 20; i++)
		{
			if (content[i])
			{
				/*根据配置项设置文字前景色*/
				int fg_color;
				if (color[i] == -1)
				{
					fg_color = random(0, 15);

					//避免与背景色撞色
					if (fg_color == led_setup.bg_color)
						fg_color++;
				}
				else fg_color = color[i];

				//随机选择显示特效
				//先确定是否存在打开的特效
				int effect;
				bool exist = 0;
				for (int i = 0; i < 4; i++)
				{
					if (led_setup.effect[i])
					{
						exist = 1;
						break;
					}
				}
				if (exist)
				{
					do
					{
						effect = random(0, 3);
					} while (led_setup.effect[effect] == 0);
				}
				else effect = 0;

				//逐字符打印内容当中的字符
				for (int j = 0; j<int(strlen(content[i])); j += 2)
				{
					//检查当前屏幕是否还有空间
					if (display_row_count == led_setup.row)
					{
						Sleep(led_setup.screen_delay * 1000);
						cls();
						display_col_count = 0;
						display_row_count = 0;
						cord_x = 0;
						cord_y = 0;
					}

					qh = content[i][j] - 0xa0;
					wh = content[i][j + 1] - 0xa0;
					offset = (94 * (qh - 1) + (wh - 1)) * 32; /*得到偏移位置*/

					FILE *HZK;
					unsigned char mat[32];
					if ((HZK = fopen(led_setup.char_lib, "rb")) == NULL)
					{
						printf("Can't open character library!\n");
						Sleep(5000);
						exit(0);
					}

					fseek(HZK, offset, SEEK_SET);
					fread(mat, sizeof(unsigned char), 32, HZK);

					//显示字符
					display_char(mat, cord_x, cord_y, led_setup,fg_color,effect);

					//统计已打印列数和行数,做换行处理
					display_col_count++;
					if (display_col_count == led_setup.col)
					{
						cord_x = 0;
						cord_y += 16;
						display_col_count = 0;
						display_row_count++;
					}
					else
					{
						cord_x += 32;
					}
				}

				//一项显示完成后的处理
				Sleep(led_setup.item_delay * 1000);
				cls();
				display_col_count = 0;
				display_row_count = 0;
				cord_x = 0;
				cord_y = 0;
			}
		}
	}
}

/********************全局函数的定义*********************/

//在指定屏幕坐标打印一个全角字符
void display_char(unsigned char mat[32], int cord_x, int cord_y,LED_SETUP led_setup,int color,int effect)
{
	int dot_matrix[16][16];
	int curr_value = 0; 

	//将点阵信息转移到待打印的点阵矩阵
	for (int i = 0; i < 16; i++)
	{
		unsigned char temp = 0x80;
		for (int j = 0; j < 8; j++)
		{
			if (temp & mat[curr_value])
			{
				dot_matrix[i][j] = 1;
			}
			else dot_matrix[i][j] = 0;
			temp >>= 1;
		}

		curr_value++;

		temp = 0x80;
		for (int j = 8; j < 16; j++)
		{
			if (temp & mat[curr_value])
			{
				dot_matrix[i][j] = 1;
			}
			else dot_matrix[i][j] = 0;
			temp >>= 1;
		}

		curr_value++;
	}

	switch (effect)
	{
	case EFFECT_1:display_effect_1(dot_matrix, cord_x, cord_y, led_setup, color); break;
	case EFFECT_2:display_effect_2(dot_matrix, cord_x, cord_y, led_setup, color); break;
	case EFFECT_3:display_effect_3(dot_matrix, cord_x, cord_y, led_setup, color); break;
	case EFFECT_4:display_effect_4(dot_matrix, cord_x, cord_y, led_setup, color); break;
	}
}

//生成指定范围以内的随机数
int random(int start, int end)
{
	srand((unsigned)time(NULL));
	return rand() % (end - start + 1) + start;
}

//字符生成特效1
void display_effect_1(int dot_matrix[16][16], int cord_x, int cord_y,LED_SETUP led_setup,int color)
{
	/*特效1:基本显示*/
	for (int i = 0; i < 16; i++)
	{
		gotoxy(cord_x, cord_y++);

		for (int j = 0; j < 16; j++)
		{
			if (dot_matrix[i][j])
			{
				setcolor(led_setup.bg_color, color);
				cout << '*';
				setcolor(led_setup.bg_color, led_setup.bg_color);
				cout << ' ';
			}
			else
			{
				setcolor(led_setup.bg_color, led_setup.bg_color);
				cout << "  ";
			}
		}
	}
}

//字符生成特效2
void display_effect_2(int dot_matrix[16][16], int cord_x, int cord_y, LED_SETUP led_setup, int color)
{
	for (int i = 0; i < 16; i++)
	{
		gotoxy(cord_x, cord_y++);

		for (int j = 0; j < 16; j++)
		{
			if (dot_matrix[i][j])
			{
				setcolor(led_setup.bg_color, color);
				cout << '*';
				setcolor(led_setup.bg_color, led_setup.bg_color);
				cout << ' ';
			}
			else
			{
				setcolor(led_setup.bg_color, led_setup.bg_color);
				cout << "  ";
			}
		}

		Sleep(25);
	}
}

//字符生成特效3 
void display_effect_3(int dot_matrix[16][16], int cord_x, int cord_y, LED_SETUP led_setup, int color)
{
	for (int i = 0; i < 16; i++)
	{
		gotoxy(cord_x, cord_y++);

		for (int j = 0; j < 16; j++)
		{
			if (dot_matrix[i][j])
			{
				setcolor(led_setup.bg_color, color);
				cout << '*';
				setcolor(led_setup.bg_color, led_setup.bg_color);
				cout << ' ';
			}
			else
			{
				setcolor(led_setup.bg_color, led_setup.bg_color);
				cout << "  ";
			}

			Sleep(10);
		}
	}
}

//字符生成特效4
void display_effect_4(int dot_matrix[16][16], int cord_x, int cord_y, LED_SETUP led_setup, int color)
{
	int X = cord_x-1;
	int Y = cord_y;

	gotoxy(cord_x, cord_y);

	for (int i = 0; i < 16; i++)
	{
		Y = cord_y;
		X += 2;
		gotoxy(X, Y);

		for (int j = 0; j < 16; j++)
		{
			if (dot_matrix[j][i])
			{
				setcolor(led_setup.bg_color, color);
				cout << '*';
				setcolor(led_setup.bg_color, led_setup.bg_color);
				cout << ' ';
			}
			else
			{
				setcolor(led_setup.bg_color, led_setup.bg_color);
				cout << "  ";
			}

			gotoxy(X, ++Y);
		}

		Sleep(25);
	}
}
/******************************************************/