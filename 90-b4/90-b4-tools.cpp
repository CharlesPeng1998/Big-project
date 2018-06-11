/*1751367 计2 彭健聪*/
#include "90-b4.h"

/*初始文本转化为UTF8字符串*/
char *G2U(const char* gb2312)
{
	int len = MultiByteToWideChar(CP_ACP, 0, gb2312, -1, NULL, 0);
	wchar_t* wstr = new wchar_t[len + 1];
	memset(wstr, 0, len + 1);
	MultiByteToWideChar(CP_ACP, 0, gb2312, -1, wstr, len);
	len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
	char* str = new char[len + 1];
	memset(str, 0, len + 1);
	WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str, len, NULL, NULL);
	if (wstr) delete[] wstr;
	return str;
}

/*析构函数，释放动态申请空间*/
QR_code::~QR_code()
{
	delete[] encoded_data;
	delete[] utf8_text;
	delete[] encoded_data_decimal;
	delete[] code_word_final;
}

/*用户输入自定义二维码纠错级别*/
void QR_code::set_err_corre_level(int n)
{
	err_corre_level = n;
}

/*用户输入初始文本*/
void QR_code::input_text(char *text)
{
	strcpy(orig_text,text);
}

/*根据文本长度选择版本*/
void QR_code::set_version()
{
	utf8_text = G2U(orig_text);
	utf8_length = int(strlen(utf8_text));

	for (int i = 0; i < 9; i++)
	{
		if (QR_VersonInfo[i].data_codewords_num[err_corre_level]-2 >= utf8_length)
		{
			version = QR_VersonInfo[i].version;
			data_codewords_num = QR_VersonInfo[i].data_codewords_num[err_corre_level];
			break;
		}
	}
}

/*将文本进行编码*/
void QR_code::encode()
{
	//根据该版本和纠错码等级下的最大容量申请动态内存
	encoded_data = new int[data_codewords_num*8];
	memset(encoded_data, 0, data_codewords_num*8*sizeof(int));

	//模式指示符（二进制:0100）
	encoded_data[0] = 0;
	encoded_data[1] = 1;
	encoded_data[2] = 0;
	encoded_data[3] = 0;

	int curr_pos = 4;
	int temp = 0x0001;
	//填写字符计数指示符
	for (int i = 0; i < COUNT_PART_LEN; i++)
	{
		if ((temp&utf8_length) != 0)
		{
			encoded_data[curr_pos + COUNT_PART_LEN - i - 1] = 1;
		}
		temp = temp << 1;
	}

	int i = 0;
	curr_pos = curr_pos + COUNT_PART_LEN;
	while (utf8_text[i] != '\0')
	{
		unsigned char ctemp = 0x80;
		for (int j = 0; j < 8; j++)
		{
			if ((ctemp&utf8_text[i]) != 0)
			{
				encoded_data[curr_pos] = 1;
			}
			ctemp = ctemp >> 1;
			curr_pos++;
		}
		i++;
	}

	encoded_length = curr_pos;
}

/*打印相关数据成员，程序调试使用*/
void QR_code::display()
{
#if 0
	cout <<"原始文本:"<< orig_text << endl;
	cout << "原始文本长度:" << strlen(orig_text) << endl;
	cout << "版本号:" << version << endl;
	cout << "纠错码级别:" << code_word_final_num << endl;
	cout << "最大容量:" << data_codewords_num << endl;
	cout << "UTF8格式字符串:" << utf8_text << endl;
	cout << "二进制编码数据长度:" << encoded_length << endl;
	cout << "编码数据:";
	for (int i = 0; i < encoded_length; i++)
	{
		cout << encoded_data[i];
	}
	cout << endl;

	for (int i = 0; i < data_decimal_length; i++)
	{
		cout << int(encoded_data_decimal[i]) << ',';
	}
	cout << endl;
	
	for (int i = 0; i < QR_VersonInfo[version].total_word_num; i++)
	{
		cout << int(code_word_final[i]) << ',';
	}
	cout << endl;

	
#endif 
#if 1
	for (int i = 0; i < m_nSymbleSize; i++)
	{
		for (int j = 0; j < m_nSymbleSize; j++)
		{
			cout << setw(2) << int(code_matrix[i][j]) << ' ';
		}
		cout << endl;
	}
	exit(-1);
#endif

#if 0
	for (int i = 0; i < QR_code_size; i++)
	{
		for (int j = 0; j < QR_code_size; j++)
		{
			cout <<setw(2)<< code_matrix[i][j] << ' ';
		}
		cout << endl;
	}
#endif 

}

/*补码至最大容量*/
void QR_code::add_code()
{
	//补0至长度为8的倍数
	while (encoded_length % 8 != 0)
	{
		encoded_data[encoded_length] = 0;
		encoded_length++;
	}

	//填充至最大容量
	int count = 0;
	while (encoded_length < data_codewords_num*8)
	{
		if (count % 2 == 0)
		{
			encoded_data[encoded_length++] = 1;
			encoded_data[encoded_length++] = 1;
			encoded_data[encoded_length++] = 1;
			encoded_data[encoded_length++] = 0;
			encoded_data[encoded_length++] = 1;
			encoded_data[encoded_length++] = 1;
			encoded_data[encoded_length++] = 0;
			encoded_data[encoded_length++] = 0;
		}
		else
		{
			encoded_data[encoded_length++] = 0;
			encoded_data[encoded_length++] = 0;
			encoded_data[encoded_length++] = 0;
			encoded_data[encoded_length++] = 1;
			encoded_data[encoded_length++] = 0;
			encoded_data[encoded_length++] = 0;
			encoded_data[encoded_length++] = 0;
			encoded_data[encoded_length++] = 1;
		}

		count++;
	}
}

/*二进制编码数据转化为十进制*/
void QR_code::binary_to_decimal()
{
	encoded_data_decimal = new unsigned char[encoded_length+1];
	int num_a = encoded_length;
	data_decimal_length = encoded_length / 8;
	int j_ = 0;
	for (int i = 0; i < num_a; i = i + 8)
	{
		int num = 0;
		if (encoded_data[i + 7] == 1)
			num += 1;
		if (encoded_data[i + 6] == 1)
			num += 2;
		if (encoded_data[i + 5] == 1)
			num += 4;
		if (encoded_data[i + 4] == 1)
			num += 8;
		if (encoded_data[i + 3] == 1)
			num += 16;
		if (encoded_data[i + 2] == 1)
			num += 32;
		if (encoded_data[i + 1] == 1)
			num += 64;
		if (encoded_data[i + 0] == 1)
			num += 128;
		encoded_data_decimal[j_] = num;
		j_++;
	}
}

//这是复制的
void QR_code::add_code_data()
{
	code_word_final = new(nothrow) unsigned char[(17 + version * 4)*(17 + version * 4)];
	code_word_final_num = QR_VersonInfo[version].total_word_num;
	memset(code_word_final, 0, code_word_final_num);

	int nDataCwIndex = 0; // 数据码字处理位置

						  // 数据块分区数
	int ncBlock1 = QR_VersonInfo[version].block_info1[err_corre_level].ncRSBlock;
	int ncBlock2 = QR_VersonInfo[version].block_info2[err_corre_level].ncRSBlock;
	int ncBlockSum = ncBlock1 + ncBlock2;

	int nBlockNo = 0; // 进程中的块数

					  // 按块的数据码数
	int ncDataCw1 = QR_VersonInfo[version].block_info1[err_corre_level].ncDataCodeWord;
	int ncDataCw2 = QR_VersonInfo[version].block_info2[err_corre_level].ncDataCodeWord;

	// 数据码字交错放置
	int i, j;
	for (i = 0; i < ncBlock1; ++i)
	{
		for (j = 0; j < ncDataCw1; ++j)
		{
			code_word_final[(ncBlockSum * j) + nBlockNo] = encoded_data_decimal[nDataCwIndex++];
		}

		++nBlockNo;
	}

	for (i = 0; i < ncBlock2; ++i)
	{
		for (j = 0; j < ncDataCw2; ++j)
		{
			if (j < ncDataCw1)
			{
				code_word_final[(ncBlockSum * j) + nBlockNo] = encoded_data_decimal[nDataCwIndex++];
			}
			else
			{
				// 二次事件块分数排列
				code_word_final[(ncBlockSum * ncDataCw1) + i] = encoded_data_decimal[nDataCwIndex++];
			}
		}

		++nBlockNo;
	}

}

//这也是复制的
void QR_code::encode_rscode(LPBYTE datacode, int ncDataCodeWord, int ncRSCodeWord)
{
	//*************生成多项式除消息多项式*******************
	for (int i = 0; i < ncDataCodeWord; i++)
	{
		if (datacode[0] != 0)
		{
			BYTE temp_first = byIntToExp[datacode[0]]; // 从第一项系数计算乘数

			for (int j = 0; j < ncRSCodeWord; j++)
			{
				// 将第一项的消息指数和生成多项式指数相加，假如大于255要对255取余
				BYTE nExpElement = (BYTE)(((int)(byRSExp[ncRSCodeWord][j] + temp_first)) % 255);

				//********同时进行xor运算**************************************
				datacode[j] = (BYTE)(datacode[j + 1] ^ byExpToInt[nExpElement]);//XOR运算
			}


			// 移位剩余数字
			for (int j = ncRSCodeWord; j < ncDataCodeWord + ncRSCodeWord - 1; j++)
				datacode[j] = datacode[j + 1];
		}
		else
		{
			// 移位剩余数字
			// 丢弃系数为0的项：
			for (int j = 0; j < ncDataCodeWord + ncRSCodeWord - 1; j++)
				datacode[j] = datacode[j + 1];
		}
	}
}

//这还是复制的
void QR_code::add_rs_code_data()
{
	int nBlockNo = 0;
	int ncBlock[] = { QR_VersonInfo[version].block_info1[err_corre_level].ncRSBlock, QR_VersonInfo[version].block_info2[err_corre_level].ncRSBlock };
	int ncDataCw[] = { QR_VersonInfo[version].block_info1[err_corre_level].ncDataCodeWord, QR_VersonInfo[version].block_info2[err_corre_level].ncDataCodeWord };
	// 每个块的 rs 代码单词数 (与当前状态相同)
	int ncRSCw[] = { QR_VersonInfo[version].block_info1[err_corre_level].ncAllCodeWord - ncDataCw[0], QR_VersonInfo[version].block_info2[err_corre_level].ncAllCodeWord - ncDataCw[1] };
	int ncBlockSum = ncBlock[0] + ncBlock[1];
	//****************如过数据大的情况，则分两个block进行运算**************************
	int num = 0;
	for (int k = 0; k < 2; k++)
	{
		for (int i = 0; i < ncBlock[k]; i++)
		{
			memset(m_byRSWork, 0, sizeof(m_byRSWork));//初始化rs纠错码数组
			memmove(m_byRSWork, encoded_data_decimal + num, ncDataCw[k]);//从数据码中提取第nDataCwIndex的数据
			encode_rscode(m_byRSWork, ncDataCw[k], ncRSCw[k]);//运算纠错码
															  // rs 码字放置
			for (int j = 0; j < ncRSCw[k]; j++)
				code_word_final[data_decimal_length + (ncBlockSum * j) + nBlockNo] = m_byRSWork[j];
			num += ncDataCw[k];
			nBlockNo++;
		}
	}
	m_nSymbleSize = version * 4 + 17;

	/*更新编码数据（添加纠错码）*/
	delete[] encoded_data;
	encoded_data = new int[code_word_final_num * 8];
	
	int curr_data = 0;
	for (int i = 0; i < code_word_final_num; i++)
	{
		unsigned char temp = 0x80;
		for (int j = 0; j < 8; j++)
		{
			if (temp & code_word_final[i])
			{
				encoded_data[curr_data++] = 1;
			}
			else encoded_data[curr_data++] = 0;

			temp = temp >> 1;
		}
	}

	encoded_length = code_word_final_num * 8;
}

/*设定二维码掩模模式*/
void QR_code::set_mask_pattern(int n)
{
	mask_pattern = n;
}

/*填充二维码*/
void QR_code::fill_matrix()
{
	QR_code_size = 17 + 4 * version;

	//将矩阵初始化为0
	memset(code_matrix, 0, 53 * 53 * sizeof(int));

	pos_detect_pattern();
	alignment();
	timing_pattern();
	format_info();
	version_info();
	code_words();
	masking();

	//最后把数据统一转化为0和1
	for (int i = 0; i < QR_code_size; i++)
	{
		for (int j = 0; j < QR_code_size; j++)
		{
			if (code_matrix[i][j] > 0)
				code_matrix[i][j] = 1;
			else code_matrix[i][j] = 0;
		}
	}

	//为掩模模式评分
	penalty = CountPenalty();
}

/*绘制位置探测图形*/
void QR_code::pos_detect_pattern()
{
	int pos_detect_pat[7][7] =
	{
		2,2,2,2,2,2,2,
		2,-1,-1,-1,-1,-1,2,
		2,-1,2,2,2,-1,2,
		2,-1,2,2,2,-1,2,
		2,-1,2,2,2,-1,2,
		2,-1,-1,-1,-1,-1,2,
		2,2,2,2,2,2,2
	};

	//画左上角
	Pos curr_cord = {0,0};
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			code_matrix[curr_cord.y][curr_cord.x++] = pos_detect_pat[i][j];
		}
		curr_cord.y++;
		curr_cord.x = 0;
	}

	//画右上角
	curr_cord = { QR_code_size - 7,0 };
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			code_matrix[curr_cord.y][curr_cord.x++] = pos_detect_pat[i][j];
		}
		curr_cord.y++;
		curr_cord.x = QR_code_size - 7;
	}

	//画左下角
	curr_cord = { 0 , QR_code_size - 7 };
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			code_matrix[curr_cord.y][curr_cord.x++] = pos_detect_pat[i][j];
		}
		curr_cord.y++;
		curr_cord.x = 0;
	}

	//左上角边框
	curr_cord = { 7 , 0 };
	for (int i = 0; i < 8; i++)
	{
		code_matrix[curr_cord.y++][curr_cord.x] = -1;
	}
	curr_cord = { 0 , 7 };
	for (int i = 0; i < 8; i++)
	{
		code_matrix[curr_cord.y][curr_cord.x++] = -1;
	}

	//右上角边框
	curr_cord = { QR_code_size - 8,0 };
	for (int i = 0; i < 8; i++)
	{
		code_matrix[curr_cord.y++][curr_cord.x] = -1;
	}
	curr_cord = { QR_code_size - 8,7 };
	for (int i = 0; i < 8; i++)
	{
		code_matrix[curr_cord.y][curr_cord.x++] = -1;
	}

	//左下角边框
	curr_cord = { 0,QR_code_size - 8 };
	for (int i = 0; i < 8; i++)
	{
		code_matrix[curr_cord.y][curr_cord.x++] = -1;
	}
	curr_cord = { 7 , QR_code_size - 8 };
	for (int i = 0; i < 8; i++)
	{
		code_matrix[curr_cord.y++][curr_cord.x] = -1;
	}
}

/*绘制对齐图形*/
void QR_code::alignment()
{
	int align_pattern[5][5] =
	{
		2,2,2,2,2,
		2,-1,-1,-1,2,
		2,-1,2,-1,2,
		2,-1,-1,-1,2,
		2,2,2,2,2
	};

	if (version == 1)
	{
		return;
	}
	else if (version < 7)
	{
		Pos central_cord = { QR_VersonInfo[version].align_point[0], QR_VersonInfo[version].align_point[0] };
		int dis_x;
		int dis_y;

		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				dis_y = i - 2;
				dis_x = j - 2;

				code_matrix[central_cord.y + dis_y][central_cord.x + dis_x] = align_pattern[i][j];
			}
		}
	}
	else if (version >= 7)
	{
		Pos central_cord[6]=
		{
			{ QR_VersonInfo[version].align_point[0], QR_VersonInfo[version].align_point[0] },
		{ QR_VersonInfo[version].align_point[1], QR_VersonInfo[version].align_point[1] },
		{ QR_VersonInfo[version].align_point[0], QR_VersonInfo[version].align_point[1] },
		{QR_VersonInfo[version].align_point[1], QR_VersonInfo[version].align_point[0]},
		{ 6, QR_VersonInfo[version].align_point[0] },
		{ QR_VersonInfo[version].align_point[0], 6 }
		};

		for (int k = 0; k < 6; k++)
		{
			int dis_x;
			int dis_y;

			for (int i = 0; i < 5; i++)
			{
				for (int j = 0; j < 5; j++)
				{
					dis_y = i - 2;
					dis_x = j - 2;

					code_matrix[central_cord[k].y + dis_y][central_cord[k].x + dis_x] = align_pattern[i][j];
				}
			}
		}
	}
}

/*绘制定位图形*/
void QR_code::timing_pattern()
{
	Pos curr_cord = { 6,8 };
	for (int i = 0; i < QR_code_size - 16; i++)
	{
		switch (i % 2)
		{
		case 0:code_matrix[curr_cord.y][curr_cord.x] = 2; break;
		case 1:code_matrix[curr_cord.y][curr_cord.x] = -1; break;
		}

		curr_cord.y++;
	}

	curr_cord = { 8,6 };
	for (int i = 0; i < QR_code_size - 16; i++)
	{
		switch (i % 2)
		{
		case 0:code_matrix[curr_cord.y][curr_cord.x] = 2; break;
		case 1:code_matrix[curr_cord.y][curr_cord.x] = -1; break;
		}

		curr_cord.x++;
	}
}

/*格式信息，顺便把小黑点画了*/
void QR_code::format_info()
{
	//先画小黑点
	code_matrix[QR_code_size - 8][8] = 2;

	int nFormatInfo;
	int i;

	switch (err_corre_level)
	{
	case LEVEL_M:
		nFormatInfo = 0x00; 
		break;

	case LEVEL_L:
		nFormatInfo = 0x08; 
		break;

	case LEVEL_Q:
		nFormatInfo = 0x18;
		break;

	default:
		nFormatInfo = 0x10; 
		break;
	}

	nFormatInfo += mask_pattern;

	int nFormatData = nFormatInfo << 10;

	for (i = 0; i < 5; ++i)
	{
		if (nFormatData & (1 << (14 - i)))
		{
			nFormatData ^= (0x0537 << (4 - i)); 
		}
	}

	nFormatData += nFormatInfo << 10;

	nFormatData ^= 0x5412; 

	format_data = nFormatData;

	int version_info[15];
	int temp = 0x4000;

	for (int i = 0; i < 15; i++)
	{
		if (temp&nFormatData)
		{
			version_info[i] = 1;
		}
		else version_info[i] = 0;

		temp >>= 1;
	}

	Pos curr_cord = { 8,0 };
	int curr_data = 0;
	for (int i = 0; i < 9; i++)
	{
		if (code_matrix[curr_cord.y][curr_cord.x] == 0)
		{
			if (version_info[curr_data++])
			{
				code_matrix[curr_cord.y][curr_cord.x] = 2;
			}
			else code_matrix[curr_cord.y][curr_cord.x] = -1;
		}
		curr_cord.y++;
	}

	curr_cord = { 7,8 };
	for (int i = 0; i < 8; i++)
	{
		if (code_matrix[curr_cord.y][curr_cord.x] == 0)
		{
			if (version_info[curr_data++])
			{
				code_matrix[curr_cord.y][curr_cord.x] = 2;
			}
			else code_matrix[curr_cord.y][curr_cord.x] = -1;
		}
		curr_cord.x--;
	}

	curr_data = 0;
	curr_cord = { QR_code_size-1,8 };
	for (int i = 0; i < 8; i++)
	{
		if (code_matrix[curr_cord.y][curr_cord.x] == 0)
		{
			if (version_info[curr_data++])
			{
				code_matrix[curr_cord.y][curr_cord.x] = 2;
			}
			else code_matrix[curr_cord.y][curr_cord.x] = -1;
		}
		curr_cord.x--;
	}

	curr_cord = { 8, QR_code_size - 7 };
	for (int i = 0; i < 7; i++)
	{
		if (code_matrix[curr_cord.y][curr_cord.x] == 0)
		{
			if (version_info[curr_data++])
			{
				code_matrix[curr_cord.y][curr_cord.x] = 2;
			}
			else code_matrix[curr_cord.y][curr_cord.x] = -1;
		}
		curr_cord.y++;
	}
}

/*版本信息*/
void QR_code::version_info()
{
	if (version < 7)
	{
		return;
	}

	int version_info_7_1[6][3] =
	{
		-1,-1,-1,
		2,2,2,
		2,2,-1,
		-1,2,-1,
		-1,2,-1,
		2,-1,-1
	};
	
	int version_info_7_2[3][6] =
	{
		-1,2,2,-1,-1,2,
		-1,2,2,2,2,-1,
		-1,2,-1,-1,-1,-1
	};

	int version_info_8_1[6][3] =
	{
		-1,-1,2,
		-1,-1,-1,
		-1,2,-1,
		2,2,-1,
		2,2,2,
		2,-1,-1
	};

	int version_info_8_2[3][6] =
	{
		-1,-1,-1,2,2,2,
		-1,-1,2,2,2,-1,
		2,-1,-1,-1,2,-1
	};

	int version_info_9_1[6][3] =
	{
		-1,-1,2,
		-1,-1,2,
		2,-1,2,
		-1,2,-1,
		-1,2,2,
		-1,-1,2
	};

	int version_info_9_2[3][6] =
	{
		-1,-1,2,-1,-1,-1,
		-1,-1,-1,2,2,-1,
		2,2,2,-1,2,2
	};


	Pos curr_cord = { QR_code_size - 11,0 };
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			switch (version)
			{
			case 7:code_matrix[curr_cord.y][curr_cord.x] = version_info_7_1[i][j]; break;
			case 8:code_matrix[curr_cord.y][curr_cord.x] = version_info_8_1[i][j]; break;
			case 9:code_matrix[curr_cord.y][curr_cord.x] = version_info_9_1[i][j]; break;
			}
			
			curr_cord.x++;
		}
		curr_cord.y++;
		curr_cord.x = QR_code_size - 11;
	}

	curr_cord = { 0,QR_code_size - 11 };
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			switch (version)
			{
			case 7:code_matrix[curr_cord.y][curr_cord.x] = version_info_7_2[i][j]; break;
			case 8:code_matrix[curr_cord.y][curr_cord.x] = version_info_8_2[i][j]; break;
			case 9:code_matrix[curr_cord.y][curr_cord.x] = version_info_9_2[i][j]; break;
			}
			curr_cord.x++;
		}
		curr_cord.y++;
		curr_cord.x = 0;
	}
}

/*填充数据区*/ /*不知道有没有可能出错*/
void QR_code::code_words()
{
	int x = QR_code_size;
	int y = QR_code_size -1;

	int nCoef_x = 1; 
	int nCoef_y = 1; 

	int i, j;

	for (i = 0; i < code_word_final_num; ++i)
	{
		for (j = 0; j < 8; ++j)
		{
			do
			{
				x += nCoef_x;
				nCoef_x *= -1;

				if (nCoef_x < 0)
				{
					y += nCoef_y;

					if (y < 0 || y == QR_code_size)
					{
						y = (y < 0) ? 0 : QR_code_size - 1;
						nCoef_y *= -1;

						x -= 2;

						if (x == 6) 
							--x;
					}
				}
			} while (code_matrix[x][y]==2 || code_matrix[x][y]==-1); 

			code_matrix[x][y] = (code_word_final[i] & (1 << (7 - j))) ? 1 : 0;
		}
	}
}

/*掩模*/
void QR_code::masking()
{
	for (int i = 0; i < QR_code_size; ++i)
	{
		for (int j = 0; j < QR_code_size; ++j)
		{
			if (code_matrix[j][i] == 1 || code_matrix[j][i] == 0)
			{
				bool change;
				switch (mask_pattern)
				{
				case 0:
					change = ((i + j) % 2 == 0);
					break;

				case 1:
					change = (i % 2 == 0);
					break;

				case 2:
					change = (j % 3 == 0);
					break;

				case 3:
					change = ((i + j) % 3 == 0);
					break;

				case 4:
					change = (((i / 2) + (j / 3)) % 2 == 0);
					break;

				case 5:
					change = (((i * j) % 2) + ((i * j) % 3) == 0);
					break;

				case 6:
					change = ((((i * j) % 2) + ((i * j) % 3)) % 2 == 0);
					break;

				default:
					change = ((((i * j) % 3) + ((i + j) % 2)) % 2 == 0);
					break;
				}

				if (change)
				{
					code_matrix[j][i] = !code_matrix[j][i];
				}
			}
		}
	}
}

//评分函数，复制的
int QR_code::CountPenalty()
{
	int nPenalty = 0;
	int i, j, k;

	// 同色の列の隣接モジュール
	for (i = 0; i < m_nSymbleSize; ++i)
	{
		for (j = 0; j < m_nSymbleSize - 4; ++j)
		{
			int nCount = 1;

			for (k = j + 1; k < m_nSymbleSize; k++)
			{
				if (((code_matrix[i][j] & 0x11) == 0) == ((code_matrix[i][k] & 0x11) == 0))
					++nCount;
				else
					break;
			}

			if (nCount >= 5)
			{
				nPenalty += 3 + (nCount - 5);
			}

			j = k - 1;
		}
	}

	// 同色の行の隣接モジュール
	for (i = 0; i < m_nSymbleSize; ++i)
	{
		for (j = 0; j < m_nSymbleSize - 4; ++j)
		{
			int nCount = 1;

			for (k = j + 1; k < m_nSymbleSize; k++)
			{
				if (((code_matrix[j][i] & 0x11) == 0) == ((code_matrix[k][i] & 0x11) == 0))
					++nCount;
				else
					break;
			}

			if (nCount >= 5)
			{
				nPenalty += 3 + (nCount - 5);
			}

			j = k - 1;
		}
	}

	// 同色のモジュールブロック（２×２）
	for (i = 0; i < m_nSymbleSize - 1; ++i)
	{
		for (j = 0; j < m_nSymbleSize - 1; ++j)
		{
			if ((((code_matrix[i][j] & 0x11) == 0) == ((code_matrix[i + 1][j] & 0x11) == 0)) &&
				(((code_matrix[i][j] & 0x11) == 0) == ((code_matrix[i][j + 1] & 0x11) == 0)) &&
				(((code_matrix[i][j] & 0x11) == 0) == ((code_matrix[i + 1][j + 1] & 0x11) == 0)))
			{
				nPenalty += 3;
			}
		}
	}

	// 同一列における 1:1:3:1:1 比率（暗:明:暗:明:暗）のパターン
	for (i = 0; i < m_nSymbleSize; ++i)
	{
		for (j = 0; j < m_nSymbleSize - 6; ++j)
		{
			if (((j == 0) || (!(code_matrix[i][j - 1] & 0x11))) && // 明 または シンボル外
				(code_matrix[i][j] & 0x11) && // 暗 - 1
				(!(code_matrix[i][j + 1] & 0x11)) && // 明 - 1
				(code_matrix[i][j + 2] & 0x11) && // 暗 ┐
				(code_matrix[i][j + 3] & 0x11) && // 暗 │3
				(code_matrix[i][j + 4] & 0x11) && // 暗 ┘
				(!(code_matrix[i][j + 5] & 0x11)) && // 明 - 1
				(code_matrix[i][j + 6] & 0x11) && // 暗 - 1
				((j == m_nSymbleSize - 7) || (!(code_matrix[i][j + 7] & 0x11))))   // 明 または シンボル外
			{
				// 前または後に4以上の明パターン
				if (((j < 2 || !(code_matrix[i][j - 2] & 0x11)) &&
					(j < 3 || !(code_matrix[i][j - 3] & 0x11)) &&
					(j < 4 || !(code_matrix[i][j - 4] & 0x11))) ||
					((j >= m_nSymbleSize - 8 || !(code_matrix[i][j + 8] & 0x11)) &&
					(j >= m_nSymbleSize - 9 || !(code_matrix[i][j + 9] & 0x11)) &&
						(j >= m_nSymbleSize - 10 || !(code_matrix[i][j + 10] & 0x11))))
				{
					nPenalty += 40;
				}
			}
		}
	}

	// 同一行における 1:1:3:1:1 比率（暗:明:暗:明:暗）のパターン
	for (i = 0; i < m_nSymbleSize; ++i)
	{
		for (j = 0; j < m_nSymbleSize - 6; ++j)
		{
			if (((j == 0) || (!(code_matrix[j - 1][i] & 0x11))) && // 明 または シンボル外
				(code_matrix[j][i] & 0x11) && // 暗 - 1
				(!(code_matrix[j + 1][i] & 0x11)) && // 明 - 1
				(code_matrix[j + 2][i] & 0x11) && // 暗 ┐
				(code_matrix[j + 3][i] & 0x11) && // 暗 │3
				(code_matrix[j + 4][i] & 0x11) && // 暗 ┘
				(!(code_matrix[j + 5][i] & 0x11)) && // 明 - 1
				(code_matrix[j + 6][i] & 0x11) && // 暗 - 1
				((j == m_nSymbleSize - 7) || (!(code_matrix[j + 7][i] & 0x11))))   // 明 または シンボル外
			{
				// 前または後に4以上の明パターン
				if (((j < 2 || !(code_matrix[j - 2][i] & 0x11)) &&
					(j < 3 || !(code_matrix[j - 3][i] & 0x11)) &&
					(j < 4 || !(code_matrix[j - 4][i] & 0x11))) ||
					((j >= m_nSymbleSize - 8 || !(code_matrix[j + 8][i] & 0x11)) &&
					(j >= m_nSymbleSize - 9 || !(code_matrix[j + 9][i] & 0x11)) &&
						(j >= m_nSymbleSize - 10 || !(code_matrix[j + 10][i] & 0x11))))
				{
					nPenalty += 40;
				}
			}
		}
	}

	// 全体に対する暗モジュールの占める割合
	int nCount = 0;

	for (i = 0; i < m_nSymbleSize; ++i)
	{
		for (j = 0; j < m_nSymbleSize; ++j)
		{
			if (!(code_matrix[i][j] & 0x11))
			{
				++nCount;
			}
		}
	}

	nPenalty += (abs(50 - ((nCount * 100) / (m_nSymbleSize * m_nSymbleSize))) / 5) * 10;

	return nPenalty;
}

/*打印二维码*/
void QR_code::print_QR_code()
{
	setconsoleborder(120, 120);
	system("cls");

	for (int i = 0; i < QR_code_size; i++)
	{
		for (int j = 0; j < QR_code_size; j++)
		{
			if (code_matrix[i][j])
			{
				setcolor(0, 0);
				cout << "  ";
			}
			else
			{
				setcolor(COLOR_HWHITE, COLOR_HWHITE);
				cout << "  ";
			}
		}
		cout << endl;
	}

	setcolor();
}