#include "Fraction.h"
#include <exception>

class dividedByZero: public exception
{
  virtual const char* what() const throw()
  {
    return "Error: Fraction divided by 0.";
  }
} divByZ;

class dividendIsZero: public exception
{
  virtual const char* what() const throw()
  {
    return "Error: Dividend is 0.";
  }
} divZ;

Fraction::Fraction(long n, long d)
{
	num = n;
	den = d;
	normalize();
}

Fraction::Fraction(vector<long> v)
{
	if(v.size() == 0)
	{
		num = 0;
		den = 1;
	}
	else
	{
		Fraction d = v[v.size()-1]-1;
		for(int i = v.size()-2; i >= 0; i--)
		{
			d.invert();
			d += v[i];
		}
		*this = d;
	}
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

		//if absolute values are way too big, they create a lot of problems. LONG_MIN is a specific troublesome case.
		if(d < -1e18)
		{
			long double fix, max17 = 99999999999999999;
			if(n > 0)	//i'm doing this because abs(LONG_MIN) is still LONG_MIN (overflow, LONG_MIN = - LONG_MAX + 1)
			{
				if(-n >= d)	//I'll reduce both numbers to as much as 17 digits.
				{
					fix = d/max17;
					d = max17;
					n = round(n/fix);
				}
				else
				{
					fix = n/max17;
					n = max17;
					d = round(d/fix);
				}
			}
			else
			{
				if(n > d)
				{
					fix = d/max17;
					d = max17;
					n = round(n/fix);
				}
				else
				{
					fix = n/max17;
					n = max17;
					d = round(d/fix);
				}
			}
		}
		if(d > 1e18)
		{
			long double fix, max17 = 99999999999999999;
			if(n > 0)
			{
				if(d >= n)
				{
					fix = d/max17;
					d = max17;
					n = round(n/fix);
				}
				else
				{
					fix = n/max17;
					n = max17;
					d = round(d/fix);
				}
			}
			else
			{
				if(-d < n)
				{
					fix = d/max17;
					d = max17;
					n = round(n/fix);
				}
				else
				{
					fix = n/max17;
					n = max17;
					d = round(d/fix);
				}
			}
		}
		long g = gcd(n,d); 
		g = abs(g);	//another thing needed to avoid SIGFPE
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
		throw divZ;
}

void Fraction::normalize()
{
	if(den != 0)
	{
		if(num == 0)
			den = 1;
		else
		{
			//if absolute values are way too big, they create a lot of problems. LONG_MIN is a specific troublesome case.
			if(den < -1e18)
			{
				long double fix, max17 = 99999999999999999;
				if(num > 0)	//i'm doing this because abs(LONG_MIN) is still LONG_MIN
				{
					if(-num > den)
					{
						fix = den/max17;
						den = max17;
						num = round(num/fix);
					}
					else
					{
						fix = num/max17;
						num = max17;
						den = round(den/fix);
					}
				}
				else
				{
					if(num > den)
					{
						fix = den/max17;
						den = max17;
						num = round(num/fix);
					}
					else
					{
						fix = num/max17;
						num = max17;
						den = round(den/fix);
					}
				}
			}
			if(den > 1e18)	//if absolute values are way too big, they create a lot of problems
			{
				long double fix, max17 = 99999999999999999;
				if(num > 0)
				{
					if(den > num)
					{
						fix = den/max17;
						den = max17;
						num = round(num/fix);
					}
					else
					{
						fix = num/max17;
						num = max17;
						den = round(den/fix);
					}
				}
				else
				{
					if(-den < num)
					{
						fix = den/max17;
						den = max17;
						num = round(num/fix);
					}
					else
					{
						fix = num/max17;
						num = max17;
						den = round(den/fix);
					}
				}
			}

			long g = gcd(num,den); 
			g = abs(g);	//another thing needed to avoid SIGFPE
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
		throw divZ;
}

void Fraction::operator=(vector<long> v)
{
	*this = fromContinuedForm(v);
}

Fraction invert(Fraction f)
{
	if(f.numerator() == 0) 
		throw divZ; 
	
	return Fraction(f.denominator(),f.numerator());
}

void Fraction::invert()
{
	if(num == 0) 
		throw divZ; 
	
	swap(num,den);
}

Fraction Fraction::operator+(Fraction f)
{
	double lcm = max(den,f.den);
	lcm /= gcd(den, f.den);
	lcm *= min(den,f.den);

	// a/c + b/d = [a*(lcd/d) + b*(lcd/c)] / lcd	//use to create normal fractions

	// a/c + b/d = [a/lcd * (lcd/c)] + [b/lcd * (lcd/d)]	//use to create fractions through double
	double p = (double)num;
	p *= lcm / (double)den;
	double q = (double)f.num;
	q *= lcm / (double)f.den;

	if(lcm >= LONG_MAX || (p + q) >= LONG_MAX)	//tested in testOverflow() over tests.cpp
	{
		//cerr << "Aproximating " << num << "/" << den << " + " << f.num << "/" << f.den << endl;
		p = (double)num / lcm;
		p *= lcm / (double)den;
		q = (double)f.num / lcm;
		q *= lcm / (double)f.den;
		return Fraction(p + q);
	}
	else
		return normal(p + q, (long)lcm);
}

Fraction Fraction::operator-(Fraction f)
{
	double lcm = max(den,f.den);
	lcm /= gcd(den, f.den);
	lcm *= min(den,f.den);

	// a/c + b/d = [a*(lcd/d) + b*(lcd/c)] / lcd	//use to create normal fractions

	// a/c + b/d = [a/lcd * (lcd/c)] + [b/lcd * (lcd/d)]	//use to create fractions through double
	double p = (double)num;
	p *= lcm / (double)den;
	double q = (double)f.num;
	q *= lcm / (double)f.den;

	if(lcm >= LONG_MAX || (p - q) >= LONG_MAX)	//tested in testOverflow() over tests.cpp
	{
		//cerr << "Aproximating " << num << "/" << den << " - " << f.num << "/" << f.den << endl;
		p = (double)num / lcm;
		p *= lcm / (double)den;
		q = (double)f.num / lcm;
		q *= lcm / (double)f.den;
		return Fraction(p - q);
	}
	else
		return normal(p - q, (long)lcm);
}

Fraction Fraction::operator*(Fraction f)
{
	//check for simplifications

	Fraction a = normal(f.num,den);
	Fraction b = normal(num, f.den);
	
	if(b.num == 0) return Fraction(0);
	if(LONG_MAX/abs(b.num) <= abs(num) || LONG_MAX/abs(b.den) <= abs(den))
	{
		double newDen = a.den;
		newDen *= b.den;
		double newNum = max(a.num, b.num) / newDen;
		newNum *= min(a.num, b.num);
		Fraction h(newNum);
		return h;
	}
	else
		return Fraction(a.num*b.num, a.den*b.den);
}

Fraction Fraction::operator/(Fraction f)
{
	if(f.num != 0)
	{
		//check for simplifications

		Fraction a = normal(num, f.num);
		Fraction b = normal(f.den, den);
		
		if(b.num == 0) return Fraction(0);	//should NEVER happen: b is f.den/den so both should be non-zero
		if(LONG_MAX/abs(b.num) <= abs(num) || LONG_MAX/abs(b.den) <= (den))
		{
			double newDen = a.den;
			newDen *= b.den;
			double newNum = max(a.num, b.num) / newDen;
			newNum *= min(a.num, b.num);
			Fraction h(newNum);
			return h;
		}
		else
			return Fraction(a.num*b.num, a.den*b.den);
	}
	else
		throw divByZ;
}

Fraction fromContinuedForm(vector<long> v)
{
	if(v.size() == 0)
	{
		return Fraction(1,0);
	}
	else
	{
		Fraction d = v[v.size()-1]-1;
		for(int i = v.size()-2; i >= 0; i--)
		{
			d.invert();
			d += v[i];
		}
		return Fraction(d);
	}
}

void Fraction::operator/=(Fraction f)
{
	*this = *this / f;
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
		throw divByZ;
}

void Fraction::operator/=(long l)
{
	if(l != 0)
	{
		den*=l;
		normalize();
	}
	else
		throw divByZ;
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
		throw divByZ;
}

void Fraction::operator/=(int i)
{
	if(i != 0)
	{
		den*=i;
		normalize();
	}
	else
		throw divByZ;
}

vector<long> Fraction::continuedForm()
{
	vector<long> res;
	long integerPart;
	Fraction d(num,den);
	double maxSize = floor(log2(den)/log2(1.61));

	while(abs(d) > 1e-8 && res.size() < maxSize)
	{
		integerPart = (long)d;
		res.push_back(integerPart);
		d -= integerPart;
		if(abs(d) > 1e-8)
			d.invert();
	}
	res[res.size()-1] += 1;	//format standard
	return res;
}

Fraction pow(Fraction f, long l)
{
	double n = pow(f.numerator(), l);
	double d = pow(f.denominator(), l);
	return Fraction(n/d);	

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

Fraction pow(Fraction base, Fraction exp)
{
	Fraction f = pow(base, exp.numerator());
	f = root(f,exp.denominator());
	return f;
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
	double res = log2(f.numerator())/log2(base);	//log2 is faster than log and log10
	res -= log2(f.denominator())/log2(base);
	return res;
}
double log(Fraction f)
{
	double res = log((double)f.numerator());
	res -= log((double)f.denominator());
	return res;
}
double log2(Fraction f)
{
	double res = log2((double)f.numerator());
	res -= log2((double)f.denominator());
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
    double maxError =  value * 1e-15;	//max accuracy for double: 1e-15. For long double should be 1e-18.

    double integer = floor(value);
    double decimal = value - integer;

    if (decimal < 1e-15)
        return Fraction((long)integer*sign, 1);

    if (decimal > 1 - 1e-15)
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