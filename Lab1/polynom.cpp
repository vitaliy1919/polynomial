// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "stdafx.h"
#include "polynom.h"

int compare(double a, double b)
{
	if (abs(a - b) > eps)
	{
		if (a > b)
			return 1;
		else
			return -1;
	}
	return 0;
}

bool operator==(const monomial & a, const monomial & b)
{
	return a.operator==(b);
}

ostream & operator<<(ostream & os,const monomial & p)
{
	p.show(os);
	return os;
}

istream & operator >> (istream & is, monomial & p)
{
	is >> p.coef;
	for (int i = 0; i < p.numb_of_variables; ++i)
		is >> p.powers[i];
	return is;
}

void monomial::show(ostream & os) const
{	
	int show_coef = compare(coef, 1);
	if (show_coef)
		os << coef;
	int first_not_show_multi = numb_of_variables - 1;
	for (; first_not_show_multi >= 0; first_not_show_multi--)
		if (powers[first_not_show_multi] != 0)
			break;
	if (first_not_show_multi!=-1)
		os << '*';
	for (int i = 0; i < numb_of_variables; ++i)
	{
		int show_var = compare(powers[i], 0);
		if (i < variables.length() && show_var)
		{
			os << variables[i];
			if (compare(powers[i], 1))
				os << '^' << powers[i];
		}
		if ((show_coef || i != 0) && (i<first_not_show_multi) && show_var)
			os << '*';
	}
}

double monomial::value(const vector<double>& a)
{
	double res = coef;
	for (int i = 0; i < numb_of_variables; ++i)
		res *= pow(a[i], powers[i]);
	return res;
}


void monomial::get()
{
	cout << "Input coefficient and " << numb_of_variables << " variable powers:\n";
	cin >> coef;
	for (int i = 0; i < numb_of_variables; i++)
	{
		cin >> powers[i];
	}
	while (cin.get() != '\n');
}

bool monomial::operator==(const monomial & m) const
{
	if (powers == m.powers)
		return true;
	return false;
}

bool monomial::operator>(const monomial & m) const
{
	if (powers > m.powers)
		return true;
	return false;
}

bool monomial::operator<(const monomial & m) const
{
	if (m.powers > powers)
		return true;
	return false;
}


ostream& operator<<(ostream & os, const polynomial& a)
{
	const Node<monomial>* p = a.pol[0];
	while (p)
	{
		if (p->data.coef > 0 && p != a.pol[0])
			cout << '+';
		os << p->data;
		p = p->next;
	}
	return os;
}

void polynomial::get()
{
	cout << "Input number of variables: ";
	cin >> numb_of_variables;
	monomial t(1,numb_of_variables);
	while(cin)
	{
		cin >> t;
		if (cin)
			pol.insertNode_sorted(t, operator<);
			//pol.addNode_tail(t);
	}
	cin.clear();
	while (cin.get() != '\n');
}
