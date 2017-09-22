CC=gcc
CFLAGS=-Wall
LDLIBS=-lm

all: rabin

rabin: rabin.o tablica.o
	$(CC) $(CFLAGS) -o rabin rabin.o tablica.o $(LDLIBS)

rabin.o: rabin.c tablica.h
	$(CC) $(CFLAGS) -c rabin.c

tablica.o: tablica.c
	$(CC) $(CFLAGS) -c tablica.c
