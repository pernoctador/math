//
// Created by fernando on 22/02/2024.
//

#ifndef DEPRECATED_H
#define DEPRECATED_H

void Matrix<T>::print(bool pretty)
{
    unsigned maxSize = 1;
    unsigned elemSize;
    for(unsigned i = 0; i < rows; i++)
    {
        for(unsigned j = 0; j < cols; j++)
        {
            elemSize = tostr((*this)(i,j)).size();
            maxSize = max(maxSize, elemSize);
        }
    }
    //cout << "maxSize: " << maxSize << endl; ╭ // L'┌'
    if (pretty){cout << "╭";}

    for (unsigned j = 0; j < cols - 1; j++) {
        cout << setw(maxSize) << (*this)(0, j) << ", ";
    }

    cout << setw(maxSize) << (*this)(0, cols-1);
    if (pretty){cout << "╮";}
    cout << endl;
    for (unsigned i = 1; i < rows - 1; i++) {
        if (pretty){cout << "│";}

        for (unsigned j = 0; j < cols - 1; j++) {
            cout << setw(maxSize) << (*this)(i, j) << ", ";
        }

        cout << setw(maxSize) << (*this)(i, cols-1);
        if (pretty){cout << "│";}
        cout << endl;
    }

    if (pretty){cout << "╰";}

    for (unsigned j = 0; j < cols - 1; j++) {
        cout << setw(maxSize) << (*this)(rows-1, j) << ", ";
    }

    cout << setw(maxSize) << (*this)(rows-1, cols-1);
    if (pretty){cout << "│";}
    cout << endl << endl;
}

#endif //DEPRECATED_H
