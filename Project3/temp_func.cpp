#include <iostream>    // For cout, endl
#include <vector>      // For vector
#include <string>      // For string
#include <armadillo>

using namespace std;
using namespace arma;


// col er et tidssteg 

void forward_euler(int n = 10);

/// denne må føres som en algoritme 
void forward_euler(int n) {
    int h = 1; 
    int m = 1; 
    // definer matrise til å være 3*n 
    mat v, r; 
    v = mat(3,n).fill(0); 
    r = mat(3,n).fill(0); 
    vec t = vec(n).fill(0); 

    cout << v << endl; 

    
    /* 
    for (int i = 0; i = n-1; i++) {
        mat a = F/m;                  // m hentes fra klassen 
        v(:,i+1) = v(:,i) + a*h;
        r(:,i+1) = r(:,i) + v(:,i) * h; 
        t(i+1) = t(i) + h; 
    }
    cout << v << r << t << endl; 
    */ 


}