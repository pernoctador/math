#ifndef _Fraction_H_
#define _Fraction_H_


#include "../utilities/math_utilities.h"
#include <cmath> 	//better than math.h
#include <iostream>
#include <climits>	//LONG_MAX
#include <string>
#include <string>
#include <vector>

typedef unsigned long ulong;
typedef long long llong;
typedef llong T_integer;	//use this if you want to change the type of Function, but beware of unforseen consecuences like accuracy.

const double FRAC_MIN = (double)1/(double)LLONG_MAX;	//remember to change this if you change the types
const T_integer FRAC_MAX = LLONG_MAX;

using namespace std;

class Fraction {
public:

	Fraction(){num = 0; den = 1;}
	Fraction(int n){num = n; den = 1;}
	Fraction(long n){num = n; den = 1;}
	Fraction(ulong n){num = n; den = 1;}
	Fraction(llong n){num = n; den = 1;}
	Fraction(const Fraction& f){num = f.num; den = f.den;}
	Fraction(int n, int d){num = n; den = d; normalize();}
	Fraction(long n, long d){num = n; den = d; normalize();}
	Fraction(llong n, llong d){num = n; den = d; normalize();}
	Fraction(double db){*this = doubleToFraction(db);}
	Fraction(vector<T_integer>);
	~Fraction();

	T_integer numerator(){return num;}
	T_integer denominator(){return den;}
	
	void print(){if(den > 1){cout << num << "/" << den;}else{cout << num;}}
	friend ostream& operator<<(ostream& os, const Fraction &f){if(f.den > 1){os << f.num << "/" << f.den;}else{os << f.num;}return os;}

	Fraction& operator()(int n, int d);
	Fraction& operator()(long n, long d);
	Fraction& operator()(long long n, long long d);
	Fraction& operator()(double db){*this = doubleToFraction(db); return *this;}

	void operator=(Fraction f){num = f.num; den = f.den;}
	void operator=(int i){num = i; den = 1;}
	void operator=(unsigned i){num = i; den = 1;}
	void operator=(long l){num = l; den = 1;}
	void operator=(llong l){num = l; den = 1;}
	void operator=(double db){*this = doubleToFraction(db);}
	void operator=(vector<T_integer> v);

	bool operator==(Fraction f){return (num == f.num && den == f.den);}
	bool operator==(int i){return (num == i && den == 1);}
	bool operator==(unsigned i){return (num == (T_integer)i && den == 1);}
	bool operator==(long i){return (num == i && den == 1);}
	bool operator==(llong i){return (num == i && den == 1);}
	bool operator==(double db){return *this == doubleToFraction(db);}

	bool operator!=(Fraction f){return !(*this == f);}
	bool operator!=(int i){return !(*this == i);}
	bool operator!=(unsigned i){return !(*this == i);}
	bool operator!=(long l){return !(*this == l);}
	bool operator!=(llong l){return !(*this == l);}
	bool operator!=(double db){return !(*this == db);}

	bool operator<(Fraction f){return (double)num*f.den < (double)f.num*den;}
	bool operator<(int i){return num < (double)i*den;}
	bool operator<(unsigned i){return num < (double)i*den;}
	bool operator<(long l){return num < (double)l*den;}
	bool operator<(llong l){return num < (double)l*den;}
	bool operator<(double db){return num < db*den;}

	bool operator>(Fraction f){return (double)num*f.den > (double)f.num*den;}	//to avoid overflow
	bool operator>(int i){return num > (double)i*den;}
	bool operator>(unsigned i){return num > (double)i*den;}
	bool operator>(long l){return num > (double)l*den;}
	bool operator>(llong l){return num > (double)l*den;}
	bool operator>(double db){return num > db*den;}

	bool operator<=(Fraction f){return *this == f || *this < f;}
	bool operator<=(int i){return *this == i || *this < i;}
	bool operator<=(unsigned i){return *this == i || *this < i;}
	bool operator<=(long l){return *this == l || *this < l;}
	bool operator<=(llong l){return *this == l || *this < l;}
	bool operator<=(double db){return *this == db || *this < db;}
	
	bool operator>=(Fraction f){return *this > f || *this == f;}
	bool operator>=(int i){return *this > i || *this == i;}
	bool operator>=(unsigned i){return *this > i || *this == i;}
	bool operator>=(long l){return *this > l || *this == l;}
	bool operator>=(llong l){return *this > l || *this == l;}
	bool operator>=(double db){return *this > db || *this == db;}

	Fraction operator-(){return Fraction(-num,den);}

	Fraction operator+(Fraction f);
	Fraction operator+(int i){return normal(num + i*den, den);}
	Fraction operator+(unsigned i){return normal(num + i*den, den);}
	Fraction operator+(long l){return normal(num + l*den, den);}
	Fraction operator+(llong l){return normal(num + l*den, den);}
	Fraction operator+(double db){return *this + doubleToFraction(db);}

	void operator+=(Fraction f){*this = *this + f;}
	void operator+=(int i){num += i*den; normalize();}
	void operator+=(unsigned i){num += i*den; normalize();}
	void operator+=(long l){num += l*den; normalize();}
	void operator+=(llong l){num += l*den; normalize();}
	void operator+=(double db){*this += doubleToFraction(db);}

	Fraction operator-(Fraction f);
	Fraction operator-(llong i){return normal(num - i*den, den);}
	Fraction operator-(long i){return normal(num - i*den, den);}
	Fraction operator-(unsigned i){return normal(num - i*den, den);}
	Fraction operator-(int l){return normal(num - l*den, den);}
	Fraction operator-(double db){return *this - doubleToFraction(db);}

	void operator-=(Fraction f){*this = *this + (-f);}
	void operator-=(int i){num -= i*den; normalize();}
	void operator-=(unsigned i){num -= i*den; normalize();}
	void operator-=(long l){num -= l*den; normalize();}
	void operator-=(llong l){num -= l*den; normalize();}
	void operator-=(double db){*this -= doubleToFraction(db);}

	// num * f.num < max => num < max/f.num => check if num >= max/f.num
	Fraction operator*(Fraction f);
	Fraction operator*(int i){Fraction f((T_integer)i, den); f.num *= num; return f;}
	Fraction operator*(unsigned i){Fraction f((T_integer)i, den); f.num *= num; return f;}
	Fraction operator*(long l){Fraction f((T_integer)l, den); f.num *= num; return f;}
	Fraction operator*(llong l){Fraction f((T_integer)l, den); f.num *= num; return f;}
	Fraction operator*(double db){return *this * doubleToFraction(db);}

	void operator*=(Fraction f){*this = *this * f; normalize();}
	void operator*=(int i){num *= i; normalize();}
	void operator*=(unsigned i){num *= i; normalize();}
	void operator*=(long l){num *= l; normalize();}
	void operator*=(llong l){num *= l; normalize();}
	void operator*=(double db){*this *= doubleToFraction(db);}

	Fraction operator/(Fraction);
	Fraction operator/(int);
	Fraction operator/(unsigned);
	Fraction operator/(long);
	Fraction operator/(llong);
	Fraction operator/(double db){return *this / doubleToFraction(db);}

	void operator/=(Fraction);
	void operator/=(int);
	void operator/=(unsigned);
	void operator/=(long);
	void operator/=(llong);
	void operator/=(double db){*this /= doubleToFraction(db);}

	void invert();

	Fraction idiv(T_integer i, Fraction& f){return normal(f.denominator()*i, f.numerator());}	//not very usefull, as i / f = 1/f * i

	vector<T_integer> continuedForm();

	operator int(){return num/den;}
	operator unsigned(){return abs(num)/den;}
	operator long(){return num/den;}
	operator llong(){return num/den;}
	operator double(){return (double)num/(double)den;}

Fraction fromContinuedForm(vector<T_integer>);

private:	
	Fraction doubleToFraction(double db);
	Fraction normal(T_integer n, T_integer d);
	void normalize();
	
	T_integer gcd(T_integer a, T_integer b){return (b == 0) ? a : gcd (b, a % b);}
	T_integer num;
	T_integer den;
};

inline Fraction abs(Fraction f) //abs(Fraction& f) gives weird compiler errors
{
	if(f < 0)
	{
		Fraction r;
		return r(0-f.numerator(), f.denominator());
	}
	else
		return f;
}

Fraction invert(Fraction f);

Fraction pow(Fraction f, T_integer l);
Fraction pow(Fraction base, Fraction exp);
double pow(T_integer l, Fraction f);	
double pow(double db, Fraction f);

Fraction root(Fraction f, T_integer l);

double logb(Fraction f, T_integer base);
double log(Fraction f);
double log2(Fraction f);
double log10(Fraction f);

#endif