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

Fraction::Fraction(vector<T_integer> v)
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

Fraction& Fraction::operator()(int n, int d)
{
	num = n;
	den = d;
	normalize();
	return *this;
}

Fraction& Fraction::operator()(long n, long d)
{
	num = n;
	den = d;
	normalize();
	return *this;
}

Fraction& Fraction::operator()(long long n, long long d)
{
	num = n;
	den = d;
	normalize();
	return *this;
}

T_integer neg(T_integer x)
{
	if(x > 0)
		x = -x;
	return x;
}

Fraction Fraction::normal(T_integer n, T_integer d)
{
	return Fraction(n,d);
}

void Fraction::normalize()
{
	if(den == 0)
		throw divZ;
	if(num == 0)
		den = 1;
	else
	{
		//if absolute values are way too big, they create a lot of problems. LONG_MIN is a specific troublesome case.
		if(den < -1e18 || den > 1e18)
		{
			long double fix, max17 = 99999999999999999;
			if(neg(den) <= neg(num))	//i'm doing this because abs(LONG_MIN) is still LONG_MIN (overflow, LONG_MIN = LONG_MAX + 1)
			{
				fix = den/max17;	//I'll reduce both numbers to as much as 17 digits.
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

		T_integer g = gcd(num,den);
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

void Fraction::operator=(vector<T_integer> v)
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

	// a/c + b/d = [a*(lcm/c) + b*(lcm/d)] / lcm	//use to create normal fractions

	// a/c + b/d = [a/lcm * (lcm/c)] + [b/lcm * (lcm/d)]	//use to create fractions through double
	double p = (double)num;
	double q = (double)f.num;
	p *= (lcm / (double)den);
	q *= (lcm / (double)f.den);

	if(lcm >= FRAC_MAX || (p + q) >= FRAC_MAX || (p + q) <= -FRAC_MAX)	//tested in testOverflow() over tests.cpp
	{
		//cerr << "Aproximating " << num << "/" << den << " + " << f.num << "/" << f.den << endl;
		p = (double)num / lcm;
		p *= lcm / (double)den;
		q = (double)f.num / lcm;
		q *= lcm / (double)f.den;
		return Fraction(p+q);
	}
	else
		return normal(p + q, (T_integer)lcm);
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

	if(lcm >= FRAC_MAX || (p - q) >= FRAC_MAX)	//tested in testOverflow() over tests.cpp
	{
		//cerr << "Aproximating " << num << "/" << den << " - " << f.num << "/" << f.den << endl;
		p = (double)num / lcm;
		p *= lcm / (double)den;
		q = (double)f.num / lcm;
		q *= lcm / (double)f.den;
		return Fraction(p - q);
	}
	else
		return normal(p - q, (T_integer)lcm);
}

Fraction Fraction::operator*(Fraction f)
{
	if(num == 0 || f.num == 0) return Fraction(0);
	//check for simplifications

	Fraction a = normal(f.num,den);
	Fraction b = normal(num, f.den);


	if(FRAC_MAX/abs(b.num) <= abs(a.num) || FRAC_MAX/abs(b.den) <= abs(a.den))
	{
		double newDen = a.den * b.den;
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
		if(FRAC_MAX/abs(b.num) <= abs(num) || FRAC_MAX/abs(b.den) <= (den))
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

Fraction Fraction::fromContinuedForm(vector<T_integer> v)
{
	if(v.size() == 0)
	{
		return Fraction(1,0);
	}else{
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

Fraction Fraction::operator/(T_integer l)
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

void Fraction::operator/=(T_integer l)
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
		Fraction f(num, (T_integer)i);
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

Fraction Fraction::operator/(unsigned i)
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

void Fraction::operator/=(unsigned i)
{
	if(i != 0)
	{
		den*=i;
		normalize();
	}
	else
		throw divByZ;
}

vector<T_integer> Fraction::continuedForm()
{
	vector<T_integer> res;
	T_integer integerPart;
	Fraction d(num,den);
	double maxSize = floor(log2(den)/log2(1.61));

	while(abs(d) > 1e-8 && res.size() < maxSize)
	{
		integerPart = (T_integer)d;
		res.push_back(integerPart);
		d -= integerPart;
		if(abs(d) > 1e-8)
			d.invert();
	}
	res[res.size()-1] += 1;	//format standard
	return res;
}

Fraction pow(Fraction f, T_integer l)
{
	double n = pow(f.numerator(), l);
	double d = pow(f.denominator(), l);
	return Fraction(n/d);

}
double pow(T_integer l, Fraction f)
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

Fraction root(Fraction f, T_integer l)
{
	double n = pow(f.numerator(), 1.0/l);
	double d = pow(f.denominator(), 1.0/l);
	Fraction nf(n);
	Fraction df(d);
	return (nf / df);
}

double logb(Fraction f, T_integer base)
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

Fraction Fraction::doubleToFraction(double value)	//Jhon Kennedy's algorithm https://begriffs.com/pdf/dec2frac.pdf
{
	T_integer sign = (value >= 0);	//if value is negative => 0. if value >= 0 => 1
    sign = sign*2 -1;		//0 or 2, then -1 or 1

    value = abs(value);

    //long maxError is 1e-9, for long long would be 1e-18. But long has many problems with casting from double. Not recomended.
	double maxError = 1e-18;

    double integer = floor(value);
    double decimal = value - integer;
	T_integer den = 1;

    if (decimal < maxError)
        return Fraction((T_integer)integer*sign, den);

    if (decimal > 1 - maxError)
        return Fraction((T_integer)(integer + 1)*sign, den);

    double z = value;
    T_integer previousDenominator = 0, previousNumerator = 0;
    T_integer denominator = 1;
    T_integer numerator = 0, Di = 0;
	double diff, zdiff;

    do
    {
        z = 1.0 / (z - floor(z));
        Di = denominator;
        denominator = Di * floor(z) + previousDenominator;

        previousNumerator = numerator;
        numerator = round(value * denominator);

        if(numerator < 0){	//this works if numerator and denominator are T_integer, but only if it fails at the third eq.
        	if(previousNumerator == 0){
        		return Fraction((T_integer)integer);
        	}
        	numerator = previousNumerator;
        	denominator = Di;
        	break;
        }

    	previousDenominator = Di;

    	diff = abs((double)numerator / (double)denominator - value);
    	zdiff = abs(z - floor(z));
    }
    while (diff > maxError && zdiff > maxError);

	if(max(numerator,denominator) > FRAC_MAX){
		double comm = floor(max(numerator,denominator) / FRAC_MAX);
		numerator = floor(numerator/comm);
		denominator = ceil(denominator/comm);
	}

    return Fraction((T_integer)numerator * sign, (T_integer)denominator);
}