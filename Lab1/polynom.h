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
	bool operator==(const monomial& m) const;
	bool operator>(const monomial& m) const;
	bool operator<(const monomial& m) const;
	friend bool operator==(const monomial& a, const monomial& b);
	friend bool operator<(const monomial& a, const monomial& b);
	friend bool operator>(const monomial& a, const monomial& b);
	friend ostream& operator<<(ostream& os,const monomial& p);
	friend istream& operator >> (istream& is, monomial&p);
};

class polynomial
{
	List<monomial> pol;
	int numb_of_variables;
public:
	polynomial(int n=1) :pol(),numb_of_variables(n) {}
	polynomial(string s) :pol() {}
	void get();
	friend ostream& operator<<(ostream& os, const polynomial& p);

	
};