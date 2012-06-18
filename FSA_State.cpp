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
/* Cnstructor
 * Parameters: one string containing the name of the constructed state*/
State::State(string name)
{
	this-> name = name;
	startState = false;
	finalState = false;
}
/* Cnstructor
 * Parameters: three strings containing the name of the constructed state and the boolean startState
 * and finalState, so it's possible to defining the states status by creating the element*/
State::State(string name, bool startState, bool finalState)
{
	this->name = name;
    this->startState = startState;
    this->finalState = finalState;
}
/* Set startState status
 *
 * if you didn't set the status by creating the state element you can use this method for defining it
 * afterwards*/
void State::setStartState()
{
	startState = true;
}
/* Set finalState status
 *
 * if you didn't set the status by creating the state element you can use this method for defining it
 * afterwards*/
void State::setFinalState()
{
	finalState = true;
}
/* Output of one state
  *
  * it gives a string that includes the name of the state*/
string State::output()
{
	return name;
}

