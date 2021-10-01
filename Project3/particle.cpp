#include "particle.hpp"
#include <string>

// Constructor

Particle::Particle(int q, double m, vec r, vec v)
{
  q_ = q;
  m_ = m;
  r_ = r;
  v_ = v;
}

// Method printing member variables (particle properties)
void Particle::info()
    {
      cout <<  "Charge: " << q_ << "Mass: " << m_ << "Position: " << r_ << "Velocity: " << v_ << endl;
    }
