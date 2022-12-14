#include "math.h"
#include "stdlib.h"
#include <ctype.h>
#include <stdio.h>
#include "useful.h"
#define PY_SSIZE_T_CLEAN

/* prints "Invalid Input!" and exits */
void invalid_input()
{
    printf("Invalid Input!");
    exit(1);
}

/* prints "An Error Has Occurred" and exits */
void error()
{
    printf("An Error Has Occurred");
    exit(1);
}

double euclidean_norm_powered(int d, double *p1, double *p2)
/* calculates the l2 distance to the second power between points p1 and p2 */
{
    int i;
    double result = 0;
    for (i=0; i < d ; i++) {
        result += pow(p1[i] - p2[i], 2);
    }
    return result;
}

double euclidean_norm(int d, double *p1, double *p2)
/* calculates the l2 distance between points p1 and p2 */
{
    return sqrt(euclidean_norm_powered(d, p1, p2));
}

/* allocates array of ints of size k */
int* allocate_memory_array_of_size(int k) 
{
    int* a = calloc(k, sizeof(int));
    if (a == NULL)
        error();
    return a;
}

/* allocates a array_sizeXd matrix of doubles */
double** allocate_memory_array_of_points(int d, int array_size) 
{
    double *p;
    double **a;
    int i;
    p = calloc(d * array_size, sizeof(double));
    a = calloc(array_size, sizeof(double *));
    for(i=0 ; i < array_size ; i++ )
        a[i] = p+ i * d;
    if ((a == NULL)||(p==NULL))
        error();
    return a;
}

/* free a matrix that was allocated by allocate_memory_array_of_points */
void free_matrix(double **matrix)
{
    free(matrix[0]); /* free the underlying array of data */
    free(matrix); /* free the array pointing to the rows in the data array */
}


/* return 1 if num>=0 else return 0 */
int sign(double num) {
    if (num >= 0) {
        return 1;
    }
    return -1;
}


