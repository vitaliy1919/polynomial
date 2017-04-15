#pragma once
#include "stdafx.h"
#include "list.h"
const double eps = 1e-6;
const string var = "xyzfgh";
typedef pair<char, double> pair_c_d;
typedef Node<pair_c_d>* p_node_pair;
int compare(double a,double b);
class monomial_list
{
	double coef;
	List<pair_c_d> var;
	int var_numb;
public:
	monomial_list(double c=0) :var(),coef(c),var_numb(0) {}
	double max_power() const;
	double sum_powers() const;
	friend monomial_list string_get(const string& s, int& i);
	int get_var_numb() const { return var_numb; }
	double get_coef() const { return coef; }
	double& set_coef() { return coef; }
	monomial_list derivative() const;
	void simplify();
	friend ostream& operator<<(ostream& os, const monomial_list& m);
	friend monomial_list operator*(const monomial_list& a, const monomial_list& b);
	double value(const vector<double>& m) const;
	friend bool divide(const monomial_list& a, const monomial_list& b, monomial_list& res);
	friend bool operator>(const monomial_list& a, const monomial_list& b);
	friend bool operator==(const monomial_list& a, const monomial_list& b);
	friend bool operator>=(const monomial_list& a, const monomial_list& b);
};
typedef monomial_list monom;
class polynomial
{
	List<monom> pol;
	int numb_of_variables;
	void add_0();
public:
	explicit polynomial(int n=1) :pol(),numb_of_variables(n) {}
	//void get(istream& is=cin);
	//void fget(fstream& fis);
	inline int numb_of_var() const { return numb_of_variables; }
	friend polynomial string_get(const string& s);
	polynomial& operator-();
	polynomial derivative() const;
	void simplify();
	double value(const vector<double> &a) const;
	friend bool divide(const polynomial& a, const polynomial& b, polynomial& quotient, polynomial& reminder);
	friend polynomial operator-(const polynomial& a, const polynomial& b);
	friend ostream& operator<<(ostream& os, const polynomial& p);
	friend polynomial operator+(const polynomial& a, const polynomial& b);
	friend polynomial operator*(const polynomial& a, const polynomial& b);
	friend polynomial operator*(const polynomial& a, const monom& b);
};