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

void make_diag_vectors(cx_vec &a,cx_vec &b, int M, double h, double dt, mat V, cx_double r)
{
  cx_double w = cx_double(0, dt/2.);
  for (int j = 0; j < V.n_rows; j++)
  {
    for (int i = 0; i < V.n_cols; i++)
    {
      a(i*V.n_cols + j) = 1. + 4.*r + w*V(i,j);
      b(i*V.n_cols + j) = 1. - 4.*r - w*V(i,j);
    }
  }
}

void make_A_B(cx_vec &a, cx_vec &b, cx_double r, int M, sp_cx_mat &A,  sp_cx_mat &B)
{
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

  for (int i = 0; i < (M-2)*(M-2); i++){
    for (int j = 0; j < (M-2)*(M-2); j++){
      //cout << A(i, j) << " ";
    }
    //cout << " " << endl;
  }

}

void solve_matrix_eq(sp_cx_mat &A,  sp_cx_mat &B, int N_t, cx_vec u_init)
{
  cx_vec u_n = u_init/norm(u_init);
  for (int i = 0; i < N_t; i++)
  {
    cx_vec y = B*u_n;
    cx_vec u_new = spsolve(A,y);
    u_new.save("u_n"+to_string(i)+".bin");
    cx_vec p_cx = conj(u_new)%u_new;
    vec p = real(p_cx);
    //p.print("p ");
    p.save("p"+to_string(i)+".bin");
    u_n = u_new;

  }

}

cx_vec wave_func(vec x, double mu, double sigma, double k)
{
  cx_vec f = exp(-0.5*pow((x-mu/sigma),2))%exp(1.0i*k*x);

  return f;
}

mat set_potential(int M, double v0, double d, double l, int N_slit)
{
  mat V = mat(M-2, M-2).fill(0);
  int m = int((M-2)/2);
  V.col(m).fill(v0);
  if (N_slit==1 or N_slit==2)
  {
    for (int i = 0; i < d; i++)
    {
      V(m+i+l,m) = 0;
      V(m-i-l,m) = 0;
    }
  }
  else if (N_slit==3)
  {
    for (int i = 0; i < d; i++)
    {
      V(m+i,m) = 0;
      V(m-i,m) = 0;
    }
    for (int i = 0; i < 2*d-1; i++)
    {
      V(m+d+l+i,m) = 0;
      V(m-d-l-i,m) = 0;
    }

  }


  V.print("V = ");

  return V;
}


int main(int argc, char const *argv[]) {
  int M = 10;
  double d = 1;
  //double l = int(M/10);
  double l = 1;
  double T = 10;
  double v0 = pow(2, 30);
  int N_slit = 3;
  double dt = 0.1;
  //int N_t = 10;
  int N_t = T/dt;
  vec t_list = linspace(0, T, N_t);
  t_list.save("t_list.bin");
  double h = 1./(M-1);
  double mu_x = 0.5;
  double sigma_x = 0.2;
  double k_x = 1;
  double mu_y = 0.5;
  double sigma_y = 0.2;
  double k_y = 0;
  cx_double r = cx_double(0, dt/(2.*h*h));
  //mat V = mat(M-2, M-2).fill(0);
  mat V = mat(M-2, M-2);
  cx_vec a((M-2)*(M-2));
  cx_vec b((M-2)*(M-2));
  sp_cx_mat A = sp_cx_mat((M-2)*(M-2), (M-2)*(M-2));
  sp_cx_mat B = sp_cx_mat((M-2)*(M-2), (M-2)*(M-2));
  vec x = vec(M-2);
  vec y = vec(M-2);

  for (int i = 0; i < M-2; i++)
  {
    x(i) = (i+1)*h;
    y(i) = (i+1)*h;
  }

  x.save("x.bin");
  y.save("y.bin");


  cx_vec f_x = wave_func(x, mu_x, sigma_x, k_x);
  cx_vec f_y = wave_func(y, mu_y, sigma_y, k_y);

  cx_vec u_init = cx_vec((M-2)*(M-2));

  for (int i = 0; i < M-2; i++){
    for (int j = 0; j < M-2; j++){
      u_init(i*(M-2) + j) = f_x(i)*f_y(j);
    }
  }
  V = set_potential(M, v0, d, l, N_slit);
  make_diag_vectors(a, b, M, h, dt, V, r);
  make_A_B(a, b, r, M, A, B);
  solve_matrix_eq(A, B, N_t, u_init);

  return 0;
}
