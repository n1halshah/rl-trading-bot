#include "../include/environment.h"
#include "../include/agent.h"
#include "../include/utils.h" 

//Declare training & evaluation functions
void train(Agent& agent, Environment& env, int total_episodes, int steps_per_episode);
void evaluate(Agent& agent, Environment& env, int steps);

int main() {
    Environment env("./data/AAPL.csv");
    int num_states = 27;
    int num_actions = 3;

    Agent agent(num_states, num_actions, 0.1, 0.9, 0.5);

    //Train
    train(agent, env, 1000, 50);

    //Evaluate
    evaluate(agent, env, 50);

    return 0;
}
