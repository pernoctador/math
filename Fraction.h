#ifndef _Fraction_H_
#define _Fraction_H_

#include <cmath> 	//better than math.h
#include <iostream>
#include <climits>

using namespace std;

/*
	I know I could use templates, but it's not the same if I recive an Integer (int, long) or a Floating Point Rational (double).
 I read there is a way using BOOST_STATIC_ASSERT, but it looks a pain in the back for just 3 classes (i don't care for more atm)
*/
const double FRAC_MIN = (double)1/(double)LONG_MAX;
const long FRAC_MAX = LONG_MAX;

class Fraction {	
public:

	Fraction(){num = 1; den = 1;}
	Fraction(long n){num = n; den = 1;}
	Fraction(const Fraction& f){num = f.num; den = f.den;}
	Fraction(long n, long d);
	~Fraction();

	long numerator(){return num;}
	long denominator(){return den;}
	
	void print(){cout << num << "/" << den;}
	friend ostream& operator<<(ostream& os, const Fraction &f){os << f.num << "/" << f.den; return os;}

	Fraction& operator()(long a, long b);

	void operator=(Fraction f){num = f.num; den = f.den;}
	void operator=(int i){num = i; den = 1;}
	void operator=(long l){num = l; den = 1;}
	void operator=(double db);

	bool operator==(Fraction f){return (num == f.num && den == f.den);}
	bool operator==(int i){return (num == i && den == 1);}
	bool operator==(long i){return (num == i && den == 1);}
	bool operator==(double db);

	bool operator!=(Fraction f){return !(*this == f);}
	bool operator!=(int i){return !(*this == i);}
	bool operator!=(long l){return !(*this == l);}
	bool operator!=(double db){return !(*this == db);}

	bool operator<(Fraction f){return num*f.den < f.num*den;}
	bool operator<(int i){return num < i*den;}
	bool operator<(long l){return num < l*den;}
	bool operator<(double db){return num < db*den;}

	bool operator>(Fraction f){return num*f.den > f.num*den;}
	bool operator>(int i){return num < i*den;}
	bool operator>(long l){return num < l*den;}
	bool operator>(double db){return num < db*den;}

	bool operator<=(Fraction f){return *this < f || *this == f;}
	bool operator<=(int i){return *this < i || *this == i;}
	bool operator<=(long l){return *this < l || *this == l;}
	bool operator<=(double db){return *this < db || *this == db;}
	bool operator>=(Fraction f){return *this > f || *this == f;}
	bool operator>=(int i){return *this > i || *this == i;}
	bool operator>=(long l){return *this > l || *this == l;}
	bool operator>=(double db){return *this > db || *this == db;}
	
	Fraction operator+(Fraction f){return normal(num*f.den + f.num*den, den*f.den);}
	Fraction operator+(int i){return normal(num + i*den, den);}
	Fraction operator+(long l){return normal(num + l*den, den);}
	Fraction operator+(double db){return *this + doubleToFraction(db);}

	void operator+=(Fraction f){num *= f.den; num += f.num*den, den*=f.den; normalize();}
	void operator+=(int i){num += i*den; normalize();}
	void operator+=(long l){num += l*den; normalize();}
	void operator+=(double db){*this += doubleToFraction(db);}

	Fraction operator-(Fraction f){return normal(num*f.den - f.num*den, den*f.den);}
	Fraction operator-(long i){return normal(num - i*den, den);}	
	Fraction operator-(int l){return normal(num - l*den, den);}	
	Fraction operator-(double db){return *this - doubleToFraction(db);}

	void operator-=(Fraction f){num *= f.den; num -= f.num*den, den*=f.den; normalize();}
	void operator-=(int i){num -= i*den; normalize();}
	void operator-=(long l){num -= l*den; normalize();}
	void operator-=(double db){*this -= doubleToFraction(db);}

	Fraction operator*(Fraction f){return normal(num*f.num, den*f.den);}
	Fraction operator*(int i){Fraction f(i, den); f.num *= num; return f;}
	Fraction operator*(long l){Fraction f(l, den); f.num *= num; return f;}
	Fraction operator*(double db){return *this * doubleToFraction(db);}

	void operator*=(Fraction f){num *= f.num; den*=f.den; normalize();}
	void operator*=(int i){num *= i; normalize();}
	void operator*=(long l){num *= l; normalize();}
	void operator*=(double db){*this *= doubleToFraction(db);}

	Fraction operator/(Fraction);
	Fraction operator/(int);
	Fraction operator/(long);
	Fraction operator/(double db){return *this / doubleToFraction(db);}

	void operator/=(Fraction);
	void operator/=(int);
	void operator/=(long);
	void operator/=(double db){*this /= doubleToFraction(db);}

	Fraction idiv(int i, Fraction f){return normal(f.den*i, f.num);}	//not very usefull, as i / f = 1/f * i

	Fraction powF(Fraction f, long l);	//unfortunately gives weird error when overloading pow(). Compiler stop finding cmath pow() and only try to match with Fraction::pow()
	double powF(long l, Fraction f);	//don't know how good is pow(x,1/root), maybe a Newton would be better (it's like binary search for real numbers)
	double powF(double db, Fraction f);

	Fraction invert(){return Fraction(den,num);}

	double logb(Fraction f, long base);	//here i had the same problem as pow(), but it got magically fix.. unfortunately i don't know hoy to fix pow() overloading yet
	double log(Fraction f);
	double log10(Fraction f);

	
	operator int(){return num/den;}
	operator long(){return num/den;}
	operator double(){return (double)num/(double)den;}
private:
	Fraction normal(long n, long d){if(d < 0){d = -d;n = -n;}long g = gcd(num,den); return Fraction(n/g, d/g);}
	void normalize(){if(den < 0){den = -den;num = -num;}long g = gcd(num,den); num/=g, den/=g;}
	Fraction doubleToFraction(double db);
	long gcd(long a, long b){return (b == 0) ? a : gcd (b, a % b);}
	long num;
	long den;
};

#endif