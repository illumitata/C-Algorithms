CC=gcc
CFLAGS=-Wall
LDLIBS=-lm

all: auto

auto: auto.o tablica.o
	$(CC) $(CFLAGS) -o auto auto.o tablica.o $(LDLIBS)

auto.o: auto.c tablica.h
	$(CC) $(CFLAGS) -c auto.c

tablica.o: tablica.c
	$(CC) $(CFLAGS) -c tablica.c
