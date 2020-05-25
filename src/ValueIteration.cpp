#include "../include/ValueIteration.h"
#include <vector>
#include <map>
#include <iostream>
#include <algorithm>
namespace CHNJAR003
{

    ValueIteration::ValueIteration(int numStates, const std::map<int, std::vector<int>> &actions, const std::map<int, std::map<int, float>> &rewards, float gamma) : numStates(numStates), Actions(actions), V(std::vector<float>(numStates, 0)), Rewards(rewards), gamma(gamma)
    {
    }

    const float ValueIteration::Q(int state, int action)
    {
        return Rewards[state][action] + gamma * V[action - 1]; //Reward for transition + discount*Value function of s'(deterministic)
    }

    void ValueIteration::performValueIteration(void)
    {

        int iterationCount = 0;
        printGrid(iterationCount);

        while (true)
        {
            ++iterationCount;

            std::vector<float> Vnew(numStates, 0);

            for (int s = 1; s <= numStates; ++s)
            {
                //std::cout << "STATE: " << s << std::endl;
                //Print out the actions for each state - testing purposes
                /*std::cout << "Actions for " << s << " are: ";
                    std::for_each(Actions[s].begin(), Actions[s].end(), [](int a) { std::cout << a << " "; });
                    std::cout << std::endl;*/

                //If not in an end state
                if (Actions[s].size() != 0)
                {
                    float currentMaxQ = Q(s, Actions[s][0]);
                    //std::cout << "Current max: " << s << "->" << Actions[s][0] << " : Q(t-1)=" << currentMaxQ << std::endl;

                    for (int a = 1; a < Actions[s].size(); ++a)
                    {
                        float nextQ = Q(s, Actions[s][a]);
                        //std::cout << "next Q: " << s << "->" << Actions[s][a] << " : Q(t-1)=" << nextQ << std::endl;
                        if (nextQ > currentMaxQ)
                        {
                            currentMaxQ = nextQ;
                            //std::cout << "Current max: " << s << "->" << Actions[s][a] << " : Q(t-1)=" << currentMaxQ << std::endl;
                        }
                    }
                    //std::cout << "Vt = " << currentMaxQ << std::endl<< std::endl;

                    Vnew[s - 1] = currentMaxQ;
                }
            }

            //Check whether the values have converged
            if (converged(Vnew))
            {
                V = Vnew; //Synchronous update of V(s)
                printGrid(iterationCount);
                break;
            }

            V = Vnew; //Synchronous update of V(s)
            printGrid(iterationCount);
        }
    }

    bool ValueIteration::converged(const std::vector<float> &newV)
    {
        float epsilon = 0.00001;

        std::vector<float> result(numStates, 0);
        std::transform(newV.begin(), newV.end(), V.begin(), result.begin(), std::minus<float>()); //result[i] = newV[i] - oldV[i];

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

    void ValueIteration::printGrid(int t)
    {
        std::cout << "______GRID WORLD______ t=" << t << std::endl;
        std::cout << "\t|0|\t|1|\t|2|\n";
        std::cout << "|1|\t";
        for (int i = 0; i < 3; ++i)
        {
            std::cout << V[i] << "\t";
        }
        std::cout << std::endl;
        std::cout << "|0|\t";
        for (int i = 3; i < 6; ++i)
        {
            std::cout << V[i] << "\t";
        }
        std::cout << "\n----------------------\n"
                  << std::endl;
    }

} // namespace CHNJAR003