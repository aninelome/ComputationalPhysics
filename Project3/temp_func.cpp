#include <iostream>    // For cout, endl
#include <vector>      // For vector
#include <string>      // For string
#include <armadillo>

using namespace std;
using namespace arma;

//Making function for Forward Euler method
void forward_euler() {
    double h = 2; //timestep
    double total_time = 10; //Time of simulation
    int n = total_time/h; //Number of timesteps
    int m = 1; //mass of particle

    // Define the matrices for the velocity and position for x,y,z-directions
    mat v, r;
    v = mat(3,n).fill(0); //making empty matrix for v with n-timesteps for 3 dimensions
    r = mat(3,n).fill(0); //making empty matix for r with n-timesteps for 3 dimensions
    vec t = vec(n).fill(0); //making empty vector for the time with n-timesteps

    vec F = vec(3); //temproray constant force (we are going to vhange this later)
    F(0) = 10, F(1) = 10, F(2) = 10;

    //looping through the time for r,v and t with FE method
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < 3; j++) {
        vec a = F/m; //We get the total force from the penning trap calss
        v(j,i+1) = v(j,i) + a(j)*h;
        r(j,i+1) = r(j,i) + v(j,i)*h;
        t(i+1) = t(i) + h;
        }
      }
    cout << v << endl;

}

//Making function for Runge-Kutta 4 method
void RK4(){
  double h = 2;//timestep
  double total_time = 10; //Time of simulation
  int n = total_time/h; //Number of timesteps
  int m = 1.0; //mass of particle
  vec K1v, K2v, K3v, K4v, K1r, K2r, K3r, K4r, v_old, r_old, v, r; //Defining the vectors used in RK4 method

  vec a = vec(3);
  v = vec(3).fill(0); //making empty vector for v in 3 dimensions
  r = vec(3).fill(0); //making empty vector for r in 3 dimensions

  vec F = vec(3); //temproray constant force (we are going to vhange this later)
  F[0] = 10, F[1] = 10, F[2] = 10;

  for (int i = 0; i < n-1; i++) {
        r_old = r;
        v_old = v;

        a = F/m;
        //No uptades for v and r
        K1v = h*a;
        K1r = h*v;

        //1. update for v and r
        r = r_old + K1r/2; //going half timestep forward
        v = v_old + K1v/2;
        K2v = h*a; //use a(i) when implementing total force
        K2r = h*v;

        //2.update for v and r
        r = r_old + K2r/2; //going half timestestep forward
        v = v_old + K2v/2;
        K3v = h*a;
        K3r = h*v;

        //3.update for v and r
        r = r_old + K3r; //going whole timestep forward
        v= v_old + K3v;
        K4v = h*a;
        K4r = h*v;

        //4. update for v and r
        v = v_old + (1/6.0)*(K1v + 2*K2v + 2*K3v + K4v);
        r = r_old + (1/6.0)*(K1r + 2*K2r + 2*K3r + K4r);
        cout << v << endl;
  }
}

int main() {
    forward_euler();
    RK4();
    return 0;
}
