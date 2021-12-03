#include "functions.hpp"

using namespace arma;
using namespace std;

// Function translating a pair of indices (i,j) into a corresponding single
// index k that gives the position of u_{ij} in the vector u
int index(int i, int j, int M)
{
  int k = i + j*(M-2);
  return k;
}

// Function making the vectors a and b that should be on the diagonal of
// respectively the A and B matrices
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

// Function making the A and B matrices
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
}

// Funtion solving the matrix equation Au^{n+1} = b for the unknown uu^{n+1}
void solve_matrix_eq(sp_cx_mat &A,  sp_cx_mat &B, int N_t, cx_vec u_init, mat &P, mat &U_re, mat &U_im)
{
  vec P_tot = vec(N_t);
  cx_vec u_n = u_init/norm(u_init);
  for (int i = 0; i < N_t; i++)
  {
    cx_vec y = B*u_n;
    cx_vec u_new = spsolve(A,y);
    U_re.col(i) = real(u_new);
    U_im.col(i) = imag(u_new);
    //u_new.save("u_n"+to_string(i)+".bin");
    cx_vec p_cx = conj(u_new)%u_new;
    vec p = real(p_cx);
    P.col(i) = p;
    P_tot(i) = sum(p);
    //p.print("p ");
    //p.save("p"+to_string(i)+".bin");
    u_n = u_new;
  }
  //P.print("P ");
  P.save("P.bin");
  U_re.save("U_re.bin");
  U_im.save("U_im.bin");
  P_tot.save("P_tot.bin");


}

// Function setting up the initial state u^{0} based on an
// expression for a Gaussian wave packet
void wave_func(vec x, vec y, double x_c, double y_c, double sigma_x, double sigma_y, double p_x, double p_y, cx_vec &u_init, int M)
{
  cx_double ii = cx_double(0,1);
  cx_vec f_x = exp(-0.5*pow((x-x_c),2)/pow(sigma_x,2) + ii*p_x*(x-x_c));
  cx_vec f_y = exp(-0.5*pow((y-y_c),2)/pow(sigma_y,2) + ii*p_y*(y-y_c));
  for (int i = 0; i < M-2; i++)
  {
    for (int j = 0; j < M-2; j++)
    {
      u_init(i + j*(M-2)) = f_x(i)*f_y(j);
    }
  }
}


// Function that initializes the potential V. Use this to construct the
// barriers used for the single-, double- and tripple slit.
// NB! Pay attention to the parametres d, l and N_slit vs M.
// Trying to set N_slit = 3 on a small matrix may lead to "std:out_of_range"
mat set_potential(int M, double v0, int d, int w, int l, int N_slit)
{
  mat V = mat(M-2, M-2).fill(0);
  int m = int((M-2)/2);
  for (int j = 0; j < w; j++)
  {
    V.col(m+j).fill(v0);

    if (N_slit==1 or N_slit==2)
    {
      for (int i = 0; i < d; i++)
      {
        V(m+i+l,m+j) = 0;
        V(m-i-l,m+j) = 0;
      }
    }
    else if (N_slit==3)
    {
      for (int i = 0; i < d; i++)
      {
        V(m+i,m+j) = 0;
        V(m-i,m+j) = 0;
      }
      for (int i = 0; i < 2*d-1; i++)
      {
        V(m+d+l+i,m+j) = 0;
        V(m-d-l-i,m+j) = 0;
      }

    }
  }
  V.print("V = ");

  return V;
}

// Funtion printing a given (sp_cx_mat) matrix in a nice layout
void print_matrix(sp_cx_mat &A, int M)
{
  for (int i = 0; i < (M-2)*(M-2); i++)
  {
    for (int j = 0; j < (M-2)*(M-2); j++)
    {
      cout << A(i, j) << " ";
    }
    cout << " " << endl;
  }
}
