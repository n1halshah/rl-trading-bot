#include <iostream>
#include "environment.h"
#include "agent.h"

int main() {
    Environment env;
    Agent agent(3); //0=Hold, 1=Buy, 2=Sell 
    env.reset();

    for (int i = 0; i < 10; i++){
        auto state = env.get_state();
        int action = agent.choose_action();
        double reward = env.step(action);
        agent.learn(reward); 
        std::cout << "Step " << i
                  << " | Price: " << state[0]
                  << " | Position: " << state[1]
                  << " | Action: " << action
                  << " | Reward: " << reward << std::endl;
    }

    return 0;
}