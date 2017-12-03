# I am a comment, and I want to say that the variable CC will be
# the compiler to use.
CC=g++
# Hey!, I am comment number 2. I want to say that CFLAGS will be the
# options I'll pass to the compiler.
OFLAGS= -c -g -ggdb -pthread -Wall -std=c++11
CFLAGS = -g -ggdb -pthread -Wall -std=c++11
#For threads: 
# needed: -pthread
# might be needed  -lpthread -Wl,--no-as-needed
#Segun algunos, hay que separarlo:
#CTHREADS = -pthread
#OTHREADS = -pthread

SOURCES = Fraction.o

all: tests

#main: $(SOURCES) main.o
#	$(CC) $(CFLAGS) $(SOURCES) main.o -o TP $(CTHREADS)

#TP.o: main.cpp
#	$(CC) $(OFLAGS) main.cpp $(OTHREADS)

tests: $(SOURCES) tests.o
	$(CC) $(CFLAGS) $(SOURCES) tests.o -o tests

tests.o: tests.cpp
	$(CC) $(OFLAGS) tests.cpp

Fraction.o: Fraction.cpp Fraction.h
	$(CC) $(OFLAGS) Fraction.cpp Fraction.h

clean:
	rm *.o
	#rm TP
	rm tests
