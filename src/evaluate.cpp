#include <iostream>
#include <fstream>
#include <vector>
#include "../include/environment.h"
#include "../include/agent.h"
#include "../include/utils.h" 

void evaluate(Agent& agent, Environment& env, int steps) {
    std::ofstream log_file("./data/evaluation_log.csv");
    log_file << "Step,Action,Price,Position,Momentum,Reward,CumulativeReward,Q_HOLD,Q_BUY,Q_SELL\n";

    std::cout << "\n=== Evaluation Run ===\n";
    env.reset();
    std::vector<double> state = normalize_state(env.get_state());
    double total_eval_reward = 0.0;

    for (int i = 0; i < steps; i++) {
        // Get Q-values for debugging
        std::vector<double> q_values = agent.net.forward(state);
        std::cout << "Step " << i << " | Q-values: ";
        for (auto q : q_values) std::cout << q << " ";
        std::cout << std::endl;

        // Pick greedy action
        int action = agent.greedy_action(state);

        // Apply action
        double reward = env.step(action);
        std::vector<double> next_state = normalize_state(env.get_state());

        total_eval_reward += reward;

        std::string act_label = action_label(action);

        std::cout << "Step " << i
                  << " | Action: " << act_label
                  << " | Reward: " << reward
                  << " | Price: " << next_state[0]*200.0
                  << " | Position: " << next_state[1]
                  << " | Momentum: " << next_state[2]*10.0
                  << std::endl;

        // CSV log including Q-values
        log_file << i << "," << act_label << "," 
                 << next_state[0]*200.0 << "," 
                 << next_state[1] << "," 
                 << next_state[2]*10.0 << "," 
                 << reward << "," 
                 << total_eval_reward << ","
                 << q_values[0] << "," << q_values[1] << "," << q_values[2] << "\n";

        // Move to next state
        state = next_state;

        if (env.is_done()) break;
    }

    log_file.close();
    std::cout << "Total Evaluation Reward: " << total_eval_reward << std::endl;
}
