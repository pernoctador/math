#ifndef _Fraction_H_
#define _Fraction_H_

#include <math.h>
#include <assert.h>
#include <utility>
#include <stdlib.h>     /* srand, rand */
#include <climits>
#include <vector>
#include <iostream>
using namespace std;

class Fraction {
public:
	Fraction(){num = 1; den = 1;}
	Fraction(long n){num = n; den = 1;}
	Fraction(const Fraction& r){num = r.num; den = r.den;}
	Fraction(long n, long d);
	~Fraction();
	
	void print(){cout << num << "/" << den;}
	friend ostream& operator<<(ostream& os, const Fraction &r){os << r.num << "/" << r.den; return os;}
	void operator=(Fraction r){num = r.num; den = r.den;}
	void operator=(int i){num = i; den = 1;}
	void operator=(long i){num = i; den = 1;}
	void operator=(double db);

	bool operator==(Fraction r){return (num == r.num && den == r.den);}
	bool operator==(int i){return (num == i && den == 1);}
	bool operator==(long i){return (num == i && den == 1);}
	bool operator==(double db);

	bool operator!=(Fraction r){return !(*this==r);}
	bool operator!=(int i){return !(*this==i);}
	bool operator!=(long i){return !(*this==i);}
	bool operator!=(double db){return !(*this==db);}

	bool operator<(Fraction r){return num*r.den < r.num*den;}
	bool operator<(int i){return num < i*den;}
	bool operator<(long i){return num < i*den;}
	bool operator<(double db){return num < db*den;}

	bool operator>(Fraction r){return num*r.den > r.num*den;}
	bool operator>(int i){return num < i*den;}
	bool operator>(long i){return num < i*den;}
	bool operator>(double db){return num < db*den;}
	
	Fraction operator+(Fraction r){return normal(num*r.den + r.num*den, den*r.den);}
	Fraction operator+(int i){return normal(num + i*den, den);}
	Fraction operator+(long i){return normal(num + i*den, den);}
	Fraction operator+(double db){return *this + doubleToFraction(db);}

	Fraction operator-(Fraction r){return normal(num*r.den - r.num*den, den*r.den);}
	Fraction operator-(long i){return normal(num - i*den, den);}	
	Fraction operator-(int i){return normal(num - i*den, den);}	
	Fraction operator-(double db){return *this - doubleToFraction(db);}

	Fraction operator*(Fraction r){return normal(num*r.num, den*r.den);}
	Fraction operator*(int i){Fraction r(i, den); r.num *= num; return r;}
	Fraction operator*(long i){Fraction r(i, den); r.num *= num; return r;}
	Fraction operator*(double db){return *this * doubleToFraction(db);}

	Fraction operator/(Fraction r);
	Fraction operator/(int i);
	Fraction operator/(long i);
	Fraction operator/(double db){return *this / doubleToFraction(db);}
	
	operator int(){return num/den;}
	operator long(){return num/den;}
	operator double(){return (double)num/(double)den;}
private:
	Fraction normal(long n, long d){long g = gcd(num,den); return Fraction(n/g, d/g);}
	void normalize(){long g = gcd(num,den); num/=g, den/=g;}
	Fraction doubleToFraction(double db);
	long gcd(long a, long b){return (b == 0) ? a : gcd (b, a % b);}
	long num;
	long den;
};

#endif