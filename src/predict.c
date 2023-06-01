#include <stdio.h>

#include "matrix.h"

Matrix *predict(Matrix *input, Matrix *weights, Matrix *biases)
{
	return add(multiply(weights, input), biases);
}

Matrix *train(Matrix *input, Matrix *weights, Matrix *biases, Matrix *expected)
{
	Matrix *prediction = predict(input, weights, biases);
	Matrix *error = subtract(prediction, expected);
	Matrix *gradient = multiply(input, error);
	Matrix *delta = scalar_multiply(gradient, 0.01);
	weights = subtract(weights, delta);
	biases = subtract(biases, error);
	delete_matrices(4, prediction, error, gradient, delta);
	printf("train\n");
	return weights;
}