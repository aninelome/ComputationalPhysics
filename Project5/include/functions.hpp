#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <iostream>
#include <armadillo>
#include <valarray>
#include <string>
#include <complex>
#include <stdexcept>
#include <vector>

using namespace arma;
using namespace std;


int index(int i, int j, int M);

void make_diag_vectors(cx_vec &a,cx_vec &b, int M, double h, double dt, mat V, cx_double r);

void make_A_B(cx_vec &a, cx_vec &b, cx_double r, int M, sp_cx_mat &A,  sp_cx_mat &B);

mat set_potential(int M, double v0, int d, int w, int l, int N_slit);

//cx_vec wave_func(vec x, double mu, double sigma, double k);
void wave_func(vec x, vec y, double x_c, double y_c, double sigma_x, double sigma_y, double p_x, double p_y, cx_vec &u_init, int M);


//void solve_matrix_eq(sp_cx_mat &A,  sp_cx_mat &B, int N_t, cx_vec u_init);
void solve_matrix_eq(sp_cx_mat &A,  sp_cx_mat &B, int N_t, cx_vec u_init, mat &P, mat &U_re, mat &U_im);


void print_matrix(sp_cx_mat &A, int M);



#endif
