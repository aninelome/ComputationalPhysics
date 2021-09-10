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
      double h = 1./(n-1);
      double hh = h*h;
      vec a(n), b(n), c(n), g(n), v(n);


      // fill vectors a, b, c with values
      a.fill( -1);
      b.fill( 2);
      c.fill( -1);

      vec x = linspace(0, 1, n);
      vec f_x = 100.0*exp(-10*x);

      g(0) = hh*f_x(0);
      g = hh*f_x;


      for (int i = 1; i <= n-2; i++) {
          b(i) = b(i) - a(i)/b(i-1) * c(i-1);
          g(i) = g(i) - a(i)/b(i-1) * g(i-1);    
      }


    v(0) = 0;
    v(n-1) = 0;
    v(n-2) = g(n-2)/b(n-2);

    for (int i = n-3; i >= 1; i--) {
        v(i) = (g(i) - c(i)*v(i+1)) / b(i);

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


void V_special(int n, string filename){
    double h = 1./(n-1);
    double hh = h*h;
    vec a(n), b(n), c(n), g(n), v(n);

    // fill vectors a, b, c with values
    a.fill(-1);
    b.fill(2);
    c.fill(-1);

    vec x = linspace(0, 1, n);
    vec f_x = 100.0*exp(-10*x);

    g(0) = hh*f_x(0);
    g = hh*f_x;
    
    // calculate b outside the algorithm 
    for (int i = 1; i < n; i++) {
        b(i) = (i + 1.)/i;
    }
    
    for (int i = 1; i <= n-2; i++) {
        g(i) = g(i) - a(i)/b(i-1) * g(i-1);    
    }

    v(0) = v(n-1) = 0;
    v(n-2) = g(n-2)/b(n-2);

    for (int i = n-3; i > 0; i--) {
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


int main () {
    //int n = pow(10,6); 

    // Begin measuring time for the general algorithm 
    clock_t t1_gen = clock(); 

    for (int i = 1; i <= 6; i++) {
        int n = pow(10, i);
        V_special(n, "prob10_gen_n_" + to_string(n) + ".txt");
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