#pragma once
#include <vector>
#include <cstdlib> //rand()
#include <ctime> //time()

class Agent {
public:
    Agent(int num_states, int num_actions, double alpha, double gamma, double epsilon); 
    //alpha - learning rate, gamma - discount factor, epsilon - exploration rate
    int choose_action(int state); //Return action to take
    void learn(int state, int action, double reward, int next_state); //Learning
    void set_epsilon(double e);
    double get_epsilon();

private:
    int num_states;
    int num_actions; 
    double alpha;
    double gamma;
    double epsilon;

    std::vector<std::vector<double>> Q; // Q[state][action]
};