#ifndef VALIT_H
#define VALIT_H
#include <vector>
#include <iostream>
#include <map>

namespace CHNJAR003
{
    class ValueIteration
    {
    private:
        float epsilon; //Threshold for convergence
        float gamma;   //discount parameter
        int numStates;
        int numIterations;
        std::vector<float> V;                        //Will store the estimated expected utility of each state - indexed by (state number - 1)
        std::map<int, int> Policy;                   //Will store the optimal policy - [state number -1] = optimal action to take
        std::map<int, std::vector<int>> Actions;     //[state] = {actions}
        std::map<int, std::map<int, float>> Rewards; //[state][action] = reward

    public:
        ValueIteration(const int numStates, const std::map<int, std::vector<int>> &actions, const std::map<int, std::map<int, float>> &rewards, const float gamma, const float epsilon); //Parameterised constructor
        const float Q(const int state, const int action);                                                                                                                                //Calculated the expected utility of taking action a from state s (discounted by gamma)
        void performValueIteration(void);                                                                                                                                                //Performs the Value Iteration algorithm
        void performPolicyExtraction(void);                                                                                                                                              //Performs extraction of the optimal policy from the values of each state once the algorithm has converged
        std::string policyRouteFromState(const int startState) const;                                                                                                                    //Provides the optimal route to be taking by following the optimal policy from a given starting state to the end state
        bool converged(const std::vector<float> &newV) const;                                                                                                                            //Determines whether the algorithm has converged by comparing the given iteration's values to the previous one's values
        std::string formatGrid(const int t) const;                                                                                                                                       //Gives the values of the grid world states in a 2D ASCII representation

        friend std::ostream &operator<<(std::ostream &os, const ValueIteration &vi); //Overloaded output stream operator
    };

} // namespace CHNJAR003

#endif