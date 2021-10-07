
#include "particle.hpp"
#include "penningtrap.hpp"


// Constructor
PenningTrap::PenningTrap(vector<Particle> particles, double B0, double V0, double d){

  particles_ = particles;
  B0_ = B0;
  V0_ = V0;
  d_ = d;
}

// Add a particle to the trap
void PenningTrap::add_particle(Particle particle){
  particles_.push_back(particle);
}

// Counts number of particles in particles
int PenningTrap::particle_count()
    {
      return particles_.size();
    }

// Prints number of particles in particles
void PenningTrap::info()
    {
      std::cout << "number of particles = " << particle_count() << endl;

    }

// External electric field at point r=(x,y,z)
vec PenningTrap::external_E_field(int i){
  vec r = particles_[i].r_;
  vec E = vec(3);
  E(0) = (V0_/(d_*d_))*(r(0));
  E(1) = (V0_/(d_*d_))*(r(1));
  E(2) = (V0_/(d_*d_))*(-2*r(2));
  return E;
}

// External magnetic field at point r=(x,y,z)
vec PenningTrap::external_B_field(int i){
  vec v = particles_[i].v_;
  int q = particles_[i].q_;
  vec B = vec(3);
  B(0) = B0_*q*v(1);
  B(1) = -B0_*q*v(0) ;
  B(2) = 0;
  return B;
}

// Force on particle_i from particle_j
vec PenningTrap::force_particle(int i, int j){
  vec r_i = particles_[i].r_;
  vec r_j = particles_[j].r_;

  int q_i = particles_[i].q_;
  int q_j = particles_[j].q_;

  double m_i = particles_[i].m_;

  double k = 1;
  //double k = 1.38935333e5;

  vec C = vec(3);
  C(0) = k*(q_i/m_i)*q_j*(r_i(0)-r_j(0))/pow(sqrt(pow((r_i(0)-r_j(0)),2) + pow((r_i(1)-r_j(1)),2) + pow((r_i(2)-r_j(2)),2)),3);
  C(1) = k*(q_i/m_i)*q_j*(r_i(1)-r_j(1))/pow(sqrt(pow((r_i(0)-r_j(0)),2) + pow((r_i(1)-r_j(1)),2) + pow((r_i(2)-r_j(2)),2)),3);
  C(2) = k*(q_i/m_i)*q_j*(r_i(2)-r_j(2))/pow(sqrt(pow((r_i(0)-r_j(0)),2) + pow((r_i(1)-r_j(1)),2) + pow((r_i(2)-r_j(2)),2)),3);
  return C;
}

// The total force on particle_i from the external fields
vec PenningTrap::total_force_external(int i){
  vec F_ext = vec(3);
  F_ext = external_E_field(i) + external_B_field(i);
  return F_ext;
}

// The total force on particle_i from the other particles
vec PenningTrap::total_force_particles(int i){
  int num = PenningTrap::particle_count();
  vec F_tot_particle =  {0,0,0};

  for (int j=0; j<num; j++){
    if (j!= i){
      F_tot_particle =  F_tot_particle + force_particle(i,j);
    }
  }
  return F_tot_particle;
}

// The total force on particle_i from both external fields and other particles
vec PenningTrap::total_force(int i){
  vec F_tot = vec(3);
  F_tot = total_force_external(i) + total_force_particles(i);
  return F_tot;
}

void PenningTrap::simulation(double dt, double total_time){
  int n = (int) (total_time/dt);
  int n_par = particles_.size();
  // Define the matrices for the velocity and position for x,y,z-directions
  t = vec(n).fill(0); // empty vector for time wiht n timesteps
  v = cube(n,n_par,3).fill(0); //empty matrix with n timesteps in 3D
  r = cube(n,n_par,3).fill(0);
  // Evolve the system one time step (dt) using Forward Euler and RK4
  for (int j=0; j<n-1; j++){
    for (int i=0; i< particles_.size(); i++){
      evolve_RK4(dt, i, j);
      evolve_forward_Euler(dt, i, j);
    }
  }
}

// Evolve the system one time step (dt) using Runge-Kutta 4th order
void PenningTrap::evolve_RK4(double dt, int i, int j){
  double m = particles_[i].m_;
  vec K1v, K2v, K3v, K4v, K1r, K2r, K3r, K4r, v_old, r_old, a;

  a = vec(3);
  // initial conditions
  r.tube(j,i) = particles_[i].r_;
  v.tube(j,i) = particles_[i].v_;


  vec F = total_force(i);
  r_old = r.tube(j,i);
  v_old = v.tube(j,i);

  a = F/m;
  //No uptades for v and r
  K1v = dt*a;   K1r = dt*v.tube(j,i);
  //1. update for v and r
  r.tube(j,i) = r_old + K1r/2; //going half timestep forward
  v.tube(j,i) = v_old + K1v/2;
  a = total_force(i)/m;
  K2v = dt*a; //use a(i) when implementing total force
  K2r = dt*v.tube(j,i);

  //2.update for v and r
  r.tube(j,i) = r_old + K2r/2; //going half timestestep forward
  v.tube(j,i) = v_old + K2v/2;
  a = total_force(i)/m;
  K3v = dt*a;
  K3r = dt*v.tube(j,i);
  //3.update for v and r
  r.tube(j,i) = r_old + K3r; //going whole timestep forward
  v.tube(j,i) = v_old + K3v;
  a = total_force(i)/m;
  K4v = dt*a;
  K4r = dt*v.tube(j,i);

  //4. update for v and r
  v.tube(j+1,i) = v_old + (1/6.0)*(K1v + 2*K2v + 2*K3v + K4v);
  r.tube(j+1,i) = r_old + (1/6.0)*(K1r + 2*K2r + 2*K3r + K4r);

  particles_[i].r_ = r.tube(j+1,i);
  particles_[i].v_ = v.tube(j+1,i);

  cout <<"RK4 r"<< endl;
  cout << r << endl;
  cout <<"RK4 v"<< endl;
  cout << v << endl;
}

void PenningTrap::evolve_forward_Euler(double dt, int i, int j){
  double m = particles_[i].m_;
  vec a = vec(3);
  // initial conditions
  r.tube(j,i) = particles_[i].r_;
  v.tube(j,i) = particles_[i].v_;

  vec F = total_force(i);

  a = F/m;
  //cout << a << endl;
  //cout << v.tube(j,i) << endl;
  v.tube(j+1,i) = particles_[i].v_ + a*dt;//v.tube(j,i) + a*dt;
  r.tube(j+1,i) = r.tube(j,i) + v.tube(j,i)*dt;
  t(j+1) = t(j) + dt;
  cout << "Euler" << v << endl;
}
