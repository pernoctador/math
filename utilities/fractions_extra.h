#ifndef _FRACTIONS_EXTRA_
#define _FRACTIONS_EXTRA_


#include <climits>		//LONG_MAX
#include <cmath> 	//better than math.h
#include <iostream>

using namespace std;


//Density of doubles
inline long doublesIn(double first, double last) 
{
    long res;

	// *reinterpret_cast<long *>(&first) return the bit pattern representing a double as a 64-bit unsigned integer.
    //cout << endl << last << " - " << first << " = " <<  *reinterpret_cast<long *>(&last) << " - " << *reinterpret_cast<long *>(&first) << endl;
    res = *reinterpret_cast<long *>(&last) - *reinterpret_cast<long *>(&first);
    return res;
}

//Density of fractions between first and last, or less.
inline double fractionsIn(double first, double last)
{
    double pi = 3.141592653589793238462643383279502884;
    double max = LONG_MAX;	//i can't use LONG_MAX directly
    double zeroToOne = max/pi * max/pi * 3;	// = approx. amount of numbers in Farey's secuence of order LONG_MAX. 
    double res = 0;

    if(first == 0)
    {
        res = zeroToOne;
        first++;
    }

    for(double i = first; i < last; i++)
    {
        res += zeroToOne/(i * i+1);
        if(i == i+1)
            i = nextafter(i+1, last);	//if this happens, i might not count some fractions, but i don't see another choice
    }
	
    return floor(res);
}

#endif