#ifndef FINAL_SPKMEANS_H
#define FINAL_SPKMEANS_H

int get_dimension_from_file(char *filename);
int get_num_of_points_from_file(char *filename);
void read_data_from_input_file_to_matrix(int dim, int num_of_points, double **mat, char *filename);
void print_mat(int d, int n, double **mat);


#endif //FINAL_SPKMEANS_H
