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

template<typename T>
inline string tostr(T value) {
    ostringstream s;
    s.precision(numeric_limits<T>::digits10);
    s << value;
    return s.str();
}

#endif