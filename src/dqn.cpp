#include "../include/dqn.h"
#include <iostream>
#include <cstdlib>
#include <ctime>


DQN::DQN(int input_size, int hidden_size, int output_size, double lr)
    : input_size(input_size), hidden_size(hidden_size), output_size(output_size), lr(lr){

    std::srand(std::time(nullptr)); 

    //Intialise weights randomly 
    W1.resize(hidden_size, std::vector<double>(input_size));
    W2.resize(output_size, std::vector<double>(hidden_size));
    b1.resize(hidden_size);
    b2.resize(output_size);

    for (int i = 0; i < hidden_size; ++i){
        b1[i] = 0.0;
        for (int j = 0; j < input_size; ++j){
            W1[i][j] == ((double) std::rand() / RAND_MAX - 0.5) * 2.0;
        }   
    }

    for (int i = 0; i < output_size; ++i) {
        b2[i] = 0.0;
        for (int j = 0; j < hidden_size; ++j)
            W2[i][j] = ((double) std::rand() / RAND_MAX - 0.5) * 2.0; 
    }
}

//ReLU activation
double DQN::relu(double x){
    return x > 0 ? x : 0;
}

//ReLU derivative
double DQN::relu_derivative(double x){
    return x > 0 ? 1 : 0;
}

//Forward Pass
std::vector<double> DQN::forward(const std::vector<double>& input){
    hidden_output.resize(hidden_size);

    //Input -> Hidden
    for (int i = 0; i < hidden_size; ++i) {
        double sum = b1[i];
        for (int j = 0; j < input_size; ++j) {
            sum += W1[i][j] * input[j];
        }
        hidden_output[i] = relu(sum);
    }

    //Hidden -> Output
    std::vector<double> output(output_size);
    for (int i = 0; i < output_size; ++i) {
        double sum = b2[i];
        for (int j = 0; j < hidden_size; ++j) {
            sum += W2[i][j] * input[j];
        }
        output[i] = sum;
    }

    return output;
}