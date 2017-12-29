#
# Specifiy the target
COMPILER = g++
FLAGS = -Wall -std=c++11

all:	CA5

# Specify the object files that the target depends on
# Also specify the object files needed to create the executable
CA5:	CA5.o Course.o Semester.o
	$(COMPILER)  CA5.o Course.o Semester.o -o schedule.exe -g

# Specify how the object files should be created from source files
CA5.o:	CA5.cpp
	$(COMPILER) $(FLAGS) -c CA5.cpp -g

Course.o: Course.h Course.cpp
	$(COMPILER) $(FLAGS) -c Course.cpp -g

Semester.o: Semester.h Semester.cpp
	$(COMPILER) $(FLAGS) -c Semester.cpp -g

# Specify the object files and executables that are generated
# and need to be removed to re-compile the whole thing
clean:
	rm -f *.o schedule.exe

