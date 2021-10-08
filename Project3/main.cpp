#include "particle.hpp"
#include "penningtrap.hpp"

#include <armadillo>
#include <vector>

using namespace arma;
using namespace std;

int main(){
  vec r1 = {1,0,1};
  vec v1 = {0,1,0};

  vec r2 = {2,3,4};
  vec v2 = {0,2,0};


  double B0, V0, d;

  double dt = 0.001;
  int i = 0;
  double total_time = 10;
  double n = total_time/dt;

  mat r = mat(3,n);
  mat v = mat(3,n);

  Particle p1 = Particle(1, 1., r1, v1);
  Particle p2 = Particle(-1, 1., r2, v2);

  vector<Particle> particle_collection;
  particle_collection.push_back(p1);

  PenningTrap penningtrap = PenningTrap(particle_collection, 96.5, 9.65e8, 1e4);

  penningtrap.add_particle(p2);

  penningtrap.simulation(dt, total_time);



  return 0;
}
