# Build

ROOT     = /home/micaellgoms/gurobi910/linux64
INC      = $(ROOT)/include/
CPP      = g++
CARGS    = -g
CPPLIB   = -L$(ROOT)/lib -lgurobi_c++ -lgurobi91

run: src/main.cpp src/reader.cpp
	$(CPP) $(CARGS) src/main.cpp src/reader.cpp -o bin/exec -I$(INC) $(CPPLIB) -lm && ./bin/exec

# build: src/main.cpp src/reader.cpp src/genetic.cpp
# 	g++ src/main.cpp src/reader.cpp src/genetic.cpp -o bin/exec && ./bin/exec

# build_txt: src/main.cpp src/reader.cpp src/genetic.cpp
# 	g++ src/main.cpp src/reader.cpp src/genetic.cpp -o bin/exec && ./bin/exec > print.txt

# debug: src/main.cpp src/reader.cpp src/genetic.cpp
# 	g++ -g src/main.cpp src/reader.cpp -o bin/exec && gdb ./bin/exec

# g++ -m64 -g src/main.cpp src/reader.cpp -o bin/exec -I C:\MinGW\include\ -L C:\MinGW\lib -lgurobi_c++ -lgurobi91 -lm