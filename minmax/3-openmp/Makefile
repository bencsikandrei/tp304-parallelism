CPPFLAGS=
CFLAGS=-g -Wall -Wextra -std=c99 -O3 -march=native -fopenmp
LDFLAGS=-g -lgomp -fopenmp

all: main main_more_advanced

main: main.o minmax.o helpers.o

main_more_advanced: main_more_advanced.o minmax.o helpers.o

clean:
	$(RM) *.o
	$(RM) main
	$(RM) main_more_advanced
