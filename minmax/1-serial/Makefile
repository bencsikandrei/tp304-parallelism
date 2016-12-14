CPPFLAGS=
CFLAGS=-g -Wall -Wextra -std=c99 -O3 -march=native -fopenmp
LDFLAGS=-g -lgomp

all: main main_one_read

main: main.o minmax.o helpers.o

asm_main: main.c
	$(CC) $(CFLAGS) -S -c $<  

clean:
	$(RM) *.o
	$(RM) main main_one_read
