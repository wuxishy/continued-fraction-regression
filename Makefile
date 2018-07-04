CXX = g++
CXXFLAGS = -g -Wall -O2 -pedantic

OBJ = main.o gp.o agent.o fraction.o func.o init.o

%.o : %.cpp
	$(CXX) -c $< $(CXXFLAGS) -o $@

main: $(OBJ) 
	$(CXX) $^ $(CXXFLAGS) -o main

all: main

clean:
	rm -f main *.o

.PHONY : all clean
