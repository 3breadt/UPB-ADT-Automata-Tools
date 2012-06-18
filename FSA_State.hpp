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
	string name;
	bool startState;
	bool finalState;

public:
	State();
	State(string name);
	State(string name, bool startState, bool finalState);
	void setStartState();
	void setFinalState();
	string output();
};

#endif /* FSA_STATE_HPP_ */
