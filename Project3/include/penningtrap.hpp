#ifndef PENNINGTRAP_HPP
#define PENNINGTRAP_HPP

#include <vector>      // For vector
#include <string>      // For string
#include <stdexcept>   // For runtime_error
#include <armadillo>   // For armadillo
#include "particle.hpp"

using namespace std;
using namespace arma;



class PenningTrap
{
private:
    vector<Particle> particles_;
    double B0_; // Magnetic field
    double V_d_ratio_; // Potential to geometric size ratio.
    bool interaction; // Set to "true" if we run simulation with interactions, and "false" if we run it without
    double d_; // Characteristic distance
    double f_; // Amplitude
    double omega_v_; // Angular frequency


public:
    int N_par; // Number of particles in the trap

    // Constructor that creates an empty penning trap
    PenningTrap() {}

    // Constructor that takes a vector of particles as input
    PenningTrap(vector<Particle> particles, double B0, double V_d_ratio, double d, double f, double omega_v);

    // Add a particle to the trap
    void add_particle(Particle p_in);

    // Counts number of particles in p_collection
    int particle_count();

    // Prints number of particles in p_collection
    void info();

    //
    void remaining_particles();

    // External electric field at point r=(x,y,z)
    vec external_E_field(int i, double t);

    // External magnetic field at point r=(x,y,z)
    vec external_B_field(int i);

    // Force on particle_i from particle_j
    vec force_particle(int i, int j);

    // The total force on particle_i from the external fields
    vec total_force_external(int i, double t);

    // The total force on particle_i from the other particles
    vec total_force_particles(int i);

    // The total force on particle_i from both external fields and other particles
    vec total_force(int i, double t);

    // Evolve the system one time step (dt) using Runge-Kutta 4th order
    void evolve_RK4(double dt, int i, int j, double t);

    // Evolve the system one time step (dt) using Forward Euler
    void evolve_forward_Euler(double dt, int i, int j, double t);

    //Simulating the movement of all the particles for given method RK4 or Forward Euler
    void simulation(double dt, double total_time, bool interaction=true, string method="RK4", string s="_");
    cube v,r;
    vec t;

};
#endif
