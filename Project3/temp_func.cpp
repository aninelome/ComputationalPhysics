#include <iostream>    // For cout, endl
#include <vector>      // For vector
#include <string>      // For string
#include <armadillo>

using namespace std;
using namespace arma;


// col er et tidssteg



/// denne må føres som en algoritme
void forward_euler(int n) {
    int h = 1;
    int m = 1;
    // Define the matrice as 3*n
    mat v, r;
    v = mat(3,n).fill(0);
    r = mat(3,n).fill(0);
    vec t = vec(n).fill(0);

    vec F = vec(3);
    F[0] = 10, F[1] = 10, F[2] = 10;

    // må sjekke n - 1
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < 3; j++) {
        vec a = F/m;                  // m hentes fra klassen
        v(j,i+1) = v(j,i) + a(i)*h;
        r(j,i+1) = r(j,i) + v(j,i) * h;
        t(i+1) = t(i) + h;
        }
    }
    //cout << v << endl;

}

void RK4(int n){
  int h = 1.0;
  int m = 1.0;
  float h2;
  vec K1v, K2v, K3v, K4v, K1r, K2r, K3r, K4r;
  vec v_old, r_old, a_new1, a_new2;
  // Define the matrice as 3*n

  vec a = vec(3);
  mat v, r;
  v = mat(3,n).fill(0);
  r = mat(3,n).fill(0);
  vec t = vec(n).fill(0);

  vec F = vec(3);
  F[0] = 10, F[1] = 10, F[2] = 10;



  for (int i = 0; i < n-1; i++) {
    //for (int j = 0; j < 3; j++) {
        r_old = r.col(i);
        v_old = v.col(i);
        cout << v << endl;
        h = t(i+1) - t(i);
        h2 = h/2.0;
        a = F/m;
        K1v = h*a;
        K1r = h*v.col(i);
        r.col(i) = r_old + K1r*h2;
        v.col(i)= v_old + K1v*h2;
        //a(i+0.5) = F/m; //total_force(...);
        K2v = h*a; //a(i)
        K2r = h*v.col(i);
        r.col(i) = r_old + K2r*h2;
        v.col(i) = v_old + K2v*h2;
        a_new1 = F/m; //total_force(...) sender inn r_new og v_new
        K3v = h*a_new1 + K2v*h2;
        K3r = h*v.col(i);
        r.col(i) = r_old + K3r*h2;
        v.col(i)= v_old + K3v*h2;
        a_new2 = F/m; //total_force(...) sender inn r_new og v_new
        K4v = h*a_new2 + K3v;
        K4r = h*v.col(i) + K3r;
        v.col(i) = v_old + (1/6.0)*(K1v + 2*K2v + 2*K3v + K4v);
        r.col(i) = r_old + (1/6.0)*(K1r + 2*K2r + 2*K3r + K4r);
  }
  //cout << v << endl;
}

int main() {
    forward_euler(3);
    RK4(3);
    return 0;
}
