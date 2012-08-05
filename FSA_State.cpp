/**
 * @file FSA_State.cpp
 * Contains the implementation of the State class.
 * @author fabiani
 */

#include "FSA_State.hpp"

using namespace std;

/** default Constructor for FSA_State.*/
State::State()
{

}
/**
 * Constructor for FSA_State.
 * @param p_szName Name of state.
 * @return FSA_state.
 * @author fabiani, andreasb
 */
State::State(string p_szName)
{
	this-> szName = p_szName;
	bStartState = false;
	bFinalState = false;
}
/** 
 * Constructor for FSA_State.
 * @param p_szName Name of state,
 * @param p_bStartState True if State is StartState,
 * @param p_bFinalState True if State is FinalState.
 * @return FSA_State.
 * @author fabiani, andreasb
 */
State::State(string p_szName, bool p_bStartState, bool p_bFinalState)
{
	this->szName = p_szName;
    this->bStartState = p_bStartState;
    this->bFinalState = p_bFinalState;
}
/**
 * Sets the startState value of FSA_State
 * @param p_bSetStartState Value for the startState.
 * @author fabiani, andreasb
 */
void State::setStartState(bool p_bSetStartState)
{
	bStartState = p_bSetStartState;
}
/**
 * Sets the finalState value of FSA_State
 * @param p_bSetFinalState Value for the finalState.
 * @author fabiani, andreasb
 */
void State::setFinalState(bool p_bSetFinalState)
{
	bFinalState = p_bSetFinalState;
}

/**
 * Gives the value of startState attribute.
 * @author fabiani, andreasb
 */
bool State::isStartState()
{
	return State::bStartState;
}

/**
 * Gives the value of finalState attribute.
 * @author fabiani, andreasb
 */
bool State::isFinalState()
{
	return State::bFinalState;
}
/** 
 * Output of one state
 * @return szName Name of the state.
 * @author fabiani, andreasb*/
string State::output()
{
	return szName;
}

/**
 * @brief  gets the name of the State.
 * @author Yacine Smaoui
 */
string State::getName()
{
	return this->szName ;
}

void State::setName(string name)
{
	this->szName = name ;
}

/**
 * @brief compares two States.
 * @author Yacine Smaoui
 */
int State::compare(State* state)
{
	if (this->getName().compare(state->getName())==0
			&& this->isFinalState() == state->isFinalState()
			&& this->isStartState() == state->isStartState())
	{
		return 0 ;
	}
	return 1;
}
