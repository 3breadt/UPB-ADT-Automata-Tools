/**
 * @file FSA_Transition.cpp
 * Contains the implementation of the Transition class.
 */

#include "FSA_Transition.hpp"
#include "FSA_State.hpp"
#include<string>
#include<cstring>

/**Constructor FSA_Transition*/
Transition::Transition(State *p_stBeginning, State *p_stFinish, string p_szEdge)
{

	 this->stBeginning = p_stBeginning;
	 this->stFinish = p_stFinish;
	 this->szEdge = p_szEdge;
}


/**
 * Output of one transition.
 * @return The transition as string.
 * @author fabiani, andreasb
 */
string Transition::output(){
	string result;
	result = stBeginning->szName + " " + szEdge + " " + stFinish->szName;
	return result;

}

/**
 * Getter for the BeginningState.
 * @return Statepointer to the BeginningState.
 * @author skowelek
 */
State* Transition::getBeginningState()
{
	return stBeginning;
}

/**
 * Getter for the FinishState.
 * @return Statepointer to the FinishState.
 * @author skowelek
 */
State* Transition::getFinishState()
{
	return stFinish;
}

/**
 * Getter for the EdgeName.
 * @return Name of the edge.
 * @author skowelek
 */
string Transition::getEdgeName()
{
	return szEdge;
}

void Transition::setBeginningState(State *p_stBeginning) {
	this->stBeginning = p_stBeginning;
}

void Transition::setFinishState(State *p_stFinish) {
	this->stFinish = p_stFinish;
}

void Transition::setEdgeName(string p_szEdge) {
	this->szEdge = p_szEdge;
}

int Transition::compare(Transition* transition)
{
	if (this->getBeginningState()->compare(transition->getBeginningState())==0
			&& this->getFinishState()->compare(transition->getFinishState())==0
			&& this->getEdgeName().compare(transition->getEdgeName()) == 0)
	{
		return 0 ;
	}
	return 1;
}
