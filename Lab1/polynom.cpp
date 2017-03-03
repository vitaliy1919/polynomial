// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "stdafx.h"
#include "polynom.h"
bool cur_order(const monomial_vector& a, const monomial_vector& b)
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
bool alfab_order(const pair_c_d& a, const pair_c_d& b)
{
	return a.first <= b.first;
}
monomial_list string_get(const string & s, int & i)
{
	monomial_list res(1);
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
		char var = s[i-1];
		if (i >= len || !isdigit(s[i]))
			res.var.insertNode_sorted({ var,1 },alfab_order);
		else
			res.var.insertNode_sorted({ var,get_number(s, i) },alfab_order);
		res.var_numb++;
	}
	return res;
}

ostream & operator<<(ostream & os, const monomial_list & m)
{
	int show_coef = compare(fabs(m.coef), 1);
	if (!compare(m.coef, -1)&& m.var_numb)
		cout << '-';
	if (show_coef || !m.var_numb)
		os << m.coef;
	if (show_coef && m.var_numb)
		os << '*';
	p_node_pair p = m.var.begin();
	while (p)
	{
		os << p->data.first;
		if (compare(p->data.second, 1))
			os << '^' << p->data.second;
		if (p->next)
			os << '*';
		p = p->next;
	}
	return os;
}

monomial_list operator*(const monomial_list & a, const monomial_list & b)
{
	monomial_list res(a.coef*b.coef);
	if (res.coef)
	{
		p_node_pair pa = a.var.begin(), pb = b.var.begin();
		while (pa && pb)
		{
			if (pa->data.first == pb->data.first)
			{
				res.var.insertNode_sorted({ pa->data.first,pa->data.second + pb->data.second }, alfab_order);
				pa = pa->next;
				pb = pb->next;
			}
			else if (alfab_order(pa->data, pb->data))
			{
				res.var.insertNode_sorted(pa->data, alfab_order);
				pa = pa->next;
			}
			else
			{
				res.var.insertNode_sorted(pb->data, alfab_order);
				pb = pb->next;
			}
			res.var_numb++;
		}
		while (pa)
		{
			res.var.insertNode_sorted(pa->data, alfab_order);
			pa = pa->next;
			res.var_numb++;
		}
		while (pb)
		{
			res.var.insertNode_sorted(pb->data, alfab_order);
			pb = pb->next;
			res.var_numb++;
		}
	}
	return res;
}

bool divide(const monomial_list & a, const monomial_list & b, monomial_list & res)
{
	if (compare(b.coef, 0))
	{
		res.~monomial_list();
		res = monomial_list(a.coef / b.coef);
		Node<pair_c_d> *pa = a.var.begin(), *pb = b.var.begin();
		while (pa && pb)
		{
			if (pa->data.first == pb->data.first)
			{
				if (compare(pa->data.second - pb->data.second, 0))
				{
					res.var.insertNode_sorted({ pa->data.first,pa->data.second - pb->data.second }, alfab_order);
					++res.var_numb;
				}
				pa = pa->next;
				pb = pb->next;
			}
			else if (alfab_order(pb->data, pa->data))
				return false;
			else
			{
				res.var.insertNode_sorted(pa->data, alfab_order);
				pa = pa->next;
				++res.var_numb;
			}
		}
		if (pb)
			return false;
		while (pa)
		{
			res.var.insertNode_sorted(pa->data, alfab_order);
			pa = pa->next;
			++res.var_numb;
		}
		return true;
	}
	return false;
}

bool operator>(const monomial_list & a, const monomial_list & b)
{
	double a_m = a.max_power(), b_m = b.max_power();
	if (a_m > b_m)
		return true;
	else if (!compare(a_m,b_m))
	{
		double a_s = a.sum_powers(), b_s = b.sum_powers();
		if (a_s > b_s)
			return true;
		else if (!compare(a_s,b_s))
		{
			p_node_pair pa = a.var.begin(), pb = b.var.begin();
			while (pa && pb && pa->data.second == pb->data.second)
			{
				pa = pa->next;
				pb = pb->next;
			}
			if (!pa)
				return alfab_order(a.var.begin()->data, b.var.begin()->data);
			else
				return (pa->data.second > pb->data.first);
		}
	}
	return false;
}

bool operator==(const monomial_list & a, const monomial_list & b)
{
	if (a.var_numb == b.var_numb)
	{
		p_node_pair pa = a.var.begin(), pb = b.var.begin();
		while (pa && pb && pa->data==pb->data)
		{
			pa = pa->next;
			pb = pb->next;
		}
		if (pa || pb)
			return false;
		return true;
	}
	return false;
}

bool operator>=(const monomial_list & a, const monomial_list & b)
{
	return (a>b) || (a==b);
}

bool divide(const monomial_vector & a, const monomial_vector & b, monomial_vector & res)
{
	if (a.power() < b.power() || a.max_power() < b.max_power() || !compare(b.coef,0))
		return false;
	res = monomial_vector(a.coef / b.coef, a.numb_of_variables);
	for (int i = 0; i < res.numb_of_variables; ++i)
	{
		if (a.powers[i] - b.powers[i] > 0 || !compare((a.powers[i] - b.powers[i]),0))
			res.powers[i] = a.powers[i] - b.powers[i];
		else
			return false;
	}
	return true;
}

bool operator==(const monomial_vector & a, const monomial_vector & b)
{
	int numb_var = (a.numb_of_variables > b.numb_of_variables ? b.numb_of_variables : a.numb_of_variables);
	const monomial_vector& t = (a.numb_of_variables > b.numb_of_variables ? a : b);
	for (int i = 0; i < numb_var; i++)
		if (compare(a.powers[i] - b.powers[i],0))
			return false;
	for (int i = numb_var; i < t.numb_of_variables; ++i)
		if (compare(t.powers[i],0))
			return false;
	return true;
}

bool operator<(const monomial_vector & a, const monomial_vector & b)
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
			const monomial_vector& t = (a.numb_of_variables < b.numb_of_variables ? b : a);
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

bool operator<=(const monomial_vector & a, const monomial_vector & b)
{
	return operator<(a,b) || operator==(a,b);
}

bool operator>(const monomial_vector & a, const monomial_vector & b)
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
			const monomial_vector& t = (a.numb_of_variables < b.numb_of_variables ? b : a);
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

bool operator>=(const monomial_vector & a, const monomial_vector & b)
{
	return operator>(a,b) || operator==(a,b);
}

ostream & operator<<(ostream & os,const monomial_vector & p)
{
	p.show(os);
	return os;
}

istream & operator >> (istream & is, monomial_vector & p)
{
	is >> p.coef;
	for (int i = 0; i < p.numb_of_variables; ++i)
		is >> p.powers[i];
	return is;
}

void monomial_vector::show(ostream & os) const
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

double monomial_vector::value(const vector<double>& a) const
{
	double res = coef;
	for (int i = 0; i < numb_of_variables; ++i)
		res *= pow(a[i], powers[i]);
	return res;
}

void monomial_vector::get()
{
	cout << "Input coefficient and " << numb_of_variables << " variable powers:\n";
	cin >> coef;
	for (int i = 0; i < numb_of_variables; i++)
	{
		cin >> powers[i];
	}
	while (cin.get() != '\n');
}

double monomial_vector::power() const
{
	double res = 0;
	for (int i = 0; i < numb_of_variables; ++i)
		res += powers[i];
	return res;
}

double monomial_vector::max_power() const
{
	int max = 0;
	for (int i = 0; i < numb_of_variables; ++i)
		if (powers[max] < powers[i])
			max = i;
	return powers[max];
}

monomial_vector string_get(const string & s, int & i,const int& numb_var) 
{
	monomial_vector res(1, numb_var);
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
	monomial_vector temp;
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
	monomial_vector temp;
	const Node<monomial_vector>* pa = a.pol[0], *pb = b.pol[0];
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
	const Node<monomial_vector>* p = a.pol.begin();
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
	monomial_vector temp;
	const Node<monomial_vector>* pa = a.pol[0], *pb = b.pol[0];
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
		monomial_vector temp = monomial_vector(0, 0);
		pol.addNode_tail(temp);
	}
}

void polynomial::get(istream& is)
{
	cout << "Input number of variables: ";
	is >> numb_of_variables;
	monomial_vector t(1,numb_of_variables);
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
	monomial_vector t(1, numb_of_variables);
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
	Node<monomial_vector>* p = pol[0];
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
	const Node<monomial_vector> *p = pol.begin();
	while (p)
	{
		if (p->data.powers[0] > 0)
		{
			monomial_vector t(p->data.coef*p->data.powers[0], numb_of_variables);
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
		const Node<monomial_vector>* p = pol.begin();
		while (p)
		{
			res += p->data.value(a);
			p = p->next;
		}
	}
	return res;
}

monomial_vector operator*(const monomial_vector& a, const monomial_vector& b)
{
	int num = (a.numb_of_variables < b.numb_of_variables ? a.numb_of_variables : b.numb_of_variables);
	const monomial_vector &t=(a.numb_of_variables > b.numb_of_variables ? a : b);
	monomial_vector res(a.coef*b.coef, t.numb_of_variables);
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
	const Node<monomial_vector>* pa = a.pol.begin();
	while (pa)
	{
		res = res + b*pa->data;
		pa = pa->next;
	}
	res.add_0();
	return res;
}

polynomial operator*(const polynomial & a, const monomial_vector & b)
{
	const Node<monomial_vector>* p = a.pol.begin();
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

double monomial_list::max_power() const
{
	p_node_pair p = var.begin();
	double max = 0;
	while (p)
	{
		if (p->data.second > max)
			max = p->data.second;
		p = p->next;
	}
	return max;
}

double monomial_list::sum_powers() const
{
	p_node_pair p = var.begin();
	double sum = 0;
	while (p)
	{
		sum += p->data.second;
		p = p->next;
	}
	return sum;
}

double monomial_list::value(const vector<double>& m) const
{
	if (m.size() == var_numb)
	{
		double res = coef;
		if (compare(res, 0))
		{
			int i = 0;
			p_node_pair p = var.begin();
			while (p)
			{
				res *= pow(m[i], p->data.second);
				p = p->next;
				i++;
			}
		}
		return res;
	}
	return 0;
}
