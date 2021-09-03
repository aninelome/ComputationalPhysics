//Prob. 2

#include <iostream> // input and output 
#include <fstream> // acces to ofstream class 
#include <math.h>
#include <armadillo>
#include <iomanip>

using namespace std;
using namespace arma;

vec U(vec x); // Declare function

int main(int argc, char const *argv[]){
int n = 11;

vec x = linspace(0, 1, n);
vec res = U(x);

// write x and U(x) to a textfile 
ofstream file; 
file.open("exact_solution.txt", ios::out); //opens file in out/write mode

for (int i = 0; i < n; i++){
    file << setw(15) << setprecision(3) << x[i];
    file <<fixed<< setw(15) << setprecision(8) << U(x)[i] << endl; 

}

file.close(); 

return 0; 
}

vec U(vec x){ //define function
    return 1 - (1 - exp(-10))*x - exp(-10*x);
   
}