QMAKE_CXXFLAGS_RELEASE -= -O1
QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_CXXFLAGS_RELEASE *= -O3 -march=native -mtune=native 
QMAKE_CXXFLAGS = -std=c++11 -g -fopenmp -Wextra
LIBS += -lgomp
