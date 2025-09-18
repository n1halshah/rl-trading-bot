#pragma once
#include <vector>

class Environment {
    public:
        Environment();
        void reset();   //Reset price and position        
        std::vector<double> get_state();    //Reset current state
        double step(int action); //Take action and return reward

    private:
        double price; //Current price
        int position; // +1=long, 0=neutral, -1=short
};