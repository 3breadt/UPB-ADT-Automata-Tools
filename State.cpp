/*
 * State.cpp
 *
 *  Created on: May 25, 2012
 *      Author: fabiani
 */

#include "State.hpp"

using namespace std;

int State::stateCount = 0;

State::State(){

}

State::State(string name){
	this-> name = name;
	startState = false;
	finalState = false;
	stateCount++;
}


  State::State(string name, bool startState, bool finalState){
	this->name = name;
    this->startState = startState;
    this->finalState = finalState;
	 }

void State::setStartState(){
	startState = true;
}

void State::setFinalState(){
	finalState = true;
}

int State::giveStateCount()
{
	return stateCount;
}
string State::output()
{
	return name;
}

