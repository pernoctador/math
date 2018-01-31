#ifndef _MATH_UTILITIES_
#define _MATH_UTILITIES_


#include <limits>       // std::numeric_limits
#include <string>       // std::string
#include <sstream>      // std::ostringstream
#include <utility>      // std::pair
#include <cmath> 	//better than math.h
#include <iostream>

using namespace std;

template <class U, class V>
ostream& operator<<(ostream& os, const pair<U,V> &p)
{
	os << "(" << p.first << " , " << p.second << ")";
	return os;
}

template<typename T>
inline string tostr(T value) {
    ostringstream s;
    s.precision(numeric_limits<T>::digits10);
    s << value;
    return s.str();
}

inline double root_d(double base, long exp)
{
	double x = log(base)/log(exp);	//cout << "x0 = " << x << endl;

	//Newton
	double a,b,c,d, prevX = 0;
	a =1.0/exp;

	int cont = 0;
	while(abs(x - prevX) > 1e-14 && cont < 100000)
	{
		prevX = x;
		cont++;

		b = (exp-1) * x;
		c = pow(x,exp-1);
		d = base/c;
		x = a * (b + d);
	}
	return x;
}

#endif