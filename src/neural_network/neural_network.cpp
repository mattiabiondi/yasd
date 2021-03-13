#include "neural_network.h"
#include <math.h>
#include <iostream>
#include <stdio.h>

NeuralNetwork::NeuralNetwork()
{
}

NeuralNetwork::NeuralNetwork(int n_inputs, int n_hidden, int n_outputs)
{
	this->n_inputs = n_inputs;
	this->n_hidden = n_hidden;
	this->n_outputs = n_outputs;
}

void NeuralNetwork::initNNParams(double **inputs_to_hidden_weights, double **hidden_to_output_weights, double *inputs_to_hidden_bias, double *hidden_to_output_bias)
{
	this->inputs_to_hidden_weights = inputs_to_hidden_weights;
	this->hidden_to_output_weights = hidden_to_output_weights;
	this->inputs_to_hidden_bias = inputs_to_hidden_bias;
	this->hidden_to_output_bias = hidden_to_output_bias;
}


double *NeuralNetwork::feedForward(double *inputs)
{
	double *hi_middle_matrix = weightsTimesPreviousInputs(this->inputs_to_hidden_weights, inputs, 7, 5, this->inputs_to_hidden_bias);
	double *hi_end_matrix = activationFunction(hi_middle_matrix, 7);
	double *ho_middle_matrix = weightsTimesPreviousInputs(this->hidden_to_output_weights, hi_end_matrix, 2, 7, this->hidden_to_output_bias);
	double *ho_end_matrix = activationFunction(ho_middle_matrix, 2);

	return ho_end_matrix;
}


double **NeuralNetwork::getMatrixWithWeights(int n_rows, int n_colums, double *weights)
{
	double **weightsMatrix = new double *[n_rows];

	for (int i = 0; i < n_rows; i++) {
		weightsMatrix[i] = new double[n_colums];
		for (int j = 0; j < n_colums; j++) {
			int k = (n_colums * i) + j;
			weightsMatrix[i][j] = weights[k];
		}
	}

	return weightsMatrix;
}

double *NeuralNetwork::weightsTimesPreviousInputs(double **weights, double *previousInputs, int n_rows, int n_columns, double *bias)
{
	double *middleOutput = new double[n_rows];

	for (int i = 0; i < n_rows; i++) {
		double rowVal = 0;
		for (int j = 0; j < n_columns; j++)
			rowVal += weights[i][j] * previousInputs[j];
		middleOutput[i] = rowVal + bias[i];
	}
	return middleOutput;
}

//double *NeuralNetwork::addBias(double *multipliedMatrix, double *bias) {
//    return nullptr;
//}

double *NeuralNetwork::activationFunction(double *matrixWithBias, int n_rows)
{
	double *outputs = new double[n_rows];

	for (int i = 0; i < n_rows; i++) {
		// outputs[i] = 1 / ( 1 + exp(matrixWithBias[i] * (-1))); // exp(x) = e^x
		// if(!choose()) outputs[i] *= -1;
		double x = matrixWithBias[i];
		// outputs[i] = x / (sqrt(1 + pow(x,2)));
		outputs[i] = x / (1 + abs(x));
	}

	return outputs;
}
