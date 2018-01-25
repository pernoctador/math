#include "Matrix.h"
#include "../Fraction/Fraction.h"
#include <cfloat>
#include <assert.h>

#include <time.h>

void printTest()
{
	Matrix<double> first(4,15);
	cout << "matrix A:" << endl;
	first.print();
	first.t();
	cout << "matrix A^t:" << endl;
	first.print();
	first.t();
	cout << "matrix (A^t)^t:" << endl;
	first.print();
	cout << endl;

	Matrix<double> second = Id<double>(4);
	second(1,2) = 46.2654;
	second.print();

	Matrix<Fraction> third = Id<Fraction>(5);
	third(1,2) = Fraction(41,53);	//don't know how to improve it
	third.print();

	try{
	first += second;
	}
	catch(exception &e){cout << "Forced exception: " << endl << "	" <<  e.what() << endl;}
	try{
	first -= second;
	}
	catch(exception &e){}
	try{
	first = first * second;
	}
	catch(exception &e){}
	first = second * first;
}
void basicMatrixOperations()
{
	Matrix<double> a(4,2);
	Matrix<double> b(2,3);
	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 2; j++)
		{
			a(i,j) = i*2+j;
		}
	}
	//cout << "a: " << endl;
	//a.print();
	for(int i = 0; i < 2; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			b(i,j) = i*3+j;
		}
	}
	//cout << "b: " << endl;
	//b.print();

	Matrix<double> c = a * b;
	Matrix<double> r(4,3);
	double v[] = {3,  4,  5, 9, 14, 19, 15, 24, 33, 21, 34, 47};
	r = v;
	assert(r == c);

	Matrix<double> d(4,2);
	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 2; j++)
		{
			d(i,j) = (i+1) * (j+1);
		}
	}
	//cout << "d: " << endl;
	//d.print(); 

	c = a + d;
	double v2[] = {1,  3, 4, 7, 7, 11, 10, 15};

	Matrix<double> r2(4,2);
	r2 = v2;
	assert(r2 == c);

	c = a - d;
	double v3[] = {-1, -1, 0, -1, 1, -1, 2, -1};
	Matrix<double> r3(4,2);
	r3 = v3;
	assert(r3 == c);
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
	//printTest();
	basicMatrixOperations();
	//GaussianEliminationTest();
	
	return 0;
}