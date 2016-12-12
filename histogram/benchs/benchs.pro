! include( ../common.pri ) {
	error( "Couldn't find the common.pri file! ")
}

TARGET = benchs
QMAKE_RPATHDIR += $ORIGIN/../../core
SOURCES = bench_all.cpp
INCLUDEPATH += ../core
LIBS += -L../core -lcore
