// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
// Lab1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "list.h"
#include "polynom.h"
//#include <vld.h> 

int main()
{
	polynomial a,b;
	fstream f("input.txt", ios::in);

	a.fget(f);
	//b.get();
	cout << a << endl;
	//cout << b << endl;
	//cout << a + b << endl;
	//cout << "Check for input:";
	//int b;
//	cin >> b;
//	cout << b << endl;
	f.close();
	system("pause");
    return 0;
}

