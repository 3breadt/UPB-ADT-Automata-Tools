/*
 * State.hpp
 *
 *  Created on: May 25, 2012
 *      Author: fabiani
 */

#ifndef STATE_HPP_
#define STATE_HPP_

#include <iostream>

using namespace std;

class State{

	friend class Transition;
	friend class FinalStateAutomata;

private:
	string name;
	bool startState;
	bool finalState;
	static int stateCount;

public:
	State();
	State(string name);
	State(string name, bool startState, bool finalState);
	void setStartState();
	void setFinalState();
	string output();
};

#endif /* STATE_HPP_ */
