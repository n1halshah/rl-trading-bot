#include <iostream>
#include "environment.h"

int main() {
    Environment env; 
    env.reset();

    for (int i = 0; i < 10; i++){
        auto state = env.get_state();
        double reward = env.step(1); //always Buy for now
        std::cout << "Step" << i
                  << " | Price: " << state[0]
                  << " | Position: " << state[1]
                  << " | Reward: " << reward << std::endl;
    }

    return 0;
}