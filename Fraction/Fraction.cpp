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

Fraction Fraction::doubleToFraction(double db)
{
	string value = tostr(db);
	size_t pos = value.find(".");
	string integer = value.substr(0,pos);
  	string decimals= value.substr(pos+1);
  	if(pos == string::npos)
  		decimals = "0";
	//now, search for a period in decimals

  	// First try: O(n^3). Even if it's ugly, n <= 15 (18 if in the future i use long double), so it's like O(1). I have to check Floyd's tortoise and hare.
  	if(decimals.size() > 12)	//if not, makes more sense to just divide by 10^|decimals|
  	{
  		int maxCicles= -1, start = 0, finish = 0, cicles = -1;
	  	for (uint init = 0; init < decimals.size()-2; init++)
	  	{
	  		cicles = -1;
	  		for (uint end = init+1; end < decimals.size()-1; end++)
	  		{
	  			//period = [init,end)
	  			if(decimals[end] == decimals[init])
	  			{
	  				//i found a possible cicle
	  				cicles = 0;
	  				for (uint elem = 1; end + elem < decimals.size() && cicles > -1; elem++)	//check if elements match
	  				{
	  					if(decimals[init + elem] != decimals[end + elem] || end + elem == decimals.size()-1)//gotta save the cicle's data
	  					{
	  						if(cicles > maxCicles)
	  						{
	  							start = init;
	  							finish = end;
	  							maxCicles= cicles;
	  						}
	  						cicles = -1;
	  						break;
	  					}
	  					if(decimals[init + elem] == decimals[end + elem] && decimals[init] == decimals[end + elem])
	  						cicles++;
	  				}
	  			}
	  		}
	  	}
	  	//cout << "start = " << start << " ; finish = " << finish << " ; maxCicles " << maxCicles<< " ; periodo = " << decimals.substr(start, finish-start) << endl;

	  	if(maxCicles > 0)
	  	{
	  		string num2S = integer + decimals.substr(0, finish);
	  		long den2 = pow(10, finish - start)-1;
	  		long num2 = stol(num2S) - stol(integer + decimals.substr(0, start));

	  		return Fraction( num2, den2 * pow(10, start));
	  	}
	}


	long number = stol(integer+decimals);
	return Fraction(number, pow(10.0, decimals.size()));
}