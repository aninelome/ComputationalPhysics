#include <iostream>    // For cout, endl
#include <vector>      // For vector
#include <string>      // For string
#include <armadillo>

using namespace std;
using namespace arma;


vec analytic_f(double t, double B0, double V0, int q, double m, double d, vec r, vec v){
  double omega_0 = abs(q)*B0/m;
  double omega_z = sqrt((2*abs(q)*V0)/(m*d*d));
  double omega_m = (omega_0-sqrt(omega_0*omega_0-2*omega_z*omega_z)/2);
  double omega_p = (omega_0+sqrt(omega_0*omega_0-2*omega_z*omega_z)/2);
  double A_p = (v(0)+omega_m*r(0))/(omega_m - omega_p);
  double A_m = -(r(0)*omega_p+v(0))/(omega_m - omega_p);
  vec f = vec(2);
  f(0) = A_p*cos(omega_p * t) + A_m*cos(omega_m * t);
  f(1) = -A_p*sin(omega_p * t) - A_m*sin(omega_m * t);
  return f;
}

int main() {
  double t = 1;
  double B0 = 96.5;
  double V0 = 9.65e8;
  int q = 1;
  double m = 1;
  double d = 10e4;
  double x0 = ?;
  double z0 = ?;
  vec r = {x0, 0, z0};
  vec v = {0, v0, 0};

  analytic_f(t, B0, V0, q, m, d, r, v)
  return 0;
}
