all: compile link run

compile:
	g++-10 -c functions.cpp main.cpp -O3

link:
	g++-10 functions.o main.o -o main.exe -larmadillo

run:
	./main.exe
