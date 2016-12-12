! include( ../common.pri ) {
	error( "Couldn't find the common.pri file!" )
}

TEMPLATE = app
QMAKE_RPATHDIR += $ORIGIN/../../core
TARGET = qt
HEADERS = controller.h histogram_view.h
SOURCES = controller.cpp histogram_view.cpp main.cpp
INCLUDEPATH += ../core
LIBS += -L../core -lcore
