#ifndef VALIT_H
#define VALIT_H
#include <vector>
#include <map>

namespace CHNJAR003
{
    class ValueIteration
    {
    private:
        float gamma;

        std::vector<float> V;   //Will store the optimal expected utility received by following the optimal policy (indexed by state s) - must initiliase with zeroes in algorithm
        std::vector<int> PiOpt; //Will store the optimal policy

        //[state][action] = reward
        std::map<int, std::vector<int>> Actions;
        std::map<int, std::map<int, float>> Rewards;

    public:
        ValueIteration(int numStates, const std::map<int, std::vector<int>> &actions, const std::map<int, std::map<int, float>> &rewards, float gamma);
        const float &Q(int state, int action);
    };

} // namespace CHNJAR003

#endif