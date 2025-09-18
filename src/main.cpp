#include <iostream>
#include <vector>
#include "environment.h"
#include "agent.h"

//Discretize price + position into a Q-table index
int discretize_state(const std::vector<double>& state){
    double price = state[0];
    int position = static_cast<int>(state[1]);

    int price_bucket;
    if (price < 95) price_bucket = 0;       //low
    else if (price < 105) price_bucket = 1; //mid
    else price_bucket = 2;                  //high

    //Combine price bucket (0-2) and position (0-1) into a unique index
    return price_bucket * 2 + position;
}

int main() {
    Environment env;

    //3 price buckets * 2 positions = 6 total states
    int num_states = 6; 
    int num_actions = 3; //hold, buy, sell
    Agent agent(num_states, num_actions, 0.1, 0.9, 0.2);   

    for (int episode = 0; episode < 100; episode++) {
        env.reset();
        int state_idx = discretize_state(env.get_state());

        for (int i = 0; i < 50; i++){
            int action = agent.choose_action(state_idx);
            double reward = env.step(action);
            int next_state_idx = discretize_state(env.get_state());

            agent.learn(state_idx, action, reward, next_state_idx); 

            std::cout << "Step " << i
                    << " | State: " << state_idx
                    << " | Action: " << action
                    << " | Reward: " << reward
                    << " | Next State> " << next_state_idx << std::endl;
            
            state_idx = next_state_idx; //move forward
        }
        std::cout << "Episode " << episode << " finished." << std::endl;
    }

    return 0;
}