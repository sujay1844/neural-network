#ifndef MODEL_H
#define MODEL_H

#include "matrix.h"

Matrix *predict(Matrix *input, Matrix *weights, Matrix *biases);
Matrix *train(Matrix *input, Matrix *weights, Matrix *biases, Matrix *expected, double learning_rate);

#endif // MODEL_H