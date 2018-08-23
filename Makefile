CXX = g++
CXXFLAGS = -g -O2 -Wall -Wextra -pedantic
LDFLAGS = -pthread

LIST = main data eval gp agent fraction func init \
       evolve recomb_op mutate_op optimize

SRC = $(addsuffix .cpp, $(LIST))
OBJ = $(addprefix bin/, $(addsuffix .o, $(LIST)))

all: main

bin/%.o : %.cpp
	$(CXX) -c $< $(CXXFLAGS) -o $@

main: $(OBJ) 
	$(CXX) $^ $(CXXFLAGS) $(LDFLAGS) -o bin/main

clean:
	rm -f bin/*

.PHONY : all clean
