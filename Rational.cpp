#include "Rational.h"



Rational::Rational(int n, int d)
{
	if(d < 0)
	{
		den = -den;
		num = -num;
	}
	if(d != 0)
	{
		int g = gcd(n,d);
		num=n/g;
		den=d/g;
	}
	else
		cout << "Error: denominador = 0;";
}

Rational::~Rational(){}

void Rational::operator=(double db)
{
	int decimals = 0;
	while(db != floor(db))
	{
		db *= 10;
		decimals++;
	}
	num = db;
	den = pow(10,decimals);
}

bool Rational::operator==(double db)
{
	return *this == doubleToRational(db);
}

Rational Rational::operator/(Rational r)
{
	if(r.num != 0)
		return normal(num*r.den, den*r.num);
	else
	{
		cout << "Error: division por 0";
		return Rational(1,1);
	}
}

Rational Rational::doubleToRational(double db)
{
	int decimals = 0;
	while(db != floor(db))
	{
		db *= 10;
		decimals++;
	}
	return Rational(db, pow(10,decimals));
}