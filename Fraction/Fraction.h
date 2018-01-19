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

	bool operator<(Fraction f){return (double)num*f.den < (double)f.num*den;}
	bool operator<(int i){return num < (double)i*den;}
	bool operator<(long l){return num < (double)l*den;}
	bool operator<(double db){return num < db*den;}

	bool operator>(Fraction f){return (double)num*f.den > (double)f.num*den;}	//to avoid overflow
	bool operator>(int i){return num > (double)i*den;}
	bool operator>(long l){return num > (double)l*den;}
	bool operator>(double db){return num > db*den;}

	bool operator<=(Fraction f){return *this == f || *this < f;}
	bool operator<=(int i){return *this == i || *this < i;}
	bool operator<=(long l){return *this == l || *this < l;}
	bool operator<=(double db){return *this == db || *this < db;}
	
	bool operator>=(Fraction f){return *this > f || *this == f;}
	bool operator>=(int i){return *this > i || *this == i;}
	bool operator>=(long l){return *this > l || *this == l;}
	bool operator>=(double db){return *this > db || *this == db;}

	Fraction operator-(){return Fraction(-num,den);}
	
	// a = f.den * num, b = den * f.num, f.den * den, b + a  <= LONG_MAX
	// f.num * den + num * f.den, f.den * den
	Fraction operator+(Fraction f);
	Fraction operator+(int i){return normal(num + i*den, den);}
	Fraction operator+(long l){return normal(num + l*den, den);}
	Fraction operator+(double db){return *this + doubleToFraction(db);}

	void operator+=(Fraction f){*this = *this + f;}
	void operator+=(int i){num += i*den; normalize();}
	void operator+=(long l){num += l*den; normalize();}
	void operator+=(double db){*this += doubleToFraction(db);}

	Fraction operator-(Fraction f);
	Fraction operator-(long i){return normal(num - i*den, den);}	
	Fraction operator-(int l){return normal(num - l*den, den);}	
	Fraction operator-(double db){return *this - doubleToFraction(db);}

	void operator-=(Fraction f){*this = *this + (-f);}
	void operator-=(int i){num -= i*den; normalize();}
	void operator-=(long l){num -= l*den; normalize();}
	void operator-=(double db){*this -= doubleToFraction(db);}

	// num * f.num < max => num < max/f.num => check if num >= max/f.num
	Fraction operator*(Fraction f);
	Fraction operator*(int i){Fraction f(i, den); f.num *= num; return f;}
	Fraction operator*(long l){Fraction f(l, den); f.num *= num; return f;}
	Fraction operator*(double db){return *this * doubleToFraction(db);}

	void operator*=(Fraction f){*this = *this * f;}
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
double pow(long l, Fraction f);	
double pow(double db, Fraction f);

Fraction root(Fraction f, long l);

double logb(Fraction f, long base);
double log(Fraction f);
double log10(Fraction f);

inline double root(long base, long root)
{
	//aproxing log_root(base)
	double s=1, t = base/root,r;
	for(int i = 0; i < root*2 && s <= t; i++)
	{
		r = pow((t+s)/root, root);
		if(r < base)
			s = (t+s)/root;
		if(r > base)
			t = (t+s)/root;
		if(r == base)
			return t+s/root;
	}
	Fraction x = t+s/root;

	//second: Newton
	Fraction a,b,d, prevX = 0;
	double c;
	a(1,root);
	//cout << "a: " << a << endl;

	
	//cout << "x: " << x << endl;

	int cont = 0;
	double dif = base;
	//cout << "	****	dist = " << (double)abs(x - prevX) << endl << endl;
	while((double)abs(x - prevX) > 1e-14 && abs(x - prevX) < dif && cont < 100000)
	{
		try
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
		catch(exception& e)
		{
			cout << "vars: " << endl;
			cout << "	x = " << x << endl;
			cout << "	b = " << b << endl;
			b = b * x; //if fails, shows x and b;
			cout << "	c = " << c << endl;
			c = pow(x,root-1);
			cout << "	d = " << d << endl;
			d(base, round(c));
			cout << "(b + d)" << (b + d) << endl;
			cout << "fail when performing a*(b+d)" << endl;
			x = a * (b + d);
		}
	}

	if (abs(x - prevX) >= dif)
	{
		cout << "	*** actualDif: " << (double)abs(x - prevX) << " , prevDif: " << dif << endl;
		return (double)prevX;
	}

	//cout << "	 -- : " << (double)abs(x - prevX) << " , " << dif << " , " << cont << endl;

	return (double)x;
}

inline long doublesIn(double first, double last) 
{
    long res;

	// *reinterpret_cast<long *>(&first) return the bit pattern representing a double as a 64-bit unsigned integer.
    res = *reinterpret_cast<long *>(&last) - *reinterpret_cast<long *>(&first);
    return res;
}

//this should give the density of fractions between first and last, or less.
inline double fractionsIn(unsigned long long first, unsigned long long last) 
{
    double pi = 3.141592653589793238462643383279502884;
    double max = LONG_MAX;	//i can't use LONG_MAX directly
    double zeroToOne = max/pi * max/pi * 3;	// = approx. amount of numbers in Farey's secuence of order LONG_MAX. 
    double res = 0;

    if(first == 0)
    {
        res = zeroToOne;
        first++;
    }

    for(double i = first; i < last; i++)
    {
        res += zeroToOne/(i * i+1);
        if(i == i+1)
            i = nextafter(i+1, last);	//if this happens, i might not count some fractions, but i have no other choice
    }
	
    return floor(res);
}

#endif