#ifndef _MATH_UTILITIES_
#define _MATH_UTILITIES_


#include <limits>       // std::numeric_limits
#include <string>       // std::string
#include <sstream>      // std::ostringstream
#include <utility>      // std::pair
#include <cmath> 	//better than math.h

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

inline double root_d(long base, long exp)
{
	double s=1, t = base, r = 0;
	for(int i = 0; i < exp*2 && s <= t && abs(r-base) > exp; i++)
	{
		r = pow(round((t+s)/2), exp);
		if(r < base)
			s = floor((t+s)/2);
		if(r > base)
			t = ceil((t+s)/2);
		if(r == base)
			return round((t+s)/2);
	}

	double x = round((t+s)/2);

	//second: Newton
	double a,b,c,d, prevX = 0;
	a =1.0/exp;
	//cout << "a: " << a << endl;

	
	//cout << "x: " << x << endl;

	int cont = 0;
	double dif = base;
	//cout << "	****	dist = " << (double)abs(x - prevX) << endl << endl;
	while(abs(x - prevX) > 1e-14 && abs(x - prevX) < dif && cont < 100000)
	{
		dif = abs(x - prevX);
		prevX = x;
		cont++;

		b = (exp-1) * x;
		//cout << "b: " << b << endl;
		c = pow(x,exp-1);
		//cout << "c: " << c << endl;
		//cout << c << " = pow(" << x << ", " << exp-1 << ")" << endl;
		//check here:
		d = base/c;
		//cout << "d: " << d << endl;
		x = a * (b + d);
		//cout << "x: " << x << " = " << (double)x << " , prevX = " << prevX << endl << endl;
		//cout << "	****	dist = " << (double)abs(x - prevX) << endl << endl;
	}

	if (abs(x - prevX) >= dif)
	{
		//cout << "	Getting worst: actualDif: " << (double)abs(x - prevX) << " , prevDif: " << dif << endl;
		return prevX;
	}

	//cout << "	 -- : " << (double)abs(x - prevX) << " , " << dif << " , " << cont << endl;

	return x;
}

#endif