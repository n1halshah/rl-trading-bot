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
        std::vector<double> state = normalize_state(env.get_state());
        double total_reward = 0.0;

        for (int step = 0; step < steps_per_episode; step++) {
            //Pick action
            int action = agent.choose_action(state);

            //Apply action            
            double reward = env.step(action);
            std::vector<double> next_state = normalize_state(env.get_state());

            //Learn with neural network
            bool done = env.is_done();
            agent.learn(state, action, reward, next_state, done);

            //Move on
            state = next_state;
            total_reward += reward;

            if (done) break;
            
        }

        // Decay epsilon
        agent.set_epsilon(std::max(0.05, agent.get_epsilon() * 0.995));

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
