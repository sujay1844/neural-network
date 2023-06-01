#include <stdio.h>

#include "matrix.h"

Matrix *predict(Matrix *input, Matrix *weights, Matrix *biases)
{
	Matrix *result = add(multiply(weights, input), biases);
	return result;
}

Matrix *train(Matrix *input, Matrix *weights, Matrix *biases, Matrix *expected)
{
	Matrix *result = predict(input, weights, biases);
	Matrix *error = subtract(result, expected);
	printf("hello\n");
	Matrix *gradient = multiply(get_transpose(input), error);
	delete_matrix(error);
	Matrix *delta = scalar_multiply(gradient, 0.01);
	delete_matrix(gradient);
	weights = subtract(weights, delta);
	delete_matrix(delta);
	biases = subtract(biases, error);
	delete_matrix(result);
	return weights;
}