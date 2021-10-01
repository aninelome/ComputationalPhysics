
#include "particle.hpp"
#include "penningtrap.hpp"


// Constructor
PenningTrap::PenningTrap(vector<Particle> particles, double B0, double V0, double d){

  particles_ = particles;
  B0_ = B0;
  V0_ = V0;
  d_ = d;
}

// Add a particle to the trap
void PenningTrap::add_particle(Particle particle){
  particles_.push_back(particle);
}

// Counts number of particles in particles
int PenningTrap::particle_count()
    {
      return particles_.size();
    }

// Prints number of particles in particles
void PenningTrap::info()
    {
      std::cout << "number of particles = " << particle_count() << endl;

    }

// External electric field at point r=(x,y,z)
vec PenningTrap::external_E_field(vec r){
  vec E = vec(3);
  E(0) = (V0_/(d_*d_))*(r(0));
  E(1) = (V0_/(d_*d_))*(r(1));
  E(2) = (V0_/(d_*d_))*(-2*r(2));
  return E;
}

// External magnetic field at point r=(x,y,z)
vec PenningTrap::external_B_field(int i){
  vec v = particles_[i].v_;
  vec B = vec(3);
  int q = particles_[i].q_;
  B(0) = B0_*q*v(1);
  B(1) = -B0_*q*v(0) ;
  B(2) = 0;
  return B;
}

// Force on particle_i from particle_j
vec PenningTrap::force_particle(int i, int j){

}

// The total force on particle_i from the external fields
vec PenningTrap::total_force_external(int i){}

// The total force on particle_i from the other particles
vec PenningTrap::total_force_particles(int i){}

// The total force on particle_i from both external fields and other particles
vec PenningTrap::total_force(int i){}

// Evolve the system one time step (dt) using Runge-Kutta 4th order
void PenningTrap::evolve_RK4(double dt){}

// Evolve the system one time step (dt) using Forward Euler
void PenningTrap::evolve_forward_Euler(double dt){}
