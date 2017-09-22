CC=gcc
CFLAGS=-Wall
LDLIBS=-lm

all: kmp

kmp: kmp.o tablica.o
	$(CC) $(CFLAGS) -o kmp kmp.o tablica.o $(LDLIBS)

kmp.o: kmp.c tablica.h
	$(CC) $(CFLAGS) -c kmp.c

tablica.o: tablica.c
	$(CC) $(CFLAGS) -c tablica.c
