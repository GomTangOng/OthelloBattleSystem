#include "OthelloState.h"
#include "OdeloBattleSystem.h"
#include "Action.h"


// 오델로배틀시스템이랑 따로 분리해서 만들어야 될듯....
// 문제가 생김

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

bool OthelloState::get_random_action(Action & action) 	// get random_action...?
{
	if (m_othello->IsPutStone(m_nStoneType))
	{
		m_othello->PutStone(action.m_nPosX, action.m_nPosY, m_nStoneType);
		m_nStoneType = (m_nStoneType == BLACK) ? WHITE : BLACK;
		return true;
	}	
	return false;
}

const std::vector<float> OthelloState::evaluate() const	// evaluate ??
{	
	return std::vector<float>();
}

std::string OthelloState::to_string() const
{
	return std::string();
}
