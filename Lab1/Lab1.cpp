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
	polynomial a,b,c,d;
	fstream f("input.txt", ios::in);
	//monomial c(1, 3);
	//cin >> c;
	a.fget(f);
	b.fget(f);
	//a.fget(f);
	//b.fget(f);
	divide(a, b, c, d);
	cout << a << endl;
	cout << b << endl;
	cout << c <<' '<<d<< endl;
	//cout << "Check for input:";
	//int b;
//	cin >> b;
//	cout << b << endl;
	f.close();
	system("pause");
    return 0;
}

