#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"
#include "model.h"

int main()
{
	double learning_rate = 0.01;
	int epochs = 1000;
	// Create a random neural network with 2 inputs, 3 hidden neurons, and 1 output
	Matrix *X = zeros(2, 4);
	X->data[0][0] = 0;
	X->data[1][0] = 0;
	X->data[0][1] = 0;
	X->data[1][1] = 1;
	X->data[0][2] = 1;
	X->data[1][2] = 0;
	X->data[0][3] = 1;
	X->data[1][3] = 1;
	Matrix *y = zeros(1, 4);
	y->data[0][0] = 0;
	y->data[0][1] = 1;
	y->data[0][2] = 1;
	y->data[0][3] = 0;

	Matrix *input = zeros(2, 1);
	Matrix *weights = zeros(2, 2);
	Matrix *biases = zeros(2, 1);
	Matrix *expected = zeros(2, 1);
	// Train the neural network to predict the XOR function
	for (int i = 0; i <= epochs; i++)
	{
		// printf("Epoch %d\n", i);
		for (int j = 0; j <= 4; j++)
		{
			input->data[0][0] = X->data[0][j];
			input->data[1][0] = X->data[1][j];
			expected->data[0][0] = y->data[0][j]? 1: 0;
			expected->data[1][0] = y->data[0][j]? 0: 1;
			weights = train(input, weights, biases, expected, learning_rate);
		}
	}
	delete_matrix(expected);

	// Print the neural network's prediction for (0, 0)
	input->data[0][0] = 0;
	input->data[1][0] = 0;
	printf("%f, %f = %f\n", input->data[0][0], input->data[1][0], predict(input, weights, biases)->data[0][0]);
	// Print the neural network's prediction for (0, 1)
	input->data[0][0] = 0;
	input->data[1][0] = 1;
	printf("%f, %f = %f\n", input->data[0][0], input->data[1][0], predict(input, weights, biases)->data[0][0]);
	// Print the neural network's prediction for (1, 0)
	input->data[0][0] = 1;
	input->data[1][0] = 0;
	printf("%f, %f = %f\n", input->data[0][0], input->data[1][0], predict(input, weights, biases)->data[0][0]);
	// Print the neural network's prediction for (1, 1)
	input->data[0][0] = 1;
	input->data[1][0] = 1;
	printf("%f, %f = %f\n", input->data[0][0], input->data[1][0], predict(input, weights, biases)->data[0][0]);
	
	print_matrix(weights, "weights");
	print_matrix(biases, "biases");
	// Free the memory
	// delete_matrices(5, input, weights, biases);

	return 0;
}