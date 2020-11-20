# Build

build: src/main.cpp src/reader.cpp src/genetic.cpp
	g++ src/main.cpp src/reader.cpp src/genetic.cpp -o bin/exec && ./bin/exec

build_txt: src/main.cpp src/reader.cpp src/genetic.cpp
	g++ src/main.cpp src/reader.cpp src/genetic.cpp -o bin/exec && ./bin/exec > print.txt

debug: src/main.cpp src/reader.cpp src/genetic.cpp
	g++ -g src/main.cpp src/reader.cpp -o bin/exec && gdb ./bin/exec