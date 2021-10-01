#include "particle.hpp"
#include <string>

// Constructor
<<<<<<< HEAD
Particle::Particle(int q, double m, vec r, vec v)
{
  q_ = q;
  m_ = m;
  r_ = r;
  v_ = v;
=======
Particle::Particle(int charge_in, int mass_in, vec position_in, vec velocity_in) {
  // Class that stores the following properties of a single particle 
  charge_ = charge_in;
  mass_ = mass_in;
  position_ = position_in;
  velocity_ = velocity_in;
>>>>>>> ccb4dfa508b1b200064fcc319335c5cd5ec9d345
}

// Method printing member variables (particle properties)
void Particle::info()
    {
      cout <<  "Charge: " << q_ << "Mass: " << m_ << "Position: " << r_ << "Velocity: " << v_ << endl;
    }
