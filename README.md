# Math classes
Some math classes I wanted to code. Each folder has a different math class, with the exception of 'utilities'. Some of these classes needs math_utilities (inside /utilities/) to work. I try to make a good balance between clear code and eficient code. WIP.

## Fraction (Beta)

C++ class for fractions, for better use of rational non-integer numbers. Trying to make it as complete as possible.

Right now is pretty okay. Besides the obvious, it checks if it's being constructed with a floating point approximation of a repeating decimal. If so, it shows the right fraction

    Example: If receives 0.33333333333333 deduces the actual number is 1/3, not 33333333333333/100000000000000

This is made by [John Kennedy's iterative algorithm](https://sites.google.com/site/johnkennedyshome/home/downloadable-papers/dec2frac.pdf) with an accuracy of 1e-14, as i found problems with higher precision for double.

Improvements: Instead of Long i could use Ulong to represent more numbers. Long Long is not needed, asi in a 64x pc is the same.

Also, I should made (as i believe it doesn't exist) a "double root(long, long)" with Newton's algoritm (for rational roots) or similar.
	That would go to math_utilities, and be used wherever i need.

## Matrix (WIP)

C++ class for math matrices, with the standard operations and other more interesting operations like LU, LDLt and QR factorization, Gauss method, eigenvalues and eigenvectors, etc (WIP: all that in the near future).

The first cool think i did is to transpose a matrix in O(1) (i know, is not that crazy, but i'm somewhat proud). Is still a WIP as i still need to make some refactoring

## math_utilities

Some usefull things i needed along the construction of the clases, that doesn't belong there. Is not the most optimized option, but is easy to get that through copy and paste


## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details