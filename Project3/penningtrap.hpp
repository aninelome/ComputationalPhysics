#ifndef PENNINGTRAP_HPP
#define PENNINGTRAP_HPP

#include <vector>      // For vector
#include <string>      // For string
#include <stdexcept>   // For runtime_error
#include <armadillo>   // For armadillo
#include <particle.hpp>

using namespace std;
using namespace arma;
  


class PenningTrap
{ 
private:
    vector<Particle> particle_collection; 
    double B0; // Magnetic field
    double V0; // Applied potential
    double d;  // Characteristic dimension
    
public:
    
    
    // Constructor that creates an empty penning trap
    Penningtrap() {}

    // Constructor that takes a vector of particles as input
    Penningtrap(vector<Particle> p_collection_in, double B0_in, double V0_in, double d_in);

    // Add a particle to the trap
    void add_particle(Particle p_in);


    // External magnetic field at point r=(x,y,z)
    vec external_B_field(vec r);  

    // Force on particle_i from particle_j
    vec force_particle(int i, int j);

    // The total force on particle_i from the external fields
    vec total_force_external(int i);

    // The total force on particle_i from the other particles
    vec total_force_particles(int i);

    // The total force on particle_i from both external fields and other particles
    vec total_force(int i);

    // Evolve the system one time step (dt) using Runge-Kutta 4th order
    void evolve_RK4(double dt);

    // Evolve the system one time step (dt) using Forward Euler
    void evolve_forward_Euler(double dt);


};
#endif



  