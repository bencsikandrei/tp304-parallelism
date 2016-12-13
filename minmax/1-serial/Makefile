CPPFLAGS=
CFLAGS=-g -Wall -Wextra -std=c99 -O3 -march=native -fopenmp
LDFLAGS=-g -lgomp

all: main

main: main.o minmax.o helpers.o

clean:
	$(RM) *.o
	$(RM) main
