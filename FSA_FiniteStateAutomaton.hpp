/**
 * @file FSA_FiniteStateAutomaton.hpp
 * Contains the definition of the FiniteStateAutomaton class.
 */

#ifndef FSA_FiniteStateAutomaton_HPP_
#define FSA_FiniteStateAutomaton_HPP_

#include <iostream>
#include "FSA_State.hpp"
#include "FSA_Transition.hpp"
#include "FSA_StateConverter.hpp"
#include <vector>
#include <sstream>
#include <map>
#include <list>

using namespace std;

class Group;
class Grammar;
//class RegularExpression;

/**
 * @brief Finite State Automaton data structure.
 **/
class FiniteStateAutomaton {
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
	bool isInTransitionList(Transition* p_tNewTransition);

public:
	FiniteStateAutomaton();
	~ FiniteStateAutomaton();
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
    void removeTransition(Transition* p_transition);
    void outputTransitionList();
	vector<string> getEdgesFromTransitionList();
	vector<Transition*>* getTransitions();
    void read(string p_szFileName);
	void write(string p_szFileName);
	void testEdge(string p_szTestEdge);
	FiniteStateAutomaton* fsaConvertNEAtoDEA();
	FiniteStateAutomaton* minimize();
	void removeEmptyEdges();
	bool isTotal();
	Grammar* convertToGrammar();
};

#endif /* FSA_FiniteStateAutomaton_HPP_ */
