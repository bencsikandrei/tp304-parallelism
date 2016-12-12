! include( ../common.pri ) {
	error( "Couldn't find the common.pri file! ")
}

TARGET = benchs_plot
QMAKE_RPATHDIR += $ORIGIN/../../core
SOURCES = bench_all.cpp
INCLUDEPATH += ../core

# For TB machines
LIBS += -L../core -lcore -l:/usr/lib/x86_64-linux-gnu/libboost_system.so.1.54.0 -l:/usr/lib/x86_64-linux-gnu/libboost_iostreams.so.1.54.0

# For others :)
#LIBS += -L../core -lcore -lboost_system -lboost_iostreams
