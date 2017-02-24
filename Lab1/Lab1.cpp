// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
// Lab1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "list.h"
#include "polynom.h"
//#include <vld.h> 
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
	char inp = 'k';
	do
	{
		cout << "Do you want to input from file (f) or from keyboard (k): ";
		//cin >> inp;
		//while (cin.get() != '\n');
	} while (cin>>inp  && inp != 'f' && inp != 'k');
	while (cin.get() != '\n');
	List<polynomial> list_pol;
	string s;
	if (inp == 'f')
	{	
		cout << "Input name of file (input.txt if blank):";
		getline(cin, s);
		if (s == "")
			s = "input.txt";
		ifstream f(s);
		while (!f.eof())
		{
			getline(f, s);
			list_pol.addNode_tail(string_get(s));
		}
	}
	else
	{
		cout << "Input your polynomials, one in each line(quit to end):\n";
		do
		{
			getline(cin, s);
			if (s != "q")
				list_pol.addNode_tail(string_get(s));
		} while (s != "q");
	}
	int size = 0;
	do
	{
		system("cls");
		size=show_list_of_pol(list_pol);
		cout << "do you want to add(+),substract(-),multiply(*), divide(/), get a value of polynomial (v), get a derivative(d)?\n"
				"You can add (a) or delete (del) polynomials from list above or save the list to file (sf)\nq for quit: ";
		cin >> s;
		while (cin.get() != '\n');
		if (is_cor(s, { "+","-","*","/","v","d","a","del","sf" }))
		{
			int num1 = -1, num2 = -1;
			if (s == "sf")
			{
				cout << "Input name of file: ";
				getline(cin, s);
				ofstream f(s, ios::out | ios::ate);
				Node<polynomial>*p = list_pol.begin();
				while (p)
				{
					f << p->data << endl;
					p = p->next;
				}
				f.close();
				continue;
			}
			if (s == "a")
			{
				cout << "input your polynom:\n";
				getline(cin, s);
				list_pol.addNode_tail(string_get(s));
				continue;
			}
			if (s == "del")
			{
				cout << "input number:\n";
				cin >> num1;
				list_pol.deleteNode_index(num1-1);
				continue;
			}
			if (s == "v" || s=="d")
			{
				cout << "input number of your polynomial from list above: ";
				cin >> num1;
				polynomial p_val = list_pol[num1 - 1]->data;
				int n_v = p_val.numb_of_var();
				if (s == "v")
				{
					vector<double> val(n_v, 0);
					cout << "Input " << n_v << " values:\n";
					for (int i = 0; i < n_v; ++i)
						cin >> val[i];
					cout << "value is " << p_val.value(val) << endl;
				}
				else if (s == "d")
				{
					polynomial res(n_v);
					res = p_val.derivative();
					cout << '(' << p_val << ")\' = " << res << endl;
					list_pol.addNode_tail(res);
				}
				system("pause");
			}
			else
			{
				cout << "Input numbers of 2 polynomials:\n";
				cin >> num1 >> num2;
				polynomial p1 = list_pol[num1 - 1]->data,p2=list_pol[num2-1]->data,res;
				if (s == "+")
				{
					res = p1 + p2;
					cout << '(' << p1 << ")+(" << p2 << ")=" << res << endl;
				}
				else if (s == "-")
				{
					res = p1 - p2;
					cout << '(' << p1 << ")-(" << p2 << ")=" << res << endl;
				}
				else if (s == "*")
				{
					res = p1 * p2;
					cout << '(' << p1 << ")*(" << p2 << ")=" << res << endl;
				}
				else if (s == "/")
				{
					polynomial reminder;
					divide(p1, p2, res, reminder);
					cout << '(' << p1 << ")/(" << p2 << ")=(" << res <<")*("<<p2<<")+("<<reminder<<")"<< endl;
					list_pol.addNode_tail(reminder);
				}
					
				list_pol.addNode_tail(res);
				system("pause");
			}
		}
	} while (cin && s!="q");
	system("pause");
    return 0;
}

