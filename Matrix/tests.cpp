#include "Matrix.h"
#include "../Fraction/Fraction.h"
#include <cfloat>
#include <assert.h>

#include <time.h>

void printTest()	//MUST check with valgrind
{
	Matrix<double> first(4,15);
	first.Zero();
	cout << "matrix A:" << endl;
	first.print();
	first.t();
	cout << "matrix A^t:" << endl;
	first.print();
	first.t();
	cout << "matrix (A^t)^t:" << endl;
	first.print();
	cout << endl;

	Matrix<double> B(2,5);
	for(unsigned i = 0; i < 2; i++)
	{
		for(unsigned j = 0; j < 5; j++)
		{
			B(i,j) = i*5 +j;
		}
	}
	cout << "matrix B:" << endl;
	B.print();
	B.t();
	cout << "matrix B^t:" << endl;
	B.print();
	B.t();
	cout << "matrix (B^t)^t:" << endl;
	B.print();
	cout << endl;

	B.t();
	Matrix<double> C(2,5);
	C = B.tr();
	cout << "matrix C = (B^t)^t:" << endl;
	C.print();
	Matrix<double> D(5,2);
	D = C.tr();
	cout << "matrix C^t:" << endl;
	D.print();
	cout << endl;

	Matrix<double> second = Id<double>(4);
	second(1,2) = 46.2654;
	second.print();

	Matrix<Fraction> third = Id<Fraction>(5);
	third(1,2) = Fraction(41,53);	//don't know how to improve it
	third.print();	
}

void basicMatrixOperations()
{
	//t, tr, =, ==, constructores
	Matrix<double> one(4,3);
	one(2,3) = 4;
	Matrix<double> two(3,4);
	two.nameElements();
	Matrix<double> three(3,4);
	three.nameElements();
	try{
		one = two;
		cout << "Error: must have thrown exception in one = two" << endl;
	}
	catch(...){}
	two.t();
	try{
		two = three;
		cout << "Error: must have thrown exception in two^t = three" << endl;
	}
	catch(...){}

	one = two;
	assert(one == two);

	two = three.tr();
	assert(two.tr() == three);

	three.t();
	assert(two == three);

	//+, -, *
	Matrix<double> a(4,2);
	Matrix<double> b(2,3);

	a.nameElements();
	b.nameElements();


	Matrix<double> c = a * b;
	Matrix<double> r(4,3);
	double v[] = {3,  4,  5, 9, 14, 19, 15, 24, 33, 21, 34, 47};
	r = v;

	assert(r == c);

	Matrix<double> d(4,2);
	for(unsigned i = 0; i < 4; i++)
	{
		for(unsigned j = 0; j < 2; j++)
		{
			d(i,j) = (i+1) * (j+1);
		}
	}
	//cout << "d: " << endl;
	//d.print(); 

	Matrix<double> c2 = a + d;
	double v2[] = {1,  3, 4, 7, 7, 11, 10, 15};

	Matrix<double> r2(4,2);
	r2 = v2;
	assert(r2 == c2);

	c2 = a - d;
	double v3[] = {-1, -1, 0, -1, 1, -1, 2, -1};
	Matrix<double> r3(4,2);
	r3 = v3;
	assert(r3 == c2);

	try{
	a += b;
	cout << "Error: must have thrown exception" << endl;
	}
	catch(exception &e){}
	try{
	b -= c;
	cout << "Error: must have thrown exception" << endl;
	}
	catch(exception &e){}
	try{
	b * a;
	cout << "Error: must have thrown exception" << endl;
	}
	catch(exception &e){}
}

void GaussianEliminationTest()
{
	Fraction first[] = {4, 16, 3, 2, 9, 8, 4, 12, 7};
	Matrix<Fraction> a(3.3);
	a = first;
	
	Fraction det = a.GaussianElimination();

	for(unsigned i = 0; i < a.size().first; i++)
		det *= a(i,i);

	assert(det == 120);

	Fraction second[] = {10,6,30,5,3,15,4,8,9};
	a = second;

	det = a.GaussianElimination();

	for(unsigned i = 0; i < a.size().first; i++)
		det *= a(i,i);

	assert(det == 0);
}

int main()
{
	//printTest();
	//basicMatrixOperations();
	GaussianEliminationTest();
	
	return 0;
}