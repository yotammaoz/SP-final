#include "useful.h"
#include "math.h"
#include "stdlib.h"
#include "matrix_calculations.h"

/* creates the weighted adjacency matrix from dXn data_points matrix */
double **createWeightedAdjacencyMatrix(int n, int d, double** data_points) 
{
    double **matrix = allocate_memory_array_of_points(n, n);
    double val;
    int i;
    int j;
    for (i=0; i < n; i++) {
        for (j=i+1; j < n; j++) {
            val = exp(-euclidean_norm(d, data_points[i], data_points[j])/2);
            matrix[i][j] = val;
            matrix[j][i] = val;
        }
    }
    return matrix;
}

/* creates the diagonal degree matrix from nXn matrix weightedMatrix */
double **createDiagonalDegreeMatrix(int n, double ** weightedMatrix) 
{
    double **matrix = allocate_memory_array_of_points(n, n);
    double val;
    int i;
    int j;
    for (i=0; i < n; i++) {
        val = 0;
        for (j=0; j < n; j++) {
            val += weightedMatrix[i][j];
        }
        matrix[i][i] = val;
    }
    return matrix;
}

/* return matrix^(-1/2) for the diagonal nXn matrix - matrix */
double ** getDiagonalMatrixPoweredByMinusHalf(int n, double ** matrix) 
{
    double **resultMatrix = allocate_memory_array_of_points(n, n);
    int i;
    for (i=0; i < n; i++) {
        resultMatrix[i][i] = 1 / sqrt(matrix[i][i]);
    }
    return resultMatrix;
}

/* returns matrixA*matrixB for nXn matrices matrixA,matrixB */
double **multiplyMatrix(int n, double **matrixA, double **matrixB) 
{
    double **matrix = allocate_memory_array_of_points(n, n);
    int i;
    int j;
    int k;
    double val;
    for (i=0; i < n ; i++) {
        for (j=0; j < n ; j++) {
            val = 0;
            for (k=0; k < n; k++) {
                val += matrixA[i][k] * matrixB[k][j];
            }
            matrix[i][j] = val;
        }
    }
    return matrix;
}

/* returns matrixA*matrixB*matrixC for nXn matrices matrixA,matrixB,matrixC */
double **multiply3Matrices(int n, double **matrixA, double **matrixB, double **matrixC) 
{
    double ** tmp = multiplyMatrix(n, matrixA, matrixB);
    double ** result = multiplyMatrix(n, tmp, matrixC);
    free_matrix(tmp);
    return result;
}

/* returns I-matrix for nXn matrix - matrix */
double **subtractIbyMatrix(int n, double **matrix) 
{
    double **result = allocate_memory_array_of_points(n, n);
    int i;
    int j;
    for (i=0; i < n; i++) {
        for (j=0; j < n; j++) {
            if (i==j) {
                result[i][j] = 1;
            }
            result[i][j] -= matrix[i][j];
        }
    }
    return result;
}

/* returns the nXn unit matrix - I */
double **getUnitMatrix(int n) 
{
    double **result = allocate_memory_array_of_points(n, n);
    int i;
    for (i=0; i < n; i++) {
        result[i][i] = 1;
    }
    return result;
}

/* returns the normalized graph laplacian matrix from nXn matrices diagonalDegreeMatrix,weightedAdjacencyMatrix */
double **createNormalizedGraphLaplacian(int n, double** diagonalDegreeMatrix, double ** weightedAdjacencyMatrix) 
{
    double ** d = getDiagonalMatrixPoweredByMinusHalf(n, diagonalDegreeMatrix);
    double ** tmp = multiply3Matrices(n, d, weightedAdjacencyMatrix, d);
    double ** result = subtractIbyMatrix(n, tmp);
    free_matrix(tmp);
    free_matrix(d);
    return result;
}

/* returns the transpose of the nXn matrix - matrix */
double **transposeMatrix(int n, double **matrix) 
{
    double **result = allocate_memory_array_of_points(n, n);
    int i;
    int j;
    for (i=0; i < n; i++) {
        for (j=0; j < n; j++) {
                result[i][j] = matrix[j][i];
        }
    }
    return result;
}

/* returns matrixP^t*matrixA*matrixP for nXn matrices matrixA,matrixP */
double **multipleFromBothSides(int n, double** matrixA, double ** matrixP) 
{
    double **matrixPTransposed = transposeMatrix(n, matrixP);
    double **result = multiply3Matrices(n, matrixPTransposed, matrixA, matrixP);
    free_matrix(matrixPTransposed);
    return result;
}

/* returns the indices of the element in nXn matrix with the largest absolute value off the diagonal */
int *getIndicesOfLargestAbsoluteValueInOffDiagonal(int n, double **matrix) 
{
    int *indices = calloc(2,sizeof(int));
    int i;
    int j;
    if (indices==NULL)
        error();
    indices[0]=0;
    indices[1]=1;
    for (i=0; i < n; i++) {
        for (j=0; j < n; j++) {
            if ((fabs(matrix[indices[0]][indices[1]]) <= fabs(matrix[i][j]))&&(i!=j))
            {
                indices[0] = i;
                indices[1] = j;
            }
        }
    }
    return indices;
}


// TODO: add functions:
int run_eigengap_heuristic(double * eigenvalues)
{
    return 0;
}

double **get_t_matrix(double ** eigen_matrix, int k)
{
    return eigen_matrix;
}