! include( ../common.pri ) {
	error( "Couldn't find the common.pri file!" )
}

TEMPLATE = lib
CONFIG += lib
HEADERS = histogram_bench.h histogram.h tools.h
SOURCES = histogram_bench.cpp histogram.cpp tools.cpp
