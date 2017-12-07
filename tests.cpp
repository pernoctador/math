#include "Fraction.h"
#include <cfloat>
#include <assert.h>

#include <time.h>

void testBasicFractions()
{
	cout << "Minimum representable positive double  : " << DBL_MIN << endl;
	cout << "Minimum representable positive fraction: " << FRAC_MIN << endl;

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

	// zeros

	//normalized fractions
}


void testBetterFractions()
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
	testBetterFractions();	//searching for periodic rational numbers when defining a Fraction with a double
	return 0;
}