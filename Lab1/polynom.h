#pragma once
#include "stdafx.h"
#include "list.h"
const double eps = 1e-6;
const string var = "xyzfgh";
int compare(double a,double b);
struct monomial
{
	double coef;
	int numb_of_variables;
	vector<double> powers;
	monomial(double c = 1, int n = 1) :coef(c), numb_of_variables(n), powers(n, 0) {}
	inline void add_powers(const vector<double>& a)
	{
		copy(a.begin(), a.end(), powers.begin());
	}
	void show(ostream &os=cout) const;
	double value(const vector<double>& a) const;
	void get();
	double power() const;
	double max_power() const;
	friend monomial string_get(const string& s,int& i,const int& numb_var);
	friend bool divide(const monomial& a, const monomial& b, monomial& res);
	friend bool operator==(const monomial& a, const monomial& b);
	friend bool operator<(const monomial& a, const monomial& b);
	friend bool operator<=(const monomial& a, const monomial& b);
	friend bool operator>(const monomial& a, const monomial& b);
	friend bool operator>=(const monomial& a, const monomial& b);
	friend monomial operator*(const monomial& a, const monomial& b);
	friend ostream& operator<<(ostream& os,const monomial& p);
	friend istream& operator>>(istream& is, monomial&p);
};

class polynomial
{
	List<monomial> pol;
	int numb_of_variables;
public:
	polynomial(int n=1) :pol(),numb_of_variables(n) {}
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
	friend polynomial operator*(const polynomial& a, const monomial& b);
	
};