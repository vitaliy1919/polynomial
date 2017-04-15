// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "stdafx.h"
//#include "polynom.h"
//bool cur_order(const monom& a, const monom& b)
//{
//	return operator>=(a, b);
//}
//double get_number(const string& s, int&i);
//bool isoper(int i)
//{
//	return (i == '+') || (i == '-') || (i == '/') || (i == '*');
//}
//int compare(double a, double b)
//{
//	if (fabs(a - b) > eps)
//	{
//		if (a > b)
//			return 1;
//		else
//			return -1;
//	}
//	return 0;
//}
//bool alfab_order(const pair_c_d& a, const pair_c_d& b)
//{
//	return a.first <= b.first;
//}
//monomial_list string_get(const string & s, int & i)
//{
//	monomial_list res(1);
//	if (isoper(s[i]))
//	{
//		if (isalpha(s[i + 1]))
//		{
//			if (s[i] == '-')
//				res.coef = -1;
//			++i;
//		}
//		else
//			res.coef = get_number(s, i);
//	}
//	else if (isdigit(s[i]))
//		res.coef = get_number(s, i);
//	int len = s.length();
//	while (i < len && s[i] != '+' && s[i] != '-')
//	{
//		i++;
//		char var = s[i-1];
//		if (i >= len || !isdigit(s[i]))
//			res.var.insertNodeSorted({ var,1 },alfab_order);
//		else
//			res.var.insertNodeSorted({ var,get_number(s, i) },alfab_order);
//		res.var_numb++;
//	}
//	res.simplify();
//	return res;
//}
//
//ostream & operator<<(ostream & os, const monomial_list & m)
//{
//	int show_coef = compare(fabs(m.coef), 1);
//	if (!compare(m.coef, -1)&& m.var_numb)
//		cout << '-';
//	if (show_coef || !m.var_numb)
//		os << m.coef;
//	if (show_coef && m.var_numb)
//		os << '*';
//	p_node_pair p = m.var.begin();
//	while (p)
//	{
//		os << p->data.first;
//		if (compare(p->data.second, 1))
//			os << '^' << p->data.second;
//		if (p->next)
//			os << '*';
//		p = p->next;
//	}
//	return os;
//}
//
//monomial_list operator*(const monomial_list & a, const monomial_list & b)
//{
//	monomial_list res(a.coef*b.coef);
//	if (compare(res.coef,0))
//	{
//		p_node_pair pa = a.var.begin(), pb = b.var.begin();
//		while (pa && pb)
//		{
//			if (pa->data.first == pb->data.first)
//			{
//				res.var.insertNodeSorted({ pa->data.first,pa->data.second + pb->data.second }, alfab_order);
//				pa = pa->next;
//				pb = pb->next;
//			}
//			else if (alfab_order(pa->data, pb->data))
//			{
//				res.var.insertNodeSorted(pa->data, alfab_order);
//				pa = pa->next;
//			}
//			else
//			{
//				res.var.insertNodeSorted(pb->data, alfab_order);
//				pb = pb->next;
//			}
//			res.var_numb++;
//		}
//		while (pa)
//		{
//			res.var.insertNodeSorted(pa->data, alfab_order);
//			pa = pa->next;
//			res.var_numb++;
//		}
//		while (pb)
//		{
//			res.var.insertNodeSorted(pb->data, alfab_order);
//			pb = pb->next;
//			res.var_numb++;
//		}
//	}
//	return res;
//}
//
//bool divide(const monomial_list & a, const monomial_list & b, monomial_list & res)
//{
//	if (compare(b.coef, 0))
//	{
//		res.~monomial_list();
//		res = monomial_list(a.coef / b.coef);
//		Node<pair_c_d> *pa = a.var.begin(), *pb = b.var.begin();
//		while (pa && pb)
//		{
//			if (pa->data.first == pb->data.first)
//			{
//				if (compare(pa->data.second - pb->data.second, 0))
//				{
//					res.var.insertNodeSorted({ pa->data.first,pa->data.second - pb->data.second }, alfab_order);
//					++res.var_numb;
//				}
//				pa = pa->next;
//				pb = pb->next;
//			}
//			else if (alfab_order(pb->data, pa->data))
//				return false;
//			else
//			{
//				res.var.insertNodeSorted(pa->data, alfab_order);
//				pa = pa->next;
//				++res.var_numb;
//			}
//		}
//		if (pb)
//			return false;
//		while (pa)
//		{
//			res.var.insertNodeSorted(pa->data, alfab_order);
//			pa = pa->next;
//			++res.var_numb;
//		}
//		return true;
//	}
//	return false;
//}
//
//bool operator>(const monomial_list & a, const monomial_list & b)
//{
//	if (!a.var.begin())
//		return false;
//	double a_m = a.max_power(), b_m = b.max_power();
//	if (a_m > b_m)
//		return true;
//	else if (!compare(a_m,b_m))
//	{
//		double a_s = a.sum_powers(), b_s = b.sum_powers();
//		if (a_s > b_s)
//			return true;
//		else if (!compare(a_s,b_s))
//		{
//			p_node_pair pa = a.var.begin(), pb = b.var.begin();
//			while (pa && pb && pa->data.second == pb->data.second)
//			{
//				pa = pa->next;
//				pb = pb->next;
//			}
//			if (!pa)
//				return alfab_order(a.var.begin()->data, b.var.begin()->data);
//			else
//				return (pa->data.second > pb->data.second);
//		}
//	}
//	return false;
//}
//
//bool operator==(const monomial_list & a, const monomial_list & b)
//{
//	if (a.var_numb == b.var_numb)
//	{
//		p_node_pair pa = a.var.begin(), pb = b.var.begin();
//		while (pa && pb && pa->data==pb->data)
//		{
//			pa = pa->next;
//			pb = pb->next;
//		}
//		if (pa || pb)
//			return false;
//		return true;
//	}
//	return false;
//}
//
//bool operator>=(const monomial_list & a, const monomial_list & b)
//{
//	return (a>b) || (a==b);
//}
//
//bool divide(const polynomial & a, const polynomial & b, polynomial & quotient, polynomial & reminder)
//{
//	if (a.numb_of_variables != b.numb_of_variables && a.numb_of_variables != 1)
//		return false;
//	monom temp;
//	reminder = a;
//	reminder.numb_of_variables = a.numb_of_variables;
//	quotient = polynomial(a.numb_of_variables);
//	while (reminder.pol.begin() && divide(reminder.pol[0]->data, b.pol[0]->data, temp))
//	{
//		quotient.pol.insertNodeSorted(temp,cur_order);
//		reminder = reminder - b*temp;
//	}
//	return true;
//}
//
//polynomial operator-(const polynomial & a, const polynomial & b)
//{
//	polynomial res(a.numb_of_variables);
//	monom temp;
//	const Node<monom>* pa = a.pol[0], *pb = b.pol[0];
//	while (pa && pb)
//	{
//		if (pa->data == pb->data)
//		{
//			temp = pa->data;
//			temp.set_coef() -= pb->data.get_coef();
//			if (compare(temp.get_coef(),0))
//				res.pol.addNodeTail(temp);
//			pa = pa->next;
//			pb = pb->next;
//		}
//		else if (pa->data > pb->data)
//		{
//			if (compare(pa->data.get_coef(),0))
//				res.pol.addNodeTail(pa->data);
//			pa = pa->next;
//		}
//		else
//		{
//			if (compare(pb->data.get_coef(),0))
//				res.pol.addNodeTail(pb->data);
//			pb = pb->next;
//		}
//	}
//	while (pa)
//	{
//		if (compare(pa->data.get_coef(), 0))
//			res.pol.addNodeTail(pa->data);
//		pa = pa->next;
//	}
//	while (pb)
//	{
//		if (compare(pb->data.get_coef(), 0))
//			res.pol.addNodeTail(pb->data);
//		pb = pb->next;
//	}
//	res.add_0();
//	return res;
//}
//
//ostream& operator<<(ostream & os, const polynomial& a)
//{
//	const Node<monom>* p = a.pol.begin();
//	while (p)
//	{
//		if (p->data.get_coef() >= 0 && p != a.pol.begin())
//			os << '+';
//		os << p->data;
//		p = p->next;
//	}
//	return os;
//}
//
//polynomial operator+(const polynomial & a, const polynomial & b)
//{
//	polynomial res(a.numb_of_variables);
//	monom temp;
//	const Node<monom>* pa = a.pol[0], *pb = b.pol[0];
//	while (pa && pb)
//	{
//		if (pa->data == pb->data)
//		{
//			temp = pa->data;
//			temp.set_coef() += pb->data.get_coef();
//			if (compare(temp.get_coef(),0))
//				res.pol.addNodeTail(temp);
//			pa = pa->next;
//			pb=pb->next;
//		}
//		else if (pa->data > pb->data)
//		{
//			if (compare(pa->data.get_coef(),0))
//				res.pol.addNodeTail(pa->data);
//			pa = pa->next;
//		}
//		else
//		{
//			if (compare(pb->data.get_coef(),0))
//				res.pol.addNodeTail(pb->data);
//			pb = pb->next;
//		}
//	}
//	while (pa)
//	{
//		if (compare(pa->data.get_coef(), 0))
//			res.pol.addNodeTail(pa->data);
//		pa = pa->next;
//	}
//	while (pb)
//	{
//		if (compare(pb->data.get_coef(), 0))
//			res.pol.addNodeTail(pb->data);
//		pb = pb->next;
//	}
//	res.add_0();
//	return res;
//}
//
//void polynomial::add_0()
//{
//	if (pol.empty())
//	{
//		monom temp = monom(0);
//		pol.addNodeTail(temp);
//	}
//}
//
////void polynomial::get(istream& is)
////{
////	cout << "Input number of variables: ";
////	is >> numb_of_variables;
////	monom t(1,numb_of_variables);
////	pol.~List();
////	while(is)
////	{
////		is >> t;
////		if (is)
////			pol.insertNode_sorted(t, cur_order);
////	}
////	is.clear();
////	while (is.get() != '\n');
////}
////
////void polynomial::fget(fstream & fis)
////{
////	fis >> numb_of_variables;
////	int number_of_lines = 0;
////	fis >> number_of_lines;
////	monom t(1, numb_of_variables);
////	pol.~List();
////	for (int i=0;i<number_of_lines && !fis.eof();++i)
////	{
////		fis >> t;
////		pol.insertNode_sorted(t, operator>);
////	}
////}
//
//double get_number(const string& s, int& i)
//{
//	string res;
//	if (isoper(s[i]))
//		res += s[i++];
//	while (isdigit(s[i]) || s[i] == '.' )
//		res += s[i++];
//	return atof(res.c_str());
//}
//
//polynomial string_get(const string & s)
//{
//	polynomial res(0);
//	int i = 0,pos=0,len=s.length(),vlen=var.length();
//	for (int j = 0; j < vlen; ++j)
//		if (s.find(var[j]) != string::npos)
//			res.numb_of_variables = j + 1;
//	string s_right;
//	for (int j = 0; j < len; ++j)
//		if (s[j] != '*' && s[j] != '^')
//			s_right += s[j];
//	len = s_right.length();
//	while (i < len)
//	{
//		res.pol.insertNodeSorted(string_get(s_right, i),cur_order);
//	}
//	res.simplify();
//	return res;
//}
//
//polynomial & polynomial::operator-()
//{
//	Node<monom>* p = pol[0];
//	while (p) 
//	{
//		p->data.set_coef() = -p->data.get_coef();
//		p = p->next;
//	}
//	return *this;
//}
//
//polynomial polynomial::derivative() const
//{
//	if (numb_of_variables!=1)
//		return polynomial();
//	polynomial res(numb_of_variables);
//	const Node<monom> *p = pol.begin();
//	while (p)
//	{
//		monom temp = p->data.derivative();
//		if (compare(temp.get_coef(),0))	
//			res.pol.insertNodeSorted(temp, cur_order);
//		p = p->next;
//	}
//	return res;
//}
//
//void polynomial::simplify()
//{
//	if (pol.begin() == pol.end() || !pol.begin())
//		return;
//	Node<monom> *p = pol.begin();
//	int i = 0;
//	while (p->next)
//	{
//		if (p->data == p->next->data)
//		{
//			p->data.set_coef() += p->next->data.get_coef();
//			pol.deleteNodeIndex(i + 1);
//			continue;
//		}
//		i++;
//		p = p->next;
//	}
//	p = pol.begin();
//	i = 0;
//	while (p)
//	{
//		Node<monom> *p_n = p->next;
//		if (!compare(p->data.get_coef(), 0))
//		{
//			pol.deleteNodeIndex(i);
//		}
//		++i;
//		p = p_n;
//	}
//	add_0();
//}
//
//double polynomial::value(const vector<double>& a) const
//{
//	double res = 0;
//	if (numb_of_variables > a.size())
//	{
//		cout << "too few values.\n";
//		return 0;
//	}
//	else
//	{
//		const Node<monom>* p = pol.begin();
//		while (p)
//		{
//			res += p->data.value(a);
//			p = p->next;
//		}
//	}
//	return res;
//}
//
//polynomial operator*(const polynomial& a, const polynomial& b)
//{
//	int num = (a.numb_of_variables > b.numb_of_variables ? a.numb_of_variables : b.numb_of_variables);
//	polynomial res(num);
//	const Node<monom>* pa = a.pol.begin();
//	while (pa)
//	{
//		res = res + b*pa->data;
//		pa = pa->next;
//	}
//	res.add_0();
//	return res;
//}
//
//polynomial operator*(const polynomial & a, const monom & b)
//{
//	const Node<monom>* p = a.pol.begin();
//	int num = (a.numb_of_variables > b.get_var_numb() ? a.numb_of_variables : b.get_var_numb());
//	polynomial res(num);
//	while (p)
//	{
//		res.pol.addNodeTail(p->data*b);
//		p = p->next;
//	}
//	res.add_0();
//	return res;
//}
//
//double monomial_list::max_power() const
//{
//	p_node_pair p = var.begin();
//	double max = 0;
//	while (p)
//	{
//		if (p->data.second > max)
//			max = p->data.second;
//		p = p->next;
//	}
//	return max;
//}
//
//double monomial_list::sum_powers() const
//{
//	p_node_pair p = var.begin();
//	double sum = 0;
//	while (p)
//	{
//		sum += p->data.second;
//		p = p->next;
//	}
//	return sum;
//}
//
//monomial_list monomial_list::derivative() const
//{
//	if (var_numb == 1 && compare(coef,0))
//	{	
//		p_node_pair p = var.begin();
//		monomial_list res(coef*p->data.second);
//		while (p)
//		{
//			if (p->data.second < 1)
//			{
//				cout << "Can't take derivative.\n";
//				return monomial_list();
//			}
//			else if (compare(p->data.second, 1))
//			{
//				res.var.addNodeTail({ p->data.first,p->data.second - 1 });
//				res.var_numb++;
//			}
//			p = p->next;
//		}
//		return res;
//	}
//	return monomial_list();
//}
//
//void monomial_list::simplify()
//{
//	if (var_numb == 0)
//		return;
//	p_node_pair p = var.begin();
//	int i = 0;
//	if (var_numb != 1)
//	{
//		while (p->next)
//		{
//			if (p->data.first == p->next->data.first)
//			{
//				p->data.second += p->next->data.second;
//				var.deleteNodeIndex(i + 1);
//				var_numb--;
//			}
//			else
//			{
//				i++;
//				p = p->next;
//			}
//		}
//		p = var.begin();
//		i = 0;
//	}
//	while (p)
//	{
//		p_node_pair t = p->next;
//		if (!compare(p->data.second, 0))
//		{
//			var.deleteNodeIndex(i);
//			var_numb--;
//		}
//		else
//			i++;
//		p = t;
//	}
//}
//
//double monomial_list::value(const vector<double>& m) const
//{
//	if (m.size() == var_numb)
//	{
//		double res = coef;
//		if (compare(res, 0))
//		{
//			int i = 0;
//			p_node_pair p = var.begin();
//			while (p)
//			{
//				res *= pow(m[i], p->data.second);
//				p = p->next;
//				i++;
//			}
//		}
//		return res;
//	}
//	return 0;
//}
