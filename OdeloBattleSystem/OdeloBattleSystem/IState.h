#pragma once

/*
 Interface that the State class needs to comply with.
 It doesn't need to extend this class, in fact, you don't need to include this file
 This is just here for reference.
 'Action' is your custom class containing action information
 See examples for usage
*/

#include <vector>
#include <string>

namespace msa {
namespace mcts {


class Action;
class State {

    // copy and assignment operators should perform a DEEP clone of the given state
    //State(const State& other);
	//State& operator = (const State& other);

    // whether or not this state is terminal (reached end)
    virtual bool is_terminal() const = 0;

    //  agent id (zero-based) for agent who is about to make a decision
    virtual int agent_id() const = 0;

    // apply action to state
    virtual void apply_action(const Action& action) = 0;

    // return possible actions from this state
    virtual void get_actions(std::vector<Action>& actions) const = 0;

    // get a random action, return false if no actions found
    virtual bool get_random_action(Action& action) const = 0;

    // evaluate this state and return a vector of rewards (for each agent)
    virtual const std::vector<float> evaluate() const = 0;

    // return state as string (for debug purposes)
    virtual std::string to_string() const = 0;

};

}
}
