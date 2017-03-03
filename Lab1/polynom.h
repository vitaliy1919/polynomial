#pragma once
#include "stdafx.h"
#include "list.h"
const double eps = 1e-6;
const string var = "xyzfgh";
typedef pair<char, double> pair_c_d;
int compare(double a,double b);
class monomial_list
{
	double coef;
	List<pair_c_d> var;
	int var_numb;
public:
	monomial_list() :var(),coef(0),var_numb(0) {}
	inline double show_coef() const { return coef; }
	inline double& set_coef() { return coef; }
	friend monomial_list string_get(const string& s, int& i);
	friend ostream& operator<<(ostream& os, const monomial_list& m);
	friend monomial_list operator*(const monomial_list& a, const monomial_list& b);
	//double value() const;
};
struct monomial_vector
{
	double coef;
	int numb_of_variables;
	vector<double> powers;
	monomial_vector(double c = 1, int n = 1) :coef(c), numb_of_variables(n), powers(n, 0) {}
	inline void add_powers(const vector<double>& a)
	{
		copy(a.begin(), a.end(), powers.begin());
	}
	void show(ostream &os=cout) const;
	double value(const vector<double>& a) const;
	void get();
	double power() const;
	double max_power() const;
	friend monomial_vector string_get(const string& s,int& i,const int& numb_var);
	friend bool divide(const monomial_vector& a, const monomial_vector& b, monomial_vector& res);
	friend bool operator==(const monomial_vector& a, const monomial_vector& b);
	friend bool operator<(const monomial_vector& a, const monomial_vector& b);
	friend bool operator<=(const monomial_vector& a, const monomial_vector& b);
	friend bool operator>(const monomial_vector& a, const monomial_vector& b);
	friend bool operator>=(const monomial_vector& a, const monomial_vector& b);
	friend monomial_vector operator*(const monomial_vector& a, const monomial_vector& b);
	friend ostream& operator<<(ostream& os,const monomial_vector& p);
	friend istream& operator>>(istream& is, monomial_vector&p);
};

typedef monomial_vector monomial;
class polynomial
{
	List<monomial_vector> pol;
	int numb_of_variables;
	void add_0();
public:
	explicit polynomial(int n=1) :pol(),numb_of_variables(n) {}
	void get(istream& is=cin);
	void fget(fstream& fis);
	inline int numb_of_var() const { return numb_of_variables; }
	friend polynomial string_get(const string& s);
	polynomial& operator-();
	polynomial derivative() const;
	double value(const vector<double> &a) const;
	friend bool divide(const polynomial& a, const polynomial& b, polynomial& quotient, polynomial& reminder);
	friend polynomial operator-(const polynomial& a, const polynomial& b);
	friend ostream& operator<<(ostream& os, const polynomial& p);
	friend polynomial operator+(const polynomial& a, const polynomial& b);
	friend polynomial operator*(const polynomial& a, const polynomial& b);
	friend polynomial operator*(const polynomial& a, const monomial_vector& b);
};