#include "../include/ValueIteration.h"
#include <vector>
#include <map>
#include <iostream>
#include <algorithm>
namespace CHNJAR003
{

    ValueIteration::ValueIteration(const int numStates, const std::map<int, std::vector<int>> &actions, const std::map<int, std::map<int, float>> &rewards, const float gamma) : numStates(numStates), Actions(actions), V(std::vector<float>(numStates, 0)), Rewards(rewards), gamma(gamma)
    {
    }

    const float ValueIteration::Q(const int state, const int action)
    {
        auto it = Rewards.find(state);
        if (it != Rewards.end())
        {
            return Rewards[state][action] + gamma * V[action - 1]; //Reward for transition + discount*Value function of s'(deterministic)
        }
        else
        {
            return 0 + gamma * V[action - 1]; //Reward for transition + discount*Value function of s'(deterministic)
        }
    }

    void ValueIteration::performValueIteration(void)
    {

        int iterationCount = 0;

        while (true)
        {
            ++iterationCount;

            std::vector<float> Vnew(numStates, 0);

            for (int s = 1; s <= numStates; ++s)
            {
                //If not in an end state
                if (Actions[s].size() != 0)
                {
                    float currentMaxQ = Q(s, Actions[s][0]);

                    if (Actions[s].size() > 1)
                    {
                        for (int a = 1; a < Actions[s].size(); ++a)
                        {
                            float nextQ = Q(s, Actions[s][a]);

                            if (nextQ > currentMaxQ)
                            {
                                currentMaxQ = nextQ;
                            }
                        }
                    }

                    Vnew[s - 1] = currentMaxQ;
                }
            }

            //Check whether the values have converged
            if (converged(Vnew))
            {
                V = Vnew; //Synchronous update of V(s)

                numIterations = iterationCount;
                performPolicyExtraction();
                break;
            }

            V = Vnew; //Synchronous update of V(s)
        }
    }

    void ValueIteration::performPolicyExtraction(void)
    {
        //Iterate though the states in the environment
        for (int s = 1; s <= numStates; ++s)
        {
            //If there are possible actions in the current state -> determine the optimal action to take based off of the state values
            if (Actions[s].size() != 0)
            {
                int aOpt = Actions[s][0];
                float currentMaxQ = Q(s, Actions[s][0]);

                for (int a = 1; a < Actions[s].size(); ++a)
                {
                    float nextQ = Q(s, Actions[s][a]);

                    if (nextQ > currentMaxQ)
                    {
                        aOpt = Actions[s][a];
                        currentMaxQ = nextQ;
                    }
                }

                Policy[s] = aOpt;
            }
        }

        /*for (auto p : Policy)
        {
            std::cout << p.first << " : " << p.second << "\n";
        }*/
    }

    bool ValueIteration::converged(const std::vector<float> &newV) const
    {
        float epsilon = 0.00001;

        std::vector<float> result(numStates, 0);
        std::transform(newV.begin(), newV.end(), V.begin(), result.begin(), std::minus<float>());

        bool conv = true;
        for (float f : result)
        {
            if (f > epsilon)
            {
                conv = false;
            }
        }

        return conv;
    }

    std::string ValueIteration::policyRouteFromState(const int startState) const
    {
        int currentState = startState;
        std::string optimalRoute = "S" + std::to_string(currentState);

        while (Actions.at(currentState).size() != 0)
        {
            int optAction = Policy.at(currentState);
            optimalRoute += " -> S" + std::to_string(optAction);
            currentState = optAction;
        }

        return optimalRoute;
    }

    std::string ValueIteration::formatGrid(const int t) const
    {
        std::string formattedGrid;

        formattedGrid += "______GRID WORLD______ t=" + std::to_string(t) + "\n";
        formattedGrid += "\t|0|\t|1|\t|2|\n";
        formattedGrid += "|1|\t";
        for (int i = 0; i < 3; ++i)
        {
            formattedGrid += std::to_string(V[i]) + "\t";
        }
        formattedGrid += "\n";
        formattedGrid += "|0|\t";
        for (int i = 3; i < 6; ++i)
        {
            formattedGrid += std::to_string(V[i]) + "\t";
        }
        formattedGrid += "\n----------------------\n\n";

        return formattedGrid;
    }

    std::ostream &operator<<(std::ostream &os, const ValueIteration &vi)
    {
        os << "Question 1:  How many iterations does it take for the Value Iteration algorithm to converge?\nIn an output text file list the optimal values (V for each state).\n";
        os << "\nThe algorithm takes: " << vi.numIterations << " iterations to converge.\n\n";
        os << "The optimal values of each state are represented in grid form as well as listed below:\n";
        os << vi.formatGrid(vi.numIterations) << std::endl;

        for (int i = 0; i < vi.V.size(); ++i)
        {
            os << "V*(" << i + 1 << ") = " << vi.V[i] << std::endl;
        }

        os << "\nQuestion 2: Assume we start in state s1, give the states that form the optimal policy to reach the terminal state (s3).\n\n";
        os << vi.policyRouteFromState(1) << std::endl;

        os << "\nQuestion 3: Is it possible to change the reward function function so that V changes, but the optimal policy remains unchanged?\n\n";
        os << "It is possible to modify the reward function so that the optimal values of each state change, such that the optimal policy remains the same.\n";
        os << "The reward function can be changed such that the rewards given to the agent are a scaled by a constant factor. For example, the rewards can be multiplied by 3.\n";
        os << "The V* values will change (increase), however the optimal policy will remain the same.\n";
        return os;
    }

} // namespace CHNJAR003