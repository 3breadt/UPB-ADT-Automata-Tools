/**
 * @file FSA_StateConverter.cpp
 * Contains the implementation of the StateConverter class.
 * @author skowelek
 */

#include "FSA_StateConverter.hpp"

using namespace std;

/**
 * Standard constructor.
 */
StateConverter::StateConverter()
{
}

/**
 * Constructor. Creates a new StateConverter and sets the member stConvertedState to the given State.
 * @param p_stState State to set stConvertedState to.
 */
StateConverter::StateConverter(State *p_stState)
{
	this->stConvertedState = p_stState;
}

/**
 * Constructor. Creates a new StateConverter and sets the members to the given values.
 * @param p_stState State to set stConvertedState to.
 * @param p_vecReferencedStates to set the referenced states vector to.
 */
StateConverter::StateConverter(State *p_stState, vector<State*> *p_vecReferencedStates)
{
	this->stConvertedState = p_stState;
	this->vecReferencedStates = *p_vecReferencedStates;
}

/**
 * Constructor. Creates a new StateConverter and creates a new State for stConvertedState
 * with the given name.
 * @param p_szStateName Name for the new stConvertedState.
 */
StateConverter::StateConverter(string p_szStateName)
{
	this->stConvertedState = new State(p_szStateName);
}

/**
 * Constructor. Creates a new StateConverter and sets the members to the given values.
 * @param p_szStateName String to use as name for the new stConvertedState.
 * @param p_vecReferencedStates to set the referenced states vector to.
 */
StateConverter::StateConverter(string p_szStateName, vector<State*> *p_vecReferencedStates)
{
	this->stConvertedState = new State(p_szStateName);
	this->vecReferencedStates = *p_vecReferencedStates;
}

/**
 * Sets the referenced states vector of a StateConverter to the given vector.
 * @param p_vecReferencedStates to set the referenced states vector to.
 */
void StateConverter::setReferencedStates(vector<State*> *p_vecReferencedStates)
{
	this->vecReferencedStates = *p_vecReferencedStates;
}

/**
 * Adds a State to the referenced states vector of this StateConverter
 * @param p_szReferencedState State to add to the referenced states vector.
 */
void StateConverter::addReferencedState(State *p_szReferencedState)
{
	this->vecReferencedStates.push_back(p_szReferencedState);
}

/**
 * Removes a State of the referenced states vector of this StateConverter
 * @param p_szStateName State to remove of the referenced states vector.
 */
void StateConverter::removeReferencedState(string p_szStateName)
{
	for(std::vector<State*>::iterator it = vecReferencedStates.begin(); it != vecReferencedStates.end(); ++it) {
		if((*it)->output() == p_szStateName) {
			vecReferencedStates.erase(it);
		}
	}
}

/**
 * Clears the referenced states vector of this StateConverter.
 */
void StateConverter::clearReferencedStates()
{
	this->vecReferencedStates.clear();
}

/**
 * Returns the stConvertedState of this StateConverter.
 * @return The stConvertedState of this StateConverter.
 */
State* StateConverter::getConvertedState()
{
	return stConvertedState;
}

/**
 * Returns the referenced states vector of this StateConverter.
 * @return The referenced states vector of this StateConverter.
 */
vector<State*>* StateConverter::getReferencedStates()
{
	return &vecReferencedStates;
}

/**
 * Checks if the referenced states vector of the given StateConverter equals
 * the one of this StateConverter.
 * @param p_scStateConverter State to compare with.
 * @return True if the referenced states vector of both StateConverters are equal, false if not.
 */
bool StateConverter::equalsReferencedStates(StateConverter *p_scStateConverter)
{
	for(std::vector<State*>::iterator itref = p_scStateConverter->vecReferencedStates.begin(); itref != p_scStateConverter->vecReferencedStates.end(); ++itref) {
		if(!this->isInStateList(*itref)) {
			return false;
		}
	}
	return true;
}

/**
 * Checks if the given State is in the referenced states vector of this StateConverter.
 * @param p_stState State to check for.
 * @return True if the State is in the referenced states vector, false if not.
 */
bool StateConverter::isInStateList(State* p_stState)
{
	for(std::vector<State*>::iterator it = vecReferencedStates.begin(); it != vecReferencedStates.end(); ++it) {
		if((*it)->output() == p_stState->output()) {
			return true;
		}
	}
	return false;
}

/**
 * Checks if any of the States in the referenced states vector is final. If it is,
 * sets the stConvertedState of this StateConverter to final.
 */
void StateConverter::checkForFinalState()
{
	for(std::vector<State*>::iterator it = vecReferencedStates.begin(); it != vecReferencedStates.end(); ++it) {
		if((*it)->isFinalState()) {
			stConvertedState->setFinalState(true);
		}
	}
}