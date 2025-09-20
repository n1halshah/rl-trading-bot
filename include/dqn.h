#pragma once
#include <vector>
#include <cmath>
#include <random>

class DQN {
    public:
        DQN(int input_size, int hidden_size, int output_size, double lr);

        std::vector<double> forward(const std::vector<double>& input);
        void backward(const std::vector<double>& input,
                      const std::vector<double>& target);
    
    private:
        int input_size, hidden_size, output_size;
        double lr; //learning rate  

        std::vector<std::vector<double>> W1, W2; //weights
        std::vector<double> b1, b2;              //biases

        std::vector<double> hidden_output;

        double relu(double x);
        double relu_derivative(double x);               
};