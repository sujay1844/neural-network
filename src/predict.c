#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"

Matrix *predict(Matrix *input, Matrix *weights, Matrix *biases)
{
	return add(multiply(weights, input), biases);
}

Matrix *train(Matrix *input, Matrix *weights, Matrix *biases, Matrix *expected)
{
	Matrix *prediction = predict(input, weights, biases);
	Matrix *error = subtract(prediction, expected);
	Matrix *gradient = normalize(error);
	Matrix *delta = scalar_multiply(gradient, 0.01);
	// print_matrix(weights);
	// print_matrix(delta);
	Matrix *new_weights = multiply(delta, weights);
	// print_matrix(new_weights);
	// biases = subtract(biases, error);
	delete_matrices(4, prediction, error, gradient, delta);
	return new_weights;
}