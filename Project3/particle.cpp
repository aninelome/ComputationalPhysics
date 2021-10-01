#include "particle.hpp"

// Constructor
Particle::Particle(int charge_in, int mass_in, vec position_in, vec velocity_in) {
  // Class that stores the following properties of a single particle 
  charge_ = charge_in;
  mass_ = mass_in;
  position_ = position_in;
  velocity_ = velocity_in;
}
