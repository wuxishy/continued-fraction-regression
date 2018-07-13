CXX = g++
CXXFLAGS = -g -Wall -Wextra -pedantic

OBJ = main.o gp.o agent.o fraction.o func.o init.o \
      evolve.o recomb_op.o optimize.o

%.o : %.cpp
	$(CXX) -c $< $(CXXFLAGS) -o $@

main: $(OBJ) 
	$(CXX) $^ $(CXXFLAGS) -o main

all: main

clean:
	rm -f main *.o

.PHONY : all clean
