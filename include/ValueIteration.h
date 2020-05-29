#ifndef VALIT_H
#define VALIT_H
#include <vector>
#include <map>

namespace CHNJAR003
{
    class ValueIteration
    {
    private:
        float gamma; //discount parameter
        int numStates;
        std::vector<float> V;                        //Will store the estimated expected utility of each state - indexed by (state number - 1)
        std::map<int, int> Policy;                   //Will store the optimal policy - [state number -1] = optimal action to take
        std::map<int, std::vector<int>> Actions;     //[state] = {actions}
        std::map<int, std::map<int, float>> Rewards; //[state][action] = reward

    public:
        ValueIteration(int numStates, const std::map<int, std::vector<int>> &actions, const std::map<int, std::map<int, float>> &rewards, float gamma);
        const float Q(int state, int action); //Calculated the expected utility of taking action a from state s (discounted by gamma)
        void performValueIteration(void);     //Performs the Value Iteration algorithm
        void performPolicyExtraction(void);
        std::string policyRouteFromState(int startState);
        bool converged(const std::vector<float> &newV);
        void printGrid(int t);
    };

} // namespace CHNJAR003

#endif