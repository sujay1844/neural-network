#include <stdio.h>

#include "matrix.h"
#include "model.h"

int main()
{
	// Create a random neural network with 2 inputs, 3 hidden neurons, and 1 output
	Matrix *input = zeros(2, 1);
	Matrix *training_x = zeros(2, 4);
	training_x->data[0][1] = 1;
	training_x->data[0][2] = 1;
	training_x->data[0][3] = 0;
	training_x->data[1][0] = 1;
	training_x->data[1][1] = 0;
	training_x->data[1][2] = 1;
	training_x->data[1][3] = 1;
	Matrix *training_y = zeros(1, 4);
	training_y->data[0][1] = 1;
	training_y->data[0][2] = 0;
	training_y->data[0][3] = 1;

	Matrix *hidden_weights = get_random_matrix(3, 2);
	Matrix *hidden_biases = get_random_matrix(3, 1);
	Matrix *output_weights = get_random_matrix(1, 3);
	Matrix *output_biases = get_random_matrix(1, 1);
	// Train the neural network to predict the XOR function
	for (int i = 0; i < 100000; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			input->data[0][0] = training_x->data[0][j];
			input->data[1][0] = training_x->data[1][j];
			Matrix *expected = zeros(1, 1);
			expected->data[0][0] = training_y->data[0][j];
			hidden_weights = train(input, hidden_weights, hidden_biases, expected);
			output_weights = train(input, output_weights, output_biases, expected);
			delete_matrix(expected);
		}
	}

	// Print the neural network's prediction for (0, 0)
	printf("0, 0\n");
	print_matrix(predict(input, hidden_weights, hidden_biases));
	// Print the neural network's prediction for (0, 1)
	input->data[1][0] = 1;
	printf("0, 1\n");
	print_matrix(predict(input, hidden_weights, hidden_biases));
	// Print the neural network's prediction for (1, 0)
	input->data[0][0] = 1;
	input->data[1][0] = 0;
	printf("1, 0\n");
	print_matrix(predict(input, hidden_weights, hidden_biases));
	// Print the neural network's prediction for (1, 1)
	input->data[1][0] = 1;
	printf("1, 1\n");
	print_matrix(predict(input, hidden_weights, hidden_biases));
	// Free the memory
	delete_matrices(5, input, hidden_weights, hidden_biases, output_weights, output_biases);

	return 0;
}