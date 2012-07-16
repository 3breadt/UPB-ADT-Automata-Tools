/*
 * Transition.hpp
 *
 *  Created on: May 25, 2012
 *      Author: fabiani
 */

#ifndef FSA_TRANSITION_HPP_
#define FSA_TRANSITION_HPP_

#include<iostream>
#include "FSA_State.hpp"

using namespace std;

class Transition{

	friend class FiniteStateAutomata;

private:
	State stBeginning;
	State stFinish;
	string szEdge;

public:
	Transition(State p_stBeginning, State p_stFinish, string p_szEdge);
	//Transition(string p_szInput);
	string output();
	State* getBeginningState();
	State* getFinishState();
	string getEdgeName();
	void setBeginningState(State p_stBeginning);
	void setFinishState(State p_stFinish);
	void setEdgeName(string p_szEdge);


};

#endif /* FSA_TRANSITION_HPP_ */
