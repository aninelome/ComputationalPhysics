//Prob. 7

#include <iostream> // input and output
#include <fstream> // access to ofstream class
#include <math.h>
#include <armadillo>
#include <cmath>

using namespace std;
using namespace arma;

void V(int n, const char* filename){
      double h = 1/n;
      vec a(n), b(n), c(n), g(n), v(n);

      // fill vectors a, b, c with values
      a.fill( -1);
      b.fill( 2);
      c.fill( -1);

      v[0] = 0;

      vec x = linspace(0, 1, n);
      vec f_x = 100*exp(-10*x);
      //cout << f_x[0] << endl;
      g[0] = pow(h,2)*f_x[0];
      //cout << g[0] << endl;

      for (int i = 1; i <= n-1; i++) {
          b[i] = b[i] - a[i]/b[i-1] * c[i-1];
          //cout << b[i] << endl;
          g[i] = g[i] - a[i]/b[i-1] * g[i-1];
          //cout << g[i] << endl;
      }

    //v[n-1] = g[n-1]/b[n-1];
    v[n-1] = 0;
    for (int i = n-2; i >= 1; i--) {
        v[i] = (g[i] - c[i]*v[i+1]) / b[i];
        //cout << v[i] << endl;
    }

    // write x and U(x) to a textfile
    ofstream file;
    file.open(filename, ios::out); //opens file in out/write mode

    for (int i = 0; i < n; i++){
        file << setw(25) << setprecision(3) << x[i];
        file <<fixed<< setw(25) << setprecision(8) << v[i] << endl;

    }

    file.close();
    return;
}
int main(int argc, char const *argv[]){
  V(10, "prob7_n_10.txt");
  V(100, "prob7_n_100.txt");
  V(1000, "prob7_n_1000.txt");
    return 0;
}
