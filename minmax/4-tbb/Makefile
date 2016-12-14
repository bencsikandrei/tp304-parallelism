CPPFLAGS=-g -Wall -Wextra -std=c++11 -O3 -march=native -fopenmp
LDFLAGS=-g -lgomp -ltbb

all: main

main: main.o minmax.o helpers.o
	g++ $^ $(CPPFLAGS) $(LDFLAGS) -o $@

minmax.o: minmax.cpp
	g++ -c $< $(CPPFLAGS) $(LDFLAGS) -o $@

clean:
	$(RM) *.o
	$(RM) main
