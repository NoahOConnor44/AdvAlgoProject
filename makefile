CC=g++
CFLAGS= -g -Wall -std=c++11

mwi_set: 1-MWI-set.cpp
	$(CC) $(CFLAGS) 1-MWI-set.cpp -o mwi-set.o
