#include "particle.hpp"
#include "penningtrap.hpp"
#include <ctime>

#include <armadillo>
#include <vector>

using namespace arma;
using namespace std;

int main(){
  double B0 = 96.5;
  double V_d_ratio = 9.65; // For problem 9
  double d = 1e4; // For problem 9
  //double V_d_ratio = 0.965; For problem 10
  //double d = 0.05e4; For problem 10
  double f = 1.0;
  double omega_v = 1.0;

  double dt = 0.01;
  int i = 0;
  double total_time = 100;
  double n = total_time/dt;

  vector<Particle> particle_collection;

  int k = 2; // Number of particles in the Penning Trap

  if (k == 1){ // Treats the case when we only want to look at one particle
    vec r1 = {1.0,0,1.0};
    vec v1 = {0,1.,0};
    Particle p1 = Particle(1, 40.078, r1, v1);
    particle_collection.push_back(p1);
  }

  if (k==2){ // Treats the case when we only want to look at two particles
    vec r1 = {1.,0,1.};
    vec v1 = {0,1.,0};
    Particle p1 = Particle(1, 40.078, r1, v1);
    particle_collection.push_back(p1);
    vec r2 = {2,0,3};
    vec v2 = {0,1.,0};
    Particle p2 = Particle(1, 40.078, r2, v2);
    particle_collection.push_back(p2);
  }
  if (k>2){  // We fill the Penning Trap with k, randomly initalized calcium particles.
    arma_rng::set_seed(12345);
    for (int j=0; j<k; j++){
      vec r = vec(3).randn() * 0.1 * d;  // random initial position
      vec v = vec(3).randn() * 0.1 * d;  // random initial velocity
      Particle p = Particle(1, 40.078, r, v);
      particle_collection.push_back(p);
    }
}

  // Make penningtrap object with desired number of particles
  PenningTrap penningtrap = PenningTrap(particle_collection, B0, V_d_ratio, d, f, omega_v); // Obs: kan ha feil v_ratio


  // Run simulation with interactions, with RK4:
  //penningtrap.run_sim(dt, total_time, true, "RK4", 0);

  // Run simulation without interactions, with RK4:
  //penningtrap.run_sim(dt, total_time, false, "RK4", 0);

  // Run simulation with interactions, with Forward Euler:
  //penningtrap.run_sim(dt, total_time, true, "ForwardEuler", 0);

  // Run simulation without interactions, with Forward Euler:
  //penningtrap.run_sim(dt, total_time, false, "ForwardEuler", 0);


  // Run sumulation without interactions, for 5 different dt-values, with RK4:
  //penningtrap.run_sim(dt, total_time, false, "RK4", 5);

  // Run sumulation without interactions, for 5 different dt-values, with Forward Euler:
  penningtrap.run_sim(dt, total_time, false, "ForwardEuler", 5);

  // Run simulation for different amplitudes and angular frequencies
  //double delta_omega = 0.02;
  //int n_omega = int((2.5 - 0.2)/delta_omega);
  ////vec omega_v_list = linspace(0.2, 2.5, n_omega); // list with omega_v values
  //vec omega_v_list = linspace(0.2, 2.5, 3);
  //vec f_list = vec(3); // list with differtn amplitudes
  //f_list(0) = 0.1;
  //f_list(1) = 0.4;
  //f_list(2) = 0.7;

  //clock_t start, end;
  //start = clock();
  //for (int i = 0; i < f_list.size(); i++){
  //  double f = f_list(i);
  //  ofstream file;
  //  file.open("remaining_particles_f:" +to_string(f) +".txt", ios::out);
  //  file << setw(25) << "omega_v" << setw(25) << "N" << endl;
  //  for (int j = 0; j < omega_v_list.size(); j++){
  //    double omega_v = omega_v_list(j);
  //    PenningTrap penningtrap = PenningTrap(particle_collection, B0, V_d_ratio, d, f, omega_v); // Obs: kan ha feil v_ratio
  //    penningtrap.run_sim(dt, total_time, false, "RK4", 0);
  //    // Write to file the number of particles remaining in the trap after
  //    // simulation with 100 random initalized particles:
  //    int N = penningtrap.particle_count_trap();
  //    file << setw(25) << omega_v << setw(25) << N << endl;
  //  }
  //  file.close();
  //}
  //end = clock();
  //double time = (end - start)/ (double) CLOCKS_PER_SEC;
  //cout << time << endl;


  return 0;
}
