#include <iostream>
#include <fstream>
using namespace std;


int main()
{
	char c;
	int num;
	
	ifstream infile("tetris.dat", ios::in);
	if (!infile.is_open())
	{
		cerr << "open error!"<<endl;
		exit(1);
	}
	while (!infile.eof())
	{
		infile.get(c);
		if (c >= 48 && c <= 57)
		{
			num = c - '0';
			cout << num << ' ';
		}
		else infile.ignore();
	}

	infile.close();

	return 0;
}
