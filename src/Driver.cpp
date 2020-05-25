#include "../include/ValueIteration.h"
#include <vector>
#include <map>
#include <iostream>

int main(int argc, char *argv[])
{
    std::map<int, std::vector<int>> Actions;
    //Valid deterministic actions that agent can execute within each state
    Actions[1] = {2, 4};
    Actions[2] = {1, 5, 3};
    Actions[3] = {}; //State 3 is the terminal state - no actions can be executed in this state
    Actions[4] = {1, 5};
    Actions[5] = {4, 2, 6};
    Actions[6] = {5, 3};

    std::map<int, std::map<int, float>> Rewards;
    //All the other state transitions are zero
    Rewards[2] = {{3, 50}};
    Rewards[6] = {{3, 100}};

    float gamma = 0.8; //discount factor

    CHNJAR003::ValueIteration algo(6, Actions, Rewards, gamma);
    std::cout << algo.Q(6, 3) << std::endl;
}