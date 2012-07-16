/*
 * Transition.cpp
 *
 *  Created on: May 25, 2012
 *      Author: fabiani
 */

#include "FSA_Transition.hpp"
#include "FSA_State.hpp"
#include<string>
#include<cstring>

/*Constructor*/
Transition::Transition(State p_stBeginning, State p_stFinish, string p_szEdge)
{

	 this->stBeginning = p_stBeginning;
	 this->stFinish = p_stFinish;
	 this->szEdge = p_szEdge;
}


 /*Erweiterung
 Transition::Transition(string input)
 {
	 char *pstr,*pTeilString;
	 pstr = new char [input.size()+1];
	 strcpy(pstr,input.c_str());
	 pTeilString = strtok(pstr," ");
	 //pInput sind die drei Teile des Input strings, durch " " von einander getrennt
	 char *pInput[3];
	 for(int idx=0; idx<3;idx++)
	 {
		 pInput[idx]= pTeilString;
		 pTeilString = strtok(NULL, " ");
	 }
 //begining = new State(string(pInput[0]));		//ALT
 //finish = new State(pInput[2]);
 // edge = pInput[1];
											//NEU
	string pInput0, pInput1, pInput2;		// change char *Array[] to string
	pInput0 = pInput[0];					// is needed to use funktion Transition
	pInput1 = pInput[1];					//
	pInput2 = pInput[2];					//

	begining = State(pInput0);
	finish = State(pInput2);
	edge = pInput1;

 transitionCount++;
 }
 */

 /* Output of one transition
  *
  * it gives a string with the predefined structure "startState edge finalState"*/
string Transition::output(){
	string result;
	result = stBeginning.szName + " " + szEdge + " " + stFinish.szName;
	return result;

}

State* Transition::getBeginningState()
{
	return &stBeginning;
}
State* Transition::getFinishState()
{
	return &stFinish;
}
string Transition::getEdgeName()
{
	return szEdge;
}

void Transition::setBeginningState(State p_stBeginning) {
	this->stBeginning = p_stBeginning;
}

void Transition::setFinishState(State p_stFinish) {
	this->stFinish = p_stFinish;
}

void Transition::setEdgeName(string p_szEdge) {
	this->szEdge = p_szEdge;
}


