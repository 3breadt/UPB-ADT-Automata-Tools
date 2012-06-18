/*
 * FinalStateAutomata.hpp
 *
 *  Created on: May 25, 2012
 *      Author: fabiani
 */

#ifndef FSA_FINITESTATEAUTOMATA_HPP_
#define FSA_FINITESTATEAUTOMATA_HPP_

#include <iostream>
#include "FSA_State.hpp"
#include "FSA_Transition.hpp"
#include <vector>


using namespace std;

class FiniteStateAutomata{
private:
	//State** stateList;
	//Transition** transitionList;
	vector<State*> vecStateList;
	vector<Transition*> vecTransitionList;

public:
	FiniteStateAutomata();
	~ FiniteStateAutomata();
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
    void read(string p_szFileName);
	void write(string p_szFileName);
	void testEdge(string testEdge);


};

#endif /* FSA_FINITESTATEAUTOMATA_HPP_ */
