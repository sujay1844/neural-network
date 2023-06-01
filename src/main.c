#include <stdio.h>

#include "matrix.h"
#include "model.h"

int main()
{
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
	Matrix *weights = ones(2, 2);
	Matrix *biases = zeros(2, 1);
	Matrix *expected = zeros(2, 1);
	// Train the neural network to predict the XOR function
	for (int i = 0; i <= 100; i++)
	{
		// printf("Epoch %d\n", i);
		for (int j = 0; j <= 4; j++)
		{
			input->data[0][0] = X->data[0][j];
			input->data[1][0] = X->data[1][j];
			expected->data[0][0] = y->data[0][j]? 1: 0;
			expected->data[1][0] = y->data[0][j]? 0: 1;
			// printf("Input\n");
			// print_matrix(input);
			// printf("Expected\n");
			// print_matrix(expected);
			weights = train(input, weights, biases, expected);
		}
	}
	delete_matrix(expected);

	// Print the neural network's prediction for (0, 0)
	input->data[0][0] = 0;
	input->data[1][0] = 0;
	printf("0, 0\n");
	print_matrix(predict(input, weights, biases));
	// Print the neural network's prediction for (0, 1)
	input->data[0][0] = 0;
	input->data[1][0] = 1;
	printf("0, 1\n");
	print_matrix(predict(input, weights, biases));
	// Print the neural network's prediction for (1, 0)
	input->data[0][0] = 1;
	input->data[1][0] = 0;
	printf("1, 0\n");
	print_matrix(predict(input, weights, biases));
	// Print the neural network's prediction for (1, 1)
	input->data[0][0] = 1;
	input->data[1][0] = 1;
	printf("1, 1\n");
	print_matrix(predict(input, weights, biases));
	
	printf("Weights\n");
	print_matrix(weights);
	printf("Biases\n");
	print_matrix(biases);
	// Free the memory
	// delete_matrices(5, input, weights, biases);

	return 0;
}