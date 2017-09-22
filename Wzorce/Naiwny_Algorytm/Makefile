CC=gcc
CFLAGS=-Wall
LDLIBS=-lm

all: naiwny

naiwny: naiwny.o tablica.o
	$(CC) $(CFLAGS) -o naiwny naiwny.o tablica.o $(LDLIBS)

naiwny.o: naiwny.c tablica.h
	$(CC) $(CFLAGS) -c naiwny.c

tablica.o: tablica.c
	$(CC) $(CFLAGS) -c tablica.c
