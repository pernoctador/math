#include "Fraction.h"
#include "deprecated.h"
#include <cfloat>
#include <assert.h>
#include <time.h>
#include <random>
#include <time.h>
#include <limits>       // std::numeric_limits


void someInfo()
{
	cout << "Range of positive doubles:  " << DBL_MIN << " to " << DBL_MAX << endl;
	cout << "Range of positive fraction: " << FRAC_MIN << "   to " << FRAC_MAX << endl << endl;

	cout << "If I use long long:         " << (double)1/(double)LLONG_MAX << "   to " << LLONG_MAX << endl;
	cout << "If I use ulong:             " << (double)1/(double)ULONG_MAX << "  to " << ULONG_MAX << endl;
	cout << "If I use ulonglong:         " << (double)1/(double)ULLONG_MAX << "  to " << ULLONG_MAX << endl << endl;

	//cout << "I don't have as many integers as double, but i have more rationals between integers" << endl;

	cout << "Digits in double: " << numeric_limits<double>::digits10 << endl;
	cout << "Digits in long: " << numeric_limits<long>::digits10 << endl;

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
	cout << " = " <<  a << "-1 " << endl;
}

void testBasicFractions()
{
	//constructor, (), = and ==, <= and >=
	Fraction a(1,2);
	Fraction aa;
	aa = a;
	Fraction aaa(aa);
	assert(aaa == a);
	assert(!(aaa != a));
	Fraction b;
	cout << "Testing if wrong constructor give an error: ";
	b(1,0);
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
	a = a.invert();
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
	assert((dc-0.00000000000001) < dcc && dcc < (dc+0.00000000000001));
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
	assert((dc-0.000000000000001) < bb && bb < (dc+0.000000000000001));	//also, with doubles there is a tiny difference, so never use == outside tests

	bb = log10(4) - log10(8);
	dc = log10(b);
	assert((dc-0.000000000000001) < bb && bb < (dc+0.000000000000001));

	//root
	a(4,9);
	a = root(a,2);
	b(2,3);
	assert(a == b);


	a(2744,19683);
	a = root(a,3);
	b(14,27);
	assert((a-0.00000000000001) < b && b < (a+0.00000000000001));

	// casting
	double da = a(9,8);
	assert(da == 1.125);
	long la = a;
	assert(la == 1);
	
}

void testCommonMistakes()
{
	//construct negative
	Fraction a(1,2);
	Fraction b(1,-2);
	assert(a > 0);
	assert(b < 0);
	assert(b.denominator() > 0);

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
	//cout << "double: " << da << endl;
	//cout << "fraction: " << b << endl;
	//cout << (double)a << " = " << (double)b << endl;
	assert(a == b);
	assert(a == da);

	a(14,55);
	da = 14.0/55.0;
	b(da);
	assert(a == b);
	assert(a == da);

	a(1571,550);
	da = 1571.0/550.0;
	b(da);
	assert(a == b);
	assert(a == da);

	da = 15.23232345678910;	//must not transform da into 15.232323232323232323
	a(da);
	double db = a;
	assert(abs(da-db) < 0.0000000000001);

	a(5,19);
	da = 5.0/19.0;	//doubles can't represent this number, and is not a recurring decimal
	b(da);
	assert(abs(a - b) < 0.000000000000001);
	assert(abs(a - da) < 0.000000000000001);
}

void compareDecimalConversions()
{
	double num, den;
	double floatpoint, doubleFunctionTime, realFunctionTime, totDTF=0, totRTF=0;
	double dFPrecc=0, rFPrecc=0;
	Fraction frac, dToFrac, realToFrac;
	clock_t start;
	for(int i = 1; i < 100000; i++)
	{
		clock_t extra = clock();
		srand(time(NULL) * (double)extra);	//ayuda a evitar seeds repetidas.
		num = (rand() % 100000000000000) + 1;
		den = (rand() % 100000000000000) + 1;
		floatpoint = num/den;
		frac(num,den);
		doubleFunctionTime = 0;
		realFunctionTime = 0;
		
		for(int j = 1; j < 1000; j++)
		{
			start = clock();
			dToFrac = MyOldDoubleToFraction(floatpoint);
			doubleFunctionTime += clock() - start;

			start = clock();
			realToFrac(floatpoint);
			realFunctionTime += clock() - start;
		}
		
		dFPrecc += abs((double)(frac - dToFrac));
		rFPrecc += abs((double)(frac - realToFrac));

		totDTF += doubleFunctionTime/1000;
		totRTF += realFunctionTime/1000;
	}
	cout << "Time:" << endl;
	cout << "Handwritten metod + checking for recurring decimal = " << totDTF/100000 << endl;
	cout << "Iterative John Kennedy's method = " << totRTF/100000 << endl << endl;
	cout << "Precision:" << endl;
	cout << "Handwritten metod + checking for recurring decimal = " << dFPrecc/100000 << endl;
	cout << "Iterative John Kennedy's method = " << rFPrecc/100000 << endl;
}


int main()
{
	//someInfo();
	//testPrint();
	testBasicFractions();	//basic tests for every operation
	testCommonMistakes();	//what i consider to be possible mistakes while programming Fractions
	testBetterperiodics();	//searching for periodic rational numbers when defining a Fraction with a double

	//checkForOptimalAccuracy(); 
		/*deprecated with latests changes: the result was 1e-16 was needed as accuracy
		However, using a lower number than 1e-14 gives precision errors.
		The reason is underflow, as doubles have around 15 decimal digits*/
	//compareDecimalConversions(); //deprecated with latests changes: the result was JK's iterative algoritm was faster and more accurate on average with 1e-16 accuracy.
		
	

	return 0;
}