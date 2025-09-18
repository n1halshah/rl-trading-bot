#include "environment.h"
#include <cstdlib> //rand()
#include <ctime> //time()

Environment::Environment() {
    std::srand(std::time(0)); //seed random number generator
    reset();
}

void Environment::reset(){
    price = 100.0; //starting price
    position = 0; //neutral
}

std::vector<double> Environment::get_state() {
    return {price, static_cast<double>(position)};
}

double Environment::step(int action) {
    double change = ((std::rand() % 2001) - 1000) / 1000.0;
    price += change;

    //Update position based on action
    if (action == 0) position = 0; //Hold
    else if (action == 1) position = 1; //Buy
    else if (action == 2) position = 0; //Sell

    //Reward = profit/loss
    double reward = position * change;
    return reward;
}