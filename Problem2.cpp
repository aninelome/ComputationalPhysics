//Prob. 2

#include <iostream> // input and output 
#include <fstream> // acces to ofstream class 
#include <math.h>
#include <armadillo>

using namespace std;
//using namespace arma;

arma::vec U(arma::vec x);

int main(int argc, char const *argv[]){
int n = 20;
//double x [n];
//for (int i = 1; i < n; i++){
//    x [i] = x [i-1] + 1./n;
//}

//arma::vec x = arma::vec(n).fill(0.);
arma::vec x = arma::linspace(0, 1, n);
x.print("x = "); //git 

arma::vec res = U(x);
//arma::vec res = arma::exp(10);
res.print("res = ");

// write x and U(x) to a textfile 
fstream file; 
file.open("exact_solution.txt", ios::out); //opens file in out/write mode

for (int i = 0; i < n; i++){
    double scale = 0.0001; // round to the nearest one-hundreth 
    x[i] = floor(x[i] / scale + 0.5) * scale; 
    U(x)[i] = floor(U(x)[i] / scale + 0.5) * scale; 
    file << x[i] << " " << U(x)[i] << "\n"; 
}

file.close(); 

return 0; 
}

arma::vec U(arma::vec x){ //declaration
    //return 1-(1-pow(exp,-10)*x-pow(exp,-10*x); //Code block or body (i.e definition)
    arma::vec tmp = arma::vec( arma::size(x) ).fill(10);
    return 1 - (1 - arma::exp(-tmp) % x) - arma::exp(-10*x);
   //return x;
}