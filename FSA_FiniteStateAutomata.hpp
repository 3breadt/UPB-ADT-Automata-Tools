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
#include "FSA_StateConverter.hpp"
#include "FSA_Group.hpp"
#include "FSA_GroupElement.hpp"
#include "RG_Grammar.h"
#include <vector>
#include <sstream>

class Group;
class Grammar;

using namespace std;

class FiniteStateAutomata{
private:
	vector<State*> vecStateList;
	vector<Transition*> vecTransitionList;
	vector<State*> vecFinalStates;
	bool isInFinalStatesVector(string p_szStateName);
	void removeFinalStates();
	bool isInStateConverterList(StateConverter* p_scStateConverter, vector<StateConverter*>* p_vecStateConverterList);
	StateConverter* getEqualStateConverterFromConverterList(StateConverter* p_scStateConverter, vector<StateConverter*>* p_vecStateConverterList);
	void setTargetStatesForEdge(string p_szEdge, State* p_stStateToCheck, vector<State*>* p_vecTargetStates);
	void setStateListFromStateConverterList(vector<State*>* p_vecStateList, vector<StateConverter*>* p_vecStateConverterList);
	string getTargetGroupName(State* p_stState, vector<Group*>* p_vecGroups);
	void setTargetGroups(vector<Group*>* p_vecGroups);
	int findGroupByGroupName(string p_szGroupName, vector<Group*>* p_vecGroups);

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
	void addTransition(State *p_stBeginningState, string p_szEdge, State *p_stFinalState);
	void addTransition(string p_szInput);
	void removeTransition(string p_szBeginningState, string p_szEdge, string p_szFinalState);
    void outputTransitionList();
	vector<string> getEdgesFromTransitionList();
	vector<Transition*>* getTransitions();
    void read(string p_szFileName);
	void write(string p_szFileName);
	void testEdge(string p_szTestEdge);
	FiniteStateAutomata* fsaConvertNEAtoDEA();
	FiniteStateAutomata* minimize();
	Grammar* convertToGrammar();
};

#endif /* FSA_FINITESTATEAUTOMATA_HPP_ */
