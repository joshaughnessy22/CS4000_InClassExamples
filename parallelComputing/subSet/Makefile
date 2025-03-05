CXX=g++
# standard flags
CPPFLAGS=-Wall -Werror
# turn on the openmp compiler options for class
CPPFLAGS+= -fopenmp 

export OMP_NUM_THREADS=10
#setting the omp environment variable 
#otherwise dynamically allocates based on the number of cores on the machine

# CCFILES is a listing of all of the files in the current directory that are C++ source files
CCFILES=${wildcard *.cc}
# PROGRAMS is like CCFILES, but removes the ".cc", so "t1.cc" turns into "t1"
PROGRAMS=${CCFILES:.cc=}

# by default, compile each CC file into its own program
default: ${PROGRAMS}

clean:
	rm -f *.o ${PROGRAMS}
