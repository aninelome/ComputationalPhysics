#include "particle.hpp"
#include "penningtrap.hpp"

#include <armadillo>
#include <vector>

using namespace arma;
using namespace std;

int main(){

  vec r1 = {2,0,2};
  vec v1 = {0,0.1,0};

  vec r2 = {2,0,4};
  vec v2 = {0,0.2,0};

  Particle p1 = Particle(1, 40.078, r1, v1);
  Particle p2 = Particle(1, 40.078, r2, v2);

  double B0, V0, d;

  double dt = 0.001;
  int i = 0;
  double total_time = 100;
  double n = total_time/dt;

  mat r = mat(3,n);
  mat v = mat(3,n);


  vector<Particle> particle_collection;
  particle_collection.push_back(p1);

  PenningTrap penningtrap = PenningTrap(particle_collection, 96.5, 9.65);

  penningtrap.add_particle(p2);

  // Run simulation with interactions, with RK4:
  //penningtrap.run_sim(dt, total_time, true, "RK4", 0);

  // Run simulation without interactions, with RK4:
  //penningtrap.run_sim(dt, total_time, false, "RK4", 0);

  // Run simulation with interactions, with Forward Euler:
  //penningtrap.run_sim(dt, total_time, true, "ForwardEuler", 0);

  // Run simulation without interactions, with Forward Euler:
  //penningtrap.run_sim(dt, total_time, false, "ForwardEuler", 0);

  // Run sumulation without interactions, for 5 different dt-values, with RK4:
  penningtrap.run_sim(dt, total_time, false, "RK4", 5);

  // Run sumulation without interactions, for 5 different dt-values, with Forward Euler:
  //penningtrap.run_sim(dt, total_time, false, "ForwardEuler", 5);


  return 0;
}
