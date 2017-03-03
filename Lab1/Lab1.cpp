// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
// Lab1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "list.h"
#include "polynom.h"
#include <vld.h> 
bool is_cor(const string& s, const set<string>& a)
{
	if (a.find(s) != a.end())
		return true;
	return false;
}
int show_list_of_pol(const List<polynomial> &a)
{
	Node<polynomial>* p = a.begin();
	int i = 0;
	while (p)
	{
		cout << ++i << ". " << p->data << endl;
		p = p->next;
	}
	return i;
}
int main()
{
	int i = 0, j = 0;;
	monom a = string_get("5",i),b=string_get("xz",j);
	cout << a << endl << b << endl << a*b << endl;;
	double mas[2] = { 3,2 };
	cout << a.value(mas, 0) << endl;
	system("pause");
    return 0;
}

