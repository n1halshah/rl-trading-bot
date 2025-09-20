#pragma once
#include <vector>
#include <string>

class Environment {
    public:
        Environment(const std::string& filename);
        void reset();   //Reset price and position        
        std::vector<double> get_state();    //Reset current state
        double step(int action); //Take action and return reward
        bool is_done() const;

    private:
        std::vector<double> prices; // historical stock prices
        double last_price;          // price at previous step
        int position;               // -1 = short, 0 = flat, 1 = long
        int current_step;           // current index in prices
};