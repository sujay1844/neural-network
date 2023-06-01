#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdarg.h>
#include <sys/types.h>
#include <string.h>

#include "matrix.h"

Matrix *multiply(Matrix *a, Matrix *b)
{
	Matrix *result = malloc(sizeof(Matrix));
	result->rows = a->rows;
	result->cols = b->cols;
	result->data = malloc(sizeof(double *) * result->rows);
	for (int i = 0; i < result->rows; i++)
	{
		result->data[i] = malloc(sizeof(double) * result->cols);
	}
	for (int i = 0; i < result->rows; i++)
	{
		for (int j = 0; j < result->cols; j++)
		{
			result->data[i][j] = 0;
			for (int k = 0; k < a->cols; k++)
			{
				result->data[i][j] += a->data[i][k] * b->data[k][j];
			}
		}
	}
	return result;
}

Matrix *add(Matrix *a, Matrix *b)
{
	Matrix *result = malloc(sizeof(Matrix));
	result->rows = a->rows;
	result->cols = a->cols;
	result->data = malloc(sizeof(double *) * result->rows);
	for (int i = 0; i < result->rows; i++)
	{
		result->data[i] = malloc(sizeof(double) * result->cols);
	}
	for (int i = 0; i < result->rows; i++)
	{
		for (int j = 0; j < result->cols; j++)
		{
			result->data[i][j] = a->data[i][j] + b->data[i][j];
		}
	}
	return result;
}

void delete_matrix(Matrix *matrix)
{
	for (int i = 0; i < matrix->rows; i++)
	{
		free(matrix->data[i]);
	}
	free(matrix->data);
	free(matrix);
}

Matrix *get_identity_matrix(int size)
{
	Matrix *result = malloc(sizeof(Matrix));
	result->rows = size;
	result->cols = size;
	result->data = malloc(sizeof(double *) * result->rows);
	for (int i = 0; i < result->rows; i++)
	{
		result->data[i] = malloc(sizeof(double) * result->cols);
	}
	for (int i = 0; i < result->rows; i++)
	{
		for (int j = 0; j < result->cols; j++)
		{
			result->data[i][j] = i == j ? 1 : 0;
		}
	}
	return result;
}

Matrix *get_transpose(Matrix *matrix)
{
	Matrix *result = malloc(sizeof(Matrix));
	result->rows = matrix->cols;
	result->cols = matrix->rows;
	result->data = malloc(sizeof(double *) * result->rows);
	for (int i = 0; i < result->rows; i++)
	{
		result->data[i] = malloc(sizeof(double) * result->cols);
	}
	for (int i = 0; i < result->rows; i++)
	{
		for (int j = 0; j < result->cols; j++)
		{
			result->data[i][j] = matrix->data[j][i];
		}
	}
	return result;
}

Matrix *scalar_multiply(Matrix *matrix, double scalar)
{
	Matrix *result = malloc(sizeof(Matrix));
	result->rows = matrix->rows;
	result->cols = matrix->cols;
	result->data = malloc(sizeof(double *) * result->rows);
	for (int i = 0; i < result->rows; i++)
	{
		result->data[i] = malloc(sizeof(double) * result->cols);
	}
	for (int i = 0; i < result->rows; i++)
	{
		for (int j = 0; j < result->cols; j++)
		{
			result->data[i][j] = matrix->data[i][j] * scalar;
		}
	}
	return result;
}

Matrix *subtract(Matrix *a, Matrix *b)
{
	return add(a, scalar_multiply(b, -1));
}

double get_determinant(Matrix *matrix)
{
	if (matrix->rows != matrix->cols)
	{
		printf("Error: determinant of non-square matrix\n");
		exit(1);
	}
	if (matrix->rows == 1)
	{
		return matrix->data[0][0];
	}
	if (matrix->rows == 2)
	{
		return matrix->data[0][0] * matrix->data[1][1] - matrix->data[0][1] * matrix->data[1][0];
	}
	double result = 0;
	for (int i = 0; i < matrix->rows; i++)
	{
		Matrix *minor = malloc(sizeof(Matrix));
		minor->rows = matrix->rows - 1;
		minor->cols = matrix->cols - 1;
		minor->data = malloc(sizeof(double *) * minor->rows);
		for (int j = 0; j < minor->rows; j++)
		{
			minor->data[j] = malloc(sizeof(double) * minor->cols);
		}
		for (int j = 1; j < matrix->rows; j++)
		{
			for (int k = 0; k < matrix->cols; k++)
			{
				if (k < i)
				{
					minor->data[j - 1][k] = matrix->data[j][k];
				}
				else if (k > i)
				{
					minor->data[j - 1][k - 1] = matrix->data[j][k];
				}
			}
		}
		result += matrix->data[0][i] * get_determinant(minor) * (i % 2 == 0 ? 1 : -1);
		for (int j = 0; j < minor->rows; j++)
		{
			free(minor->data[j]);
		}
		free(minor->data);
		free(minor);
	}
	return result;
}

Matrix *get_sigmoid(Matrix *matrix)
{
	Matrix *result = malloc(sizeof(Matrix));
	result->rows = matrix->rows;
	result->cols = matrix->cols;
	result->data = malloc(sizeof(double *) * result->rows);
	for (int i = 0; i < result->rows; i++)
	{
		result->data[i] = malloc(sizeof(double) * result->cols);
	}
	for (int i = 0; i < result->rows; i++)
	{
		for (int j = 0; j < result->cols; j++)
		{
			result->data[i][j] = 1 / (1 + exp(-matrix->data[i][j]));
		}
	}
	return result;
}

Matrix *get_random_matrix(int rows, int cols)
{
	Matrix *result = malloc(sizeof(Matrix));
	result->rows = rows;
	result->cols = cols;
	result->data = malloc(sizeof(double *) * result->rows);
	for (int i = 0; i < result->rows; i++)
	{
		result->data[i] = malloc(sizeof(double) * result->cols);
	}
	for (int i = 0; i < result->rows; i++)
	{
		for (int j = 0; j < result->cols; j++)
		{
			// use random values between -1 and 1
			result->data[i][j] = 2 * ((double)rand() / RAND_MAX) - 1;
		}
	}
	return result;
}

Matrix *ones(int rows, int cols)
{
	Matrix *result = malloc(sizeof(Matrix));
	result->rows = rows;
	result->cols = cols;
	result->data = malloc(sizeof(double *) * result->rows);
	for (int i = 0; i < result->rows; i++)
	{
		result->data[i] = malloc(sizeof(double) * result->cols);
	}
	for (int i = 0; i < result->rows; i++)
	{
		for (int j = 0; j < result->cols; j++)
		{
			result->data[i][j] = 1;
		}
	}
	return result;
}

Matrix *zeros(int rows, int cols)
{
	return scalar_multiply(ones(rows, cols), 0);
}

void print_matrix(Matrix *matrix)
{
	printf("Size: %d x %d\n", matrix->rows, matrix->cols);
	for (int i = 0; i < matrix->rows; i++)
	{
		for (int j = 0; j < matrix->cols; j++)
		{
			printf("%f\t", matrix->data[i][j]);
		}
		printf("\n");
	}
}

// using variable arguments to allow for any number of matrices to be passed in
void delete_matrices(int num_matrices, ...)
{
	va_list matrices;
	va_start(matrices, num_matrices);
	for (int i = 0; i < num_matrices; i++)
	{
		Matrix *matrix = va_arg(matrices, Matrix *);
		for (int j = 0; j < matrix->rows; j++)
		{
			free(matrix->data[j]);
		}
		free(matrix->data);
		free(matrix);
	}
	va_end(matrices);
}

Matrix *normalize(Matrix *matrix)
{
	Matrix *result = malloc(sizeof(Matrix));
	result->rows = matrix->rows;
	result->cols = matrix->cols;
	result->data = malloc(sizeof(double *) * result->rows);
	for (int i = 0; i < result->rows; i++)
	{
		result->data[i] = malloc(sizeof(double) * result->cols);
	}
	double max = matrix->data[0][0];
	double min = matrix->data[0][0];
	for (int i = 0; i < matrix->rows; i++)
	{
		for (int j = 0; j < matrix->cols; j++)
		{
			if (matrix->data[i][j] > max)
			{
				max = matrix->data[i][j];
			}
			if (matrix->data[i][j] < min)
			{
				min = matrix->data[i][j];
			}
		}
	}
	for (int i = 0; i < result->rows; i++)
	{
		for (int j = 0; j < result->cols; j++)
		{
			result->data[i][j] = (matrix->data[i][j] - min) / (max - min);
		}
	}
	return result;
}

// Matrix *import_from_csv(char *filename)
// {
// 	FILE *file = fopen(filename, "r");
// 	if (file == NULL)
// 	{
// 		printf("Error: file not found\n");
// 		exit(1);
// 	}
// 	int rows = 0;
// 	int cols = 0;
// 	char *line = NULL;
// 	size_t len = 0;
// 	ssize_t read;
// 	while ((read = getline(&line, &len, file)) != -1)
// 	{
// 		rows++;
// 		char *token = strtok(line, ",");
// 		while (token != NULL)
// 		{
// 			cols++;
// 			token = strtok(NULL, ",");
// 		}
// 		break;
// 	}
// 	rewind(file);
// 	Matrix *result = malloc(sizeof(Matrix));
// 	result->rows = rows;
// 	result->cols = cols;
// 	result->data = malloc(sizeof(double *) * result->rows);
// 	for (int i = 0; i < result->rows; i++)
// 	{
// 		result->data[i] = malloc(sizeof(double) * result->cols);
// 	}
// 	int i = 0;
// 	while ((read = getline(&line, &len, file)) != -1)
// 	{
// 		char *token = strtok(line, ",");
// 		int j = 0;
// 		while (token != NULL)
// 		{
// 			result->data[i][j] = atof(token);
// 			j++;
// 			token = strtok(NULL, ",");
// 		}
// 		i++;
// 	}
// 	fclose(file);
// 	if (line)
// 	{
// 		free(line);
// 	}
// 	return result;
// }