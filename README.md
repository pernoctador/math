# math
some math stuff i wanted to code

#Fraction
C++ class for fractions, for better use of rational non-integer numbers. Trying to make it as complete as possible.

Right now is pretty okay. Besides the obvious, it checks if it's being constructed with a floating point approximation of a periodic number. If so, it shows the right fraction (the algorithm is straightforward and clumsy, but i might improve it in the future)

    i.e. if recibes 0.33333333333333 deduces the actual number is 1/3, not 33333333333333/100000000000000

Improvements: Instead of Long i could use Ulong to represent more numbers. Long Long is not needed, asi in a 64x pc is the same. doubleToFraction() could be improved.

Also, I should made (as i believe it doesn't exist) a "double root(double, double)" with either binary search (good for integer values) or Newton's algoritm (for rational numbers).
	That would go to math_utilities, and be used wherever i need.

#Matrix (WIP)
C++ class for math matrices, with the standard operations and other more interesting operations like LU, LDLt and QR factorization, Gauss method, eigenvalues and eigenvectors, etc

The first cool think i did is to transpose a matrix in O(1) (i know, is not that crazy, but i'm somewhat proud). Is still a WIP as i still need to made some refactoring

#math_utilities
Some usefull things i needed along the construction of the clases, that doesn't belong there. Is not the most optimized option, but is easy to get that through copy and paste