#******************************************************************************
# Calvin Hong, cbhong
# 2019 Summer CMPS101 PA1
# Makefile
# Makefile for PA1
#******************************************************************************
#------------------------------------------------------------------------------
# Makefile for CMPS 101 Programming Assignment 1
#
#       make                   makes Lex
#       make ListClient        makes ListClient
#------------------------------------------------------------------------------

Lex : Lex.o List.o
	gcc -o Lex Lex.o List.o

Lex.o : Lex.c List.h
	gcc -c -std=c99 -Wall Lex.c

ListClient: ListClient.o List.o
	gcc -o ListClient ListClient.o List.o

ListClient.o : ListClient.c List.h
	gcc -c -std=c99 -Wall ListClient.c

List.o : List.c List.h
	gcc -c -std=c99 -Wall List.c

clean :
	rm -f Lex ListClient Lex.o ListClient.o List.o

check:
	ls /afs/cats.ucsc.edu/class/cmps101-pt.u19/pa1/cbhong

memCheck:
	valgrind --leack-check=full ListClient

submit :
	submit cmps101-pt.u19 pa1 List.h List.c ListClient.c Lex.c Makefile README