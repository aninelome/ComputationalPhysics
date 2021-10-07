#include "particle.hpp"
#include "penningtrap.hpp"

#include <armadillo>
#include <vector>

using namespace arma;
using namespace std;

int main(){
  vec r1 = {1,0,2};
  vec r2 = {0,2,2};

  vec v1 = {0,4,0};
  vec v2 = {1,4,1};


  Particle test_p1 = Particle(1, 1., r1, v1);

  Particle test_p2 = Particle(-1, 2., r2, v2);


  vector<Particle> particle_collection;
  particle_collection.push_back(test_p1);

  PenningTrap test_penningtrap = PenningTrap(particle_collection, 1, 1, 1);

  test_penningtrap.add_particle(test_p2);

  test_penningtrap.info();

  cout << "B: " << test_penningtrap.external_B_field(0) << endl;

  cout << "E: " << test_penningtrap.external_E_field(0) << endl;

  cout << "C: " << test_penningtrap.force_particle(0,1) << endl;

  cout << "F_ext: " << test_penningtrap.total_force_external(0) << endl;

  cout << "F_tot_particle: " << test_penningtrap.total_force_particles(0) << endl;

  cout << "F_tot: " << test_penningtrap.total_force(0) << endl;

  //test_penningtrap.evolve_forward_Euler(2, 0, 10);
  //test_penningtrap.evolve_RK4(2,0,10);
  test_penningtrap.simulation(2,10);


  return 0;
}
