#include "../utilities/math_utilities.h"
#include "Fraction.h"
#include <cmath> 	//better than math.h

//Deprecated code i didn't wanted to loose:

//1) My method to get the fraction representing a double:
/*
	This method is not bad. It actually give on some ocations better results than the JK's iterative method, but on average the other is better and faster.
	Still I like it because is a nice translation from the handwrite method + cicle detection to check if a fraction is a recurring decimal

*/

Fraction MyOldDoubleToFraction(double db)
{
	string value = tostr(db);
	size_t pos = value.find(".");
	string integer = value.substr(0,pos);
  	string decimals= value.substr(pos+1);
  	if(pos == string::npos)
  		decimals = "0";
	// check if it's a repeating (or recurring) decimal. For that, I search for a repetend in decimals:
	//	1. it must be a complete cicle (at least I must found the repetend 2 times). In the code => cicles > 0
	//	2. it would be the first repetend I found.
	//	3. it must reach the end-1 of the decimal part. The -1 is to avoid errors with rounded decimals

  	// First try: O(decimals.size()^3). Even if it looks slow, decimals.size() <= 15 (18 if in the future I use long double), so it's actually O(1).
  	//I have to check Floyd's tortoise and hare. It's not the same problem but maybe I can get inspired and reduce complexity.
  	if(decimals.size() > 10)	//if not, makes more sense to just divide by 10^|decimals|
  	{
  		int cicles;
	  	for (uint init = 0; init < decimals.size()-3; init++)	//can't find a cicle in the last 3 elements
	  	{
	  		cicles = -1;

	  		// 2*repetend.size < size-init	//because I need "space" to have a second cicle
	  		// 2*(end-init) < decimal.size()-1 - init
	  		// 2*end < decimal.size()-1 + init
	  		for (uint end = init+1; 2*end < decimals.size()-1 + init; end++)	//I'm testing the period [init,end)
	  		{
	  			if(decimals[end] == decimals[init])
	  			{
	  				cicles = 0;	//I found a possible repetend
	  				for (uint elem = 1; end + elem < decimals.size()-1 && cicles > -1; elem++)	//check if elements match
	  				{
	  					if(decimals[init + elem] != decimals[end + elem])	//it doesn't reach the end-1
	  					{
	  						cicles = -1;
	  						break;
	  					}

	  					//decimals[init + elem] == decimals[end + elem]

	  					if(!((elem+1) % (end-init)))	// check if it's the last element of it's cicle
	  						cicles++;

	  					if(end + elem == decimals.size()-2 && cicles > 0)//found the repentend
	  					{
	  						string num2S = integer + decimals.substr(0, end);
					  		long den2 = pow(10, end - init)-1;
					  		long num2 = stol(num2S) - stol(integer + decimals.substr(0, init));

					  		return Fraction( num2, den2 * pow(10, init));
	  					}
	  				}
	  			}
	  		}
	  	}
	}

	long number = stol(integer+decimals);
	
	return Fraction(number, pow(10.0, decimals.size()));
}

//2) Jhon Kennedy's original iterative method
/*
	This method receives the acuracity. For a lot of instances 1e-6 seems a good one, but not in general. 
	It will depend on your needs, but I preffer to have this value hardcoded

*/

Fraction JKsRealToFraction(double value, double accuracy)
{
    if (accuracy <= 0.0 || accuracy >= 1.0)
    {
        //throw new ArgumentOutOfRangeException("accuracy", "Must be > 0 and < 1.");
        cout << "Accuracy  must be > 0 and < 1" << endl;
    }

    long sign = (value >= 0);	//0 if value is neg. 1 if 0 or greater
    sign = sign*2 -1;		//0 or 2, then -1 or 1

    value = abs(value);

    // Accuracy is the maximum relative error; convert to absolute maxError
    double maxError = sign == 0 ? accuracy : value * accuracy;

    double integer = floor(value);
    double decimal = value - integer;

    if (decimal < maxError)
        return Fraction(sign * integer, 1);

    if (1 - maxError < decimal)
        return Fraction(sign * (integer + 1), 1);

    double z = value;
    long previousDenominator = 0;
    long denominator = 1;
    long numerator, temp;

    do
    {
        z = 1.0 / (z - floor(z));
        temp = denominator;
        denominator = denominator * floor(z) + previousDenominator;
        previousDenominator = temp;
        numerator = round(value * denominator);
    }
    while (abs(value - (double)numerator / (double)denominator) > maxError && z != floor(z));

    return Fraction(numerator * sign, denominator);
}