#ifndef _Matrix_H_
#define _Matrix_H_


#include "../utilities/math_utilities.h"
#include <cmath> 	//better than math.h
#include <vector>
#include <iostream>
#include <iomanip>		//setw

using namespace std;

template <class T>
class Matrix {	//intended for math matrix
public:
	//all constructors are null matrix
	Matrix(){matrix = vector<vector<T> >(1, vector<T>(1,0)); transpose = false; cols = 0; rows = 0;}
	Matrix(int Rows, int Cols){matrix = vector<vector<T> >(Rows, vector<T>(Cols,0)); transpose = false; cols = Cols; rows = Rows;}
	Matrix(const Matrix<T> &M){matrix = M.matrix; transpose = M.transpose; cols = M.cols; rows = M.rows;}
	Matrix(vector<T> &horizontal){matrix = vector<vector<T> >(1, vector<T>(horizontal)); transpose = false; cols = horizontal.size(); rows = 1;}
	Matrix(int size);
	~Matrix(){}

	void print() const;
	
	pair<int,int> size(){return pair<int,int>(rows, cols);}

	void t(){transpose = -transpose; int aux = cols; cols = rows; rows = aux;} //transpose Matrix  //WIP. needs refactoring

	T& operator()(int row, int col){if(transpose) return matrix[col][row]; else return matrix[row][col];}	//WIP. needs refactoring
	T elemConst(int row, int col) const {if(transpose) return matrix[col][row]; else return matrix[row][col];}
	T& elem(int row, int col){if(transpose) return matrix[col][row]; else return matrix[row][col];}	//WIP. needs refactoring
	//Idk the refactor's name, but the idea is to take away the if and make: t(){/*change what operator() does*/}

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

	void swapRow(int,int);

private:
		

	vector<vector<T> > matrix;
	bool transpose;
	int cols;
	int rows;
};

template <class T>
void Matrix<T>::swapRow(int i, int j)
{
	if(i != j && i >= 0 && j >= 0 && i < rows && j < cols)
	{
		if(!transpose)
		{
			vector<T> v = move(matrix[i]);	//this cast matrix[] as rvalue, and use the move assignment. O(1)?
			matrix[i] = move(matrix[j]);
			matrix[j] = move(v);
			
		}
		else
		{
			T aux;
			for(int k = 0; k < cols; k++)	//here I have elements from different vectors.
			{
				aux = elem(i,k);
				elem(i,k) = elem(j,k);
				elem(j,k) = aux;
			}
		}
	}
}

template <class T>
Matrix<T> Id(int size)
{
	Matrix<T> res(size);
	for(int i = 0; i < size; i++)
	{
		res(i,i) = T(1.0);
	}
	return res;
}

template <class T>
Matrix<T>::Matrix(int size)
{
	matrix = vector<vector<T> >(size, vector<T>(size,T(0.0)));
	transpose = false; cols = size; rows = size;
}

template <class T>
void Matrix<T>::print() const
{
	//cout << "rows: " << rows << ", cols: " << cols << endl;
	//cout << "rows: " << matrix.size() << ", cols: " << matrix[0].size() << endl;

	int maxSize = 1;
	int elemSize;
	for(int i = 0; i < rows; i++)
	{
		for(int j = 0; j < cols; j++)
		{
			elemSize = tostr(elemConst(i,j)).size();
			maxSize = max(maxSize, elemSize);
		}
	}
	cout << "maxSize: " << maxSize << endl;

	cout << "╭";

	for (int j = 0; j < cols - 1; j++) {
		cout << setw(maxSize) << elemConst(0, j) << ", ";
	}

	cout << setw(maxSize) << elemConst(0, cols-1) << "╮" << endl;

	for (int i = 1; i < rows - 1; i++) {
		cout << "│";

		for (int j = 0; j < cols - 1; j++) {
			cout << setw(maxSize) << elemConst(i, j) << ", ";
		}

		cout << setw(maxSize) << elemConst(i, cols-1) << "│" << endl;
	}

	cout << "╰";

	for (int j = 0; j < cols - 1; j++) {
		cout << setw(maxSize) << elemConst(rows-1, j) << ", ";
	}

	cout << setw(maxSize) << elemConst(rows-1, cols-1) << "╯" << endl;
}

template <class T>
Matrix<T> Matrix<T>::operator+(Matrix<T>& m)
{
	Matrix<T> res(*this);

	if(this->size() != m.size())
		cout << "Error: in matrix addition, dimensions doesn't match: " << this->size() << " != " << m.size() << endl;
	else
	{
		for(int i = 0; i < rows; i++)
		{
			for(int j = 0; j < cols; j++)
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
		cout << "Error: in matrix addition, dimensions doesn't match: " << this->size() << " != " << m.size() << endl;
	else
	{
		for(int i = 0; i < rows; i++)
		{
			for(int j = 0; j < cols; j++)
			{
				*this(i,j) += m(i,j);
			}
		}
	}
}

template <class T>
Matrix<T> Matrix<T>::operator+(T e)
{
	Matrix<T> res(*this);

	for(int i = 0; i < rows; i++)
	{
		for(int j = 0; j < cols; j++)
		{
			res(i,j) *= e; 
		}
	}
	return res;
}

template <class T>
void Matrix<T>::operator+=(T e)
{
	for(int i = 0; i < rows; i++)
	{
		for(int j = 0; j < cols; j++)
		{
			*this(i,j) *= e; 
		}
	}
}

template <class T>
Matrix<T> Matrix<T>::operator-(Matrix<T>& m)
{
	Matrix<T> res(*this);

	if(this->size() != m.size())
		cout << "Error: in matrix substraction, dimensions doesn't match: " << this->size() << " != " << m.size() << endl;
	else
	{
		for(int i = 0; i < rows; i++)
		{
			for(int j = 0; j < cols; j++)
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
		cout << "Error: in matrix substraction, dimensions doesn't match: " << this->size() << " != " << m.size() << endl;
	else
	{
		for(int i = 0; i < rows; i++)
		{
			for(int j = 0; j < cols; j++)
			{
				*this(i,j) -= m(i,j);
			}
		}
	}
}

template <class T>
Matrix<T> Matrix<T>::operator-(T e)
{
	Matrix<T> res(*this);

	for(int i = 0; i < rows; i++)
	{
		for(int j = 0; j < cols; j++)
		{
			res(i,j) = elemConst(i,j) - e; 
		}
	}
	return res;
}

template <class T>
void Matrix<T>::operator-=(T e)
{
	for(int i = 0; i < rows; i++)
	{
		for(int j = 0; j < cols; j++)
		{
			*this(i,j) -= e; 
		}
	}
}

template <class T>
Matrix<T> Matrix<T>::operator*(Matrix<T>& m)
{
	Matrix<T> res(rows, m.cols);
	if(cols != m.rows)
		cout << "Error: in matrix multiplication, dimensions doesn't match: " << cols << " != " << m.rows << endl;
	else
	{
		for(int i = 0; i < rows; i++)
		{
			for(int j = 0; j < m.cols; j++)
			{
				for(int k = 0; k < cols; k++)
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

	for(int i = 0; i < rows; i++)
	{
		for(int j = 0; j < cols; j++)
		{
			res(i,j) *= e; 
		}
	}
	return res;
}

template <class T>
void Matrix<T>::operator*=(T e)
{
	for(int i = 0; i < rows; i++)
	{
		for(int j = 0; j < cols; j++)
		{
			*this(i,j) *= e; 
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

//replace original matrix. Returns operations value (for determinant).
//I advice to use Fraction as T if the original matrices have only integers.
template <class T>
int Matrix<T>::GaussianElimination(/*Matrix<T>& Extra = Matrix<T>()*/)	//extra is optional
{
	//Extra should be a vector.
	int det = 1;
	for(int k = 0; k < min(rows, cols); k++)
	{
		T maxAbs = abs<T>(elem(k,k));
		int pibot = k;
		for(int m = k+1; m < rows; m++)
		{
			if(abs<T>(elem(m,k)) > maxAbs)
			{
				maxAbs = abs<T>(elem(m,k));
				pibot = m;
			}
		}
		if(elem(pibot,k) == 0)
		{
			cout << "Matrix is singular" << endl;
			return det;
		}

		if(k != pibot)
		{
			swapRow(k,pibot);
			det = -det;
		}

		for(int i = k+1; i < rows; i++)
		{
			T f = elem(i,k) / elem(k,k);

			for(int j = k+1; j < cols; j++)
			{
				elem(i,j) -= elem(k,j) * f;
			}
			//Extra(i,1) -= Extra(k,1) * f;

			elem(i,k) = 0;
		}
	}

	return det;
}

#endif