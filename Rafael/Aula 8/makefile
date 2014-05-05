# makefile para a arvore ABP (Arvore Binaria de Pesquisa)
CC = gcc
CFLAGS = -ansi -Wall

OBJM = queue.o stack.o abp.o
HEADERS = queue.h stack.h abp.h

OBJECTS = $(OBJM) tabp.o irabp.o
EXES = tabp irabp

all:	$(EXES)

tabp:	tabp.o $(OBJM)
	$(CC) $(CFLAGS) tabp.o $(OBJM) -o tabp

irabp:	irabp.o $(OBJM)
	$(CC) $(CFLAGS) irabp.o $(OBJM) -o irabp

$(OBJM):	$(HEADERS)

clean:
	rm -f $(OBJECTS) *~

cleanall:	clean
	rm -f $(EXES)
