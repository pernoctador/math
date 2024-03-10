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

void GaussianEliminationTest(unsigned n, Fraction af[], Fraction bf[], double ad[], double bd[]) {
	cout << "First eq test (fractions):" << endl;
	Matrix<Fraction> A(n,n);
	Matrix<Fraction> B(n,1);
	A = af;
	B = bf;
	Matrix<Fraction> A2(n,n);
	Matrix<Fraction> B2(n,1);
	Matrix<Fraction> check(n,1);
	A2 = A;
	B2 = B;

	double det = A.GaussianElimination(&B);
	if(det == 0) {
		cout << "Matrix is singular" << endl;
	} else {
		check = A2*B;
		double dist = check.distance(B2);
		A2.print(B);
		cout << "  ====================  " << endl;
		check.print(B2);
		cout << "Dist = " << dist << endl;
	}

	cout << "First eq test (double):" << endl;
	Matrix<double> C(n,n);
	Matrix<double> D(n,1);
	C = ad;
	D = bd;
	Matrix<double> C2(n,n);
	Matrix<double> D2(n,1);
	Matrix<double> check2(n,1);
	C2 = C;
	D2 = D;

	double det2 = C.GaussianElimination(&D);
	if(det2 == 0) {
		cout << "Matrix is singular" << endl;
	} else {
		check2 = C2*D;
		double dist2 = check2.distance(D2);
		//C2.print(D);
		cout << "  ====================  " << endl;
		check2.print(D2);
		cout << "Dist = " << dist2 << endl;
	}
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
	srand(time(NULL));
	for(int n = 1; n < 50; n++) {
		bool breaked = false;
		cout << n << endl;
		for(int t = 1; t < 9; t++){
			int limit = pow(10,t);
			for(int i = 0; i < 10000000; i++) {
				Matrix<double> A(n,n);
				A.Random(-limit, limit);
				Matrix<double> B(n,1);
				B.Random(-limit,limit);
				Matrix<double> A2(n,n);
				Matrix<double> B2(n,1);
				Matrix<double> check(n,1);
				A2 = A;
				B2 = B;
				double det = A.GaussianElimination(&B);
				if(det != 0) {
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

	Fraction af[] = {-6, -1, 8, 1, 8, -1, -7, 1, 9, -10, 6, -9, -4, -3, 9, 3};
	Fraction bf[] = {2, 8, 3, 7};
	double ad[] = {-6, -1, 8, 1, 8, -1, -7, 1, 9, -10, 6, -9, -4, -3, 9, 3};
	double bd[] = {2, 8, 3, 7};
	GaussianEliminationTest(4, af, bf, ad, bd);

	Fraction cf[] = {-9.99907e+07, -9.99944e+07, -9.99855e+07,
					-9.99825e+07, -9.99713e+07, -9.99829e+07,
					-9.99831e+07, -9.99868e+07, -9.99778e+07};
	Fraction df[] = {-9.99695e+07,
					-9.99742e+07,
					-9.99896e+07};
	double cd[] = {-9.99907e+07, -9.99944e+07, -9.99855e+07, -9.99825e+07, -9.99713e+07, -9.99829e+07, -9.99831e+07, -9.99868e+07, -9.99778e+07};
	double dd[] = {-9.99695e+07, -9.99742e+07, -9.99896e+07};
	GaussianEliminationTest(3, cf, cf, cd, dd);
	//pressureGETest();
	//timeTestGaussian();
	return 0;
}