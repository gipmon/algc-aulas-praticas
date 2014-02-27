# makefile para os vectores
CC = gcc
CFLAGS = -ansi -Wall

OBJM = vector.o
HEADERS = vector.h

OBJECTS = $(OBJM) testvector.o simvector.o
EXES = tvec svec

all:	$(EXES)

tvec:	testvector.o $(OBJM) 
	$(CC) $(CFLAGS) testvector.o $(OBJM) -o tvec

svec:	simvector.o $(OBJM)
	$(CC) $(CFLAGS) simvector.o $(OBJM) -o svec

$(OBJM):	$(HEADERS)

clean:
	rm -f $(OBJECTS) *~

cleanall:	clean
	rm -f $(EXES)
