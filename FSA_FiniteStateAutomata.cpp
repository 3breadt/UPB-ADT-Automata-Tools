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

/* number of States and Transitions that can be build for this final state automata
 * so final state automata can save listLength Sate and listLength Transitions*/
int listLength = 100;

/* Constructor for FSA*/
FiniteStateAutomata :: FiniteStateAutomata()
{

	/*stateList = new State* [listLength];			// a list of element state, including all states of FSA
	transitionList = new Transition* [listLength];	// a list of element transition, including all transitions of FSA
	for(int i=0; i<listLength; i++)					// initialisation
		{
			stateList[i] = NULL;
			transitionList[i] = NULL;
		}*/
}

/* Destructor for FSA*/
FiniteStateAutomata::~FiniteStateAutomata()
{
	/*for(int i=0; i<listLength; i++)
		{
			if(stateList[i]!= NULL)				// Checking value of each stateList element for it's existing, nearly each method has to do this check
			{
				delete stateList[i];			// free the lists element one by one
			}
			if(transitionList[i] != NULL)
			{
				delete transitionList[i];
			}
		}
	delete stateList;
	delete transitionList;*/

	vecStateList.clear();
	vecTransitionList.clear();

	/*
	int iStateListSize = vecStateList.size();
	int iTransitionListSize = vecTransitionList.size();


	for(std::vector<State>::iterator it = vecStateList.begin(); it != vecStateList.end(); ++it) {
		delete *it;
	}

	for(std::vector<Transition>::iterator it = vecTransitionList.begin(); it != vecTransitionList.end(); ++it) {
		delete *it;
	}

	delete vecStateList;
	delete vecTransitionList;*/

}

/* Add a new state to FSA
 * Parameters: a string, containing the name of added state
 *
 * find the first empty place in list and store the new state there, increase couter, then return*/
void FiniteStateAutomata::addState(string stateName)		
{
	State *newState = new State(stateName);

	addState(newState);

	/*for(int i=0; i<listLength; i++)
	{
		if(stateList[i] == NULL)
		{
			stateList[i] = newState;
			automataStateCount++;
			return;
		}

	}
	cout << "Statelist is full." << endl;
	delete newState;*/
}

/* Add a new state to FSA
 * Parameters: a state element, initialized in the calling class
 *
 * for explanation look at method above*/
void FiniteStateAutomata::addState(State *stateName)
{

	vecStateList.push_back(stateName);
	
	/*for(int i=0; i<listLength; i++)
	{
		if(stateList[i] == NULL)
		{
			stateList[i] = stateName;
			automataStateCount++;
			return;
		}

	}
	cout << "Statelist is full." << endl;
	delete stateName;*/
}
/* Remove state from FSA
 * Parameters: a string, containing the name of removable state */
void FiniteStateAutomata::removeState(string stateName)		
{

	for(std::vector<State*>::iterator it = vecStateList.begin(); it != vecStateList.end(); ++it) {
		if((*it)->name == stateName) {
			vecStateList.erase(it);
			break;
		}
	}

	/* search State with parameters name in stateList, by checking only the elements, that aren't empty,
	 * when found the element free it and set it to null afterwards, so that it can be reused, decrease
	 * counter*/
	/*for(int i = 0; i< listLength;i++)
	{
		if(stateList[i]!= NULL)							
		{
			if(stateList[i]->name == stateName)
			{
				delete stateList[i];
				stateList[i] = NULL;
				automataStateCount--;
			}
		}

	}*/
	/* Cause a state has been removed, it is necessary, that you remove all transitions, that uses
	 * this state, same way as removing the state*/
	/*for (int i = 0;i<listLength;i++)
	{
		if(transitionList[i]!= NULL)
		{
			if(transitionList[i]->begining.name == stateName || transitionList[i]->finish.name == stateName)
			{
				delete transitionList[i];
				transitionList[i] = NULL;
				automataTransitionCount--;
			}
		}
	}*/
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

	/*
	for(int idx=0; idx<listLength; idx++)
	{
		if(stateList[idx]!=NULL)
		{
			cout << stateList[idx]->output() << endl;
		}
	}*/
}

/* Output the names of all startStates
 *
 * for each state element in stateList, that isn't null, check there property of startState,
 * if it's true, then output there name on console*/
void FiniteStateAutomata::getStartState()
{
	cout<<endl;
	cout<<"Start State:"<< endl;

	for(std::vector<State*>::iterator it = vecStateList.begin(); it != vecStateList.end(); ++it) {
		if((*it)->startState == true) {
			cout << (*it)->output() << endl;
			break;
		}
	}
	/*
	for (int i = 0; i<listLength;i++)
	{
		if(stateList[i]!= NULL)
		{
			if(stateList[i]->startState == true)
			{
				cout << stateList[i]->output() << endl;
			}
		}

	}*/
	cout<<endl;
}

/** Output the names of all finalStates 
 *
 * for each state element in stateList, that isn't null, check there property of startState,
 * if it's true, then output there name on console*/
void FiniteStateAutomata::getFinalState()
{
	cout<<endl;
	cout<<"Final State:"<< endl;
	
	for(std::vector<State*>::iterator it = vecStateList.begin(); it != vecStateList.end(); ++it) {
		if((*it)->finalState == true) {
			cout << (*it)->output() << endl;
			break;
		}
	}
	
	/*for (int i = 0; i<listLength;i++)
	{
		if(stateList[i]!= NULL)
		{
			if(stateList[i]->finalState == true)
			{
				cout << stateList[i]->output() << endl;
			}
		}

	}*/
	cout<<endl;
}

/* Add a transition
 * Parameters: 3 strings, containing the state, the transition starts with (beginingState),
 * the name of connection between the two states (edge)
 * and the state, the transition ends with(finalState)*/
void FiniteStateAutomata::addTransition(string p_szBeginningState,string edge, string finalState)
{
	bool beginning = false;
	bool final = false;
	State *pBeginning;
	State *pFinal;
	// check whether the states off added transition still exist, if one state exist, set it boolean to true
	for(std::vector<State*>::iterator it = vecStateList.begin(); it != vecStateList.end(); ++it) {
		if((*it)->name == p_szBeginningState) {
			beginning = true;
			pBeginning = *it;
		}
		if((*it)->name == finalState) {
			final = true;
			pFinal = *it;
		}
	}
	
	/*for(int i=0; i<listLength; i++)
		{
			if(stateList[i] != NULL)
			{
				if(stateList[i]->name == p_szBeginningState)
					{
						beginning = true;
						pBeginning = stateList[i];
					}
				if(stateList[i]->name == finalState)
				{
					final = true;
					pFinal = stateList[i];
				}
			}
		}*/
	// if the states don't exist, add them to the FSA, cause we don't want a transition added that never can be used
	if(beginning == false)
	{
		addState(p_szBeginningState);
	}
	if (final == false)
	{
		addState(finalState);
	}
	/* if one or both states didn't exist and had to been added, then recursively repeat the
	 * addTransition method with the same values, so that the states can be found in stateList now,
	 * so you don't want to add two transition so return after recursively repetition
	*/
	if(beginning== false || final == false)
	{
		addTransition(p_szBeginningState, edge, finalState);
		return;
	}
	/* after both states had been found in transition list start adding the transition and storing it
	 * at the first empty place of transitionListk, so with the method implemented till now it's possible
	 * to save one transition more than once, that's maybe critical and maybe has to be fixed*/
	Transition *newTransition = new Transition(*pBeginning,*pFinal,edge);

	//for(std::vector<Transition*>::iterator it = vecTransitionList.begin(); it != vecTransitionList.end(); ++it) {
		vecTransitionList.push_back(newTransition);
	//}

	/*for(int i=0; i<listLength; i++)
	{
		if(transitionList[i] == NULL)
		{
			transitionList[i] = newTransition;
			automataTransitionCount++;
			return;
		}
	}
	cout << "Transitionlist is full." << endl;
	delete newTransition;
	*/
}

/* Add a transition
 * Parameters: a string containing the transition as following "beginningState edge finalState"
 *
 * deviding the parameters string into three strings for geting the startState, edge and finalState,
 * then using the method above for adding a new transition to transitionList, managing strings is a bit
 * complicated by C++*/
void FiniteStateAutomata::addTransition(string input)
{
	string pInput0, pInput1, pInput2;
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
	/* change char *Array[] to stringis needed to use funktion Transition*/
	pInput0 = pInput[0];
	pInput1 = pInput[1];
	pInput2 = pInput[2];

	addTransition(pInput0,pInput1,pInput2);
}

/* Remove a transition
 * Parameters: 3 strings, conteining the beginning state(explanation at function "addtransition"),
 * the edge and the finalState
 *
 * search transition with parameters in transitionList, by checking only the elements, that aren't empty,
 * when found the element free it and set it to null afterwards, so that it can be reused, decrease
 * counter (all three parameters must match*/
void FiniteStateAutomata::removeTransition(string beginingState,string edge, string finalState)
{

	for(std::vector<Transition*>::iterator it = vecTransitionList.begin(); it != vecTransitionList.end(); ++it) {
		if((*it)->begining.name == beginingState && (*it)->finish.name == finalState && (*it)->edge == edge) {
			vecTransitionList.erase(it);
		}
	}

	/*for(int i = 0; i< listLength;i++)
	{
		if(transitionList[i] != NULL)
		{
			if(transitionList[i]->begining.name == beginingState
				&& transitionList[i]->finish.name == finalState
				&& transitionList[i]->edge == edge)
			{
				delete transitionList[i];
				transitionList[i] = NULL;
				automataTransitionCount--;
			}
		}
	}*/
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

	/*for(int idx=0; idx<listLength; idx++)
	{
		if(transitionList[idx]!=NULL)
		{
			cout << transitionList[idx]->output() << endl;
		}

	}*/
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
			FiniteStateAutomata::addState(szLine);
			continue;
		}
		if(bTransitions) {
			FiniteStateAutomata::addTransition(szLine);
			continue;
		}
		if(bFinalState) {
			bool bFoundState = false;
			for(std::vector<State*>::iterator it = vecStateList.begin(); it != vecStateList.end(); ++it) {
				if((*it)->name == szLine) {
					(*it)->setFinalState();
					bFoundState = true;
					break;
				}
			}
			if(!bFoundState) {
				State *newState = new State(szLine);
				newState->finalState = true;
				addState(newState);
			}
		}
		if(bStartState) {
			bool bFoundState = false;
			for(std::vector<State*>::iterator it = vecStateList.begin(); it != vecStateList.end(); ++it) {
				if((*it)->name == szLine) {
					(*it)->setStartState();
					bFoundState = true;
					break;
				}
			}
			if(!bFoundState) {
				State *newState = new State(szLine);
				newState->startState = true;
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
		
		ofsFile << (*it)->name << endl;

		if((*it)->startState) {
			stateStart = *it;
		}
	
		if((*it)->finalState) {
			stateFinal = *it;
		}
	}

	/*for(int idx=0; idx<State::stateCount; idx++)
	{
		if(stateList[idx] == NULL) {
			continue;
		}
		ofsFile << stateList[idx]->name << endl;

		if(stateList[idx]->startState) {
			stateStart = stateList[idx];
		}

		if(stateList[idx]->finalState) {
			stateFinal = stateList[idx];
		}
	}*/
	  
	ofsFile << "</States>\n";

	if(stateStart != NULL) {
		ofsFile << "<StartState>\n";
		ofsFile << stateStart->name << endl;
		ofsFile << "</StartState>\n";
	}
	
	if(stateFinal != NULL) {
		ofsFile << "<FinalState>\n";
		ofsFile << stateFinal->name << endl;
		ofsFile << "</FinalState>\n";
	}

	ofsFile << "<Transitions>\n";

	for(std::vector<Transition*>::iterator it = vecTransitionList.begin(); it != vecTransitionList.end(); ++it) {
		ofsFile << (*it)->output() << endl;
	}
	  
	/*for(int idx=0; idx<Transition::transitionCount; idx++)
	{
		if(transitionList[idx] == NULL) {
			continue;
		}
		ofsFile << transitionList[idx]->output() << endl;
	}*/

	ofsFile << "</Transitions>\n";
	  
	ofsFile.close();
}

/* Testing an edge
 * Parameters: a string containing the name of the edge, that has to be tested
 *
 * for each transition element in transitionList, that isn't null, comparing there edge to the
 * parameter, if it matches, output the transition to console*/
void FiniteStateAutomata::testEdge(string testEdge)
{
	cout<<endl;
	cout<<"Following transitions include the edge '"<< testEdge <<"':"<<endl;
	
	for(std::vector<Transition*>::iterator it = vecTransitionList.begin(); it != vecTransitionList.end(); ++it) {
		if((*it)->edge == testEdge) {
			cout << (*it)->output() << endl;
		}
	}
	
	/*for (int i=0; i<listLength; i++)
	{
		if(transitionList[i]!= NULL)
		{
			if (transitionList[i]->edge == testEdge)
			{
				cout << transitionList[i]->output() << endl;
			}
		}
	}*/
	cout<<endl;
}



