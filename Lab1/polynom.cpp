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

bool divide(const monomial & a, const monomial & b, monomial & res)
{
	if (a.numb_of_variables != b.numb_of_variables || b.coef==0)
		return false;
	res = monomial(a.coef / b.coef, a.numb_of_variables);
	for (int i = 0; i < res.numb_of_variables; ++i)
	{
		if (a.powers[i] - b.powers[i] >= 0)
			res.powers[i] = a.powers[i] - b.powers[i];
		else
			return false;
	}
	return true;
}

inline bool operator==(const monomial & a, const monomial & b)
{
	return a.powers == b.powers;
}

bool operator<(const monomial & a, const monomial & b)
{
	if (b.power() > a.power())
		return true;
	else if (b.power() == a.power())
		return b.max_power() > a.max_power() ? true : (b.max_power() == a.max_power() ? b.powers > a.powers:false);
	return false;
}

bool operator<=(const monomial & a, const monomial & b)
{
	return operator<(a,b) || operator==(a,b);
}

bool operator>(const monomial & a, const monomial & b)
{
	if (a.power() > b.power())
		return true;
	else if (a.power() == b.power())
		return a.max_power() > b.max_power() ? true : (a.max_power() == b.max_power() ? a.powers > b.powers:false);
	return false;
}

bool operator>=(const monomial & a, const monomial & b)
{
	return operator>(a,b) || operator==(a,b);
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
	int show_coef = compare(abs(coef), 1);
	
	int first_not_show_multi = numb_of_variables - 1;
	for (; first_not_show_multi >= 0; first_not_show_multi--)
		if (powers[first_not_show_multi] != 0)
			break;
	if (!compare(coef, -1) && first_not_show_multi != -1)
		cout << '-';
	if (show_coef || first_not_show_multi == -1)
		os << coef;
	if (show_coef && first_not_show_multi!=-1)
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
		if (i<first_not_show_multi && show_var)
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

double monomial::power() const
{
	double res = 0;
	for (int i = 0; i < numb_of_variables; ++i)
		res += powers[i];
	return res;
}

double monomial::max_power() const
{
	int max = 0;
	for (int i = 0; i < numb_of_variables; ++i)
		if (powers[max] < powers[i])
			max = i;
	return powers[max];
}

bool divide(const polynomial & a, const polynomial & b, polynomial & quotient, polynomial & reminder)
{
	if (a.numb_of_variables != b.numb_of_variables && a.numb_of_variables != 1)
		return false;
	const Node<monomial>* pa = a.pol[0];
	monomial temp;
	reminder = a;
	reminder.numb_of_variables = a.numb_of_variables;
	quotient = polynomial(a.numb_of_variables);
	while (reminder.pol.begin() && divide(reminder.pol[0]->data, b.pol[0]->data, temp))
	{
		quotient.pol.insertNode_sorted(temp,operator>);
		reminder = reminder - b*temp;
	//	cout << quotient << endl;
		//cout << reminder << endl;
	}
	return true;
}

polynomial operator-(const polynomial & a, const polynomial & b)
{
	
	if (a.numb_of_variables != b.numb_of_variables)
		return polynomial();
	polynomial res(a.numb_of_variables);
	monomial temp;
	const Node<monomial>* pa = a.pol[0], *pb = b.pol[0];
	while (pa && pb)
	{
		if (pa->data == pb->data)
		{
			temp = pa->data;
			temp.coef -= pb->data.coef;
			if (temp.coef)
				res.pol.addNode_tail(temp);
			pa = pa->next;
			pb = pb->next;
		}
		else if (pa->data > pb->data)
		{
			res.pol.addNode_tail(pa->data);
			pa = pa->next;
		}
		else
		{
			res.pol.addNode_tail(pb->data);
			pb = pb->next;
		}
	}
	while (pa)
	{
		res.pol.addNode_tail(pa->data);
		pa = pa->next;
	}
	while (pb)
	{
		res.pol.addNode_tail(pb->data);
		pb = pb->next;
	}
	return res;
}

ostream& operator<<(ostream & os, const polynomial& a)
{
	const Node<monomial>* p = a.pol[0];
	if (!p)
		cout << 0;
	while (p)
	{
		if (p->data.coef > 0 && p != a.pol[0])
			cout << '+';
		os << p->data;
		p = p->next;
	}
	return os;
}

polynomial operator+(const polynomial & a, const polynomial & b)
{
	if (a.numb_of_variables != b.numb_of_variables)
		return polynomial();
	polynomial res(a.numb_of_variables);
	monomial temp;
	const Node<monomial>* pa = a.pol[0], *pb = b.pol[0];
	while (pa && pb)
	{
		if (pa->data == pb->data)
		{
			temp = pa->data;
			temp.coef += pb->data.coef;
			if (temp.coef)
				res.pol.addNode_tail(temp);
			pa = pa->next;
			pb=pb->next;
		}
		else if (pa->data > pb->data)
		{
			res.pol.addNode_tail(pa->data);
			pa = pa->next;
		}
		else
		{
			res.pol.addNode_tail(pb->data);
			pb = pb->next;
		}
	}
	while (pa)
	{
		res.pol.addNode_tail(pa->data);
		pa = pa->next;
	}
	while (pb)
	{
		res.pol.addNode_tail(pb->data);
		pb = pb->next;
	}
	return res;
}

void polynomial::get(istream& is)
{
	cout << "Input number of variables: ";
	is >> numb_of_variables;
	monomial t(1,numb_of_variables);
	pol.~List();
	while(is)
	{
		is >> t;
		if (is)
			pol.insertNode_sorted(t, operator>);
	}
	is.clear();
	while (is.get() != '\n');
}

void polynomial::fget(fstream & fis)
{
	fis >> numb_of_variables;
	int number_of_lines = 0;
	fis >> number_of_lines;
	monomial t(1, numb_of_variables);
	pol.~List();
	for (int i=0;i<number_of_lines && !fis.eof();++i)
	{
		fis >> t;
		pol.insertNode_sorted(t, operator>);
	}
}

polynomial & polynomial::operator-()
{
	Node<monomial>* p = pol[0];
	while (p) 
	{
		p->data.coef = -p->data.coef;
		p = p->next;
	}
	return *this;
}


monomial operator*(const monomial& a, const monomial& b)
{
	if (a.powers.size() != b.powers.size())
		return monomial();
	monomial res(a.coef*b.coef, a.powers.size());
	if (res.coef)
	{
		for (int i = 0; i < res.numb_of_variables; ++i)
			res.powers[i] = a.powers[i] + b.powers[i];
	}
	return res;
}

polynomial operator*(const polynomial& a, const polynomial& b)
{
	if (a.numb_of_variables != b.numb_of_variables)
		return polynomial();
	polynomial res(a.numb_of_variables);
	const Node<monomial>* pa = a.pol[0], *pb = b.pol[0];
	while (pa)
	{
		pb = b.pol[0];
		while (pb)
		{
			monomial t = pa->data*pb->data;
			if (!res.pol.begin() || res.pol.end()->data>t)
				res.pol.addNode_tail(t);
			else
			{
				Node<monomial>* p = res.pol[0];
				while (p)
				{
					if (p->data == t)
					{
						p->data.coef += t.coef;
						break;
					}
					if (t > p->data)
					{
						res.pol.insertNode_after(p, t);
						break;
					}
					p = p->next;
				}
			}
			pb = pb->next;
		}
		pa = pa->next;
	}
	return res;
}

polynomial operator*(const polynomial & a, const monomial & b)
{
	if (a.numb_of_variables != b.numb_of_variables)
		return polynomial();
	const Node<monomial>* p = a.pol[0];
	polynomial res(a.numb_of_variables);
	while (p)
	{
		res.pol.addNode_tail(p->data*b);
		p = p->next;
	}
	return res;
}
