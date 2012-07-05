/*
 * State.hpp
 *
 *  Created on: May 25, 2012
 *      Author: fabiani
 */

#ifndef FSA_STATE_HPP_
#define FSA_STATE_HPP_

#include <iostream>

using namespace std;

class State{

	friend class Transition;
	friend class FiniteStateAutomata;

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
	int compare(State* state);
};

#endif /* FSA_STATE_HPP_ */
