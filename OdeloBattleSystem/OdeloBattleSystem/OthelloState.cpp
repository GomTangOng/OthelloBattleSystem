#include "OthelloState.h"
#include "OdeloBattleSystem.h"
#include "Action.h"


#define MAX_ACTIONS 60

OthelloState::OthelloState(const OthelloState & state)
{
	memcpy(m_othello, state.m_othello, sizeof(COdeloBattleSytem));
	m_nStoneType = state.m_nStoneType;
}

OthelloState::~OthelloState()
{

}

bool OthelloState::is_terminal() const
{
	return !m_othello->IsPutStone(m_nStoneType);
}

int OthelloState::agent_id() const	// ???
{
	return 0;
}

void OthelloState::apply_action(const Action & action)
{
	m_othello->PutStone(action.m_nPosX, action.m_nPosY, m_nStoneType);
	m_nStoneType = (m_nStoneType == BLACK) ? WHITE : BLACK;
}

void OthelloState::get_actions(std::vector<Action>& actions) const
{
	actions.resize(MAX_ACTIONS);
	m_othello->GetPutPosition(actions, m_nStoneType);
}

bool OthelloState::get_random_action(Action & action) 	
{
	std::vector<Action> actions;
	if (m_othello->IsPutStone(m_nStoneType))
	{
		//m_othello->PutStone(action.m_nPosX, action.m_nPosY, m_nStoneType);
		//m_nStoneType = (m_nStoneType == BLACK) ? WHITE : BLACK;
		get_actions(actions);
		
		action = actions[rand() % actions.size()];

		return true;
	}	
	return false;
}

const std::vector<float> OthelloState::evaluate() const		// to do coding
{	
	std::vector<float> rewards(2);

	if (m_othello->IsPutStone(m_nStoneType))
	{

	}
	
	return 0;	// game still going
}

std::string OthelloState::to_string() const
{
	return std::string();
}
