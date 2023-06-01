#ifndef MATRIX_H
#define MATRIX_H

typedef struct Matrix
{
	int rows;
	int cols;
	double **data;
} Matrix;

Matrix *get_random_matrix(int rows, int cols);
Matrix *get_sigmoid(Matrix *matrix);
void print_matrix(Matrix *matrix);
double get_determinant(Matrix *matrix);
Matrix *get_transpose(Matrix *matrix);
Matrix *get_identity_matrix(int size);
Matrix *zeros(int rows, int cols);
Matrix *ones(int rows, int cols);
void delete_matrix(Matrix *matrix);
void delete_matrices(int num_matrices, ...);
Matrix *add(Matrix *a, Matrix *b);
Matrix *subtract(Matrix *a, Matrix *b);
Matrix *multiply(Matrix *a, Matrix *b);
Matrix *scalar_multiply(Matrix *matrix, double scalar);

#endif // MATRIX_H