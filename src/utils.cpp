#include "../include/utils.h"
#include <vector>
#include <string>
#include <cstdlib>

// Discretize price + position + momentum into a Q-table index
int discretize_state(const std::vector<double>& state) {
    double price = state[0];
    int position = static_cast<int>(state[1]);
    double last_change = state[2];

    int price_bucket;
    if (price < 95) price_bucket = 0;       // low
    else if (price < 105) price_bucket = 1; // mid
    else price_bucket = 2;                  // high

    int momentum_bucket;
    if (last_change < -0.2) momentum_bucket = 0;    // falling
    else if (last_change < 0.2) momentum_bucket = 1; // flat
    else momentum_bucket = 2;                       // rising

    // Combine price (3) × momentum (3) × position (3) = 27 states
    int position_bucket = position + 1; // map -1,0,1 to 0,1,2

    return (price_bucket * 9) + (momentum_bucket * 3) + position_bucket;
}

std::string action_label(int action) {
    if (action == 0) return "HOLD";
    else if (action == 1) return "BUY";
    else if (action == 2) return "SELL";
    else return "UNKNOWN";
}
