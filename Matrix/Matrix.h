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
	Matrix(int size);
	~Matrix(){}

	void print() const;
	
	pair<int,int> size(){return pair<int,int>(rows, cols);}

	void t(){transpose = -transpose; int aux = cols; cols = rows; rows = aux;} //transpose Matrix  //WIP. needs refactoring

	T& operator()(int row, int col){if(transpose) return matrix[col][row]; else return matrix[row][col];}	//WIP. needs refactoring
	T elem(int row, int col) const {if(transpose) return matrix[col][row]; else return matrix[row][col];}
	//Idk the refactoring's name, but the idea is to take away the if and make: t(){/*change what operator() does*/}

	Matrix<T> operator+(Matrix<T>& m);
	Matrix<T> operator+(T e);
	Matrix<T> operator-(Matrix<T>& m);
	Matrix<T> operator-(T e);
	Matrix<T> operator*(Matrix<T>& m);
	Matrix<T> operator*(T e);

private:
	vector<vector<T> > matrix;
	bool transpose;
	int cols;
	int rows;
};

template <class T>
Matrix<T> Id(int size)
{
	Matrix<T> res(size);
	for(int i = 0; i < size; i++)
	{
		res(i,i) = (T)1;
	}
	return res;
}

template <class T>
Matrix<T>::Matrix(int size)
{
	matrix = vector<vector<T> >(size, vector<T>(size,0));
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
			elemSize = tostr(elem(i,j)).size();
			maxSize = max(maxSize, elemSize);
		}
	}

	cout << "╭";

	for (int j = 0; j < cols - 1; j++) {
		cout << setw(maxSize) << elem(0, j) << ", ";
	}

	cout << setw(maxSize) << elem(0, cols-1) << "╮" << endl;

	for (int i = 1; i < rows - 1; i++) {
		cout << "│";

		for (int j = 0; j < cols - 1; j++) {
			cout << setw(maxSize) << elem(i, j) << ", ";
		}

		cout << setw(maxSize) << elem(i, cols-1) << "│" << endl;
	}

	cout << "╰";

	for (int j = 0; j < cols - 1; j++) {
		cout << setw(maxSize) << elem(rows-1, j) << ", ";
	}

	cout << setw(maxSize) << elem(rows-1, cols-1) << "╯" << endl;
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
				res(i,j) = elem(i,j) + m(i,j);
			}
		}
	}
	return res;
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
				res(i,j) = elem(i,j) - m(i,j);
			}
		}
	}
	return res;
}

template <class T>
Matrix<T> Matrix<T>::operator-(T e)
{
	Matrix<T> res(*this);

	for(int i = 0; i < rows; i++)
	{
		for(int j = 0; j < cols; j++)
		{
			res(i,j) -= e; 
		}
	}
	return res;
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
					res(i,j) += elem(i,k) * m(k,j);
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

#endif