#include "Matrix.h"
#include "../Fraction/Fraction.h"
#include <cfloat>
#include <assert.h>

#include <time.h>

void printTest()	//MUST check with valgrind
{
	//initialize matrix:
	Matrix<double> zero(5,7);
	zero.Zero();
	zero.print();

	Matrix<double> id(7,4);
	id.Id();
	id.print();

	Matrix<double> id2(3,4);
	id2.Id();
	id2.print();

	Matrix<double> rnd(4,6);
	rnd.Random(20,40);
	rnd.print();

	//Transpose, print and transpose again
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

	//change elements
	Matrix<double> second = Id<double>(4);
	second(1,2) = 46.2654;
	second.print();

	Matrix<Fraction> third = Id<Fraction>(5);
	third(1,2) = Fraction(41,53);
	third.print();	//don't know how to improve this print

	//prints with 2 matrix
	B.print(D);

	//this ones shouldn't print, different cols
	B.print(C);
	B.print(first);

}

void basicMatrixOperations()
{
	//t, tr, =, ==, constructores
	Matrix<double> one(4,3);
	one(2,1) = 4;
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

	// ()
	Matrix<double> f(2,4);
	f.nameElements();
	assert(f(1,2) == 6);
	f.t();
	assert(f(3,1) == 7);
}

void TriangulateTest()
{

	Fraction first[] = {4, 16, 3, 2, 9, 8, 4, 12, 7};
	Matrix<Fraction> a(3.3);
	cout << "First test:" << endl;
	a = first;
	
	Fraction det = a.GaussianElimination();

	for(unsigned i = 0; i < a.size().first; i++)
		det *= a(i,i);

	assert(det == 120);

	cout << "Second test:" << endl;
	Fraction second[] = {4,8,9,5,3,15,10,6,30};
	a = second;

	det = a.GaussianElimination();
	a.print();
	for(unsigned i = 0; i < a.size().first; i++)
		det *= a(i,i);

	assert(det == 0);
}

void GaussianEliminationTest(){
	cout << "First eq test (fractions):" << endl;
	unsigned eq = 2;
	Fraction first[] = {1, 2, -2, -2};
	Fraction result[] = {34, -38};
	Matrix<Fraction> a(eq,eq);
	Matrix<Fraction> c(eq,eq);
	a = first;
	c = a;

	Matrix<Fraction> b(eq,1);
	b = result;
	a.print(b);

	a.GaussianElimination(&b);	//this gauss doesn't return any specific 'a' matrix
	a.print(b);

	//Fraction solf[] = {4, 15};
	Matrix<Fraction> checkf(eq,1);
	checkf = c * b;
	assert(checkf == result);


	cout << "First eq test (double):" << endl;
	eq = 2;
	double firstd[] = {1, 2, -2, -2};
	double resultd[] = {34, -38};
	Matrix<double> d(eq,eq);
	Matrix<double> f(eq,eq);
	d = firstd;
	f = d;

	Matrix<double> e(eq,1);
	e = resultd;
	d.print(e);

	d.GaussianElimination(&e);  //d gets destroyed
	e.print();

	Matrix<double> checkd(eq,1);
	checkd = f * e;
	assert(checkd == resultd);

	eq = 3;
	cout << "Second eq test (fractions):" << endl;
	Fraction second[] = {-1, -10, -4 , 3, 5, 2, -2, 2, 2};
	Fraction result2[] = {9, -2, 14};
	Matrix<Fraction> g(eq,eq);
	Matrix<Fraction> i(eq,eq);
	g = second;
	i = g;

	Matrix<Fraction> h(eq,1);
	h = result2;
	g.print(h);

	g.GaussianElimination(&h); //g gets destroyed
	h.print();

	Matrix<Fraction> check2f(eq,1);
	check2f = i * h;
	assert(check2f == result2);


	cout << "Second eq test (double):" << endl;
	double secondd[] = {-1, -10, -4 , 3, 5, 2, -2, 2, 2};
	double result2d[] = {9, -2, 14};
	Matrix<double> j(eq,eq);
	Matrix<double> l(eq,eq);
	j = secondd;
	l = j;

	Matrix<double> k(eq,1);
	k = result2d;
	j.print(k);

	j.GaussianElimination(&k); //j gets destroyed
	k.print();

	Matrix<double> ckeck2d(eq,1);
	ckeck2d = l * k;
	cout << "ckeck2d:" << endl;
	ckeck2d.print();
	k = result2d;
	cout << "distance:" << ckeck2d.distance(k) << endl;
	assert(ckeck2d.distance(k) < 1e-14);
}

void GaussianEliminationTest2() {
	cout << "First eq test (fractions):" << endl;
	unsigned n = 3;
	Fraction a[] = {944,    2,  -70, 369, -856, -876, -866,  272,  934};
	Fraction b[] = {944,    2,  -70};
	Matrix<Fraction> A(n,n);
	Matrix<Fraction> B(n,1);
	A = a;
	B = b;
	Matrix<Fraction> A2(n,n);
	Matrix<Fraction> B2(n,1);
	Matrix<Fraction> check(n,1);
	A2 = A;
	B2 = B;

	A.GaussianElimination(&B);
	check = A2*B;
	double dist = check.distance(B2);
	A2.print(B);
	cout << "  ====================  " << endl;
	check.print(B2);
	cout << "Dist = " << dist << endl;

	cout << "First eq test (double):" << endl;
	double c[] = {944,    2,  -70, 369, -856, -876, -866,  272,  934};
	double d[] = {944,    2,  -70};
	Matrix<double> C(n,n);
	Matrix<double> D(n,1);
	C = c;
	D = d;
	Matrix<double> C2(n,n);
	Matrix<double> D2(n,1);
	Matrix<double> check2(n,1);
	C2 = C;
	D2 = D;

	C.GaussianElimination(&D);
	check2 = C2*D;
	dist = check2.distance(D2);
	C2.print(D);
	cout << "  ====================  " << endl;
	check2.print(D2);
	cout << "Dist = " << dist << endl;
}

void GaussianEliminationTest3() {
	cout << "First eq test (fractions):" << endl;
	unsigned n = 4;
	/*
	 0, -1, -1,  0 |  0
	-1,  0,  1,  0 | -1
	 0,  0, -1,  1 | -1
	 1,  0,  0, -1 |  0
*/
	Fraction a[] = {0, -1, -1, 0, -1, 0, 1, 0, 0, 0, -1, 1, 1, 0, 0, -1};
	Fraction b[] = {0, -1, -1, 0};
	Matrix<Fraction> A(n,n);
	Matrix<Fraction> B(n,1);
	A = a;
	B = b;
	Matrix<Fraction> A2(n,n);
	Matrix<Fraction> B2(n,1);
	Matrix<Fraction> check(n,1);
	A2 = A;
	B2 = B;

	A.GaussianElimination(&B);
	check = A2*B;
	double dist = check.distance(B2);
	A2.print(B);
	cout << "  ====================  " << endl;
	check.print(B2);
	cout << "Dist = " << dist << endl;

	cout << "First eq test (double):" << endl;
	double c[] = {0, -1, -1, 0, -1, 0, 1, 0, 0, 0, -1, 1, 1, 0, 0, -1};
	double d[] = {0, -1, -1, 0};
	Matrix<double> C(n,n);
	Matrix<double> D(n,1);
	C = c;
	D = d;
	Matrix<double> C2(n,n);
	Matrix<double> D2(n,1);
	Matrix<double> check2(n,1);
	C2 = C;
	D2 = D;

	C.GaussianElimination(&D);
	check2 = C2*D;
	dist = check2.distance(D2);
	C2.print(D);
	cout << "  ====================  " << endl;
	check2.print(D2);
	cout << "Dist = " << dist << endl;
}

void timeTestGaussian()
{
	Matrix<double> a(100,100);
	Matrix<double> b(100,100);
	clock_t watch;
	double prom = 0, promt = 0;
	for(int i = 0; i < 10000; i++)
	{
		a.Random(-1000, 2000);

		watch = clock();
		a.GaussianElimination();
		watch = clock() - watch;
		prom += watch;
		
		b = a.tr();
		b.t();
		
		watch = clock();
		a.GaussianElimination();
		watch = clock() - watch;
		promt += watch;		
	}

	prom /= 10000;
	promt /= 10000;

	cout << "GaussianElimination standard takes " << prom << endl;
	cout << "GaussianElimination transposed takes " << promt << endl << endl;
}

void pressureGETest() {
	for(int n = 1; n < 1000; n++) {
		bool breaked = false;
		cout << n << endl;
		for(int t = 0; t < 5; t++){
			int limit = pow(10,t);
			for(int i = 0; i < 10000; i++) {
				Matrix<Fraction> A(n,n);
				A.Random(-limit, limit);
				Matrix<Fraction> B(n,1);
				B.Random(-limit,limit);
				Matrix<Fraction> A2(n,n);
				Matrix<Fraction> B2(n,1);
				Matrix<Fraction> check(n,1);
				A2 = A;
				B2 = B;
				A.GaussianElimination(&B);
				check = A2*B;
				double dist = check.distance(B2);
				if (dist > 1) {
					cout << "    dist = " << dist << endl;
					A2.print(B2);
					cout << "  ====================  " << endl;
					B.print();
					breaked = true;
					break;
				}
			}
			if(breaked)
				break;
		}
		if(breaked)
			break;
	}
}


int main()
{
	//printTest();
	//basicMatrixOperations();
	//TriangulateTest();
	//GaussianEliminationTest();
	//GaussianEliminationTest2();
	GaussianEliminationTest3();
	//pressureGETest();
	//timeTestGaussian();
	return 0;
}