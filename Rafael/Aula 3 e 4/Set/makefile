# makefile para os sets
CC = gcc
CFLAGS = -ansi -Wall

OBJM = set.o
HEADERS = set.h

OBJECTS = $(OBJM) testset.o simset.o
EXES = tset sset

all:	$(EXES)

tset:	testset.o $(OBJM) 
	$(CC) $(CFLAGS) testset.o $(OBJM) -o tset

sset:	simset.o $(OBJM)
	$(CC) $(CFLAGS) simset.o $(OBJM) -o sset

$(OBJM):	$(HEADERS)

clean:
	rm -f $(OBJECTS) *~

cleanall:	clean
	rm -f $(EXES)
