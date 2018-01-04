#ifndef _Fraction_H_
#define _Fraction_H_


#include "../utilities/math_utilities.h"
#include <cmath> 	//better than math.h
#include <iostream>
#include <climits>	//LONG_MAX

using namespace std;


const double FRAC_MIN = (double)1/(double)LONG_MAX;
const long FRAC_MAX = LONG_MAX;

//FUTURE WORK: use ulong instead of long. long long is not needed, as long in a 64x processor is transformed into long long.

class Fraction {	
public:

	Fraction(){num = 1; den = 1;}
	Fraction(int n){num = n; den = 1;}
	Fraction(long n){num = n; den = 1;}
	Fraction(const Fraction& f){num = f.num; den = f.den;}
	Fraction(long n, long d);
	Fraction(double db){*this = doubleToFraction(db);}
	~Fraction();

	long numerator(){return num;}
	long denominator(){return den;}
	
	void print(){if(den > 1){cout << num << "/" << den;}else{cout << num;}}
	friend ostream& operator<<(ostream& os, const Fraction &f){if(f.den > 1){os << f.num << "/" << f.den;}else{os << f.num;}return os;}

	Fraction& operator()(long a, long b);
	Fraction& operator()(double db){*this = doubleToFraction(db); return *this;}

	void operator=(Fraction f){num = f.num; den = f.den;}
	void operator=(int i){num = i; den = 1;}
	void operator=(long l){num = l; den = 1;}
	void operator=(double db){*this = doubleToFraction(db);}

	bool operator==(Fraction f){return (num == f.num && den == f.den);}
	bool operator==(int i){return (num == i && den == 1);}
	bool operator==(long i){return (num == i && den == 1);}
	bool operator==(double db){return *this == doubleToFraction(db);}

	bool operator!=(Fraction f){return !(*this == f);}
	bool operator!=(int i){return !(*this == i);}
	bool operator!=(long l){return !(*this == l);}
	bool operator!=(double db){return !(*this == db);}

	bool operator<(Fraction f){return num*f.den < f.num*den;}
	bool operator<(int i){return num < i*den;}
	bool operator<(long l){return num < l*den;}
	bool operator<(double db){return num < db*den;}

	bool operator>(Fraction f){return num*f.den > f.num*den;}
	bool operator>(int i){return num > i*den;}
	bool operator>(long l){return num > l*den;}
	bool operator>(double db){return num > db*den;}

	bool operator<=(Fraction f){return *this < f || *this == f;}
	bool operator<=(int i){return *this < i || *this == i;}
	bool operator<=(long l){return *this < l || *this == l;}
	bool operator<=(double db){return *this < db || *this == db;}
	
	bool operator>=(Fraction f){return *this > f || *this == f;}
	bool operator>=(int i){return *this > i || *this == i;}
	bool operator>=(long l){return *this > l || *this == l;}
	bool operator>=(double db){return *this > db || *this == db;}
	
	Fraction operator+(Fraction f){
		if(LONG_MAX/num <= f.den || LONG_MAX/f.num <= den || LONG_MAX/den <= f.den || LONG_MAX-num*f.den >= f.num*den)	//mmm better check this 
		{
			double d = den*f.den;
			double a = (double)(num/d)*f.den;
			double b = (double)(f.num/d)*den;
			return Fraction(a+b);
		}
		else
			return normal(num*f.den + f.num*den, den*f.den);
	}
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

	// num * f.num < max => num < max/f.num => check if num >= max/f.num
	Fraction operator*(Fraction f){
		//check for simplifications

		Fraction a = normal(f.num,den);
		Fraction b = normal(num, f.den);
		
		if(LONG_MAX/b.num <= num || LONG_MAX/b.den <= den)
		{
			cerr << "aproximating " << a.num << "/" << a.den << " * " << b.num << "/" << b.den;
			double newDen = a.den;
			newDen *= b.den;
			double newNum = max(a.num, b.num) / newDen;
			newNum *= min(a.num, b.num);
			Fraction h(newNum);
			cerr << " as " << h << endl;
			return h;
		}
		else
			return Fraction(a.num*b.num, a.den*b.den);
	}

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

	Fraction invert(){return Fraction(den,num);}

	Fraction idiv(long i, Fraction& f){return normal(f.denominator()*i, f.numerator());}	//not very usefull, as i / f = 1/f * i

	
	operator int(){return num/den;}
	operator long(){return num/den;}
	operator double(){return (double)num/(double)den;}

private:	
	Fraction doubleToFraction(double db);
	Fraction normal(long n, long d);
	void normalize();
	
	long gcd(long a, long b){return (b == 0) ? a : gcd (b, a % b);}
	long num;
	long den;
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

Fraction pow(Fraction f, long l);
Fraction pow(Fraction base, Fraction exp);
double pow(long l, Fraction f);	//pow(x,1.0/root) is not very good to find roots, maybe a Newton would be better.
double pow(double db, Fraction f);

Fraction root(Fraction f, long l);

double logb(Fraction f, long base);
double log(Fraction f);
double log10(Fraction f);

inline double root(long base, long root)
{
	Fraction x(base,root);	//maybe binary search?

	/*
	double i = base/root;
	while(true)
	{
		if(pow(i,root) < base)
			i + (base - );
		else
		{
			if(pow(i,root) > base)
				i--;
			else
				break;
	}
	*/

	//second: Newton
	Fraction a,b,d, prevX = 0;
	double c;
	a(1,root);
	//cout << "a: " << a << endl;

	
	//cout << "x: " << x << endl;

	int cont = 0;
	double dif = base;
	//cout << "	****	dist = " << (double)abs(x - prevX) << endl << endl;
	while((double)abs(x - prevX) > 1e-14 && abs(x - prevX) < dif && cont < 1000)
	{
		dif = (double)abs(x - prevX);
		prevX = x;
		cont++;

		b((root-1));
		b = b * x;
		//cout << "b: " << b << endl;
		c = pow(x,root-1);
		//cout << "c: " << c << endl;
		//cout << c << " = pow(" << x << ", " << root-1 << ")" << endl;
		d(base, round(c));
		//cout << "d: " << d << endl;
		x = a * (b + d);
		//cout << "x: " << x << " = " << (double)x << " , prevX = " << prevX << endl << endl;
		//cout << "	****	dist = " << (double)abs(x - prevX) << endl << endl;
	}

	if (abs(x - prevX) >= dif)
	{
		//cout << "*** actualDif: " << (double)abs(x - prevX) << " , prevDif: " << dif << endl;
		return (double)prevX;
	}

	//cout << " -- : " << (double)abs(x - prevX) << " , " << dif << " , " << cont << endl;

	return (double)x;
}

#endif