#pragma once
#include "stdafx.h"
#include "list.h"
const double eps = 1e-6;
int compare(double a,double b);
struct monomial
{
	double coef;
	int numb_of_variables;
	vector<double> powers;
	string variables;

	monomial(double c = 1, int n = 1,const string& v="xyzfgh") :coef(c), numb_of_variables(n), powers(n, 1),variables(v) {}
	inline void add_powers(const vector<double>& a)
	{
		copy(a.begin(), a.end(), powers.begin());
	}
	void show(ostream &os=cout) const;
	double value(const vector<double>& a);
	void get();
	double power() const;
	double max_power() const;
	friend bool operator==(const monomial& a, const monomial& b);
	friend bool operator<(const monomial& a, const monomial& b);
	friend bool operator>(const monomial& a, const monomial& b);
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
	polynomial(string s) :pol() {}
	void get(istream& is=cin);
	void fget(fstream& fis);
	polynomial& operator-();
	friend polynomial operator-(const polynomial& a, const polynomial& b);
	friend ostream& operator<<(ostream& os, const polynomial& p);
	friend polynomial operator+(const polynomial& a, const polynomial& b);
	friend polynomial operator*(const polynomial& a, const polynomial& b);
};