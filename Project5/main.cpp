#include "functions.hpp"



int main(int argc, char const *argv[]) {
  arma::mat Param;
  Param.load("prob7_2.txt", arma::raw_ascii);

  double h = Param(0);              // step size in x and y direction
  int M = int((1./h) + 1);          // number of points along the x- and y-axis,
                                    // including the boundary points

  int N_slit = 2;                   // number of slits
  int d = int(0.05*(M-2));          // width of the slit(s) in the y_direction
  int w = int(0.02*(M-2));          // width of the slit(s) in the x_direction
  int l = int(0.025*(M-2));         // distance from the middle of the
                                    // barriere-column to the slit(s)

  //int N_slit = 1;                   // number of slits
  //int d = int(0.05*(M-2));          // width of the slit(s) in the y_direction
  //int w = int(0.02*(M-2));          // width of the slit(s) in the x_direction
  //int l = 0;

  //int N_slit = 3;                   // number of slits
  //int d = int(0.025*(M-2));         // width of the slit(s) in the y_direction
  //int w = int(0.02*(M-2));          // width of the slit(s) in the x_direction
  //int l = int(0.05*(M-2));

  double T = Param(2);                    // final time step
  double dt = Param(1);                  // step size for time
  int N_t = T/dt;                   // number of time steps
  //int N_t = 10;
  vec t_list = linspace(0, T, N_t); // list of all time steps
  t_list.save("t_list.bin");        // save t_list to bin

  cx_double r = cx_double(0, dt/(2.*h*h)); // complex constant

  mat V = mat(M-2, M-2);            // declaring potential
  double v0 = Param(9);           // high constant value used to set potential
                                    // in the barriere

  cx_vec a((M-2)*(M-2));            // declaring diagonal vector a for matrix A
  cx_vec b((M-2)*(M-2));            // declaring diagonal vector b for matrix B

  sp_cx_mat A = sp_cx_mat((M-2)*(M-2), (M-2)*(M-2)); // declaring matrix A
  sp_cx_mat B = sp_cx_mat((M-2)*(M-2), (M-2)*(M-2)); // declaring matrix B

  vec x = vec(M-2);                 // declaring vector for x postions
  vec y = vec(M-2);                 // declaring vector for y postions

  cx_vec u_init = cx_vec((M-2)*(M-2)); // declaring the initial state
  mat P = mat((M-2)*(M-2), N_t);
  mat U_re = mat((M-2)*(M-2), N_t);
  mat U_im = mat((M-2)*(M-2), N_t);



  double x_c = Param(3);                //
  double sigma_x = Param(4);            //
  double y_c = Param(6);                //
  double sigma_y = Param(7);            //
  double p_x = Param(5);
  double p_y = Param(8);


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
  wave_func(x, y, x_c, y_c, sigma_x, sigma_y, p_x, p_y, u_init, M);


  V = set_potential(M, v0, d, w, l, N_slit);
  make_diag_vectors(a, b, M, h, dt, V, r);
  make_A_B(a, b, r, M, A, B);
  //print_matrix(B, M);
  solve_matrix_eq(A, B, N_t, u_init, P, U_re, U_im);

  return 0;
}
