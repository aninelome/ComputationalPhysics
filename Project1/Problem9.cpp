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
    vec a(n), b(n), c(n), g(n), v(n); // define vectors 

    // fill vectors a, b, c with values
    a.fill(-1);
    b.fill(2);
    c.fill(-1);

    vec x = linspace(0, 1, n);         // define x from 0 to 1 
    double h = x(1) - x(0);            // define h and h^2 
    double hh = h*h;
    vec f_x = 100.0*exp(-10*x);

    // set initial values for g 
    g(0) = hh*f_x(0);
    g = hh*f_x;
    
    for (int i = 1; i < n; i++) {                 // calculate b outside the algorithm 
        b(i) = (i + 1.)/i;
    }
    
    for (int i = 2; i <= n-2; i++) {              // calculate g 
        g(i) = g(i) - a(i)/b(i-1) * g(i-1);    
    }

    // Define initial values for v 
    v(0) = v(n-1) = 0;
    v(n-2) = g(n-2)/b(n-2);

    for (int i = n-3; i >= 1; i--) {                // calculate v
        v(i) = (g(i) - c(i)*v(i+1)) / b(i);
    }

    // write x and v to a textfile
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
    // run V_special for n=10
    for (int i = 1; i <= 1; i++) {
        int n = pow(10, i);
        cout << "n = " << n << endl;
        V_special(n, "prob9_n_" + to_string(n) + ".txt");
    }
    return 0;
}
