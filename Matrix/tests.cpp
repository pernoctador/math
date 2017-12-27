#include "Matrix.h"
#include "../Fraction/Fraction.h"
#include <cfloat>
#include <assert.h>

#include <time.h>

void basicMatrixOperations()
{
	Matrix<double> first(4,15);
	first.t();
	first.t();
	first.print();

	Matrix<double> second = Id<double>(5);
	second(1,2) = 4.3;
	second.print();

	Matrix<double> third = Id<double>(4);
	third(1,2) = 46.2654;
	third.print();

	Matrix<double> a(4,2);
	Matrix<double> b(2,3);
	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 2; j++)
		{
			a(i,j) = i*2+j;
		}
	}
	cout << "a: " << endl;
	a.print();
	for(int i = 0; i < 2; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			b(i,j) = i*3+j;
		}
	}
	cout << "b: " << endl;
	b.print();
	Matrix<double> c = a * b;
	c.print();

	Matrix<double> d(4,2);
	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 2; j++)
		{
			d(i,j) = (i+1) * (j+1);
		}
	}
	cout << "d: " << endl;
	d.print(); 

	c = a + d;
	c.print();

	c = a - d;
	c.print();

	c = a + b;
}

void GaussianEliminationTest()
{
	Matrix<Fraction> a = Id<Fraction>(3);
	a(0,0) = 4;
	a(0,1) = 16;
	a(0,2) = 12;

	a(1,0) = 2;
	a(1,1) = 9;
	a(1,2) = 8;

	a(2,0) = 3;
	a(2,1) = 12;
	a(2,2) = 10;

	a.print();
	
	Fraction det = a.GaussianElimination();
	
	a.print();

	cout << "determinant = ";

	for(int i = 0; i < a.size().first; i++)
		det *= a(i,i);

	cout << det << endl;
}

int main()
{
	//basicMatrixOperations();
	GaussianEliminationTest();
	
	return 0;
}