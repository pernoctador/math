#include "Fraction.h"
#include <cfloat>
#include <assert.h>
#include <time.h>

void testBasicFractions()
{
	cout << "Range of positive doubles:  " << DBL_MIN << " to " << DBL_MAX << endl;
	cout << "Range of positive fraction: " << FRAC_MIN << "   to " << FRAC_MAX << endl;

	cout << "If I use long long:         " << (double)1/(double)LLONG_MAX << "   to " << LLONG_MAX << endl;
	cout << "If I use ulong:             " << (double)1/(double)ULONG_MAX << "  to " << ULONG_MAX << endl;
	cout << "If I use ulonglong:         " << (double)1/(double)ULLONG_MAX << "  to " << ULLONG_MAX << endl;

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
	assert(dc == dcc);
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
	assert((dc-1.00000000000001) < bb && bb < (dc+1.00000000000001));	//also, with doubles there is a tiny difference, so never use ==

	bb = log10(4) - log10(8);
	dc = log10(b);
	assert((dc-1.00000000000001) < bb && bb < (dc+1.00000000000001));

	//root
	a(4,9);
	a = root(a,2);
	b(2,3);
	assert(a == b);

	a(2744,19683);
	a = root(a,3);
	b(14,27);
	assert(a == b);

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
}

int main()
{
	testBasicFractions();	//basic tests for every operation
	testCommonMistakes();	//what i consider to be possible mistakes while programming Fractions
	testBetterperiodics();	//searching for periodic rational numbers when defining a Fraction with a double
	return 0;
}