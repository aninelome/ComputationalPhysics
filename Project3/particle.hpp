#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include <iostream>    // For cout, endl
#include <vector>      // For vector
#include <string>      // For string

using namespace std;
using namespace arma;

class Particle
{
  // Public stuff
  public:

    // Constructor
    Particle(int charge_in, int mass_in, vec position_in, vec velocity_in);
    int charge_, mass_;
    vec position_, velocity_;

};

#endif
