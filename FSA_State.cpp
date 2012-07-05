/*
 * State.cpp
 *
 *  Created on: May 25, 2012
 *      Author: fabiani
 */

#include "FSA_State.hpp"

using namespace std;

/* default Constructor, needed to use the constructor of transition*/
State::State()
{

}
/* Constructor
 * Parameters: one string containing the name of the constructed state*/
State::State(string p_szName)
{
	this-> szName = p_szName;
	bStartState = false;
	bFinalState = false;
}
/* Cnstructor
 * Parameters: three strings containing the name of the constructed state and the boolean startState
 * and finalState, so it's possible to defining the states status by creating the element*/
State::State(string p_szName, bool p_bStartState, bool p_bFinalState)
{
	this->szName = p_szName;
    this->bStartState = p_bStartState;
    this->bFinalState = p_bFinalState;
}
/* Set startState status
 *
 * if you didn't set the status by creating the state element you can use this method for defining it
 * afterwards*/
void State::setStartState(bool p_bSetStartState)
{
	bStartState = p_bSetStartState;
}
/* Set finalState status
 *
 * if you didn't set the status by creating the state element you can use this method for defining it
 * afterwards*/
void State::setFinalState(bool p_bSetFinalState)
{
	bFinalState = p_bSetFinalState;
}

bool State::isStartState()
{
	return State::bStartState;
}

bool State::isFinalState()
{
	return State::bFinalState;
}
/* Output of one state
  *
  * it gives a string that includes the name of the state*/
string State::output()
{
	return szName;
}

/**
 * @author Yacine Smaoui
 */
string State::getName()
{
	return this->szName ;
}

/**
 * @brief compares two States
 * @author Yacine Smaoui
 */
int State::compare(State* state)
{
	if (this->getName().compare(state->getName())==0
			&& this->isFinalState() == state->isFinalState()
			&& this->isStartState() == state->isStartState())
	{
		return 0 ;
	}
	return 1;
}
