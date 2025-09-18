#pragma once
#include <cstdlib> //rand()

class Agent {
public:
    Agent(int num_actions); //Constructor
    int choose_action(); //Return action to take
    void learn(double reward); //Learning

private:
    int num_actions; //number of possible actions
};