all: compile link run

compile:
	c++ -c Problem2.cpp -std=c++11

link:
	c++ -o main.out Problem2.o -larmadillo

run:
	./main.out

all_seven:
	compile_seven link_seven run_seven

compile_seven:
	c++ -c Problem7.cpp -std=c++11

link_seven:
	c++ -o main.out Problem7.o -larmadillo

run_seven:
	./main.out
