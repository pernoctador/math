#ifndef _RATIONAL_H_
#define _RATIONAL_H_

#include <math.h>
#include <assert.h>
#include <utility>
#include <stdlib.h>     /* srand, rand */
#include <climits>
#include <vector>
#include <iostream>
using namespace std;

class Rational {
public:
	Rational(){num = 1; den = 1;}
	Rational(int n){num = n; den = 1;}
	Rational(const Rational& r){num = r.num; den = r.den;}
	Rational(int n, int d);
	~Rational();
	
	void print(){cout << num << "/" << den;}
	friend ostream& operator<<(ostream& os, const Rational &r){os << r.num << "/" << r.den; return os;}
	void operator=(Rational r){num = r.num; den = r.den;}
	void operator=(int i){num = i; den = 1;}
	void operator=(double db);
	bool operator==(Rational r){return (num == r.num && den == r.den);}
	bool operator==(int i){return (num == i && den == 1);}
	bool operator==(double db);
	Rational operator+(Rational r){return normal(num*r.den + r.num*den, den*r.den);}
	Rational operator+(int i){return normal(num + i*den, den);}
	Rational operator+(double db){return *this + doubleToRational(db);}
	Rational operator-(Rational r){return normal(num*r.den - r.num*den, den*r.den);}
	Rational operator-(int i){return normal(num - i*den, den);}	
	Rational operator-(double db){return *this - doubleToRational(db);}
	Rational operator*(Rational r){return normal(num*r.num, den*r.den);}
	Rational operator*(int i){Rational r(i, den); r.num *= num; return r;}
	Rational operator*(double db){return *this * doubleToRational(db);}
	Rational operator/(Rational r);
	operator int(){return num/den;}
	operator double(){return (double)num/(double)den;}
private:
	Rational normal(int n, int d){int g = gcd(num,den); return Rational(n/g, d/g);}
	void normalize(){int g = gcd(num,den); num/=g, den/=g;}
	Rational doubleToRational(double db);
	int gcd(int a, int b){return (b == 0) ? a : gcd (b, a % b);}
	int num;
	int den;
};

#endif