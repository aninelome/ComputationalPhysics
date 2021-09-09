//Prob. 9

#include <iostream> // input and output
#include <fstream> // access to ofstream class
#include <math.h>
#include <armadillo>
#include <cmath>
#include <iomanip>
#include <string>

using namespace std;
using namespace arma;

void V_special(int n, string filename){
      double h = 1./(n-1);
      double hh = h*h;
      vec g(n), v(n);

    // all vectors are same number 
      int a, c = -1;
      int b = 3/2;

      vec x = linspace(0, 1, n);
      vec f_x = 100.0*exp(-10*x);

      g(0) = hh*f_x(0);
      g = hh*f_x;

      //b = 3/2; 
      float CONST = -1/2; 

      for (int i = 1; i <= n-2; i++) {
          g(i) = g(i) - CONST * g(i-1);    
      }


    v(0) = 0;
    v(n-1) = 0;
    v(n-2) = g(n-2)/b;

    for (int i = n-3; i >= 1; i--) {
        v(i) = g(i) / b - CONST*v(i+1);

    }

    // write x and U(x) to a textfile
    ofstream file;
    file.open(filename, ios::out); //opens file in out/write mode

    for (int i = 0; i < n; i++){
        file << setw(25) << setprecision(3) << x(i);
        file <<fixed<< setw(25) << setprecision(8) << v(i) << endl;

    }

    file.close();
    return;
}

int main(int argc, char const *argv[]){ 
    for (int i = 1; i <= 4; i++) {
        int n = pow(10, i);
        V_special(n, "prob9_n_" + to_string(n) + ".txt");
    }
    return 0;
}
