#ifndef _Matrix_H_
#define _Matrix_H_

#include "../utilities/math_utilities.h"
#include <cmath> 	//better than math.h
#include <vector>
#include <iostream>
#include <iomanip>		//setw
#include <exception>

using namespace std;

class zeroRowsOrCols: public exception
{
  virtual const char* what() const throw()
  {
    return "Error: ammount of rows and columns must be greater than 0.";
  }
} zeroCells;

class wrongDimensions: public exception
{
  virtual const char* what() const throw()
  {
    return "Error: wrong dimensions in matrix operation.";
  }
} wrongDim;

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
	void operator=(T v[]);

	void Zero();
	void nameElements();

	bool operator==(Matrix<T> B);

	pair<unsigned,unsigned> size(){return pair<unsigned,unsigned>(rows, cols);}

	void t();
	Matrix<T> tr() const;

	T& operator() (unsigned row, unsigned col){return M[row*rcont + col*ccont];}	//i won't check for limits to improve performance... later i'll check if it makes sense
	T  operator() (unsigned row, unsigned col) const {return M[row*rcont + col*ccont];}

	void print() const;


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

	int GaussianElimination();

private:
	T* M;
	bool transpose = false;
	unsigned rows;
	unsigned cols;
	unsigned rcont;
	unsigned ccont = 1;

	T& elem (unsigned row, unsigned col){return M[row*rcont + col*ccont];}
	T  elemConst (unsigned row, unsigned col) const {return M[row*rcont + col*ccont];}
	void swapRow(unsigned ,unsigned );
};

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
			//cout << "M[" << i <<  "] = B.M[" << i << "] => " << M[i] << " = " << B.M[i] << endl;
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
			elem(i,j) = v[(i*cols)+j];
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
			elem(i,j) = v[(i*cols)+j];
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
			if(elem(i,j) != B(i,j))
			{
				//cout << i << ", " << j << " : elem=" << elem(i,j) << " , B=" << B(i,j) << endl; 
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
Matrix<T> Zero(unsigned size)
{
	Matrix<T> res(size);
	for(unsigned i = 0; i < size; i++)
	{
		for(unsigned j = 0; j < size; j++)
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
void Matrix<T>::print() const
{
	unsigned maxSize = 1;
	unsigned elemSize;
	for(unsigned i = 0; i < rows; i++)
	{
		for(unsigned j = 0; j < cols; j++)
		{
			elemSize = tostr(elemConst(i,j)).size();
			maxSize = max(maxSize, elemSize);
		}
	}
	//cout << "maxSize: " << maxSize << endl;

	cout << "╭";

	for (unsigned j = 0; j < cols - 1; j++) {
		cout << setw(maxSize) << elemConst(0, j) << ", ";
	}

	cout << setw(maxSize) << elemConst(0, cols-1) << "╮" << endl;

	for (unsigned i = 1; i < rows - 1; i++) {
		cout << "│";

		for (unsigned j = 0; j < cols - 1; j++) {
			cout << setw(maxSize) << elemConst(i, j) << ", ";
		}

		cout << setw(maxSize) << elemConst(i, cols-1) << "│" << endl;
	}

	cout << "╰";

	for (unsigned j = 0; j < cols - 1; j++) {
		cout << setw(maxSize) << elemConst(rows-1, j) << ", ";
	}

	cout << setw(maxSize) << elemConst(rows-1, cols-1) << "╯" << endl/*;

	cout << "***********" << endl << "t = " << boolalpha << transpose << endl << "rows = " << rows << endl << "cols = " << cols << endl << "rcont = " << rcont << endl;
	cout << "ccont = " << ccont << endl*/ << endl;
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
				res(i,j) = elemConst(i,j) + m(i,j);
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
				elem(i,j) += m(i,j);
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
			elem(i,j) *= e; 
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
				res(i,j) = elemConst(i,j) - m(i,j);
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
				elem(i,j) -= m(i,j);
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
			res(i,j) = elemConst(i,j) - e; 
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
			elem(i,j) -= e; 
		}
	}
}

template <class T>
Matrix<T> Matrix<T>::operator*(Matrix<T>& m)
{
	Matrix<T> res(rows, m.cols);
	if(cols != m.rows)
		throw wrongDim;
	else
	{
		for(unsigned i = 0; i < rows; i++)
		{
			for(unsigned j = 0; j < m.cols; j++)
			{
				res(i,j) = 0;
				for(unsigned k = 0; k < cols; k++)
				{
					res(i,j) += elemConst(i,k) * m(k,j);
				}
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
			elem(i,j) *= e; 
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
	if(i != j && i >= 0 && j >= 0 && i < rows && j < cols)
	{
		T aux;
		for(unsigned k = 0; k < cols; k++)
		{
			aux = elem(i,k);
			elem(i,k) = elem(j,k);
			elem(j,k) = aux;
		}
	}
}

//replace original matrix. Returns operations value (for determinant).
//I advice to use Fraction as T if the original matrices have only integers.
template <class T>
int Matrix<T>::GaussianElimination()
{
	int det = 1;
	for(unsigned k = 0; k < min(rows, cols); k++)
	{
		T maxAbs = abs<T>(elem(k,k));
		unsigned pibot = k;
		for(unsigned m = k+1; m < rows; m++)
		{
			if(abs<T>(elem(m,k)) > maxAbs)
			{
				maxAbs = abs<T>(elem(m,k));
				pibot = m;
			}
		}
		if(elem(pibot,k) == 0)
		{
			cout << "Matrix is singular" << endl;	//in Gaussian Elimination this should not always be an exception
			det = 0;
		}
		else
		{
			if(k != pibot)
			{
				swapRow(k,pibot);
				det = -det;
			}

			for(unsigned i = k+1; i < rows; i++)
			{
				T f = elem(i,k) / elem(k,k);

				for(unsigned j = k+1; j < cols; j++)
				{
					elem(i,j) -= elem(k,j) * f;
				}

				elem(i,k) = 0;
			}
		}
	}

	return det;
}

#endif