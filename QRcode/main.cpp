#include"90-b4.h"
int main() {

	QRcode a;
	cout << "��������Ҫת�ɶ����Ƶ��ַ���" << endl;
	cout << "��ַ������http://ǰ׺��" << endl;
	char input_[200];
	cin.getline(input_, 200, '\n');
	cout << "�����������(0-3)" << endl;
	int num;
	cin >> num;
	int num_str = strlen(input_);
	if (num_str > 20)
		setfontsize("Terminal", 5, 5);
	else
		setfontsize("Terminal", 10, 10);
	setconsoleborder(200, 100);
	a.encode_qrcode(input_, num);
	system("cls");

	//a.display();
#if 1
	int i, j;
	for (i = 0; i < 17 + a.version * 4; i++) {
		for (j = 0; j < 17 + a.version * 4; j++) {
			if (a.module_code[i][j]) {
				SetConsoleTextAttribute(hout, 0 * 16 + 7);
				cout << "  ";
			}
			else {
				SetConsoleTextAttribute(hout, 7 * 16 + 7);
				cout << "  ";
			}
		}
		cout << endl;
	}
#endif 
	system("pause");

	return 0;
}