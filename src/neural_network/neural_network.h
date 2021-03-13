#include "src/utils.h"

class NeuralNetwork {
private:
int n_inputs;
int n_outputs;
int n_hidden;     //we assume we have only one hidden layer

double **inputs_to_hidden_weights;
double **hidden_to_output_weights;

double *inputs_to_hidden_bias;
double *hidden_to_output_bias;

public:
NeuralNetwork();
NeuralNetwork(int n_inputs, int n_hidden, int n_outputs);
void initNNParams(double **inputs_to_hidden_weights, double **hidden_to_output_weights, double *inputs_to_hidden_bias, double *hidden_to_output_bias);
double *feedForward(double *inputs);
double **getMatrixWithWeights(int n_rows, int n_colums, double *weights);     // weights will be DNA later
double *weightsTimesPreviousInputs(double **weights, double *previousInputs, int n_rows, int n_columns, double *bias);
double *activationFunction(double *matrixWithBias, int n_rows);
//    double *addBias(double *multipliedMatrix, double *bias);
};
