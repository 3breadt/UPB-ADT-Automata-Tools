/*
 * Transition.hpp
 *
 *  Created on: May 25, 2012
 *      Author: fabiani
 */

#ifndef TRANSITION_HPP_
#define TRANSITION_HPP_

#include<iostream>
#include "State.hpp"

using namespace std;

class Transition{

	friend class FinalStateAutomata;

private:
	State begining;
	State finish;
	string edge;
	static int transitionCount;

public:
	Transition(State begining, State finish, string edge);
	Transition(string input);
	string output();


};

#endif /* TRANSITION_HPP_ */
