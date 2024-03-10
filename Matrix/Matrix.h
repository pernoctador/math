#ifndef _Matrix_H_
#define _Matrix_H_

#include "../utilities/math_utilities.h"
#include <cmath> 	//better than math.h
#include <vector>
#include <iostream>
#include <iomanip>		//setw
#include <exception>
// if ur going to use Random():
#include <algorithm>
#include <time.h>
#include <random>

using namespace std;

class zeroRowsOrCols: public exception
{
  virtual const char* error() const throw()
  {
    return "Error: ammount of rows and columns must be greater than 0.";
  }
} zeroCells;

class wrongDimensions: public exception
{
  virtual const char* error() const throw()
  {
    return "Error: wrong dimensions in matrix operation.";
  }
} wrongDim;

class needSquareMatrix: public exception
{
  virtual const char* error() const throw()
  {
    return "Error: matrix must be square.";	// QR?
  }
} squareMatrix;

class needPositiveDefinite: public exception
{
  virtual const char* error() const throw()
  {
    return "Error: matrix must be positive-definite.";	//for cholesky
  }
} posDef;

class outOfBounds: public exception
{
  virtual const char* error() const throw()
  {
    return "Error: Element out of matrix's bounds.";	//for cholesky
  }
} wrongElem;

template <class T>
class Matrix {	//intended for math matrix
public:
	//all constructors are uninitialized matrixes
	Matrix(unsigned rows, unsigned cols);
	Matrix(const Matrix<T> &B);
	Matrix(vector<T> &horizontal);
	Matrix(unsigned size);
	~Matrix();

	void operator=(Matrix<T> B);
	void operator=(vector<T>& v);
	void operator=(const vector<T>& v);
	void operator=(T v[]);

	void Id();
	void Zero();
	void nameElements();
	void Random(int from, int to);

	bool operator==(Matrix<T> B);
	bool operator==(T v[]);

	bool operator!=(Matrix<T> B){return !(*this == B);};
	bool operator!=(T v[]){return !(*this == v);};

	pair<unsigned,unsigned> size() const {return pair<unsigned,unsigned>(rows, cols);}

	void t();	// transpose matrix in O(1)
	Matrix<T> tr() const;	// returns transposed matrix properly arranged in memory

	T& operator() (unsigned row, unsigned col){if(row >= rows || col >= cols) throw wrongElem; return M[row*rcont + col*ccont];}
	T  operator() (unsigned row, unsigned col) const {if(row >= rows || col >= cols) throw wrongElem; return M[row*rcont + col*ccont];}

	void print();
	void print(Matrix<T>);

	Matrix<T> operator+(Matrix<T>& m);
	void operator+=(Matrix<T>& m);
	Matrix<T> operator+(T e);
	void operator+=(T e);

	Matrix<T> operator-(Matrix<T>& m);
	void operator-=(Matrix<T>& m);
	Matrix<T> operator-(T e);
	void operator-=(T e);

	Matrix<T> operator*(Matrix<T>& m);
	Matrix<T> operator*(T e);
	void operator*=(T e);

	double distance(Matrix<T> B);

	int GaussianElimination();
	double GaussianElimination(Matrix<T>* extra);


private:
	T* M;
	bool transpose = false;
	unsigned rows;
	unsigned cols;
	unsigned rcont;
	unsigned ccont = 1;

	Matrix();	//Null matrix

	void draw(T v[], unsigned);
	void swapRow(unsigned ,unsigned );
	int triangulate(Matrix<T>* extra);
};

template <class T>
Matrix<T>::Matrix()	//Null matrix
{
	rows = 0;
	cols = 0;
	rcont = 0;
	M = new T[0];
}

template <class T>
Matrix<T>::Matrix(unsigned r, unsigned c)
{
	if(r < 1 || c < 1)
		throw zeroCells;
	rows = r;
	cols = c;
	rcont = cols;
	M = new T[r*c];
}

template <class T>
Matrix<T>::Matrix(const Matrix<T> &B)
{
	rows = B.rows;
	cols = B.cols;
	rcont = B.rcont;
	ccont = B.ccont;
	M = new T[rows * cols];
	for(unsigned i = 0; i < rows*cols; i++)
		M[i] = B.M[i];
	transpose = B.transpose;
}

template <class T>
Matrix<T>::Matrix(vector<T> &horizontal)
{
	if(horizontal.size() < 1)
		throw zeroCells;
	rows = 1;
	cols = horizontal.size();
	rcont = cols;
	M = new T[rows * cols];
}
template <class T>
Matrix<T>::Matrix(unsigned size)
{
	if(size < 1)
		throw zeroCells;
	rows = size;
	cols = size;
	rcont = cols;
	M = new T[size*size];
}

template <class T>
Matrix<T>::~Matrix()
{
	delete[] M;
}

template <class T>
void Matrix<T>::operator=(Matrix<T> B)	//if B was transposed in O(1), *this will be equal to B but without the flag
{
	//if(rows*cols != B.rows*B.cols)	//This is the least B must ensure

	if(rows != B.rows || cols != B.cols)//However, this might help avoid mistakes
		throw wrongDim;

	if(!B.transpose)
	{
		for(unsigned i = 0; i < rows*cols; i++)
		{
			M[i] = B.M[i];
		}

	}
	else
	{
		for(unsigned i = 0; i < rows; i++)
		{
			for(unsigned j = 0; j < cols; j++)
			{
				M[i*cols + j] = B.M[j*rows + i];
			}
		}
	}
	rcont = cols;
	ccont = 1;
	transpose = false;
}

template <class T>
void Matrix<T>::operator=(vector<T>& v)
{
	if(v.size() != rows*cols)
		throw wrongDim;

	for(unsigned i = 0; i < rows; i++)
	{
		for(unsigned j = 0; j < cols; j++)
		{
			(*this)(i,j) = v[(i*cols)+j];
		}
	}
}

template <class T>
void Matrix<T>::operator=(const vector<T>& v)
{
	if(v.size() != rows*cols)
		throw wrongDim;

	for(unsigned i = 0; i < rows; i++)
	{
		for(unsigned j = 0; j < cols; j++)
		{
			(*this)(i,j) = v[(i*cols)+j];
		}
	}
}

template <class T>
void Matrix<T>::operator=(T v[])
{
	//WARNING: can't check for size

	for(unsigned i = 0; i < rows; i++)
	{
		for(unsigned j = 0; j < cols; j++)
		{
			(*this)(i,j) = v[(i*cols)+j];
		}
	}
}

template <class T>
bool Matrix<T>::operator==(Matrix<T> B)
{
	if(rows != B.rows || cols != B.cols)
		return false;

	for(unsigned i = 0; i < rows; i++)
	{
		for(unsigned j = 0; j < cols; j++)
		{
			if((*this)(i,j) != B(i,j))
			{
				return false;
			}
		}
	}
	return true;
}

template <class T>
bool Matrix<T>::operator==(T v[]) {
	for(unsigned i = 0; i < rows; i++)
	{
		for(unsigned j = 0; j < cols; j++)
		{
			if((*this)(i,j) != v[(i*cols)+j])
			{
				return false;
			}
		}
	}
	return true;
}

template <class T>
Matrix<T> Id(unsigned size)
{
	Matrix<T> res(size);
	for(unsigned i = 0; i < size; i++)
	{
		for(unsigned j = 0; j < size; j++)
		{
			res(i,j) = (i==j);
		}
	}
	return res;
}

template <class T>
void Matrix<T>::Id()
{
	for(unsigned i = 0; i < rows; i++)
	{
		for(unsigned j = 0; j < cols; j++)
		{
			(*this)(i,j) = (i==j);
		}
	}
}

template <class T>
Matrix<T> Zero(unsigned rows, unsigned cols)
{
	Matrix<T> res(rows,cols);
	for(unsigned i = 0; i < rows; i++)
	{
		for(unsigned j = 0; j < cols; j++)
		{
			res(i,j) = 0;
		}
	}
	return res;
}

template <class T>
void Matrix<T>::Zero()
{
	for(unsigned i = 0; i < rows * cols; i++)
	{
		M[i] = 0;
	}
}

template <class T>
void Matrix<T>::nameElements()
{
	for(unsigned i = 0; i < rows*cols; i++)
	{
		M[i] = i;
	}
}

template <class T>
void Matrix<T>::t()
{
	swap(rows, cols);
	swap(rcont, ccont);
	transpose = !transpose;
}

template <class T>
void Matrix<T>::Random(int from, int to)
{
	for(unsigned i = 0; i < rows*cols; i++)
	{
		M[i] = (rand() % (to-from+1)) + from;
	}
}

template <class T>
Matrix<T> Matrix<T>::tr() const
{
	if(transpose)	//was transposed in O(1), so i just need to copy what i have in memory and mark it as not transposed.
	{
		Matrix<T> res(*this);
		res.t();
		return res;
	}
	else		
	{
		Matrix<T> res(this->cols, this->rows);
		for(unsigned i = 0; i < rows; i++)
		{
			for(unsigned j = 0; j < cols; j++)
			{
				res.M[j*rows + i] = M[i*cols + j];
			}
		}
		return res;
	}
}

template <class T>
void Matrix<T>::print() {
	T vv[] = {};
	draw(vv, 0);
}
template <class T>
void Matrix<T>::print(Matrix<T> B) {
	if(B.rows == rows) {
		draw(B.M, B.cols*B.rows);
	}
}
template <class T>
void Matrix<T>::draw(T v[], unsigned size)
{
	//v ether have 0 elements or same rows as this
	unsigned vcols = size/rows;
	unsigned maxSize = 1;
	unsigned elemSize;
	for(unsigned i = 0; i < rows; i++)
	{
		for(unsigned j = 0; j < cols; j++)
		{
			elemSize = tostr((*this)(i,j)).size();
			maxSize = max(maxSize, elemSize);
		}
		for(unsigned j = 0; j < vcols; j++)
		{
			elemSize = tostr(v[i*vcols + j]).size();
			maxSize = max(maxSize, elemSize);
		}
	}

	for (unsigned i = 0; i < rows; i++) {

		for (unsigned j = 0; j < cols - 1; j++) {
			cout << setw(maxSize) << (*this)(i, j) << ", ";
		}

		cout << setw(maxSize) << (*this)(i, cols-1);

		if (vcols > 0) {
			cout << " | " << setw(maxSize) << v[i*vcols];

			for (unsigned j = 1; j < vcols; j++) {
				cout << ", " << setw(maxSize) << v[i*vcols + j];
			}
		}

		cout << endl;
	}

	cout << endl;
}

template <class T>
ostream& operator<<(ostream& os, const Matrix<T> &m)
{
	unsigned maxSize = 1;
	unsigned elemSize;
	for(unsigned i = 0; i < m.size().first; i++)
	{
		for(unsigned j = 0; j < m.size().second; j++)
		{
			elemSize = tostr(m(i,j)).size();
			maxSize = max(maxSize, elemSize);
		}
	}

	os << "╭";

	for (unsigned j = 0; j < m.size().second - 1; j++) {
		cout << setw(maxSize) << m(0, j) << ", ";
	}

	os << setw(maxSize) << m(0, m.size().second-1) << "╮" << endl;

	for (unsigned i = 1; i < m.size().first - 1; i++) {
		os << "│";

		for (unsigned j = 0; j < m.size().second - 1; j++) {
			os << setw(maxSize) << m(i, j) << ", ";
		}

		os << setw(maxSize) << m(i, m.size().second-1) << "│" << endl;
	}

	os << "╰";

	for (unsigned j = 0; j < m.size().second - 1; j++) {
		os << setw(maxSize) << m(m.size().first-1, j) << ", ";
	}

	os << setw(maxSize) << m(m.size().first-1, m.size().second-1) << "╯" << endl/*;

	os << "***********" << endl << "t = " << boolalpha << transpose << endl << "rows = " << rows << endl << "cols = " << cols << endl << "rcont = " << rcont << endl;
	os << "ccont = " << ccont << endl*/ << endl;
	return os;
}

template <class T>
Matrix<T> Matrix<T>::operator+(Matrix<T>& m)
{
	Matrix<T> res(*this);
	if(rows != m.rows || cols != m.cols)
		throw wrongDim;
	else
	{
		for(unsigned i = 0; i < rows; i++)
		{
			for(unsigned j = 0; j < cols; j++)
			{
				res(i,j) = (*this)(i,j) + m(i,j);
			}
		}
	}
	return res;
}

template <class T>
void Matrix<T>::operator+=(Matrix<T>& m)
{
	if(this->size() != m.size())
		throw wrongDim;
	else
	{
		for(unsigned i = 0; i < rows; i++)
		{
			for(unsigned j = 0; j < cols; j++)
			{
				(*this)(i,j) += m(i,j);
			}
		}
	}
}

template <class T>
Matrix<T> Matrix<T>::operator+(T e)
{
	Matrix<T> res(*this);

	for(unsigned i = 0; i < rows; i++)
	{
		for(unsigned j = 0; j < cols; j++)
		{
			res(i,j) *= e; 
		}
	}
	return res;
}

template <class T>
void Matrix<T>::operator+=(T e)
{
	for(unsigned i = 0; i < rows; i++)
	{
		for(unsigned j = 0; j < cols; j++)
		{
			(*this)(i,j) *= e; 
		}
	}
}

template <class T>
Matrix<T> Matrix<T>::operator-(Matrix<T>& m)
{
	Matrix<T> res(*this);

	if(this->size() != m.size())
		throw wrongDim;
	else
	{
		for(unsigned i = 0; i < rows; i++)
		{
			for(unsigned j = 0; j < cols; j++)
			{
				res(i,j) = (*this)(i,j) - m(i,j);
			}
		}
	}
	return res;
}

template <class T>
void Matrix<T>::operator-=(Matrix<T>& m)
{
	if(this->size() != m.size())
		throw wrongDim;
	else
	{
		for(unsigned i = 0; i < rows; i++)
		{
			for(unsigned j = 0; j < cols; j++)
			{
				(*this)(i,j) -= m(i,j);
			}
		}
	}
}

template <class T>
Matrix<T> Matrix<T>::operator-(T e)
{
	Matrix<T> res(*this);

	for(unsigned i = 0; i < rows; i++)
	{
		for(unsigned j = 0; j < cols; j++)
		{
			res(i,j) = (*this)(i,j) - e; 
		}
	}
	return res;
}

template <class T>
void Matrix<T>::operator-=(T e)
{
	for(unsigned i = 0; i < rows; i++)
	{
		for(unsigned j = 0; j < cols; j++)
		{
			(*this)(i,j) -= e; 
		}
	}
}

template <class T>
Matrix<T> Matrix<T>::operator*(Matrix<T>& m) {
	if(cols != m.rows)
		throw wrongDim;

	Matrix<T> res(rows, m.cols);

	for(unsigned i = 0; i < rows; i++)
	{
		for(unsigned j = 0; j < m.cols; j++)
		{
			res(i,j) = 0;
			for(unsigned k = 0; k < cols; k++)
			{
				T a = (*this)(i,k);
				if(a == (double)-70 || a == (double)-876 || a == (double)934) {
					T b = m(k,j);
					T semi = a * b;
					double semid = (double)a * (double)b;
					T ress = res(i,j);
					double ressd = (double)ress;

					T tot =  semi + ress;
					double totd = semid + ressd;

					if(abs(totd - (double)tot) > 1e-10) {
						cout << a << " * " << b << " + " << ress << " == " << tot << " != " << totd << endl;
					}
				}
				res(i,j) += (*this)(i,k) * m(k,j);
			}
		}
	}

	return res;
}

template <class T>
Matrix<T> Matrix<T>::operator*(T e)
{
	Matrix<T> res(*this);

	for(unsigned i = 0; i < rows; i++)
	{
		for(unsigned j = 0; j < cols; j++)
		{
			res(i,j) *= e; 
		}
	}
	return res;
}

template <class T>
void Matrix<T>::operator*=(T e)
{
	for(unsigned i = 0; i < rows; i++)
	{
		for(unsigned j = 0; j < cols; j++)
		{
			(*this)(i,j) *= e; 
		}
	}
}

template <class T>
inline T abs(T e)
{
	if(e < 0)
		e = e - e*2;
	return e;
}

template <class T>
void Matrix<T>::swapRow(unsigned i, unsigned j)
{
	if(i != j && i < rows && j < rows)
	{
		T aux;
		for(unsigned k = 0; k < cols; k++)
		{
			aux = (*this)(i,k);
			(*this)(i,k) = (*this)(j,k);
			(*this)(j,k) = aux;
		}
	}
}

template <class T>
double Matrix<T>::distance(Matrix<T> B) {
	if(cols != B.cols || rows != B.rows) {
		return -1;
	}
	T dist = 0;
	for(unsigned i = 0; i < rows; i++) {
		for(unsigned j = 0; j < cols; j++) {
			double a = (*this)(i,j);
			double b = B(i,j);
			dist += abs(a-b);
		}
	}
	return (double)dist;
}

template <class T>
int Matrix<T>::triangulate(Matrix<T>* extra) {
	int detSign = 1;
	//this->print(*extra);
	for(unsigned k = 0; k < min(rows, cols); k++) {
		T maxAbs = abs<T>((*this)(k,k));
		unsigned pibot = k;
		for(unsigned m = k+1; m < rows; m++)
		{
			if(abs<T>((*this)(m,k)) > maxAbs)
			{
				maxAbs = abs<T>((*this)(m,k));
				pibot = m;
			}
		}
		if(abs((*this)(pibot,k)) < 1e-12)
		{
			//cerr << "Matrix is singular" << endl;	//in Gaussian Elimination this should not always be an exception
			detSign = 0;
		}
		else
		{
			if(k != pibot)
			{
				swapRow(k,pibot);
				if(extra->rows > 0) {
					extra->swapRow(k, pibot);
				}
				detSign = -detSign;
				//this->print(*extra);
			}

			for(unsigned i = k+1; i < rows; i++)
			{
				T f = (*this)(i,k) / (*this)(k,k);

				for(unsigned j = k+1; j < cols; j++)
				{
					(*this)(i,j) -= (*this)(k,j) * f;
				}

				(*this)(i,k) = 0;

				for(int j = 0; j < (int)extra->cols; j++)
				{
					(*extra)(i,j) -= (*extra)(k,j) * f;
				}
			}
			//this->print(*extra);
		}
	}
	return detSign;
}
//replace original matrix. Returns operations value (for determinant).
//I advice to use Fraction as T if the original matrices have only integers.
template <class T>
int Matrix<T>::GaussianElimination()
{
	Matrix<T> extra;
	return triangulate(&extra);
}

//replace original matrix. Returns operations value (for determinant).
//I advice to use Fraction as T if the original matrices have only integers.
template <class T>
double Matrix<T>::GaussianElimination(Matrix<T>* extra)
{
	if(extra->rows != rows)
		throw wrongDim;

	double determinant = this->triangulate(extra);

	//this->print(*extra);

	if(determinant != 0) {

		for(int i = rows-1; i >= 0; i--) {
			for(int j = cols-1; j >= i+1; j--) {
				for(unsigned k = 0; k < extra->cols; k++) {
					//sub
					(*extra)(i,k) -= (*this)(i,j) * (*extra)(j,k);
				}
			}
			//div
			(*extra)(i,0) /= (*this)(i,i);
			determinant *= (double)(*this)(i,i);
			(*this)(i,i) = 1;
		}
	}
	return determinant;
}

#endif