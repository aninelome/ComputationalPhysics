#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include <iostream>    // For cout, endl
#include <vector>      // For vector
#include <string>      // For string
#include <armadillo>

using namespace std;
using namespace arma;

class Particle
{
  // Public stuff
  public:

    // Constructor
    Particle(int q, double m, vec r, vec v);
    int q_;
    double m_;
    vec r_, v_;

    // Method printing member variables (particle properties)
    void info();

};

#endif
