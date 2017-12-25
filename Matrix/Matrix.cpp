#include "Matrix.h"



/*
template <class T>
ostream& Matrix<T>::operator<<(ostream& os, const Matrix<T>& m)
{
	os << "╭";

	for (int j = 0; j < m.cols - 1; j++) {
		os << setw(3) << m.matrix[0][j] << ", ";
	}

	os << setw(3) << m.matrix[0][m.cols - 1] << "╮" << endl;

	for (int i = 1; i < m.rows - 1; i++) {
		os << "│";

		for (int j = 0; j < m.cols - 1; j++) {
			os << setw(3) << m.matrix[i][j] << ", ";
		}

		os << setw(3) << m.matrix[i][m.cols - 1] << "│" << endl;
	}

	os << "╰";

	for (int j = 0; j < m.cols - 1; j++) {
		os << setw(3) << m.matrix[m.rows - 1][j] << ", ";
	}

	os << setw(3) << m.matrix[m.ows - 1][m.cols - 1] << "╯" << endl;

	return os;
}
*/