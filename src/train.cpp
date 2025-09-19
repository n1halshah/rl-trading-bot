#include <iostream>
#include <fstream>
#include <vector>
#include "../include/environment.h"
#include "../include/agent.h"
#include "../include/utils.h" 

void train(Agent& agent, Environment& env, int total_episodes, int steps_per_episode) {
    std::ofstream training_log("./data/training_log.csv");
    training_log << "Episode,TotalReward,Epsilon\n";

    for (int episode = 0; episode < total_episodes; episode++) {
        env.reset();
        int state_idx = discretize_state(env.get_state());
        double total_reward = 0.0;

        for (int step = 0; step < steps_per_episode; step++) {
            int action = agent.choose_action(state_idx);

            double last_change = env.get_state()[2];
            int position = static_cast<int>(env.get_state()[1]);

            double reward = env.step(action);

            //Reward shaping
            if ((position > 0 && last_change > 0) || (position < 0 && last_change < 0))
                reward += 0.1;
            else if ((position > 0 && last_change < 0) || (position < 0 && last_change > 0))
                reward -= 0.05;

            int next_state_idx = discretize_state(env.get_state());
            agent.learn(state_idx, action, reward, next_state_idx);

            state_idx = next_state_idx;
            total_reward += reward;
        }

        // Adaptive epsilon decay 
        if (episode % 10 == 0) {
            if (total_reward < 0.5)
                agent.set_epsilon(std::min(1.0, agent.get_epsilon() * 1.05));
            else
                agent.set_epsilon(std::max(0.05, agent.get_epsilon() * 0.99));
        }

        //Logging
        training_log << episode << "," << total_reward << "," << agent.get_epsilon() << "\n";

        if (episode % 10 == 0) {
            std::cout << "Episode " << episode
                      << " | Total Reward: " << total_reward
                      << " | Epsilon: " << agent.get_epsilon()
                      << std::endl;
        }
    }

    training_log.close();
}
