
all: compile link run

compile:
	c++ -c temp_func.cpp -std=c++11

link:
	c++ -o main.exe temp_func.o -larmadillo

run:
	./main.exe

all_particle: compile_particletest link_particletest run_particletest

compile_particletest:
	c++ -c particle.cpp penningtrap.cpp testing.cpp -std=c++11

link_particletest:
	c++ -o main.exe particle.o penningtrap.o testing.o -larmadillo

run_particletest:
	./main.exe

all_particlemain: compile_particlemian link_particlemian run_particlemian

compile_particlemian:
	c++ -c particle.cpp penningtrap.cpp main.cpp -std=c++11

link_particlemian:
	c++ -o main.exe particle.o penningtrap.o main.o -larmadillo

run_particlemian:
	./main.exe
