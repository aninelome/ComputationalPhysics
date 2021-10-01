#include "particle.hpp"
#include "penningtrap.hpp"

#include <armadillo>
#include <vector>

using namespace arma;
using namespace std;

int main(){
  vec r1 = {0,1,2};
  vec r2 = {0,2,2};

  vec v1 = {3,4,1};
  vec v2 = {1,4,1};


  Particle test_p1 = Particle(1, 1., r1, v1);

  Particle test_p2 = Particle(-1, 2., r2, v2);


  vector<Particle> particle_collection;
  particle_collection.push_back(test_p1);

  PenningTrap test_penningtrap = PenningTrap(particle_collection, 1, 1, 1);

  test_penningtrap.add_particle(test_p2);

  test_penningtrap.info();

  cout << "B: " << test_penningtrap.external_B_field(0) << endl;

  cout << "E: " << test_penningtrap.external_E_field(r1) << endl;






  return 0;
}
