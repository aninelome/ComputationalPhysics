
all: compile link run

compile:
	c++ -c temp_func.cpp -std=c++11 -O3

link:
	c++ -o main.exe temp_func.o -larmadillo

run:
	./main.exe

all_test: compile_test link_test run_test

compile_test:
	c++ -c particle.cpp penningtrap.cpp testing.cpp -std=c++11

link_test:
	c++ -o main.exe particle.o penningtrap.o testing.o -larmadillo

run_test:
	./main.exe

all_main: compile_main link_main run_main

compile_main:
	c++ -c particle.cpp penningtrap.cpp main.cpp -std=c++11 -Ofast

link_main:
	c++ -o main.exe particle.o penningtrap.o main.o -larmadillo

run_main:
	./main.exe
