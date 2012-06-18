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



int Transition::transitionCount = 0;		// Counts the number of created transition, isn't necessary till now
/*Constructor*/
Transition::Transition(State begining, State finish, string edge)
{

	 this->begining = begining;
	 this->finish = finish;
	 this->edge = edge;
	 transitionCount++;
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
	result = begining.name + " " + edge + " " + finish.name;
	return result;

}




