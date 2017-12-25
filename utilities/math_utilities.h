#ifndef _MATH_UTILITIES_
#define _MATH_UTILITIES_


#include <limits>       // std::numeric_limits
#include <string>       // std::string
#include <sstream>      // std::ostringstream
#include <utility>      // std::pair

using namespace std;

template <class U, class V>
ostream& operator<<(ostream& os, const pair<U,V> &p)
{
	os << "(" << p.first << " , " << p.second << ")";
	return os;
}

inline double root(long base, long root)
{
	//based on https://web.archive.org/web/20131227144655/http://metamerist.com/cbrt/cbrt.htm

	const int ebits = 11;
	const int fbits = 52;

	long long i = (long long) base;
	const long long bias = (1 << (ebits-1))-1;
	i = (i - (bias << fbits)) / root + (bias << fbits);

	//now i apply Newton method x4 or halley x3

	return 0;	//WIP
}

template<typename T>
inline string tostr(T value) {
    ostringstream s;
    s.precision(numeric_limits<T>::digits10);
    s << value;
    return s.str();
}

#endif