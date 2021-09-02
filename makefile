all: compile link run

compile:
	c++ -c *.cpp -std=c++11

link:
	c++ -o main.out *.o -larmadillo

run:
	./main.out
