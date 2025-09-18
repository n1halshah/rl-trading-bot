#include "agent.h"
#include <vector>
#include <ctime>
#include <algorithm>
#include <cstdlib> //rand()

Agent::Agent(int num_states, int num_actions, double alpha, double gamma, double epsilon)
    : num_states(num_states), num_actions(num_actions), alpha(alpha), gamma(gamma), epsilon(epsilon)
{
    Q = std::vector<std::vector<double>>(num_states, std::vector<double>(num_actions, 0.0));
    std::srand(std::time(0)); //seed RNG
}

int Agent::choose_action(int state) {
    double r = (double) rand() / RAND_MAX;
    if (r < epsilon) {
        return rand() % num_actions; //random action
    } else {
        auto &row = Q[state];
        return std::distance(row.begin(), std::max_element(row.begin(), row.end()));
    }
}

void Agent::learn(int state, int action, double reward, int next_state) {
    double max_next_Q = *std::max_element(Q[next_state].begin(), Q[next_state].end());

    Q[state][action] = Q[state][action] + alpha * (reward + gamma * max_next_Q - Q[state][action]);
    
}