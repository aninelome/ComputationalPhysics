all: compile link run

compile:
	g++-10 -c functions.cpp main.cpp

link:
	g++-10 functions.o main.o -o main.exe -larmadillo

run:
	./main.exe

all_test: compile_test link_test run_test

compile_test:
	c++ -c test.cpp -std=c++11

link_test:
	c++ test.o -o test.exe -larmadillo

run_test:
	./test.exe
