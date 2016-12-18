CC=g++
CFLAGS= -std=c++11 -g

all: main.o 

%.o:%.cpp
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -rfv *.o

mrproper: clean

.PHONY: all clean mrproper

