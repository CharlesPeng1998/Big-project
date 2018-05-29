/*1751367 计2 彭健聪*/
#include "90-b4.h"

int main()
{
	//八种掩模模式的二维码
	QR_code qr_code[8];

	//用户输入纠错码级别
	int level;
	cout << "请输入二维码纠错级别\n0-3分别代表L,M,Q,H:";

	while (1)
	{
		cin >> level;
		//检验输入是否合法，下同
		if (cin.fail() || level < 0 || level > 3)
		{
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail(), '\n');
			cout << "纠错码级别不合法，请重新输入     ";
			continue;
		}
		else break;
	}

	//用户输入初始文本
	char text[101];
	cout << "\n\n请输入初始文本(长度不超过100字节):";
	getchar();
	cin.getline(text, 101);

	for (int i = 0; i < 8; i++)
	{
		qr_code[i].set_err_corre_level(level);
		qr_code[i].input_text(text);
		qr_code[i].set_mask_pattern(i);
		qr_code[i].set_version();
		qr_code[i].encode();
		qr_code[i].add_code();
		qr_code[i].binary_to_decimal();
		qr_code[i].add_code_data();
		qr_code[i].add_rs_code_data();
		qr_code[i].fill_matrix();
	}

	int best = 0;
	for (int i = 1; i < 8; i++)
	{
		if (qr_code[i].penalty < qr_code[best].penalty)
		{
			best = i;
		}
	}


	qr_code[best].print_QR_code();

#if 0
	for (int i = 0; i < 8; i++)
	{
		qr_code[i].display();
	}
#endif 	
		

	
		
	


	
	return 0;

}