#include <iostream>    // For cout, endl
#include <vector>      // For vector
#include <string>      // For string
#include <armadillo>

using namespace std;
using namespace arma;


// col er et tidssteg

void forward_euler() {
    double h = 2;
    double total_time = 10;
    int n = total_time/h;
    int m = 1;
    cout << n << endl;
    // Define the vectors for x,y,z
    mat v, r;
    v = mat(3,n).fill(0);
    r = mat(3,n).fill(0);
    vec t = vec(n).fill(0);
    cout << n << endl;
    vec F = vec(3);
    F(0) = 10, F(1) = 10, F(2) = 10;
    cout << n << endl;

    // må sjekke n - 1
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < 3; j++) {
        vec a = F/m;                  // m hentes fra klassen
        v(j,i+1) = v(j,i) + a(j)*h;
        r(j,i+1) = r(j,i) + v(j,i)*h;
        t(i+1) = t(i) + h;
        }
      }
    cout << v << endl;

}

void RK4(){
  //int h = 1.0;
  double h = 2;
  double total_time = 10;
  int n = total_time/h;
  int m = 1.0;
  float h2;
  vec K1v, K2v, K3v, K4v, K1r, K2r, K3r, K4r;
  vec v_old, r_old, v, r;
  // Define the matrice as 3*n

  vec a = vec(3);
  v = vec(3).fill(0);
  r = vec(3).fill(0);

  vec F = vec(3);
  F[0] = 10, F[1] = 10, F[2] = 10;

  for (int i = 0; i < n-1; i++) {
        r_old = r;
        v_old = v;

        h2 = h/2.0;
        a = F/m;
        //No uptades for v and r
        K1v = h*a;
        K1r = h*v;

        //1. update for v and r
        r = r_old + K1r/2; //going half step forward
        v = v_old + K1v/2;
        K2v = h*a; //use a(i) when implementing total force
        K2r = h*v;

        //2.update for v and r
        r = r_old + K2r/2;
        v = v_old + K2v/2;
        K3v = h*a;
        K3r = h*v;

        //3.update for v and r
        r = r_old + K3r;
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
