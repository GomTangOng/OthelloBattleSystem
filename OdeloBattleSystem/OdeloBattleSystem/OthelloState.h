#pragma once

#include "IState.h"

class COdeloBattleSytem;
class Action;
class OthelloState : public msa::mcts::State
{
public:
	OthelloState(const OthelloState& state);
	~OthelloState();

	bool is_terminal() const override;

	//  agent id (zero-based) for agent who is about to make a decision
	int agent_id() const override;

	// apply action to state
	void apply_action(const Action& action);

	// return possible actions from this state
	void get_actions(std::vector<Action>& actions) const;

	// get a random action, return false if no actions found
	bool get_random_action(Action& action);

	// evaluate this state and return a vector of rewards (for each agent)
	const std::vector<float> evaluate() const override;

	// return state as string (for debug purposes)
	std::string to_string() const override;
private :
	COdeloBattleSytem *m_othello;
	int m_nStoneType;
public :
	
};

