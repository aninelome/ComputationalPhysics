#include <iostream>    // For cout, endl
#include <vector>      // For vector
#include <string>      // For string
#include <armadillo>

using namespace std;
using namespace arma;


// col er et tidssteg 



/// denne må føres som en algoritme 
void forward_euler(int n) {
    int h = 1; 
    int m = 1; 
    // Define the matrice as 3*n 
    mat v, r; 
    v = mat(3,n).fill(0); 
    r = mat(3,n).fill(0); 
    vec t = vec(n).fill(0); 

    int F = 10; 


    // må sjekke n - 1 
    for (int i = 0; i = n-2; i++) {
        for (int j = 0; j = 2; j++) {
        int a = F/m;                  // m hentes fra klassen 
        v(j,i+1) = v(j,i) + a*h;
        r(j,i+1) = r(j,i) + v(j,i) * h; 
        t(i+1) = t(i) + h; 
        }
    }
    cout << v << endl; 


}

int main() {
    forward_euler(3);
    return 0; 
}