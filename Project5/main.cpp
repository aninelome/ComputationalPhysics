#include "functions.hpp"



int main(int argc, char const *argv[]) {
  int M = 5;                       // number of points along the x- and y-axis,
                                    // including the boundary points

  int N_slit = 2;                   // number of slits
  double d = 1;                     // width of the slit(s)
  double l = 1;                     // distance from the middle of the
                                    // barriere-column to the slit(s)
  //double l = int(M/10);

  double T = 9;                    // final time step
  double dt = 1;                  // step size for time
  int N_t = T/dt;                   // number of time steps
  //int N_t = 10;
  vec t_list = linspace(0, T, N_t); // list of all time steps
  t_list.save("t_list.bin");        // save t_list to bin

  double h = 1./(M-1);              // step size in x and y direction
  cx_double r = cx_double(0, dt/(2.*h*h)); // complex constant

  mat V = mat(M-2, M-2);            // declaring potential
  double v0 = pow(2, 30);           // high constant value used to set potential
                                    // in the barriere

  cx_vec a((M-2)*(M-2));            // declaring diagonal vector a for matrix A
  cx_vec b((M-2)*(M-2));            // declaring diagonal vector b for matrix B

  sp_cx_mat A = sp_cx_mat((M-2)*(M-2), (M-2)*(M-2)); // declaring matrix A
  sp_cx_mat B = sp_cx_mat((M-2)*(M-2), (M-2)*(M-2)); // declaring matrix B

  vec x = vec(M-2);                 // declaring vector for x postions
  vec y = vec(M-2);                 // declaring vector for y postions

  cx_vec u_init = cx_vec((M-2)*(M-2)); // declaring the initial state
  mat P = mat((M-2)*(M-2), N_t);


  double mu_x = 0.5;                //
  double sigma_x = 0.2;             //
  double k_x = 1;                   //
  double mu_y = 0.5;                //
  double sigma_y = 0.2;             //
  double k_y = 0;                   //

  // Fill x and y vectors
  for (int i = 0; i < M-2; i++)
  {
    x(i) = (i+1)*h;
    y(i) = (i+1)*h;
  }
  // save x and y vectors to bin
  x.save("x.bin");
  y.save("y.bin");

  // Setting up the initial state based on given wave packet:
  cx_vec f_x = wave_func(x, mu_x, sigma_x, k_x);
  cx_vec f_y = wave_func(y, mu_y, sigma_y, k_y);
  for (int i = 0; i < M-2; i++){
    for (int j = 0; j < M-2; j++){
      u_init(i*(M-2) + j) = f_x(i)*f_y(j);
    }
  }

  V = set_potential(M, v0, d, l, N_slit);
  make_diag_vectors(a, b, M, h, dt, V, r);
  make_A_B(a, b, r, M, A, B);
  //print_matrix(B, M);
  solve_matrix_eq(A, B, N_t, u_init, P);


  return 0;
}
