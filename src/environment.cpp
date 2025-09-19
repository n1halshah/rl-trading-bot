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
    last_change = 0.0; //flat

    drift = (std::rand() % 2 == 0) ? 0.2 : -0.2; //50-50 chance of bullish/bearish market
}

std::vector<double> Environment::get_state() {
    return {price, static_cast<double>(position), last_change};
}

double Environment::step(int action) {
    //random noise
    double change = ((std::rand() % 2001) - 1000) / 5000.0;
    //add bias / drift
    change += drift;

    price += change;
    last_change = change;

    //Update position based on action
    if (action == 0) position = 0; //Hold
    else if (action == 1) position = 1; //Buy
    else if (action == 2) position = -1; //Sell

    //Reward = profit/loss
    double reward = position * change;
    return reward;
}