#pragma once
#include <vector>
#include <cstdlib> //rand()
#include <ctime> //time()
#include <algorithm>
#include "../include/dqn.h"

class Agent {
public:
    Agent(int state_size, int hidden_size, int num_actions, double gamma, double epsilon, double lr); 
    //alpha - learning rate, gamma - discount factor, epsilon - exploration rate
    int choose_action(const std::vector<double>& state); //ε-greedy
    int greedy_action(const std::vector<double>& state); //greedy
    void learn(const std::vector<double>& state, int action, double reward, const std::vector<double>& next_state, bool done); //Learning
    void set_epsilon(double e);
    double get_epsilon();
    DQN net;

private:
    int state_size;
    int num_actions; 
    double alpha;
    double gamma;
    double epsilon;    
};