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
	//polynomial a,b,c,d;
	fstream f("input.txt", ios::in);
	//monomial c(1, 3);
	////cin >> c;
	//a.fget(f);
	//b.fget(f);
	////a.fget(f);
	////b.fget(f);
	//divide(a, b, c, d);
	//cout << a << endl;
	//cout << b << endl;
	//cout << a.derivative().derivative().derivative().derivative() << endl;
	////cout << atof("+5") << endl;
	//cout << c <<' '<<d<< endl;
	string s1 = "x2-2xy+y2",s2="x-y";
	int i = 0;
	polynomial r = string_get(s1),y=string_get(s2);
	cout << r << endl << y << endl;
	cout <<"r+y= "<< r+y << endl;
	cout <<"r*y= "<< r*y << endl;
	//cout << "Check for input:";
	//int b;
//	cin >> b;
//	cout << b << endl;
	f.close();
	system("pause");
    return 0;
}

