#include "agent.h"
#include <cstdlib> //rand()

Agent::Agent(int num_actions){
    this->num_actions = num_actions;
}

int Agent::choose_action() {
    return rand() % num_actions; //returns 0, 1, or 2 randomly
}

void Agent::learn(double reward) {
    //Do nothing, for now.
}