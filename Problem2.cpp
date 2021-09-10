//Prob. 2

#include <iostream> // input and output
#include <fstream> // acces to ofstream class
#include <math.h>
#include <armadillo>
#include <iomanip>

using namespace std;
using namespace arma;


vec U(vec x){ // define function for exact solution
    return 1 - (1 - exp(-10))*x - exp(-10*x);
  }

void compute_U(int n, const char* filename){ // define function that computes u(x) and writes to file for a given n
    vec x = linspace(0, 1, n);
    vec res = U(x);

    // write x and U(x) to a textfile
    ofstream file;
    file.open(filename, ios::out); //opens file in out/write mode

    for (int i = 0; i < n; i++){
        file << setw(15) << setprecision(3) << x[i];
        file <<fixed<< setw(15) << setprecision(8) << res[i] << endl;

    }

    file.close();
    return;
}

int main(int argc, char const *argv[]){
  for (int i = 1; i <= 7; i++) {
      int n = pow(10, i);
      cout << "n = " << n << endl;
      compute_U(n, "prob2_n_" + to_string(n) + ".txt");
  }
  return 0;
}
