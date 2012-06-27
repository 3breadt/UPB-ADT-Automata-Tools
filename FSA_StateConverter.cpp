/*
 * StateConverter.cpp
 *
 *  Created on: May 25, 2012
 *      Author: skowelek
 */

#include "FSA_StateConverter.hpp"

using namespace std;

/* default Constructor, needed to use the constructor of transition*/
StateConverter::StateConverter()
{
}

StateConverter::StateConverter(State *p_stState)
{
	this->stConvertedState = p_stState;
}

StateConverter::StateConverter(State *p_stState, vector<State*> *p_vecReferencedStates)
{
	this->stConvertedState = p_stState;
	this->vecReferencedStates = *p_vecReferencedStates;
}

StateConverter::StateConverter(string p_szStateName)
{
	this->stConvertedState = new State(p_szStateName);
}

StateConverter::StateConverter(string p_szStateName, vector<State*> *p_vecReferencedStates)
{
	this->stConvertedState = new State(p_szStateName);
	this->vecReferencedStates = *p_vecReferencedStates;
}

void StateConverter::setReferencedStates(vector<State*> *p_vecReferencedStates)
{
	this->vecReferencedStates = *p_vecReferencedStates;
}

void StateConverter::addReferencedState(State *p_szReferencedState)
{
	this->vecReferencedStates.push_back(p_szReferencedState);
}

void StateConverter::removeReferencedState(string p_szStateName)
{
	for(std::vector<State*>::iterator it = vecReferencedStates.begin(); it != vecReferencedStates.end(); ++it) {
		if((*it)->output() == p_szStateName) {
			vecReferencedStates.erase(it);
		}
	}
}

void StateConverter::clearReferencedStates()
{
	this->vecReferencedStates.clear();
}

State* StateConverter::getConvertedState()
{
	return stConvertedState;
}

vector<State*>* StateConverter::getReferencedStates()
{
	return &vecReferencedStates;
}

bool StateConverter::equalsReferncedStates(StateConverter *p_scStateConverter)
{
	for(std::vector<State*>::iterator itref = p_scStateConverter->vecReferencedStates.begin(); itref != p_scStateConverter->vecReferencedStates.end(); ++itref) {
		if(!this->isInStateList(*itref)) {
			return false;
		}
	}
	return true;
}

bool StateConverter::isInStateList(State* p_stState)
{
	for(std::vector<State*>::iterator it = vecReferencedStates.begin(); it != vecReferencedStates.end(); ++it) {
		if((*it)->output() == p_stState->output()) {
			return true;
		}
	}
	return false;
}

void StateConverter::checkForFinalState()
{
	for(std::vector<State*>::iterator it = vecReferencedStates.begin(); it != vecReferencedStates.end(); ++it) {
		if((*it)->isFinalState()) {
			stConvertedState->setFinalState(true);
		}
	}
}