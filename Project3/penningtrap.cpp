
#include "particle.hpp"
#include "penningtrap.hpp"


// Constructor
PenningTrap::PenningTrap(vector<Particle> particles, double B0, double V_d_ratio, double d, double f, double omega_v){

  particles_ = particles;
  B0_ = B0;
  V_d_ratio_ = V_d_ratio;
  d_ = d;
  f_ = f;
  omega_v_ = omega_v;
}

// Add a particle to the trap
void PenningTrap::add_particle(Particle particle){
  particles_.push_back(particle);
}

// Counts number of particles in particles
void PenningTrap::remaining_particles(){
  N_par = 0;
  for (int i=0; i< particles_.size(); i++){
    if (norm(particles_[i].r_) <= d_){
      N_par = N_par + 1;
    }
  }
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
  vec PenningTrap::external_E_field(int i, double t){
    vec r = particles_[i].r_;
    vec E = vec(3);

    if (norm(r) <= d_){
      E(0) = r(0);
      E(1) = r(1);
      E(2) = -2*r(2);
      //When we want a time-dependent field, we multiply V_d_ratio_ with the factor (1+ f_*cos(omega_v_ *t))
      E  = E*V_d_ratio_; //*(1+ f_*cos(omega_v_ *t ));
    }
    else{
      E(0) = 0;
      E(1) = 0;
      E(2) = 0;
    }

    return E;
  }

  // External magnetic field at point r=(x,y,z)
  vec PenningTrap::external_B_field(int i){
    vec r = particles_[i].r_;
    vec v = particles_[i].v_;
    vec B = vec(3).fill(0.);
    if (norm(r) <= d_){
      B(0) = B0_*v(1);
      B(1) = -B0_*v(0) ;
      B(2) = 0;
    }


    return B;
  }

  // Force on particle_i from particle_j
  vec PenningTrap::force_particle(int i, int j){
    vec r_i = particles_[i].r_;
    vec r_j = particles_[j].r_;

    int q_i = particles_[i].q_;
    int q_j = particles_[j].q_;

    double m_i = particles_[i].m_;

    double k = 1.38935333e5;
    vec dr = r_i-r_j;
    double dr_norm = arma::norm(dr);
    dr_norm = pow(dr_norm, 3);

    vec C = k*(q_i/m_i)*q_j*dr/dr_norm;
    return C;
  }

  // The total force on particle_i from the external fields
  vec PenningTrap::total_force_external(int i, double t){
    vec F_ext = vec(3);
    int q = particles_[i].q_;
    F_ext = q*(external_E_field(i, t) + external_B_field(i));

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
  vec PenningTrap::total_force(int i, double t){
    vec F_tot = vec(3);
    F_tot = total_force_external(i, t);
    if (interaction){
      F_tot += total_force_particles(i);
    }
    return F_tot;
  }

  void PenningTrap::simulation(double dt, double total_time, bool interaction_in, string method, string s){
    int n = (int) (total_time/dt);
    int n_par = particles_.size();
    interaction = interaction_in;

    // Define the matrices for the velocity and position for x,y,z-directions
    t = vec(n).fill(0); // empty vector for time wiht n timesteps
    v = cube(3,n_par,n).fill(0); //empty matrix with n timesteps in 3D
    r = cube(3,n_par,n).fill(0);
    vec time = linspace(0, total_time, n);
    // Evolve the system one time step (dt) using Forward Euler and RK4
    for (int j=0; j<n-1; j++){
      for (int i=0; i< particles_.size(); i++){
        if (method == "RK4"){
          evolve_RK4(dt, i, j, time(j));
        }
        else if (method == "ForwardEuler"){
          evolve_forward_Euler(dt, i, j, time(j));
        }
        else {
          cout << "No matching method for" + method << endl;
        }

      }
      for (int i=0; i< particles_.size(); i++){
        particles_[i].r_ = r.slice(j+1).col(i);
        particles_[i].v_ = v.slice(j+1).col(i);
      }

    }
    remaining_particles();
    time.save("time_"+s+".bin");
    if (interaction){
      r.save("position_with_interaction_"+s+".bin");
      v.save("velocity_with_interaction_"+s+".bin");
    }
    else{
      r.save("position_without_interaction_"+s+".bin");
      v.save("velocity_without_interaction_"+s+".bin");
    }
  }
  // Evolve the system one time step (dt) using Runge-Kutta 4th order
  void PenningTrap::evolve_RK4(double dt, int i, int j, double t){
    double m = particles_[i].m_;
    vec K1v, K2v, K3v, K4v, K1r, K2r, K3r, K4r, v_old, r_old;

    vec a = vec(3);
    // initial conditions

    r.slice(j).col(i) = particles_[i].r_;
    v.slice(j).col(i) = particles_[i].v_;

    vec F = total_force(i, t);

    r_old = r.slice(j).col(i);
    v_old = v.slice(j).col(i);


    a = F/m;
    //No uptades for v and r
    K1v = dt*a;
    K1r = dt*particles_[i].v_;
    //1. update for v and r
    particles_[i].r_ = r_old + K1r/2;
    particles_[i].v_ = v_old + K1v/2;

    a = total_force(i,t+(0.5*dt))/m;
    K2v = dt*a;
    K2r = dt*particles_[i].v_;


    //2.update for v and r
    particles_[i].r_ = r_old + K2r/2;
    particles_[i].v_ = v_old + K2v/2;

    a = total_force(i,t+(0.5*dt))/m;
    K3v = dt*a;
    K3r = dt*particles_[i].v_;
    //3.update for v and r
    particles_[i].r_ = r_old + K3r;
    particles_[i].v_ = v_old + K3v;

    a = total_force(i,t+dt)/m;
    K4v = dt*a;
    K4r = dt*particles_[i].v_;


    //4. update for v and r
    v.slice(j+1).col(i) = v_old + (1/6.0)*(K1v + 2*K2v + 2*K3v + K4v);
    r.slice(j+1).col(i) = r_old + (1/6.0)*(K1r + 2*K2r + 2*K3r + K4r);

    particles_[i].r_ = r_old;
    particles_[i].v_ = v_old;
  }

  void PenningTrap::evolve_forward_Euler(double dt, int i, int j, double t){
    double m = particles_[i].m_;
    vec a = vec(3);
    vec r_old, v_old;
    // initial conditions
    v_old = particles_[i].v_;
    r_old = particles_[i].r_;
    r.slice(j).col(i) = particles_[i].r_;
    v.slice(j).col(i) = particles_[i].v_;

    vec F = total_force(i, t);

    a = F/m;

    v.slice(j+1).col(i) = particles_[i].v_ + a*dt;
    r.slice(j+1).col(i) = particles_[i].r_ + v.slice(j).col(i)*dt;

    particles_[i].r_ = r_old;
    particles_[i].v_ = v_old;

  }
