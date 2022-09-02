#ifndef FINAL_USEFUL_H
#define FINAL_USEFUL_H

double euclidean_norm_powered(int d, double *p1, double *p2);
double euclidean_norm(int d, double *p1, double *p2);
int* allocate_memory_array_of_size(int k);
double** allocate_memory_array_of_points(int d, int array_size);
int sign(double num);
void free_matrix(double **matrix);
void invalid_input();
void error();


#endif 
