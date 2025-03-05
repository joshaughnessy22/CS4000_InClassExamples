CXX=g++
CC=gcc
MACOS=$(shell uname -s | sed 's/Darwin/-DMACOS/')
CPPFLAGS=-Wall -Werror -fopenmp -Wno-deprecated-declarations ${MACOS}

CSOURCES=${wildcard *.c}
CCSOURCES=${wildcard *.cc}
TARGETS=${CSOURCES:.c=} ${CCSOURCES:.cc=} 

all: ${TARGETS}

clean:
	rm -f *.o ${TARGETS}
