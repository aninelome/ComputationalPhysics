
#include "particle.hpp"
#include "penningtrap.hpp"
  
  
  

// Constructor 
PenningTrap::PenningTrap(vector<Particle> p_collection_in, double B0_in, double V0_in, double d_in){ 
  
  p_collection = p_collection_in;
  B0 = B0_in; 
  V0 = V0_in;
  d = d_in;
}

// Add a particle to the trap
void Penningtrap::add_particle(Particle p_in){
  p_collection.push_back(p_in);
} 

// External electric field at point r=(x,y,z)
vec Penningtrap::external_E_field(vec r){
  vec V = 
  vec E = - 
}  

// External magnetic field at point r=(x,y,z)
vec Penningtrap::external_B_field(vec r){
}  

// Force on particle_i from particle_j
vec Penningtrap::force_particle(int i, int j){

}

// The total force on particle_i from the external fields
vec Penningtrap::total_force_external(int i){}

// The total force on particle_i from the other particles
vec Penningtrap::total_force_particles(int i){}

// The total force on particle_i from both external fields and other particles
vec Penningtrap::total_force(int i){}

// Evolve the system one time step (dt) using Runge-Kutta 4th order
void Penningtrap::evolve_RK4(double dt){}

// Evolve the system one time step (dt) using Forward Euler
void Penningtrap::evolve_forward_Euler(double dt){}

