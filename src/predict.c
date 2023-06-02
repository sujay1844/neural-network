#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"

Matrix *predict(Matrix *input, Matrix *weights, Matrix *biases)
{
	return add(multiply(weights, input), biases);
}

Matrix *train(Matrix *input, Matrix *weights, Matrix *biases, Matrix *expected, double learning_rate)
{
	Matrix *prediction = predict(input, weights, biases);
	Matrix *error = subtract(expected, prediction);
	Matrix *gradient = multiply(error, get_transpose(input));
	Matrix *delta = scalar_multiply(gradient, learning_rate);
	Matrix *new_weights = add(weights, delta);
	delete_matrices(4, prediction, error, gradient, delta);
	return new_weights;
}