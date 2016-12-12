CPPFLAGS=-I/usr/include/qt4/QtCore -I/usr/include/qt4/QtGui -I/usr/include/qt4
CXXFLAGS=-O3 -std=c++0x -mtune=native -march=native -Wall -Wextra  -g -fopenmp
LDFLAGS=-L/opt/tbb-latest/lib
LDLIBS=-lQtCore -lQtGui -lgomp
CC=g++

all: main
main: main.o helpers.o edge_detect.o

clean:
	rm *.o
	rm main
