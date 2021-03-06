#include "particle.hpp"
#include "penningtrap.hpp"
#include <ctime>
#include <iomanip>
#include <armadillo>
#include <vector>

using namespace arma;
using namespace std;


// Runs the simulation with either with a single dt-value or for several
void run_sim(double dt, double total_time, bool interaction, string method, int n, double B0, double V_d_ratio, double d, double f, double omega_v, std::vector<Particle> particle_collection){
  if (n==0){
    PenningTrap penningtrap = PenningTrap(particle_collection, B0, V_d_ratio, d, f, omega_v);
    penningtrap.simulation(dt, total_time, interaction, method);
  }
  else{
    arma::vec dt_values = vec(n);
    for (int i = 0; i < dt_values.size(); i++){
      PenningTrap penningtrap = PenningTrap(particle_collection, B0, V_d_ratio, d, f, omega_v);
      dt_values(i) = 1 / (pow(2, i+8)); // Here we set the dt-values, need to change it when we change from RK4 to F.E
      double dt_ = dt_values(i);
      string s = "dt:2**-" + to_string(int(i+8));
      penningtrap.simulation(dt_, total_time, interaction, method, s);
    }
  }
}

// Runs simulation for different amplitudes and angular frequencies
void run_sim_resonance(double dt, double total_time, double delta_omega, double start_omega, double stop_omega, bool interaction, double B0, double V_d_ratio, double d, double f, double omega_v, std::vector<Particle> particle_collection){
  int n_omega = int((stop_omega - start_omega)/delta_omega);
  vec omega_v_list = linspace(start_omega, stop_omega, n_omega); // list with omega_v values

  vec f_list = vec(3); // list with different amplitudes
  f_list(0) = 0.1;
  f_list(1) = 0.4;
  f_list(2) = 0.7;

  clock_t start, end;
  start = clock();
  for (int i = 0; i < f_list.size(); i++){
    double f = f_list(i);
    cout << "f:" << f << endl;
    ofstream file;
    file.open("remaining_particles_f:" +to_string(f)+ "_" + to_string(interaction) + "_from_omega:" + to_string(start_omega) + ".txt", ios::out);
    file << setw(25) << "omega_v" << setw(25) << "N" << endl;
    for (int j = 0; j < omega_v_list.size(); j++){
      double omega_v = omega_v_list(j);
      PenningTrap penningtrap = PenningTrap(particle_collection, B0, V_d_ratio, d, f, omega_v);
      penningtrap.simulation(dt, total_time, interaction, "RK4");
      // Write to file the number of particles remaining in the trap after
      // simulation with 100 random initalized particles:
      int N = penningtrap.N_par;
      file << setw(25) << omega_v << setw(25) << N << endl;
      cout << "N:" << N << endl;

  }
    file.close();
  }
  end = clock();
  double time = (end - start)/ (double) CLOCKS_PER_SEC;
  cout << time << endl;
}



int main(){
  double B0 = 96.5;
  //double V_d_ratio = 9.65; // For problem 9
  //double d = 1e4; // For problem 9
  double V_d_ratio = 0.965; //For problem 10
  double d = 0.05e4; //For problem 10
  double f = 1.0;
  double omega_v = 1.0;

  double dt = 0.1;
  int i = 0;
  double total_time = 500; // Change to 500 for Problem 10
  double n = total_time/dt;

  vector<Particle> particle_collection;

  int k = 100; // Number of particles in the Penning Trap

  if (k == 1){ // Treats the case when we only want to look at one particle
    vec r1 = {1.0,0,1.0}; // Initial position
    vec v1 = {0,1.,0};   // Initial velocity
    Particle p1 = Particle(1, 40.078, r1, v1);
    particle_collection.push_back(p1);
  }

  if (k==2){ // Treats the case when we only want to look at two particles
    vec r1 = {1.,0,1.};   // Initial position
    vec v1 = {0,1.,0};   // Initial velocity
    Particle p1 = Particle(1, 40.078, r1, v1);
    particle_collection.push_back(p1);
    vec r2 = {2,0,3};    // Initial position
    vec v2 = {0,1.,0};   // Initial velocity
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

  // IN THE FOLLOWING CODE WE NEED TO UNCOMMENT DIFFERENT PARTS BASED ON
  // WHICH SIMULATION WE WANT

  // Run simulation with interactions, with RK4:
  //run_sim(dt, total_time, true, "RK4", 0, B0, V_d_ratio, d, f, omega_v, particle_collection);

  // Run simulation without interactions, with RK4:
  //run_sim(dt, total_time, false, "RK4", 0, B0, V_d_ratio, d, f, omega_v, particle_collection);

  // Run simulation with interactions, with Forward Euler:
  //run_sim(dt, total_time, true, "ForwardEuler", 0, B0, V_d_ratio, d, f, omega_v, particle_collection);

  // Run simulation without interactions, with Forward Euler:
  //run_sim(dt, total_time, false, "ForwardEuler", 0, B0, V_d_ratio, d, f, omega_v, particle_collection);


  // Run sumulation without interactions, for 5 different dt-values, with RK4:
  //run_sim(dt, total_time, false, "RK4", 5, B0, V_d_ratio, d, f, omega_v, particle_collection);


  // Run sumulation without interactions, for 5 different dt-values, with Forward Euler:
  //run_sim(dt, total_time, false, "ForwardEuler", 5, B0, V_d_ratio, d, f, omega_v, particle_collection);


  // Run simulation for different amplitudes and angular frequencies from 0.2 to 2.5 without interactions
  run_sim_resonance(dt, total_time, 0.002, 0.2, 2.5, false, B0, V_d_ratio, d, f, omega_v, particle_collection);


  // Fine-grained frequency scans from 0.3 to 0.7 without interactions
  //run_sim_resonance(dt, total_time, 0.01, 0.3, 0.7, false, B0, V_d_ratio, d, f, omega_v, particle_collection);


  // Fine-grained frequency scans from 0.3 to 0.7 with interactions
  //run_sim_resonance(dt, total_time, 0.02, 0.3, 0.7, true, B0, V_d_ratio, d, f, omega_v, particle_collection);



  ////Here we tested which dt-values is reasonable to use for estimating error
  ////by simulating for diffent dt-values and
  ////plotting (in plotting.py) in the xy-plane:
  //double dt_test=1 / (pow(2,6));
  //PenningTrap penningtrap = PenningTrap(particle_collection, B0, V_d_ratio, d, f, omega_v);
  //penningtrap.simulation(dt_test, total_time, false, "RK4");
  ////penningtrap.simulation(dt_test, total_time, false, "ForwardEuler");

  return 0;
}
