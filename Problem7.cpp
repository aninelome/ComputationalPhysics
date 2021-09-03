//Prob. 7

#include <iostream> // input and output 
#include <fstream> // access to ofstream class 
#include <math.h>
#include <armadillo>

using namespace std;
using namespace arma;

int main(int argc, char const *argv[]){
    int n = 4; 
    vec a[n], b[n], c[n], g[n], v[n]; 

    // fill vectors a, b, c with values 
    a.fill(int -1);
    b.fill(int 2);
    c.fill(int -1);

    v[0] = 0; 

    vec x = linspace(0, 1, n);
    vec f_x = 100*exp(-10*x); 
    g = h^2 + f_x; 

    for (int i = 1; i <= n-1; i++) {
        b[i] = b[i] - a[i]/b[i-1] * c[i-1];
        g[i] = g[i] - a[i]/b[i-1] * g[i-1];
    }
    
    v[n-1] = g[n-1]/b[n-1]

    for (int i = n-2; i >= 0; i++) {
        v[i] = (g[i] - c[i]*v[i+1]) / b[i]; 
    }

    // write x and U(x) to a textfile 
    ofstream file; 
    file.open("solutions_prob7.txt", ios::out); //opens file in out/write mode

    for (int i = 0; i < n; i++){
        file << setw(15) << setprecision(3) << x[i];
        file <<fixed<< setw(15) << setprecision(8) << v[i] << endl; 

    }

    file.close(); 

    return 0; 
}