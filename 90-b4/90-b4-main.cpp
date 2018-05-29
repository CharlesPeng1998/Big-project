/*1751367 ��2 ����*/
#include "90-b4.h"

int main()
{
	//������ģģʽ�Ķ�ά��
	QR_code qr_code[8];

	//�û���������뼶��
	int level;
	cout << "�������ά�������\n0-3�ֱ����L,M,Q,H:";

	while (1)
	{
		cin >> level;
		//���������Ƿ�Ϸ�����ͬ
		if (cin.fail() || level < 0 || level > 3)
		{
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail(), '\n');
			cout << "�����뼶�𲻺Ϸ�������������     ";
			continue;
		}
		else break;
	}

	//�û������ʼ�ı�
	char text[101];
	cout << "\n\n�������ʼ�ı�(���Ȳ�����100�ֽ�):";
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