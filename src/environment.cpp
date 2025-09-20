#include "../include/environment.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>

Environment::Environment(const std::string& filename){
    std::ifstream file(filename);
    if (!file.is_open()){
        throw std::runtime_error("Could not open CSV file: " + filename);
    }

    std::string line;
    bool first_line = true; 

    while (std::getline(file, line)) {
        if (first_line) { first_line = false; continue; } // skip header

        std::stringstream ss(line);
        std::string cell;
        int col_idx = 0;
        double close_price = 0.0;

        while (std::getline(ss, cell, ',')) {
            if (col_idx == 1) { // Close column
                try { close_price = std::stod(cell); }
                catch (...) { close_price = 0.0; }
                break;
            }
            col_idx++;
        }
        if (close_price > 0) prices.push_back(close_price);
    }

    if (prices.empty()) {
        throw std::runtime_error("No valid Close price data found in file: " + filename);
    }

    reset();
}

void Environment::reset(){
    current_step = 1; //starts from 1 so last_price exists
    last_price = prices[0];
    position = 0;
}

std::vector<double> Environment::get_state() {
    double price = prices[current_step];
    double last_change = price - last_price;
    return {price, static_cast<double>(position), last_change};
}

double Environment::step(int action) {
    if (is_done()) return 0.0;

    double price = prices[current_step];
    double reward = 0.0;
    bool position_change = false;

    if (action == 1 && position != 1) { position = 1; position_change = true; }        // BUY
    else if (action == 2 && position != -1) { position = -1; position_change = true; } // SELL
    else if (action == 0 && position != 0) { position = 0; position_change = true; }   // HOLD

    if (position == 1) reward = price - last_price;
    else if (position == -1) reward = last_price - price;
    else reward = 0.0;

    // Apply transaction cost if position changed
    double transaction_cost = 0.001 * price;
    if (position_change) reward -= transaction_cost;

    last_price = price;
    current_step++;

    return reward;
}


bool Environment::is_done() const{
    return current_step >= (int)prices.size();
}

