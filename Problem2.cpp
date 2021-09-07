//Prob. 2

#include <iostream> // input and output
#include <fstream> // acces to ofstream class
#include <math.h>
#include <armadillo>
#include <iomanip>

using namespace std;
using namespace arma;

vec U(vec x){ //define function
    return 1 - (1 - exp(-10))*x - exp(-10*x);
  }

void readU(int n, const char* filename){
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
//int n = 11;
  readU(10, "prob2_n_10.txt");
  readU(100, "prob2_n_100.txt");
  readU(1000, "prob2_n_1000.txt");
  return 0;
}
