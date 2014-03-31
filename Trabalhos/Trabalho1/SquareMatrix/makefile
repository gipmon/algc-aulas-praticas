# makefile para as matrizes quadradas
CC = gcc
CFLAGS = -ansi -Wall

OBJM = squarematrix.o
HEADERS = squarematrix.h

OBJECTS = $(OBJM) simsquarematrix.o

sqmat:	simsquarematrix.o $(OBJM)
	$(CC) $(CFLAGS) simsquarematrix.o $(OBJM) -o sqmat

$(OBJM):	$(HEADERS)

clean:	
	rm -f $(OBJECTS) *~

cleanall:	clean
	rm -f sqmat
