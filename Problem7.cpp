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


vec U(vec x){// define function for exact solution
  return 1. - (1. - exp(-10))*x - arma::exp(-10.*x);
}

void V(int n, string filename){// function computing the approximation v(x) for a given n using the algorithm for Gaussian elimination
      vec a(n), b(n), c(n), g(n), v(n); // define vectors


      // fill vectors a, b, c with values
      a.fill( -1);
      b.fill( 2);
      c.fill( -1);

      vec x = linspace(0, 1, n);       // define x from 0 to 1
      double h = x(1)-x(0);           // define h and h^2
      double hh = h*h;
      vec f_x = 100.0*exp(-10*x);


      // set initial values for g
      g(0) = hh*f_x(0);
      g = hh*f_x;


      for (int i = 2; i <= n-2; i++) {            // calculate b and g
          b(i) = b(i) - a(i)/b(i-1) * c(i-1);
          g(i) = g(i) - a(i)/b(i-1) * g(i-1);
      }


    v(0) = 0;
    v(n-1) = 0;
    v(n-2) = g(n-2)/b(n-2);

    for (int i = n-3; i >= 1; i--) {              // calculate v
        v(i) = (g(i) - c(i)*v(i+1)) / b(i);

    }

    // write x and v(x) to a textfile
    ofstream file;
    file.open(filename, ios::out); //opens file in out/write mode
    vec res = U(x);
    vec AbsoluteError = arma::log10(arma::abs(res-v));
    vec RelativeError = vec(size(AbsoluteError)).fill(0.);
    for (int i = 1; i < n-1; i++) RelativeError(i) = log10(fabs(res(i)-v(i)/res(i)));


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
    for (int i = 1; i <= 7; i++) {
        int n = pow(10, i);
        cout << "n = " << n << endl;
        V(n, "prob7_n_" + to_string(n) + ".txt");
    }
    return 0;
}
