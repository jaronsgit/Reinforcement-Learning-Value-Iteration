#include "../include/ValueIteration.h"
namespace CHNJAR003
#include <vector>
#include <map>
{

    ValueIteration::ValueIteration(int numStates, const std::map<int, std::vector<int>> &actions, const std::map<int, std::map<int, float>> &rewards, float gamma) : Actions(actions), V(std::vector<float>(numStates, 0)), Rewards(rewards), gamma(gamma)
    {
    }

    const float &ValueIteration::Q(int state, int action)
    {
        return Rewards[state][action];
    }

} // namespace CHNJAR003