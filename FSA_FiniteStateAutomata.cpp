/*
 * FinalStateAutomata.cpp
 *
 *  Created on: May 25, 2012
 *      Author: fabiani
 */

#include "FSA_FiniteStateAutomata.hpp"
#include<string>
#include<cstring>
#include<iostream>
#include<fstream>
#include<vector>

using namespace std;

/* Constructor for FSA*/
FiniteStateAutomata :: FiniteStateAutomata()
{
}

/* Destructor for FSA*/
FiniteStateAutomata::~FiniteStateAutomata()
{
	vecStateList.clear();
	vecTransitionList.clear();
}

/* Add a new state to FSA
 * Parameters: a string, containing the name of added state
 *
 * find the first empty place in list and store the new state there, increase couter, then return*/
void FiniteStateAutomata::addState(string p_szStateName)		
{
	State *stNewState = new State(p_szStateName);
	addState(stNewState);
}

/* Add a new state to FSA
 * Parameters: a state element, initialized in the calling class
 *
 * for explanation look at method above*/
void FiniteStateAutomata::addState(State *p_stNewState)
{
	vecStateList.push_back(p_stNewState);
}
/* Remove state from FSA
 * Parameters: a string, containing the name of removable state */
void FiniteStateAutomata::removeState(string p_szStateName)		
{

	for(std::vector<State*>::iterator it = vecStateList.begin(); it != vecStateList.end(); ++it) {
		if((*it)->szName == p_szStateName) {
			vecStateList.erase(it);
			break;
		}
	}
}

/* Output of all states
 *
 * for each state element in stateList, that isn't null, output the state, meaning giving it name
 * to console */
void FiniteStateAutomata::outputStateList( )
{
	cout<<"StateList:"<< endl;

	for(std::vector<State*>::iterator it = vecStateList.begin(); it != vecStateList.end(); ++it) {
		cout << (*it)->output() << endl;
	}
}

/* Output the names of all startStates
 *
 * for each state element in stateList, that isn't null, check there property of startState,
 * if it's true, then output there name on console*/
void FiniteStateAutomata::printStartState()
{
	cout<<endl;
	cout<<"Start State:"<< endl;

	for(std::vector<State*>::iterator it = vecStateList.begin(); it != vecStateList.end(); ++it) {
		if((*it)->bStartState == true) {
			cout << (*it)->output() << endl;
			break;
		}
	}
	cout<<endl;
}

/** Output the names of all finalStates 
 *
 * for each state element in stateList, that isn't null, check there property of startState,
 * if it's true, then output there name on console*/
void FiniteStateAutomata::printFinalState()
{
	cout<<endl;
	cout<<"Final State:"<< endl;
	
	for(std::vector<State*>::iterator it = vecStateList.begin(); it != vecStateList.end(); ++it) {
		if((*it)->bFinalState == true) {
			cout << (*it)->output() << endl;
			break;
		}
	}
	cout<<endl;
}

bool FiniteStateAutomata::bStateExists(string p_szName)
{
	for(std::vector<State*>::iterator it = vecStateList.begin(); it != vecStateList.end(); ++it) {
		if((*it)->szName == p_szName) {
			return true;
		}
	}
	return false;
}

State* FiniteStateAutomata::getState(string p_szName)
{
	for(std::vector<State*>::iterator it = vecStateList.begin(); it != vecStateList.end(); ++it) {
		if((*it)->szName == p_szName) {
			return *it;
		}
	}
	return NULL;
}

State* FiniteStateAutomata::getStartState()
{
	for(std::vector<State*>::iterator it = vecStateList.begin(); it != vecStateList.end(); ++it) {
		if((*it)->bStartState == true) {
			return *it;
		}
	}
	return NULL;
}

State* FiniteStateAutomata::getFinalState()
{
	for(std::vector<State*>::iterator it = vecStateList.begin(); it != vecStateList.end(); ++it) {
		if((*it)->bFinalState == true) {
			return *it;
		}
	}
	return NULL;
}

vector<State*>* FiniteStateAutomata::getStateList()
{
	return &vecStateList;
}

/* Add a transition
 * Parameters: 3 strings, containing the state, the transition starts with (beginingState),
 * the name of connection between the two states (edge)
 * and the state, the transition ends with(finalState)*/
void FiniteStateAutomata::addTransition(string p_szBeginningState, string p_szEdge, string p_szFinalState)
{
	bool bBeginning = false;
	bool bFinal = false;
	State *pBeginning;
	State *pFinal;
	// check whether the states off added transition still exist, if one state exist, set it boolean to true
	for(std::vector<State*>::iterator it = vecStateList.begin(); it != vecStateList.end(); ++it) {
		if((*it)->szName == p_szBeginningState) {
			bBeginning = true;
			pBeginning = *it;
		}
		if((*it)->szName == p_szFinalState) {
			bFinal = true;
			pFinal = *it;
		}
	}
	
	// if the states don't exist, add them to the FSA, cause we don't want a transition added that never can be used
	if(bBeginning == false)
	{
		addState(p_szBeginningState);
	}
	if (bFinal == false)
	{
		addState(p_szFinalState);
	}
	/* if one or both states didn't exist and had to been added, then recursively repeat the
	 * addTransition method with the same values, so that the states can be found in stateList now,
	 * so you don't want to add two transition so return after recursively repetition
	*/
	if(bBeginning== false || bFinal == false)
	{
		addTransition(p_szBeginningState, p_szEdge, p_szFinalState);
		return;
	}
	/* after both states had been found in transition list start adding the transition and storing it
	 * at the first empty place of transitionListk, so with the method implemented till now it's possible
	 * to save one transition more than once, that's maybe critical and maybe has to be fixed*/
	Transition *newTransition = new Transition(*pBeginning, *pFinal, p_szEdge);

	vecTransitionList.push_back(newTransition);
}

/* Add a transition
 * Parameters: a string containing the transition as following "beginningState edge finalState"
 *
 * deviding the parameters string into three strings for geting the startState, edge and finalState,
 * then using the method above for adding a new transition to transitionList, managing strings is a bit
 * complicated by C++*/
void FiniteStateAutomata::addTransition(string p_szInput)
{
	string szBeginningState, szEdge, szFinalState;
	char *pstr,*pTeilString;
	pstr = new char [p_szInput.size()+1];
	strcpy(pstr,p_szInput.c_str());
	pTeilString = strtok(pstr," ");
	//pInput sind die drei Teile des Input strings, durch " " von einander getrennt
	char *pInput[3];
	for(int idx=0; idx<3;idx++)
		 {
			 pInput[idx]= pTeilString;
			 pTeilString = strtok(NULL, " ");
		 }
	/* change char *Array[] to stringis needed to use funktion Transition*/
	szBeginningState = pInput[0];
	szEdge = pInput[1];
	szFinalState = pInput[2];

	addTransition(szBeginningState, szEdge, szFinalState);
}

/* Remove a transition
 * Parameters: 3 strings, conteining the beginning state(explanation at function "addtransition"),
 * the edge and the finalState
 *
 * search transition with parameters in transitionList, by checking only the elements, that aren't empty,
 * when found the element free it and set it to null afterwards, so that it can be reused, decrease
 * counter (all three parameters must match*/
void FiniteStateAutomata::removeTransition(string p_szBeginningState, string p_szEdge, string p_szFinalState)
{

	for(std::vector<Transition*>::iterator it = vecTransitionList.begin(); it != vecTransitionList.end(); ++it) {
		if((*it)->stBeginning.szName == p_szBeginningState && (*it)->stFinish.szName == p_szFinalState && (*it)->szEdge == p_szEdge) {
			vecTransitionList.erase(it);
		}
	}
}

/* Output of all transitions
 *
 * for each transition element in transitionList, that isn't null, output the transition,
 * meaning giving a string, structured like "starState edge finalState" to console*/
void FiniteStateAutomata::outputTransitionList( )
{
	cout<<"TransitionList:"<< endl;

	for(std::vector<Transition*>::iterator it = vecTransitionList.begin(); it != vecTransitionList.end(); ++it) {
		cout << (*it)->output() << endl;
	}
}

void FiniteStateAutomata::read(string p_szFileName)
{
	ifstream ifsFile;
	ifsFile.open(p_szFileName.c_str(), ios::in);
	string szLine;
	bool bStates = false;
	bool bTransitions = false;
	bool bFinalState = false;
	bool bStartState = false;
  
	while(getline(ifsFile, szLine))
	{
		if(szLine == "<States>") {
		bStates = true;
		continue;
		}
		if(szLine == "</States>") {
			bStates = false;
			continue;
		}
		if(szLine == "<Transitions>") {
			bTransitions = true;
			continue;
		}
		if(szLine == "</Transitions>") {
			bTransitions = false;
			continue;
		}
		if(szLine == "<FinalState>") {
			bFinalState = true;
			continue;
		}
		if(szLine == "</FinalState>") {
			bFinalState = false;
			continue;
		}
		if(szLine == "<StartState>") {
			bStartState = true;
			continue;
		}
		if(szLine == "</StartState>") {
			bStartState = false;
			continue;
		}
		if(bStates) {
			if(!bStateExists(szLine)) {
				FiniteStateAutomata::addState(szLine);
			}
			continue;
		}
		if(bTransitions) {
			FiniteStateAutomata::addTransition(szLine);
			continue;
		}
		if(bFinalState) {
			bool bFoundState = false;
			for(std::vector<State*>::iterator it = vecStateList.begin(); it != vecStateList.end(); ++it) {
				if((*it)->szName == szLine) {
					(*it)->setFinalState();
					bFoundState = true;
					break;
				}
			}
			if(!bFoundState) {
				State *newState = new State(szLine);
				newState->bFinalState = true;
				addState(newState);
			}
		}
		if(bStartState) {
			bool bFoundState = false;
			for(std::vector<State*>::iterator it = vecStateList.begin(); it != vecStateList.end(); ++it) {
				if((*it)->szName == szLine) {
					(*it)->setStartState();
					bFoundState = true;
					break;
				}
			}
			if(!bFoundState) {
				State *newState = new State(szLine);
				newState->bStartState = true;
				addState(newState);
			}
		}
  }
}

void FiniteStateAutomata::write(string p_szFileName)
{
	ofstream ofsFile;
	State *stateStart = NULL;
	State *stateFinal = NULL;

	ofsFile.open(p_szFileName.c_str());

	if(!ofsFile.is_open()) {
		cout << "ERROR: Couldn't access file for writing.";
		return;
	}
	  
	ofsFile << "<States>\n";

	for(std::vector<State*>::iterator it = vecStateList.begin(); it != vecStateList.end(); ++it) {
		
		ofsFile << (*it)->szName << endl;

		if((*it)->bStartState) {
			stateStart = *it;
		}
	
		if((*it)->bFinalState) {
			stateFinal = *it;
		}
	}
	  
	ofsFile << "</States>\n";

	if(stateStart != NULL) {
		ofsFile << "<StartState>\n";
		ofsFile << stateStart->szName << endl;
		ofsFile << "</StartState>\n";
	}
	
	if(stateFinal != NULL) {
		ofsFile << "<FinalState>\n";
		ofsFile << stateFinal->szName << endl;
		ofsFile << "</FinalState>\n";
	}

	ofsFile << "<Transitions>\n";

	for(std::vector<Transition*>::iterator it = vecTransitionList.begin(); it != vecTransitionList.end(); ++it) {
		ofsFile << (*it)->output() << endl;
	}
	
	ofsFile << "</Transitions>\n";
	  
	ofsFile.close();
}

/* Testing an edge
 * Parameters: a string containing the name of the edge, that has to be tested
 *
 * for each transition element in transitionList, that isn't null, comparing there edge to the
 * parameter, if it matches, output the transition to console*/
void FiniteStateAutomata::testEdge(string p_szTestEdge)
{
	cout<<endl;
	cout<<"Following transitions include the edge '"<< p_szTestEdge <<"':"<<endl;
	
	for(std::vector<Transition*>::iterator it = vecTransitionList.begin(); it != vecTransitionList.end(); ++it) {
		if((*it)->szEdge == p_szTestEdge) {
			cout << (*it)->output() << endl;
		}
	}
	cout<<endl;
}



