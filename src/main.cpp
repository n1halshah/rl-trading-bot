#include <iostream>
#include <vector>
#include "environment.h"
#include "agent.h"

//Discretize price + position into a Q-table index
int discretize_state(const std::vector<double>& state){
    double price = state[0];
    int position = static_cast<int>(state[1]);
    double last_change = state[2];

    int price_bucket;
    if (price < 95) price_bucket = 0;       //low
    else if (price < 105) price_bucket = 1; //mid
    else price_bucket = 2;                  //high

    int momentum_bucket;
    if (last_change < -0.2) momentum_bucket = 0; //falling
    else if (last_change < 0.2) momentum_bucket = 1; //flat
    else momentum_bucket = 2; //rising


    //Combine price bucket (3) and position (3: -1,0,1) * momentum (3) = 27 states
    int position_bucket = position + 1; //map -1,0,1 to 0,1,2
    return (price_bucket * 9) + (momentum_bucket * 3) + position_bucket;
}

int main() {
    Environment env;

    //3 price buckets * 2 positions = 6 total states
    int num_states = 27; 
    int num_actions = 3; //hold, buy, sell
    Agent agent(num_states, num_actions, 0.1, 0.9, 0.5);   

    int total_episodes = 1000;
    int steps_per_episode = 50;

    for (int episode = 0; episode < total_episodes; episode++) {
        env.reset();
        int state_idx = discretize_state(env.get_state());
        double total_reward = 0.0;

        for (int i = 0; i < 50; i++){
            int action = agent.choose_action(state_idx);
            double reward = env.step(action);
            int next_state_idx = discretize_state(env.get_state());

            agent.learn(state_idx, action, reward, next_state_idx); 

            state_idx = next_state_idx; 
            total_reward += reward;
        }

        agent.set_epsilon(std::max(0.05, agent.get_epsilon() * 0.99));

        if (episode % 10 == 0) {
            std::cout << "Episode " << episode
                      << " | Total Reward: " << total_reward
                      << " | Epsilon: " << agent.get_epsilon()
                      << std::endl;
        }        
    }       

    std::cout << "\n Evaluation Run \n";
    env.reset();
    int state_idx = discretize_state(env.get_state());
    double total_eval_reward = 0.0;

    for (int i = 0; i< 50; i++){
        //greedy action (no exploration)
        int action = agent.greedy_action(state_idx);

        double reward = env.step(action);
        int next_state_idx = discretize_state(env.get_state());

        state_idx = next_state_idx;
        total_eval_reward += reward;

        std::cout << "Step " << i
              << " | Action: " << action
              << " | Reward: " << reward
              << " | Price: " << env.get_state()[0]
              << " | Position: " << env.get_state()[1]
              << std::endl;
    }

    std::cout << "Total Evaluation Reward: " << total_eval_reward << std::endl;

    return 0;
}