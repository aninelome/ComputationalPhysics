
#include <iostream> // input and output 
#include <fstream>  
#include <math.h>
#include <armadillo>
#include <iomanip>

using namespace std;
using namespace arma;

mat make_A(int N);
void solve_eig_prob(mat A, vec* eigval, mat* eigvec);