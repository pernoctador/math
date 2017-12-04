#include "Fraction.h"



Fraction::Fraction(long n, long d)
{
	if(d != 0)
	{
		if(d < 0)
		{
			den = -den;
			num = -num;
		}
		long g = gcd(n,d);
		num=n/g;
		den=d/g;
	}
	else
		cout << "Error: denominador = 0;" << endl;	//this could be an exception
}

Fraction::~Fraction(){}

Fraction& Fraction::operator()(long n, long d)
{
	if(d != 0)
	{
		if(d < 0)
		{
			den = -den;
			num = -num;
		}
		long g = gcd(n,d);
		num=n/g;
		den=d/g;
	}
	else
		cout << "Error: denominador = 0" << endl;	//this could be an exception
	return *this;
}

void Fraction::operator=(double db)
{
	double decimals = 0;
	double ten = 10;
	while(db != floor(db))
	{
		db *= 10;
		decimals++;
	}
	num = db;
	den = pow(ten,decimals);
	normalize();
}

bool Fraction::operator==(double db)
{
	return *this == doubleToFraction(db);
}

Fraction Fraction::operator/(Fraction f)
{
	if(f.num != 0)
		return normal(num*f.den, den*f.num);
	else
	{
		cout << "Error: division por 0" << endl;	//this could be an exception
		return Fraction(1,1);
	}
}

void Fraction::operator/=(Fraction f)
{
	if(f.num != 0)
	{
		num*=f.den;
		den*=f.num;
		normalize();
	}
	else
	{
		cout << "Error: division por 0" << endl;	//this could be an exception
	}
}

Fraction Fraction::operator/(long l)
{
	if(l != 0)
	{
		Fraction f(num, l);
		f.den *= den;
		return f;
	}
	else
	{
		cout << "Error: division por 0" << endl;	//this could be an exception
		return Fraction(1,1);
	}
}

void Fraction::operator/=(long l)
{
	if(l != 0)
	{
		den*=l;
		normalize();
	}
	else
	{
		cout << "Error: division por 0" << endl;	//this could be an exception
	}
}

Fraction Fraction::operator/(int i)
{
	if(i != 0)
	{
		Fraction f(num, i);
		f.den *= den;
		return f;
	}
	else
	{
		cout << "Error: division por 0" << endl;	//this could be an exception
		return Fraction(1,1);
	}
}

void Fraction::operator/=(int i)
{
	if(i != 0)
	{
		den*=i;
		normalize();
	}
	else
	{
		cout << "Error: division por 0" << endl;	//this could be an exception
	}
}

Fraction Fraction::powF(Fraction f, long l){
	double n = pow(f.num, l);
	double d = pow(f.den, l);
	return Fraction((long)n,(long)d);
}
double Fraction::powF(long l, Fraction f)
{
	double res = pow(l, f.num);
	res = pow(res, 1/f.den);
	return res;
}
double Fraction::powF(double db, Fraction f){
	double res = pow(db, f.num);
	res = pow(res, 1/f.den);
	return res;
}

double Fraction::logb(Fraction f, long base)
{
	double res = log(f.num)/log(base);
	res -= log(f.den)/log(base);
	return res;
}
double Fraction::log(Fraction f)
{
	double res = log((double)f.num);
	res -= log((double)f.den);
	return res;
}
double Fraction::log10(Fraction f)
{
	double res = log10((double)f.num);
	res -= log10((double)f.den);
	return res;
}

Fraction Fraction::doubleToFraction(double db)
{
	if(db*9 == floor(db*9))
		return Fraction(db*9,9);	//actually, i should chech for shortest period (cycle detection) to chech if it's a periodic number 
	double decimals = 0;
	while(db != floor(db))
	{
		db *= 10;
		decimals++;
	}
	double ten = 10;
	return Fraction(db, pow(ten,decimals));
}