/*
 * FinalStateAutomata.hpp
 *
 *  Created on: May 25, 2012
 *      Author: fabiani
 */

#ifndef FINALSTATEAUTOMATA_HPP_
#define FINALSTATEAUTOMATA_HPP_

#include <iostream>
#include "State.hpp"
#include "Transition.hpp"


using namespace std;

class FinalStateAutomata{
private:
	State** stateList;
	Transition** transitionList;
	static int automataStateCount;
	static int automataTransitionCount;

public:
	FinalStateAutomata();
	~ FinalStateAutomata();
	void addState(string stateName);
	void addState(State *stateName);
	void removeState(string stateName);
	void outputStateList();
	void getStartState();
	void getFinalState();
	void addTransition(string beginingState,string edge, string finalState);
	void addTransition(string input);
	void removeTransition(string beginingState,string edge, string finalState);
    void outputTransitionList();
    void read();						//TODO
	void write();						//TODO
	void testEdge(string testEdge);


};

#endif /* FINALSTATEAUTOMATA_HPP_ */
