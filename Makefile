# Build

ROOT     = /home/micaellgoms/gurobi910/linux64
INC      = $(ROOT)/include/
CPP      = g++
CARGS    = -g
CPPLIB   = -L$(ROOT)/lib -lgurobi_c++ -lgurobi91

all: build run

build: src/main.cpp src/reader.cpp
	$(CPP) $(CARGS) src/main.cpp src/reader.cpp -o bin/exec -I$(INC) $(CPPLIB) -lm

run:
	./bin/exec