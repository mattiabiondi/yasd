#include "src/utils.h"

class NeuralNetwork {

private:
    int n_inputs;
    int n_outputs;
    int n_hidden; //we assume we have only one hidden layer

    float **inputs_to_hidden_weights;
    float **hidden_to_output_weights;

    float *inputs_to_hidden_bias;
    float *hidden_to_output_bias;

public:
    NeuralNetwork();
    NeuralNetwork(int n_inputs, int n_hidden, int n_outputs);
    void initNNParams(float **inputs_to_hidden_weights, float **hidden_to_output_weights, float *inputs_to_hidden_bias,  float *hidden_to_output_bias);
    float *feedForward(float *inputs, float *genes);
    float **getMatrixWithWeights(int n_rows, int n_colums, float *weights); // weights will be DNA later
    float *weightsTimesPreviousInputs(float **weights, float *previousInputs, int n_rows, int n_columns,  float *bias);
    float *activationFunction(float *matrixWithBias, int n_rows);
//    float *addBias(float *multipliedMatrix, float *bias);

};


