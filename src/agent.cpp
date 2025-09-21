#include "../include/agent.h"
#include <vector>
#include <ctime>
#include <algorithm>
#include <cstdlib> //rand()

Agent::Agent(int state_size, int hidden_size, int num_actions, double gamma, double epsilon, double lr)
    : state_size(state_size), num_actions(num_actions), gamma(gamma), epsilon(epsilon),
    net(state_size, hidden_size, num_actions, lr)
{
    std::srand(std::time(0)); //seed RNG
}

int Agent::choose_action(const std::vector<double>& state) {
    double r = (double) rand() / RAND_MAX;
    if (r < epsilon) {
        return rand() % num_actions; //random action
    } else {
        std::vector<double> q_values = net.forward(state);
        return std::distance(q_values.begin(), std::max_element(q_values.begin(), q_values.end()));
    }
}

int Agent::greedy_action(const std::vector<double>& state){
    std::vector<double> q_values = net.forward(state);
    return std::distance(q_values.begin(), std::max_element(q_values.begin(), q_values.end()));
}

void Agent::learn(const std::vector<double>& state, int action, double reward, const std::vector<double>& next_state, bool done) {
    //Predict current Q-values
    std::vector<double> q_values = net.forward(state);

    //Predict next state Q-values
    std::vector<double> next_q_values = net.forward(next_state);
    double max_next_q = *std::max_element(next_q_values.begin(), next_q_values.end());

    //Build target Q-values (copy of q_values, but update only chosen action)
    std::vector<double> target = q_values;
    if (done) {
        target[action] = reward; //terminal state
    } else {
        target[action] = reward + gamma * max_next_q;
    }

    net.backward(state, target);
}

void Agent::set_epsilon(double e){
    epsilon = e;
}

double Agent::get_epsilon(){
    return epsilon;
}

