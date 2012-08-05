/**
 * @file FSA_StateConverter.hpp
 * Contains the definition of the StateConverter class.
 * @author skowelek
 */

#ifndef FSA_STATECONVERTER_HPP_
#define FSA_STATECONVERTER_HPP_

#include <iostream>
#include <string>
#include "FSA_StateConverter.hpp"
#include "FSA_State.hpp"
#include <vector>

using namespace std;

/**
 * Helper class used during conversion from NDA to DFA.
 **/
class StateConverter{

	friend class Transition;
	friend class FiniteStateAutomaton;
	friend class State;

private:
	State *stConvertedState;
	vector<State*> vecReferencedStates;
	bool isInStateList(State* p_stState);
	void checkForFinalState();

public:
	StateConverter();
	StateConverter(State *p_stState);
	StateConverter(State *p_stState, vector<State*> *p_vecReferencedStates);
	StateConverter(string p_szStateName);
	StateConverter(string p_szStateName, vector<State*> *p_vecReferencedStates);
	void setReferencedStates(vector<State*> *p_vecReferencedStates);
	void addReferencedState(State *p_szReferencedState);
	void removeReferencedState(string p_szStateName);
	void clearReferencedStates();
	State* getConvertedState();
	vector<State*>* getReferencedStates();
	bool equalsReferencedStates(StateConverter *p_scStateConverter);
};

#endif /* FSA_STATE_HPP_ */
