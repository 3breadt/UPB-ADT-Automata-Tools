/**
 * @file FSA_State.hpp
 * Contains the definition of the State class.
 * @author fabiani
 */


#ifndef FSA_STATE_HPP_
#define FSA_STATE_HPP_

#include <iostream>

using namespace std;

/**
 * @brief A state in a Finite State Automaton
 **/
class State{

	friend class Transition;
	friend class FiniteStateAutomaton;

private:
	string szName;
	bool bStartState;
	bool bFinalState;

public:
	State();
	State(string p_szName);
	State(string p_szName, bool p_bStartState, bool p_bFinalState);
	void setStartState(bool p_bSetStartState);
	void setFinalState(bool p_bSetFinalState);
	bool isStartState();
	bool isFinalState();
	string output();

	string getName();
	void setName(string name);
	int compare(State* state);
};

#endif /* FSA_STATE_HPP_ */
