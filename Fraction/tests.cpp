#include "Fraction.h"
#include <cfloat>
#include <assert.h>
#include <time.h>
#include <random>
#include "../utilities/fractions_extra.h"

void someInfo()
{
	cout << "Range of positive doubles:  " << DBL_MIN << " to " << DBL_MAX << endl;
	cout << "Range of positive fraction: " << FRAC_MIN << "   to " << FRAC_MAX << endl << endl;

	cout << "If I use long long:         " << (double)1/(double)LLONG_MAX << "   to " << LLONG_MAX << endl;
	cout << "If I use int:               " << (double)1/(double)INT_MAX << "  to " << INT_MAX << endl;
	cout << "If I use uint:              " << (double)1/(double)UINT_MAX << "  to " << UINT_MAX << endl;
	cout << "If I use ulong:             " << (double)1/(double)ULONG_MAX << "  to " << ULONG_MAX << endl;
	cout << "If I use ulonglong:         " << (double)1/(double)ULLONG_MAX << "  to " << ULLONG_MAX << endl << endl;

	//cout << "I don't have as many integers as double, but i have more rationals between integers" << endl;

	cout << "Digits in double: " << numeric_limits<double>::digits10 << endl;
	cout << "Digits in long: " << numeric_limits<long>::digits10 << endl << endl;

}

void testDensity()
{
	cout << "Density between 0,1:                | 1,2              | 1e6,1e6+1   | 1e14,1e14+1 | 1e15-1,1e15 | 1e17-10,1e17 | 1e19-10000,1e19 | 1e19-1000,1e19" << endl;
	cout << "    Doubles:    " << doublesIn(0,1) << " | " << doublesIn(1,2) << " | " << doublesIn(1e6,1e6+1) << "  | " << doublesIn(1e14,1e14+1) << "          | ";
	cout << doublesIn(1e15-1,1e15) << "           | " << doublesIn(1e17-10,1e17) << "            | " << doublesIn(1e19-10000,1e19) << "               | " << doublesIn(1e19-1000,1e19) << endl;

	cout << "    Fractions:  " << fractionsIn(0,1) << "         | " << fractionsIn(1,2) << "      | " << fractionsIn(1e6,1e6+1) << " | " << fractionsIn(1e14,1e14+1) << " | ";
	cout << fractionsIn(1e15-1,1e15) << " | " << fractionsIn(1e17-10,1e17) << "         | " << fractionsIn(1e19-10000,1e19) << "               | " << fractionsIn(1e19-1000,1e19) << endl << endl;
}

void testPrint()
{
	//cout, print
	Fraction a, b;
	a = 3;
	b(9,3);
	b.print();
	cout << " = " <<  a << endl;
	a /= 4;
	b /= 4;
	b.print();
	cout << " = " <<  a << endl;
	a(0,7);
	b(5,-5);
	b.print();
	cout << " = " <<  a << " - 1 " << endl;

	try{
		b(1,0);
		cout << "Error: no exception fired when dividend is 0" << endl;
	}
	catch(exception &e){}
	try{
		b = 0;
		a /= b;
		cout << "Error: no exception fired when dividing by 0" << endl;
	}
	catch(exception &e){}
	
}

void testBasicFractions()
{
	cout.precision(numeric_limits<double>::digits10);
	//constructor, (), = and ==, <= and >=
	Fraction a(1,2);
	Fraction aa;
	aa = a;
	Fraction aaa(aa);
	assert(aaa == a);
	assert(!(aaa != a));
	Fraction b;
	b = 0.5;
	assert(a == b);
	assert(!(a != b));
	assert(a <= b);
	assert(a >= b);
	double bb = 1.25;
	b(5,4);
	assert(b == bb);

	// <, >, <= and >=
	a = 4;
	a = a / 3;
	b(5,4);
	assert(a > b);	//1+1/3 > 1+1/4
	assert(a >= b);
	assert(b < a);
	assert(b <= a);

	// +, -, *, /
	a(1,3);
	b(1,2);
	Fraction c(5,6);
	//cout << a+b << endl;
	assert(a + b == c);
	assert(a + 0.5 == c);
	assert(b + 2 == 2.5);
	c(1,-6);
	assert(a - b == c);
	
	assert(a - 0.5 == c);	
	assert(b - 2 == -1.5);
	c(1,6);
	assert(a * b == c);
	assert(a * 0.5 == c);
	assert(b * 2 == 1);
	c(2,3);
	assert(a / b == c);
	assert(a / 0.5 == c);	
	assert(b / 2 == 0.25);

	// +=, -=, *=, /=
	a(1,3);
	b(1,2);
	c(5,6);
	a += b;
	assert(a == c);
	b += 2.3;
	c(14,5);
	assert(b == c);
	a += 1;
	c(11,6);
	assert(a == c);

	a(1,3);
	b(1,2);
	c(-1,6);
	a -= b;
	assert(a == c);
	b -= 2.3;
	c(-9,5);
	assert(b == c);
	a -= 1;
	c(-7,6);
	assert(a == c);

	a(1,3);
	b(1,2);
	c(1,6);
	a *= b;
	assert(a == c);
	b *= 2.3;
	c(23,20);
	assert(b == c);
	a *= -3;
	c(-1,2);
	assert(a == c);

	a(1,3);
	b(1,2);
	c(2,3);
	a /= b;
	assert(a == c);
	b /= 2.3;
	c(5,23);
	assert(b == c);
	a /= -3;
	c(-2,9);
	assert(a == c);

	// idiv, invert
	a(1,3);
	assert(a.idiv(3,a) == 9);	
	a(2,3);
	assert(a.idiv(4,a) == 6);

	a(7,9);
	b(9,7);
	c = invert(a);
	assert(c == b);

	a.invert();
	assert(a == b);

	// pow
	a(2,3);
	b = pow(a, 3);
	a(8,27);
	assert(a == b);
	
	c(2,3);
	long lc = 27;
	double dc = pow(lc, c);
	double dcc = 9;
	//cout << dc << " = " << dcc << " , dif = " << dc - dcc << endl;
	//assert(dc == dcc);
	assert((dc-1e-15) < dcc && dcc < (dc+1e-15));
	lc = -3;
	dc = pow(lc, c);
	assert(dc > 0);

	//log
	b(64,8);
	bb = logb(b,2);
	assert(bb == 3);

	b(4,8);
	bb = log(4) - log(8);
	dc = log(b);
	cout << "Beware of hidden differences! " << bb << " != " << dc  << endl;
	//with doubles there is a tiny difference, so never use == outside tests
	assert((dc-1e-15) < bb && bb < (dc+1e-15));

	bb = log10(4) - log10(8);
	dc = log10(b);
	assert((dc-1e-15) < bb && bb < (dc+1e-15));

	//root
	a(4,9);
	a = root(a,2);
	b(2,3);
	assert(a == b);


	a(2744,19683);
	a = root(a,3);
	b(14,27);
	cout << "Beware of rounding! "<<  a << " = " << a << " - 1e-10 == "<< a << " + 1e-10 = " << a+1e-10 << endl;
	//sometimes numbers get rouded, even when they are big. Use a propper error margin according to your needs. And use <= outside tests
	assert((a-1e-9) < b && b < (a+1e-9));

	// casting
	double da = a(9,8);
	assert(da == 1.125);
	long la = a;
	assert(la == 1);

	//continued fractions
	a(951,8462);
	b(81958,65199);
	c(469,327);

	Fraction ca(a.continuedForm());
	Fraction cb(b.continuedForm());
	Fraction cc(c.continuedForm());

	assert(a == ca);
	assert(b == cb);
	assert(c == cc);

}

void testCommonMistakes()
{
	//construct negative
	Fraction a(1,2);
	Fraction b(1,-2);
	assert(a > 0);
	assert(b < 0);
	assert(b.denominator() > 0);

	a(-3,-7);
	assert(a > 0);
	assert(a.denominator() > 0);

	a(1,-2);
	b(1,2);
	assert(a < 0);
	assert(b > 0);
	assert(a.denominator() > 0);
	b /= a;
	assert(b < 0);
	assert(b.denominator() > 0);

	// zeros
	a(0);
	b(0,5);
	assert(a == b);
	assert(a.denominator() == 1);
	assert(b.denominator() == 1);
	a(3,5);
	b(3,5);
	a-=b;
	Fraction c(0.0);
	assert(a == 0);
	assert(a == c);
	assert(a.denominator() == 1);

	//normalized fractions (kind of already tested in other tests)
	a(103*2161, 31*1009);
	assert(a.numerator() == (103*2161));

	a(4093*5869, 4093*4397);
	assert(a.numerator() == 5869);
	assert(a.denominator() == 4397);

	a(103*103*197*197, 103*197*197*197);
	assert(a.numerator() == 103);
	assert(a.denominator() == 197);
}

void testBetterperiodics()
{
	Fraction a;
	double da;
	Fraction b;

	a(1,3);
	da = 1.0/3.0;
	b(da);
	assert(a == b);
	assert(a == da);
	
	a(136,99);
	da = 136.0/99.0;
	b(da);
	assert(a == b);
	assert(a == da);

	a(14,55);
	da = 14.0/55.0;
	b(da);
	assert(a == b);
	assert(a == da);

	a(0.33333333333333);
	b(1,3);
	assert(b == (1.0/3.0));
	assert(a == b);

	a(1571,550);
	da = 1571.0/550.0;
	b(da);
	assert(a == b);
	assert(a == da);

	da = 15.2323232345678910;	//must not transform da into 15.232323232323232323
	a(da);
	double db = a;
	assert(abs(da-db) < 1e-13);

	a(5,19);
	da = 5.0/19.0;	//doubles can't represent this number, and is not a recurring decimal
	b(da);
	assert(abs(a - b) < 1e-15);
	assert(abs(a - da) < 1e-15);
}

void testCloseToZeroNumbers()
{
	double t, df, dif, maxErr=0, averageErr=0;
	Fraction f,g;
	for(double i = 1000; i >= 1; i--)
	{
		t = i/LONG_MAX;
		f(t);
		g(i,LONG_MAX);
		
		dif = abs(f - g);
		if(dif > maxErr)
			maxErr = dif;
		averageErr+=dif;

		t = 1/(LONG_MAX-i);
		f(t);
		g(1,LONG_MAX-i);
		dif = abs(f - g);
		if(dif > maxErr)
			maxErr = dif;
		averageErr+=dif;
	} 
	averageErr /= 2000;
	cout << "Max error found in conversion from double to fraction close to zero: " <<  maxErr << endl;
	cout << "Average error found in conversion from double to fraction close to zero: " << averageErr << endl;

	maxErr=0;
	averageErr=0;
	
	for(double i = 1000; i >= 1; i--)
	{
		f(i,LONG_MAX);
		df = f;
		t = i/LONG_MAX;
		
		dif = abs(df - t);
		if(dif > maxErr)
			maxErr = dif;
		averageErr+=dif;

		f(1,LONG_MAX-i);
		df = f;
		t = 1/(LONG_MAX-i);
		dif = abs(df - t);
		if(dif > maxErr)
			maxErr = dif;
		averageErr+=dif;
	} 
	averageErr /= 2000;
	cout << "Max error found in conversion from fraction to double close to zero: " <<  maxErr << endl;
	cout << "Average error found in conversion from fraction to double close to zero: " << averageErr << endl << endl;
}

void testInfoOverflow()
{	
	cout.precision(numeric_limits<double>::max_digits10);
	
	double a, b, c;
	long e;

	double m,n;


	cout << "Can I operate with long overflow, casting to double?: "; 

	e = LONG_MAX;
	m = e + 1;
	n = e;
	n++;
	a = e;
	a += e;
	b = a;
	b -= 1;
	c = a - b;

	cout << boolalpha << (c == 1) << endl;

	a = e;
	a++;
	cout << "Can I detect strict overflow casting to double?: " << boolalpha << (a > LONG_MAX) << endl << endl;
	cout << "Can I detect overflow casting to double?: " << boolalpha << ((a >= LONG_MAX) && (e == LONG_MAX)) << endl; 
	a = e;
	a *= a;
	a += a;
	cout << "Can I detect max overflow in fractions casting to double?: " << boolalpha << ((a >= LONG_MAX) && (e == LONG_MAX)) << endl << endl; 

	e+=1;
	cout.precision(numeric_limits<double>::max_digits10);
	cout << "WARNING! (double)LONG_MAX + 1 is still overflow: " << fixed << m << endl << "	But double e = LONG_MAX; e+1 is OK: " << n << endl << "Must always explicitly cast to double" << endl << endl;
	cout << "overflow: 1 + " << LONG_MAX << " = (long)" << e << " = (double)" << n << endl;

	unsigned long long p = ULLONG_MAX;
	p++;
	n = ULLONG_MAX;
	n+=1;
	cout << "overflow: 1 + " << ULLONG_MAX << " = (unsigned long long) " << p << "  =  (double)" << n << endl << endl;

	e = 1e8;
	long e2 = e*e;
	cout << "Testing e*e: " << e << " * " << e << " = " << e2 << endl;
	cout << "	Detect overflow after: " << boolalpha << (e2/e != e) << endl;
	cout << "	Detected before with division: " << boolalpha << (LONG_MAX/e <= e) << endl;

	cout << endl << "Partial casting: " << endl << (double)e*LONG_MAX << " == " << endl << e*(double)LONG_MAX << endl;
	
}

int main()
{

	//someInfo();
	//testPrint();
	testDensity();
	/*testCloseToZeroNumbers();
	testInfoOverflow();
*/
/*
	testBasicFractions();	//basic tests for every operation
	testCommonMistakes();	//what i consider to be possible mistakes while programming Fractions
	testBetterperiodics();	//searching for periodic rational numbers when defining a Fraction with a double
*/
	
	return 0;
}
