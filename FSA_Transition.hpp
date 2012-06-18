/*
 * Transition.hpp
 *
 *  Created on: May 25, 2012
 *      Author: fabiani
 */

#ifndef FSA_TRANSITION_HPP_
#define FSA_TRANSITION_HPP_

#include<iostream>
#include "FSA_State.hpp"

using namespace std;

class Transition{

	friend class FiniteStateAutomata;
	static int transitionCount;

private:
	State begining;
	State finish;
	string edge;

public:
	Transition(State begining, State finish, string edge);
	Transition(string input);
	string output();


};

#endif /* FSA_TRANSITION_HPP_ */
