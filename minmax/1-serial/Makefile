CPPFLAGS=
CFLAGS=-g -Wall -Wextra -std=c99 -O3 -march=native -fopenmp
LDFLAGS=-g -lgomp

all: main_one_read main_two_reads

main_one_read: main_one_read.o minmax.o helpers.o

main_two_reads: main_two_reads.o minmax.o helpers.o

clean:
	$(RM) *.o
	$(RM) main

mrproper:
	rm main_one_read main_two_reads

.PHONY: all clean mrproper
