//Prob. 10

#include <iostream> // input and output
#include <fstream> // access to ofstream class
#include <math.h>
#include <armadillo>
#include <cmath>
#include <iomanip>
#include <time.h>

using namespace std;
using namespace arma;


void V(int n, string filename){
    vec a(n), b(n), c(n), g(n), v(n); // define vectors 

    // fill vectors a, b, c with values
    a.fill( -1);
    b.fill( 2);
    c.fill( -1);

    vec x = linspace(0, 1, n); // define x from 0 to 1 
    double h = x(1)-x(0);      // define h and h^2 
    double hh = h*h;
    vec f_x = 100.0*exp(-10*x);

    // set initial values for g 
    g(0) = hh*f_x(0);
    g = hh*f_x;

    // Begin Algorithm 
    for (int i = 2; i <= n-2; i++) {
        b(i) = b(i) - a(i)/b(i-1) * c(i-1);
        g(i) = g(i) - a(i)/b(i-1) * g(i-1);
    }

    // define initial values for v 
    v(0) = v(n-1) = 0;
    v(n-2) = g(n-2)/b(n-2);

    for (int i = n-3; i >= 1; i--) {              // calculate v 
        v(i) = (g(i) - c(i)*v(i+1)) / b(i);
    }

    return;
}

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
    
    for (int i = 1; i < n; i++) {                 // calculate b outside the main algorithm 
        b(i) = (i + 1.)/i;
    }
    
    // Begin Algorithm 
    for (int i = 2; i <= n-2; i++) {              // calculate g 
        g(i) = g(i) - a(i)/b(i-1) * g(i-1);    
    }

    // Define initial values for v 
    v(0) = v(n-1) = 0;
    v(n-2) = g(n-2)/b(n-2);

    for (int i = n-3; i >= 1; i--) {                // calculate v
        v(i) = (g(i) - c(i)*v(i+1)) / b(i);
    }

    return;
}

int main () {
    // Begin measuring time for the general algorithm 
    clock_t t1_gen = clock(); 

    for (int i = 1; i <= 6; i++) {
        int n = pow(10, i);
        V(n, "prob10_gen_n_" + to_string(n) + ".txt");
    }

    clock_t t2_gen = clock(); // Stop measuring time 


    // Begin measuring time for the special algorithm 
    clock_t t1_special = clock();

    for (int i = 1; i <= 6; i++) {
        int n = pow(10, i);
        V_special(n, "prob10_spess_n_" + to_string(n) + ".txt");
    }

    clock_t t2_special = clock(); // Stop measuring time

    // Calculate the elapsed time.
    double duration_seconds_gen = ((double) (t2_gen - t1_gen)) / CLOCKS_PER_SEC;
    double duration_seconds_special = ((double) (t2_special - t1_special)) / CLOCKS_PER_SEC; 

    cout << "General Algorithm: " << duration_seconds_gen << " s" << endl; 
    cout << "Special Algorithm: " << duration_seconds_special << " s" << endl; 

    return 0; 
}
