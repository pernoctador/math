#include "Fraction.h"
#include <cfloat>
#include <assert.h>

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
	cout << "Debe dar error: ";
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

	// idiv, pow, invert, log

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
	Fraction a(1,3);
	double da = 1.0/3.0;
	assert(a == da);
	a(136,99);
	da = 136.0/99.0;
	assert(a == da);
}

int main()
{
	testBasicFractions();
	testCommonMistakes();
	//testBetterFractions();
	return 0;
}