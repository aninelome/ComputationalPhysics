#include <iostream>
#include <armadillo>
#include <valarray>
#include <stdexcept>
#include <vector>
#include <string>
#include <complex>
using namespace arma;
using namespace std;


int index(int i, int j, int M)
{
  int k = i + j*(M-2);
  return k;
}

cx_mat make_diag_mat(int M, double h, double dt, mat V)
{
  cx_double r = cx_double(0, dt/(2.*h*h));
  cx_double w = cx_double(0, dt/2.);
  cx_mat diag_mat = cx_mat(2, pow((M-2),2));
  cout << "hei" << endl;
  for (int j = 0; j < V.n_rows; j++)
  {
    for (int i = 0; i < V.n_cols; i++)
    {
      cout << "k(" + to_string(i) + "," + to_string(j) + "): " << index(i,j,M) << endl;
      diag_mat(0, index(i,j,M)) = 1. + 4.*r + w*V(i,j);
      diag_mat(1, index(i,j,M)) = 1. - 4.*r - w*V(i,j);

    }
  }
  return diag_mat;
}

int main(int argc, char const *argv[]) {
  //cout << "k: " << index(1,2,5) << endl;

  int M = 5;
  int r = 9;
  double h = 0.1;
  double dt = 0.1;
  mat V = mat(M-2, M-2).fill(1);
  //vec a = vec((M-2)*(M-2)).fill(0);
  //vec b = vec((M-2)*(M-2)).fill(0);
  cx_mat A = cx_mat((M-2)*(M-2), (M-2)*(M-2)).fill(0);
  cx_mat B = cx_mat((M-2)*(M-2), (M-2)*(M-2)).fill(0);

  //vec a = linspace(0,15, 16);
  //vec b = linspace(0,15, 16);

  cx_mat diag_mat = make_diag_mat(M, h, dt, V);

  cx_vec a((M-2)*(M-2));
  cx_vec b((M-2)*(M-2));
  a = diag_mat.row(0);
  b =  diag_mat.row(1);
  cout << a << endl;
  cout << b << endl;

  for (int i = 0; i <= M-3; i++)
  {
      for (int j = 0; j < M-2; j++)
      {
        A(i+j*(M-2),i+j*(M-2)) = a(i+j*(M-2));
        B(i+j*(M-2),i+j*(M-2)) = b(i+j*(M-2));
      }
      for (int j = 0; j < M-3; j++)
      {
        A(i+j*(M-2),i+(j+1)*(M-2)) = -r;
        B(i+j*(M-2),i+(j+1)*(M-2)) = r;

        A(i+(j+1)*(M-2), i+j*(M-2)) = -r;
        B(i+(j+1)*(M-2), i+j*(M-2)) = r;
      }
  }

  for (int i = 0; i <= M-4; i++)
  {
    for (int j = 0; j < M-2; j++)
    {
      A(i+1+j*(M-2), i+j*(M-2)) = -r;
      A(i+j*(M-2), i+1+j*(M-2)) = -r;
      B(i+1+j*(M-2), i+j*(M-2)) = r;
      B(i+j*(M-2), i+1+j*(M-2)) = r;
    }
  }
  cout << A << endl;
  cout << B << endl;
  return 0;
}
