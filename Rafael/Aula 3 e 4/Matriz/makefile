# makefile para as matrizes
CC = gcc
CFLAGS = -ansi -Wall

OBJM = matrix.o
HEADERS = matrix.h

OBJECTS = $(OBJM) testmatrix.o simmatrix.o
EXES = tmat smat

all:	$(EXES)

tmat:	testmatrix.o $(OBJM) 
	$(CC) $(CFLAGS) testmatrix.o $(OBJM) -o tmat

smat:	simmatrix.o $(OBJM)
	$(CC) $(CFLAGS) simmatrix.o $(OBJM) -o smat

$(OBJM):	$(HEADERS)

clean:
	rm -f $(OBJECTS) *~

cleanall:	clean
	rm -f $(EXES)
