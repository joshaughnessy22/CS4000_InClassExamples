# Generic C++ Threads Makefile
# Ostermann - Feb 25, 2022 
CXX=g++
CPPFLAGS=-Wall -Werror -O2 -lpthread -pthread

CSOURCES=${wildcard *.c}
CCSOURCES=${wildcard *.cc}
ALLTARGETS=${CSOURCES:.c=} ${CCSOURCES:.cc=} 

all: ${ALLTARGETS}	
	
clean:
	rm -f  *.o ${ALLTARGETS}
