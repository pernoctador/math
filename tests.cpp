#include "Fraction.h"

void testFractions()
{
	//constructor, = and ==
	Fraction a(1,2);
	Fraction aa;
	aa = a;
	Fraction aaa(aa);
	cout << boolalpha << (aaa == a) << endl;
	Fraction b;
	b = 0.5;
	cout << (a == b) << endl;
	b = 1000.0001;
	cout << b << endl;
}


int main()
{
	testFractions();
	return 0;
}