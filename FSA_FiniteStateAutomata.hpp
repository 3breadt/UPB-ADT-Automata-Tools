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
	vector<State*> vecStateList;
	vector<Transition*> vecTransitionList;
	vector<State*> vecFinalStates;
	bool isInFinalStatesVector(string p_szStateName);

public:
	FiniteStateAutomata();
	~ FiniteStateAutomata();
	void addState(string p_szStateName);
	void addState(State *p_stNewState);
	void removeState(string p_szStateName);
	void outputStateList();
	void printStartState();
	void printFinalState();
	bool bStateExists(string p_szName);
	State* getState(string p_szName);
	State* getStartState();
	vector<State*>* getFinalStates();
	vector<State*>* getStateList();
	void addTransition(string p_szBeginningState, string p_szEdge, string p_szFinalState);
	void addTransition(string p_szInput);
	void removeTransition(string p_szBeginningState, string p_szEdge, string p_szFinalState);
    void outputTransitionList();
	vector<Transition*>* getTransitions();
    void read(string p_szFileName);
	void write(string p_szFileName);
	void testEdge(string p_szTestEdge);


};

#endif /* FSA_FINITESTATEAUTOMATA_HPP_ */
