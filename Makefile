CXX = g++
CXXFLAGS = -Wall -O2 -pedantic

%.o : %.cpp
	$(CXX) -c $< $(CXXFLAGS) -o $@

main: main.o
	$(CXX) $^ $(CXXFLAGS) -o main

all: main

clean:
	rm -f main *.o

.PHONY : all clean
