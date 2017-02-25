// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "stdafx.h"
#include "polynom.h"
bool cur_order(const monomial& a, const monomial& b)
{
	return operator>=(a, b);
}
double get_number(const string& s, int&i);
bool isoper(int i)
{
	return (i == '+') || (i == '-') || (i == '/') || (i == '*');
}
int compare(double a, double b)
{
	if (fabs(a - b) > eps)
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
	if (a.power() < b.power() || a.max_power() < b.max_power() || !compare(b.coef,0))
		return false;
	res = monomial(a.coef / b.coef, a.numb_of_variables);
	for (int i = 0; i < res.numb_of_variables; ++i)
	{
		if (a.powers[i] - b.powers[i] > 0 || !compare((a.powers[i] - b.powers[i]),0))
			res.powers[i] = a.powers[i] - b.powers[i];
		else
			return false;
	}
	return true;
}

bool operator==(const monomial & a, const monomial & b)
{
	int numb_var = (a.numb_of_variables > b.numb_of_variables ? b.numb_of_variables : a.numb_of_variables);
	const monomial& t = (a.numb_of_variables > b.numb_of_variables ? a : b);
	for (int i = 0; i < numb_var; i++)
		if (compare(a.powers[i] - b.powers[i],0))
			return false;
	for (int i = numb_var; i < t.numb_of_variables; ++i)
		if (compare(t.powers[i],0))
			return false;
	return true;
}

bool operator<(const monomial & a, const monomial & b)
{
	double pow_a = a.power(), pow_b = b.power();
	if (pow_b > pow_a)
		return true;
	else if (!compare(pow_b - pow_a,0))
	{
		if (b.max_power() > a.max_power())
			return true;
		else
		{
			int numb_var = (a.numb_of_variables < b.numb_of_variables ? a.numb_of_variables : b.numb_of_variables);
			const monomial& t = (a.numb_of_variables < b.numb_of_variables ? b : a);
			for (int i = 0; i < numb_var; ++i)
			{
				if (a.powers[i] > b.powers[i])
					return false;
				else if (a.powers[i] < b.powers[i])
					return true;
			}
			if (t.numb_of_variables != a.numb_of_variables)
			{
				for (int i = numb_var; i < t.numb_of_variables; i++)
				{
					if (t.powers[i] > 0)
						return true;
				}
			}
		}
	}
	return false;
}

bool operator<=(const monomial & a, const monomial & b)
{
	return operator<(a,b) || operator==(a,b);
}

bool operator>(const monomial & a, const monomial & b)
{
	double pow_a = a.power(), pow_b = b.power();
	if (pow_a > pow_b)
		return true;
	else if (!compare(pow_a - pow_b, 0))
	{
		if (a.max_power() > b.max_power())
			return true;
		else
		{
			int numb_var = (a.numb_of_variables < b.numb_of_variables ? a.numb_of_variables : b.numb_of_variables);
			const monomial& t = (a.numb_of_variables < b.numb_of_variables ? b : a);
			for (int i = 0; i < numb_var; ++i)
			{
				if (a.powers[i] > b.powers[i])
					return true;
				else if (a.powers[i] < b.powers[i])
					return false;
			}
			if (t.numb_of_variables != b.numb_of_variables)
			{
				for (int i = numb_var; i < t.numb_of_variables; i++)
				{
					if (t.powers[i] > 0)
						return true;
				}
			}
		}
	}
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
	int show_coef = compare(fabs(coef), 1);
	int first_not_show_multi = numb_of_variables - 1;
	for (; first_not_show_multi >= 0; first_not_show_multi--)
		if (fabs(powers[first_not_show_multi])>eps)
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
		if (i < var.length() && show_var)
		{
			os << var[i];
			if (compare(powers[i], 1))
				os << '^' << powers[i];
		}
		if (i<first_not_show_multi && show_var)
			os << '*';
	}
}

double monomial::value(const vector<double>& a) const
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

monomial string_get(const string & s, int & i,const int& numb_var) 
{
	monomial res(1, numb_var);
	if (isoper(s[i]))
	{
		if (isalpha(s[i + 1]))
		{
			if (s[i] == '-')
				res.coef = -1;
			++i;
		}
		else
			res.coef = get_number(s, i);
	}
	else if (isdigit(s[i]))
		res.coef = get_number(s, i);
	int len = s.length();
	while (i < len && s[i] != '+' && s[i] != '-')
	{
		i++;
		int pos = var.find(s[i - 1]);
		if (i>=len || !isdigit(s[i]))
			res.powers[pos] = 1;
		else
			res.powers[pos] = get_number(s, i);
	}
	return res;
}

bool divide(const polynomial & a, const polynomial & b, polynomial & quotient, polynomial & reminder)
{
	if (a.numb_of_variables != b.numb_of_variables && a.numb_of_variables != 1)
		return false;
	//const Node<monomial>* pa = a.pol[0];
	monomial temp;
	reminder = a;
	reminder.numb_of_variables = a.numb_of_variables;
	quotient = polynomial(a.numb_of_variables);
	while (reminder.pol.begin() && divide(reminder.pol[0]->data, b.pol[0]->data, temp))
	{
		quotient.pol.insertNode_sorted(temp,operator>);
		reminder = reminder - b*temp;
	}
	return true;
}

polynomial operator-(const polynomial & a, const polynomial & b)
{
	polynomial res(a.numb_of_variables);
	monomial temp;
	const Node<monomial>* pa = a.pol[0], *pb = b.pol[0];
	while (pa && pb)
	{
		if (pa->data == pb->data)
		{
			temp = pa->data;
			temp.coef -= pb->data.coef;
			if (compare(temp.coef,0))
				res.pol.addNode_tail(temp);
			pa = pa->next;
			pb = pb->next;
		}
		else if (pa->data > pb->data)
		{
			if (compare(pa->data.coef,0))
				res.pol.addNode_tail(pa->data);
			pa = pa->next;
		}
		else
		{
			if (compare(pb->data.coef,0))
				res.pol.addNode_tail(pb->data);
			pb = pb->next;
		}
	}
	while (pa)
	{
		if (compare(pa->data.coef, 0))
			res.pol.addNode_tail(pa->data);
		pa = pa->next;
	}
	while (pb)
	{
		if (compare(pb->data.coef, 0))
			res.pol.addNode_tail(pb->data);
		pb = pb->next;
	}
	res.add_0();
	return res;
}

ostream& operator<<(ostream & os, const polynomial& a)
{
	const Node<monomial>* p = a.pol.begin();
	/*if (!p)
		cout << 0;*/
	while (p)
	{
		if (p->data.coef >= 0 && p != a.pol.begin())
			os << '+';
		os << p->data;
		p = p->next;
	}
	return os;
}

polynomial operator+(const polynomial & a, const polynomial & b)
{
	polynomial res(a.numb_of_variables);
	monomial temp;
	const Node<monomial>* pa = a.pol[0], *pb = b.pol[0];
	while (pa && pb)
	{
		if (pa->data == pb->data)
		{
			temp = pa->data;
			temp.coef += pb->data.coef;
			if (compare(temp.coef,0))
				res.pol.addNode_tail(temp);
			pa = pa->next;
			pb=pb->next;
		}
		else if (pa->data > pb->data)
		{
			if (compare(pa->data.coef,0))
				res.pol.addNode_tail(pa->data);
			pa = pa->next;
		}
		else
		{
			if (compare(pb->data.coef,0))
				res.pol.addNode_tail(pb->data);
			pb = pb->next;
		}
	}
	while (pa)
	{
		if (pa->data.coef != 0)
			res.pol.addNode_tail(pa->data);
		pa = pa->next;
	}
	while (pb)
	{
		if (pb->data.coef != 0)
			res.pol.addNode_tail(pb->data);
		pb = pb->next;
	}
	res.add_0();
	return res;
}

void polynomial::add_0()
{
	if (pol.isempty())
	{
		monomial temp = monomial(0, 0);
		pol.addNode_tail(temp);
	}
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
			pol.insertNode_sorted(t, cur_order);
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
double get_number(const string& s, int& i)
{
	string res;
	if (isoper(s[i]))
		res += s[i++];
	while (isdigit(s[i]) || s[i] == '.' )
		res += s[i++];
	return atof(res.c_str());
}
polynomial string_get(const string & s)
{
	polynomial res(0);
	int i = 0,pos=0,len=s.length(),vlen=var.length();
	for (int j = 0; j < vlen; ++j)
		if (s.find(var[j]) != string::npos)
			res.numb_of_variables = j + 1;
	string s_right;
	for (int j = 0; j < len; ++j)
		if (s[j] != '*' && s[j] != '^')
			s_right += s[j];
	len = s_right.length();
	while (i < len)
	{
		res.pol.insertNode_sorted(string_get(s_right, i, res.numb_of_variables),cur_order);
	}
	return res;
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

polynomial polynomial::derivative() const
{
	if (numb_of_variables!=1)
		return polynomial();
	polynomial res(numb_of_variables);
	const Node<monomial> *p = pol.begin();
	while (p)
	{
		if (p->data.powers[0] > 0)
		{
			monomial t(p->data.coef*p->data.powers[0], numb_of_variables);
			t.powers[0] = p->data.powers[0] - 1;
			res.pol.addNode_tail(t);
		}
		p = p->next;
	}
	return res;
}

double polynomial::value(const vector<double>& a) const
{
	double res = 0;
	if (numb_of_variables > a.size())
	{
		cout << "too few values.\n";
		return 0;
	}
	else
	{
		const Node<monomial>* p = pol.begin();
		while (p)
		{
			res += p->data.value(a);
			p = p->next;
		}
	}
	return res;
}


monomial operator*(const monomial& a, const monomial& b)
{
	int num = (a.numb_of_variables < b.numb_of_variables ? a.numb_of_variables : b.numb_of_variables);
	const monomial &t=(a.numb_of_variables > b.numb_of_variables ? a : b);
	monomial res(a.coef*b.coef, t.numb_of_variables);
	if (compare(res.coef,0))
	{
		for (int i = 0; i < num; ++i)
			res.powers[i] = a.powers[i] + b.powers[i];
		for (int i = num; i < t.numb_of_variables; ++i)
			res.powers[i] = t.powers[i];
	}
	return res;
}

polynomial operator*(const polynomial& a, const polynomial& b)
{
	int num = (a.numb_of_variables > b.numb_of_variables ? a.numb_of_variables : b.numb_of_variables);
	polynomial res(num);
	const Node<monomial>* pa = a.pol.begin();
	while (pa)
	{
		res = res + b*pa->data;
		pa = pa->next;
	}
	res.add_0();
	return res;
}

polynomial operator*(const polynomial & a, const monomial & b)
{
	const Node<monomial>* p = a.pol.begin();
	int num = (a.numb_of_variables > b.numb_of_variables ? a.numb_of_variables : b.numb_of_variables);
	polynomial res(num);
	while (p)
	{
		res.pol.addNode_tail(p->data*b);
		p = p->next;
	}
	res.add_0();
	return res;
}
