# I am a comment, and I want to say that the variable CC will be
# the compiler to use.
CC=g++
# Hey!, I am comment number 2. I want to say that CFLAGS will be the
# options I'll pass to the compiler.
OFLAGS= -c -g  -Wall -std=c++11
CFLAGS = -g -Wall -std=c++11
#For threads: 
# needed: -pthread
# might be needed  -lpthread -Wl,--no-as-needed
#Segun algunos, hay que separarlo:
#CTHREADS = -pthread
#OTHREADS = -pthread

#SOURCES = Fraction.o Matrix.o

all: tests

tests: Fraction.o tests.o 
	$(CC) $(CFLAGS) Fraction.o tests.o -o tests

tests.o: Matrix.h tests.cpp
	$(CC) $(OFLAGS) Matrix.h tests.cpp

Fraction.o: ../Fraction/Fraction.cpp ../Fraction/Fraction.h ../utilities/math_utilities.h
	$(CC) $(OFLAGS) ../Fraction/Fraction.cpp ../Fraction/Fraction.h ../utilities/math_utilities.h


clean:
	rm *.gch
	rm *.o
	rm tests
