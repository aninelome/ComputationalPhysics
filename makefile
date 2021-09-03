all: compile link run

compile:
	c++ -c Problem2.cpp -std=c++11

link:
	c++ -o main.out Problem2.o -larmadillo

run:
	./main.out

compile_seven:
	c++ -c Problem7.cpp -std=c++11
