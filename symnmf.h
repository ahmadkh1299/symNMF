//
// Created by 97250 on 10/1/2023.
//

#ifndef NMF_C_SYMNMF_H
#define NMF_C_SYMNMF_H

double norm(double **DataPoints, int i, int j, int dimensions);
double **mat_multiply(double **A_mat, double **B_mat,int PointCount);
double **Similarity_matrix(double **DataPoints, int PointCount, int dimensions);
double **DDG(double **Simi_mat, int PointCount);
double **Normal_sim(double **DDG, double **sim_mat, int PointCount);
void Sizefile(char *filename, int *dimension, int *rows);
void print_matrix(double **matrix, int row, int col);
double **sym_case(double **matrix, int N, int d);
double **ddg_case(double **matrix, int N, int d);
double **norm_case(double **matrix, int N,int d);
double **symnmf(double **DataPoints, double **init_H, int N, int d, int k);
double** Transpose(double** A,int N,int d);
double **mat_multiply_plus(double **A_mat, double **B_mat,int row1,int column1 ,int column2);

#endif //NMF_C_SYMNMF_H
