#include "Fraction.h"



Fraction::Fraction(long n, long d)
{
	if(d < 0)
	{
		den = -den;
		num = -num;
	}
	if(d != 0)
	{
		long g = gcd(n,d);
		num=n/g;
		den=d/g;
	}
	else
		cout << "Error: denominador = 0;";
}

Fraction::~Fraction(){}

void Fraction::operator=(double db)
{
	long decimals = 0;
	while(db != floor(db))
	{
		db *= 10;
		decimals++;
	}
	num = db;
	den = pow(10,decimals);
	normalize();
}

bool Fraction::operator==(double db)
{
	return *this == doubleToFraction(db);
}

Fraction Fraction::operator/(Fraction r)
{
	if(r.num != 0)
		return normal(num*r.den, den*r.num);
	else
	{
		cout << "Error: division por 0";
		return Fraction(1,1);
	}
}

Fraction Fraction::operator/(long i)
{
	if(i != 0)
	{
		Fraction r(num, i);
		r.den *= den;
		return r;
	}
	else
	{
		cout << "Error: division por 0";
		return Fraction(1,1);
	}
}

Fraction Fraction::operator/(int i)
{
	if(i != 0)
	{
		Fraction r(num, i);
		r.den *= den;
		return r;
	}
	else
	{
		cout << "Error: division por 0";
		return Fraction(1,1);
	}
}


Fraction Fraction::doubleToFraction(double db)
{
	if(db*9 == floor(db*9))
		return Fraction(db*9,9);	//actually, i should chech for shortest period (cycle detection) to chech if it's a periodic number 
	long decimals = 0;
	while(db != floor(db))
	{
		db *= 10;
		decimals++;
	}
	return Fraction(db, pow(10,decimals));
}