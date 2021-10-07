#include "particle.hpp"
#include "penningtrap.hpp"

#include <armadillo>
#include <vector>

using namespace arma;
using namespace std;

int main(){
  vec r1 = {1,0,1};
  vec v1 = {0,1,0};


  double B0, V0, d;

  double dt = 0.0001;
  int i = 0;
  double total_time = 100;
  double n = total_time/dt;

  mat r = mat(3,n);
  mat v = mat(3,n);

  Particle p1 = Particle(1, 1., r1, v1);

  vector<Particle> particle_collection;
  particle_collection.push_back(p1);

  PenningTrap penningtrap = PenningTrap(particle_collection, 96.5, 9.65e8, 1e4);

  //penningtrap.evolve_RK4(dt, i, total_time);
  //penningtrap.evolve_forward_Euler(dt, i, total_time);

  penningtrap.simulation(dt, total_time);



  return 0;
}
