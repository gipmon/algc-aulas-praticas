# makefile para os polinómios
CC = gcc
CFLAGS = -ansi -Wall

OBJM = polynomial.o
HEADERS = polynomial.h

OBJECTS = $(OBJM) simpolynomial.o

spol:	simpolynomial.o $(OBJM)
	$(CC) $(CFLAGS) simpolynomial.o $(OBJM) -lm -o spol

$(OBJM):	$(HEADERS)

clean:	
	rm -f $(OBJECTS) *~

cleanall:	clean
	rm -f spol
