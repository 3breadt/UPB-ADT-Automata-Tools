/*
 * FSA_FSAtoREConverter.cpp
 *
 *  Created on: 21.06.2012
 *      Author: daniel
 */

#include "FSA_FSAtoREConverter.hpp"
#include "FSA_Transition.hpp"
#include "FSA_State.hpp"
#include <vector>
#include <map>
#include <string>
#include "RE_RegularExpression.hpp"

namespace std {

/**
 * Converts a given finite state automaton to a regular expression.
 *
 * WARNING: The given automaton will be destroyed
 *
 * The algorithm is based on the paper "Obtaining shorter regular expressions
 * from finite-state automata" by Yo-Sub Han and Derick Wood.
 * @see http://www.sciencedirect.com/science/article/pii/S0304397506007523
 * @param fsa The FSA to convert.
 * @return A regular expression corresponding to the given FSA.
 * @author Daniel Dreibrodt
 */
RegularExpression *FSAtoREConverter::toRE(FiniteStateAutomata *fsa) {
	//TODO Minimize, or require given automata to be already minimal

	vector<State*> *states = fsa->getStateList();
	vector<Transition*> *transitions = fsa->getTransitions();

	/**
	 * First make sure that the automaton is non-returning and non-exiting
	 */

	//This is done by creating a new start state with an empty transition to the old one
	State *originalStartState = fsa->getStartState();
	originalStartState->setStartState(false);
	State *startState = new State("FSA_TO_RE_STARTSTATE",true,false);
	states->push_back(startState);
	transitions->push_back(new Transition(*startState,*originalStartState,""));

	//And by creating a new final state to which all old final states have empty transitions
	State *finalState = new State("FSA_TO_RE_FINALSTATE",false,false);
	states->push_back(finalState);
	for(vector<State*>::iterator it = states->begin(); it != states->end(); ++it) {
		State *currentState = *it;
		if(currentState->isFinalState()) {
			transitions->push_back(new Transition(*currentState,*finalState,""));
			currentState->setFinalState(false);
		}
	}

	finalState->setFinalState(true);

	/**
	 * create hash-maps to easily find transitions to/from states
	 */
	map<State*, vector<Transition*>*> transitionsFromState;
	map<State*, vector<Transition*>*> transitionsToState;

	for(vector<Transition*>::iterator it = transitions->begin(); it != transitions->end(); ++it) {
		//Add transition to transitionsFromState map
		transitionsFromState[(*it)->getBeginningState()]->push_back(*it);
		//Add transition to transitionsToState map
		transitionsToState[(*it)->getFinishState()]->push_back(*it);
	}

	//remove useless (unreachable) states
	for(vector<State*>::iterator it = states->begin(); it != states->end(); ++it) {
		State *currentState = *it;
		if(currentState!=startState) {
			if(transitionsToState[currentState]->size()==0) {
				//useless state
				states->erase(it);
			}
		}
	}


	/**
	 * State elimination
	 **/

	for(vector<State*>::iterator it = states->begin(); it != states->end(); ++it) {

	}

	return NULL;
}

} /* namespace std */
