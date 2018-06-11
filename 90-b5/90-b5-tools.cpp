/*1751367 ��2 ����*/
#include "90-b5.h"

/*****************����ַ�--->ȫ���ַ�ת����*****************/
//ʮ����ASCII��33-126��Ҫ����ת��
const char *Halfw_To_Fullw[127] =
{
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	NULL, "��", "��", "��", "��", "��", "��", "��",
	"��", "��", "��", "��", "��", "��", "��", "��",
	"��", "��", "��", "��", "��", "��", "��", "��",
	"��", "��", "��", "��", "��", "��", "��", "��",
	"��", "��", "��", "��", "��", "��", "��", "��",
	"��", "��", "��", "��", "��", "��", "��", "��",
	"��", "��", "��", "��", "��", "��", "��", "��",
	"��", "��", "��", "��", "��", "��", "��", "��",
	"��", "��", "��", "��", "��", "��", "��", "��",
	"��", "��", "��", "��", "��", "��", "��", "��",
	"��", "��", "��", "��", "��", "��", "��", "��",
	"��", "��", "��", "��", "��", "��", "��"
};

/****************LED_SETUP��ĳ�Ա��������***************/

/*���캯��*/
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

//�������ļ��ж�ȡ������
void LED_SETUP::read_cfg()
{
	fstream cfgfile;

	if (open_cfgfile(cfgfile, "led.cfg", OPEN_OPT_RDWR) == 0)
	{
		setcolor(0, COLOR_HBLUE);
		cout << "�޷��������ļ���������Ĭ������" << endl;
		setcolor();
		Sleep(3000);
		cls();
		return ;
	}

	//��ȡ����
	item_get_value(cfgfile, "setup", "����", &row, TYPE_INT);
	if (row < 1 || row>5)
		row = 4;

	//��ȡ����
	item_get_value(cfgfile, "setup", "����", &col, TYPE_INT);
	if (col < 8 || col>10)
		col = 8;

	//��ȡ����ɫ
	item_get_value(cfgfile, "setup", "����ɫ", &bg_color, TYPE_INT);
	if (bg_color < 0 || bg_color>15)
		bg_color = 0;

	//�Ƿ�������Ч
	char effect_on;
	for (int i = 0; i < 4; i++)
	{
		if (item_get_value(cfgfile, "setup", "��Ч1", &effect_on, TYPE_CHARACTER))
		{
			if (effect_on == 'Y')
				effect[i] = 1;
			else if (effect_on == 'N')
				effect[i] = 0;
		}
	}

	//����ʱ
	item_get_value(cfgfile, "setup", "����ʱ", &screen_delay, TYPE_INT);
	if (screen_delay < 0 || screen_delay>10)
		screen_delay = 2;

	//����ʱ
	item_get_value(cfgfile, "setup", "����ʱ", &item_delay, TYPE_INT);
	if (item_delay < 0 || item_delay>10)
		item_delay = 3;


	//�ֿ�
	item_get_value(cfgfile, "setup", "�ֿ�", char_lib, TYPE_STRING);
	if (strcmp(char_lib, "HZK16F") && strcmp(char_lib, "HZK16"))
	{
		strcpy(char_lib, "HZK16");
	}

}

//��ӡ������Ϣ��������
void LED_SETUP::print_cfg()
{
	cout << "����:" << row << endl;
	cout << "����:" << col << endl;
	cout << "����ɫ:" << bg_color << endl;
	for (int i = 0; i < 4; i++)
	{
		cout << "��Ч" << i + 1 << ':' << effect[i] << endl;
	}
	cout << "����ʱ:" << screen_delay << endl;
	cout << "����ʱ:" << item_delay << endl;
	cout << "�ֿ�:" << char_lib << endl;
}

/**********LED_CONTENT��ĳ�Ա��������**********/

/*���캯��*/
LED_CONTENT::LED_CONTENT()
{
	//ǰ��ɫ����Ĭ��Ϊ���
	for (int i = 0; i < 20; i++)
	{
		color[i] = -1;
	}

	for (int i = 0; i < 20; i++)
	{
		content[i] = NULL;
	}
}

//�������ļ��ж�ȡLED����
void LED_CONTENT::read_cfg()
{
	fstream cfgfile;

	if (open_cfgfile(cfgfile, "led.cfg", OPEN_OPT_RDWR) == 0)
	{
		setcolor(0, COLOR_HBLUE);
		cout << "�޷��������ļ���������Ĭ������" << endl;
		setcolor();
		Sleep(3000);
		cls();
		return;
	}
	//��ȡǰ��ɫ����
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

	//��ȡitem����
	char cfg_item_content[6] = "itemx";

	for (int i = 0; i < 20; i++)
	{	
		cfg_item_content[4] = '1' + i;
		char temp[257]; //��ʱ�洢 ��Ϊ�ı��п��ܴ��ڴ�ת���İ���ַ�

		if (item_get_value(cfgfile, "content", cfg_item_content, temp, TYPE_STRING))
		{
			content[i] = new char[257];

			//����ʱ�ı�ת�Ƶ�content����
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

//��ӡ������Ϣ,������
void LED_CONTENT::print_cfg()
{
	for (int i = 0; i < 20; i++)
	{
		if (content[i])
		{
			cout << "ǰ��ɫ:" << color[i] << endl;
			cout << "����:" << content[i] << endl;
		}
	}
}

//��������
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

//��ʾLED����
void LED_CONTENT::display_content(LED_SETUP led_setup)
{
	setcursor(CURSOR_INVISIBLE);
	setconsoleborder(led_setup.col * 32, led_setup.row * 16, led_setup.col * 32, led_setup.row * 16);
	setfontsize("��������", 3, 3);
	unsigned char qh; //����
	unsigned char wh; //λ��
	unsigned long offset;

	//ָ����ӡ���ֵ�����
	int cord_x = 0;
	int cord_y = 0;

	int display_col_count = 0; //��ǰһ���Ѿ���ʾ���ַ�����
	int display_row_count = 0; //��ǰ��ʾ������

	while (1)
	{
		for (int i = 0; i < 20; i++)
		{
			if (content[i])
			{
				/*������������������ǰ��ɫ*/
				int fg_color;
				if (color[i] == -1)
				{
					fg_color = random(0, 15);

					//�����뱳��ɫײɫ
					if (fg_color == led_setup.bg_color)
						fg_color++;
				}
				else fg_color = color[i];

				//���ѡ����ʾ��Ч
				//��ȷ���Ƿ���ڴ򿪵���Ч
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

				//���ַ���ӡ���ݵ��е��ַ�
				for (int j = 0; j<int(strlen(content[i])); j += 2)
				{
					//��鵱ǰ��Ļ�Ƿ��пռ�
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
					offset = (94 * (qh - 1) + (wh - 1)) * 32; /*�õ�ƫ��λ��*/

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

					//��ʾ�ַ�
					display_char(mat, cord_x, cord_y, led_setup,fg_color,effect);

					//ͳ���Ѵ�ӡ����������,�����д���
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

				//һ����ʾ��ɺ�Ĵ���
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

/********************ȫ�ֺ����Ķ���*********************/

//��ָ����Ļ�����ӡһ��ȫ���ַ�
void display_char(unsigned char mat[32], int cord_x, int cord_y,LED_SETUP led_setup,int color,int effect)
{
	int dot_matrix[16][16];
	int curr_value = 0; 

	//��������Ϣת�Ƶ�����ӡ�ĵ������
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

//����ָ����Χ���ڵ������
int random(int start, int end)
{
	srand((unsigned)time(NULL));
	return rand() % (end - start + 1) + start;
}

//�ַ�������Ч1
void display_effect_1(int dot_matrix[16][16], int cord_x, int cord_y,LED_SETUP led_setup,int color)
{
	/*��Ч1:������ʾ*/
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

//�ַ�������Ч2
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

//�ַ�������Ч3 
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

//�ַ�������Ч4
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