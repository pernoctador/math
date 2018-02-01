# Math classes
Some math classes I wanted to code. Each folder has a different math class, with the exception of 'utilities'. Some of these classes needs math_utilities (inside /utilities/) to work. I try to make a good balance between clear code and eficient code. WIP.

## Fraction 1.1

C++ class for fractions, for better use of rational non-integer numbers. Trying to make it as complete as possible.

Right now is pretty okay. Besides the obvious, it checks if it's being constructed with a floating point approximation of a repeating decimal. If so, it shows the right fraction

    Example: If receives 0.33333333333333 deduces the actual number is 1/3, not 33333333333333/100000000000000

This is made by [John Kennedy's iterative algorithm](https://sites.google.com/site/johnkennedyshome/home/downloadable-papers/dec2frac.pdf), hardcoded with an accuracy of 1e-15, wich is the max accuracy for doubles.

In deprecated.h there is another way, a translation of the human way of finding a fraction from a decimal, searching for a repetend. Is straightforward and of reasonable time, but the iterative method seems better on average. I will study if adding some ideas of the old algorithm improve JK's.

Another propperty it has is to avoid overflow as much as possible. Also, I can convert both ways to continued fractions.

There is a couple of functions and constants to show properties of the class.

## Matrix Beta

C++ class for math matrices, with the standard operations and other more interesting operations  

 * Done: Basic opeartions, transpose in O(1), fixing transpose at copy, GaussianElimination  

 * TODO: LU, LDLt and QR factorization, eigenvalues and eigenvectors, inverse...

## math_utilities

Some usefull things i needed along the construction of the clases, that doesn't belong there. Is not the most optimized option, but is easy to get that through copy and paste


## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details