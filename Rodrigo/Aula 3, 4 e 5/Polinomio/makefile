# makefile para os polinómios
CC = gcc
CFLAGS = -ansi -Wall

OBJM = polynomial.o
HEADERS = polynomial.h

OBJECTS = $(OBJM) testpolynomial.o simpolynomial.o
EXES = tpol spol

all:	$(EXES)

tpol:	testpolynomial.o $(OBJM) 
	$(CC) $(CFLAGS) testpolynomial.o $(OBJM) -lm -o tpol

spol:	simpolynomial.o $(OBJM)
	$(CC) $(CFLAGS) simpolynomial.o $(OBJM) -lm -o spol

$(OBJM):	$(HEADERS)

clean:
	rm -f $(OBJECTS) *~

cleanall:	clean
	rm -f $(EXES)
