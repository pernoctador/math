#ifndef _MATH_UTILITIES_
#define _MATH_UTILITIES_


#include <limits>       // std::numeric_limits
#include <string>       // std::string
#include <sstream>      // std::ostringstream
#include <utility>      // std::pair
#include <cmath> 	//better than math.h
#include <vector>

#define log2Int(X) ((unsigned) (8*sizeof (unsigned long long) - __builtin_clzll((X)) - 1)) 

using namespace std;

template <class U, class V>
ostream& operator<<(ostream& os, const pair<U,V> &p)
{
	os << "(" << p.first << " , " << p.second << ")";
	return os;
}

template <class U>
ostream& operator<<(ostream& os, const vector<U> &p)
{
	os << "[";
	int length = p.size() -1;
	for(int i = 0; i < length; i++)
	{
		os << p[i] << ", ";
	}

	if(p.size() > 0)
		os << p[p.size()-1] ;
	os << "]";
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