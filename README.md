# math
some math stuff i wanted to code

#Fraction
C++ class for fractions, for better use of rational non-integer numbers. Trying to make it as complete as possible.

Right now is pretty okay. Besides the obvious, it checks if it's being constructed with a floating point approximation of a periodic number. If so, it shows the right fraction (the algorithm is straightforward and clumsy, but i might improve it in the future)

    i.e. if recibes 0.33333333333333 deduces the actual number is 1/3, not 33333333333333/100000000000000

Improvements: I should made (as i believe it doesn't exist) a "double root(double, double)" with either binary search (good for integer values) or Newton's algoritm (for rational numbers).
