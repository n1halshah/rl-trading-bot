#include <iostream>
#include <fstream>
#include <vector>
#include "../include/environment.h"
#include "../include/agent.h"
#include "../include/utils.h" 

void evaluate(Agent& agent, Environment& env, int steps) {
    std::ofstream log_file("./data/evaluation_log.csv");
    log_file << "Step,Action,Price,Position,Momentum,Reward,CumulativeReward\n";

    std::cout << "\n=== Evaluation Run ===\n";
    env.reset();
    int state_idx = discretize_state(env.get_state());
    double total_eval_reward = 0.0;

    for (int i = 0; i < steps; i++) {
        int action = agent.greedy_action(state_idx);
        double reward = env.step(action);
        int next_state_idx = discretize_state(env.get_state());

        state_idx = next_state_idx;
        total_eval_reward += reward;

        std::string act_label = action_label(action);

        std::cout << "Step " << i
                  << " | Action: " << act_label
                  << " | Reward: " << reward
                  << " | Price: " << env.get_state()[0]
                  << " | Position: " << env.get_state()[1]
                  << " | Momentum: " << env.get_state()[2]
                  << std::endl;

        log_file << i << "," << act_label << ","
                 << env.get_state()[0] << ","
                 << env.get_state()[1] << ","
                 << env.get_state()[2] << ","
                 << reward << ","
                 << total_eval_reward << "\n";
    }

    log_file.close();
    std::cout << "Total Evaluation Reward: " << total_eval_reward << std::endl;
}
