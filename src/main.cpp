#include "../include/environment.h"
#include "../include/agent.h"
#include "../include/utils.h" 

//Declare training & evaluation functions
void train(Agent& agent, Environment& env, int total_episodes, int steps_per_episode);
void evaluate(Agent& agent, Environment& env, int steps);

int main() {
    Environment env("./data/AAPL.csv");
    int state_size = 3;       // price, position, momentum
    int hidden_size = 64;
    int num_actions = 3;
    double gamma = 0.95;
    double epsilon = 1.0;
    double lr = 0.0005;

    Agent agent(state_size, hidden_size, num_actions, gamma, epsilon, lr);

    //Train
    train(agent, env, 2000, 200);
    
    //Evaluate
    evaluate(agent, env, 100);

    return 0;
}
