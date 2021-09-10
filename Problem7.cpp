//Prob. 7

#include <iostream> // input and output
#include <fstream> // access to ofstream class
#include <math.h>
#include <armadillo>
#include <cmath>
#include <iomanip>
#include <string>

using namespace std;
using namespace arma;


vec U(vec x){
  return 1. - (1. - exp(-10))*x - arma::exp(-10.*x);
}

void V(int n, string filename){
      vec a(n), b(n), c(n), g(n), v(n);


      // fill vectors a, b, c with values
      a.fill( -1);
      b.fill( 2);
      c.fill( -1);

      vec x = linspace(0, 1, n);
      double h = x(1)-x(0);
      double hh = h*h;
      vec f_x = 100.0*exp(-10*x);

      g(0) = hh*f_x(0);
      g = hh*f_x;


      for (int i = 2; i <= n-2; i++) {
          b(i) = b(i) - a(i)/b(i-1) * c(i-1);
          g(i) = g(i) - a(i)/b(i-1) * g(i-1);
      }


    v(0) = 0;
    v(n-1) = 0;
    v(n-2) = g(n-2)/b(n-2);

    for (int i = n-3; i >= 1; i--) {
        v(i) = (g(i) - c(i)*v(i+1)) / b(i);

    }



    // write x and U(x) to a textfile
    ofstream file;
    file.open(filename, ios::out); //opens file in out/write mode
    vec res = U(x);
    vec RelativeError = arma::log10(arma::abs(res - v)/res);
    vec AbsoluteError = arma::log10(arma::abs(res-v));
    for (int i = 0; i < n; i++){
        file << setw(25) << setprecision(3) << x(i);
        file <<fixed<< setw(25) << setprecision(8) << v(i);
        file <<fixed<< setw(25) << setprecision(8) << RelativeError(i);
        file <<fixed<< setw(25) << setprecision(8) << AbsoluteError(i) << endl;
    }

    file.close();
    return;
}


int main(int argc, char const *argv[]){
    for (int i = 1; i <= 4; i++) {
        int n = pow(10, i);
        V(n, "prob7_n_" + to_string(n) + ".txt");
    }
    return 0;
}
