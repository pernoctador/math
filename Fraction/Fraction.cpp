#include "Fraction.h"

Fraction::Fraction(long n, long d)
{
	num = n;
	den = d;
	normalize();
}

Fraction::~Fraction(){}

Fraction& Fraction::operator()(long n, long d)
{
	num = n;
	den = d;
	normalize();
	return *this;
}

Fraction Fraction::normal(long n, long d)
{
	if(d != 0)
	{
		if(n == 0)
			return Fraction(0,1);

		long g = gcd(n,d); 
		n/=g; 
		d/=g; 
		if(d < 0)
		{
			d = -d;
			n = -n;
		}
		return Fraction(n,d);
	}
	else
	{
		cout << "Error: denominator = 0" << endl;	//this could be an exception
		return Fraction(0,1);
	}
}

void Fraction::normalize()
{
	if(den != 0)
	{
		if(num == 0)
			den = 1;
		else
		{
			long g = gcd(num,den); 
			num/=g; 
			den/=g; 
			if(den < 0)
			{
				den = -den;
				num = -num;
			}
		}
	}
	else
		cout << "Error: denominator = 0" << endl;	//this could be an exception
}

Fraction Fraction::operator/(Fraction f)
{
	if(f.num != 0)
		return normal(num*f.den, den*f.num);
	else
	{
		cout << "Error: divide by 0" << endl;	//this could be an exception
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
		cout << "Error: divide by 0" << endl;	//this could be an exception
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
		cout << "Error: divide by 0" << endl;	//this could be an exception
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
		cout << "Error: divide by 0" << endl;	//this could be an exception
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
		cout << "Error: divide by 0" << endl;	//this could be an exception
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
		cout << "Error: divide by 0" << endl;	//this could be an exception
}

Fraction pow(Fraction f, long l){
	double n = pow(f.numerator(), l);
	double d = pow(f.denominator(), l);
	return Fraction((long)n,(long)d);
}
double pow(long l, Fraction f)
{
	double res = pow(l, f.numerator());
	double root = 1.0/f.denominator();
	res = pow(res, root);
	Fraction buff(res);	//needed. Otherwise will have an presicion error. i tested pow(27, Fraction(2,3)), it gives me 9 if i do cout, but if i do pow() == 9 returns false.
	return (double)buff;
}
double pow(double db, Fraction f){
	double res = pow(db, f.numerator());
	double root = 1.0/f.denominator();
	res = pow(res, root);
	Fraction buff(res);
	return (double)buff;
}

Fraction root(Fraction f, long l)
{
	double n = pow(f.numerator(), 1.0/l); 
	double d = pow(f.denominator(), 1.0/l); 
	Fraction nf(n); 
	Fraction df(d); 
	return (nf / df);
}

double logb(Fraction f, long base)
{
	double res = log(f.numerator())/log(base);
	res -= log(f.denominator())/log(base);
	return res;
}
double log(Fraction f)
{
	double res = log((double)f.numerator());
	res -= log((double)f.denominator());
	return res;
}
double log10(Fraction f)
{
	double res = log10((double)f.numerator());
	res -= log10((double)f.denominator());
	return res;
}

Fraction Fraction::doubleToFraction(double value)
{
	long sign = (value >= 0);	//0 if value is neg. 1 if 0 or greater
    sign = sign*2 -1;		//0 or 2, then -1 or 1

    value = abs(value);

    // Accuracy is the maximum relative error; convert to absolute maxError
    double maxError =  value * 0.00000000000001;	//doesn't work propperly with more accuracy than 1e-14

    double integer = floor(value);
    double decimal = value - integer;

    if (decimal < 0.00000000000001)
        return Fraction((long)integer*sign, 1);

    if (decimal > 0.99999999999999)
        return Fraction((long)(integer + 1)*sign, 1);

    double z = value;
    long previousDenominator = 0;
    long denominator = 1;
    long numerator, temp;

    do
    {
        z = 1.0 / (z - floor(z));
        temp = denominator;
        denominator = denominator * floor(z) + previousDenominator;
        previousDenominator = temp;
        numerator = round(value * denominator);
    }
    while (abs(value - (double)numerator / (double)denominator) > maxError && z != floor(z));

    return Fraction(numerator * sign, denominator);
}