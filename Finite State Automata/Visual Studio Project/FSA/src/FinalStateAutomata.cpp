/*
 * FinalStateAutomata.cpp
 *
 *  Created on: May 25, 2012
 *      Author: fabiani
 */

#include "FinalStateAutomata.hpp"
#include<string>
#include<cstring>
#include<iostream>
#include<fstream>

using namespace std;

/* number of States and Transitions that can be build for this final state automata
 * so final state automata can save listLength Sate and listLength Transitions*/
int listLength = 100;
int FinalStateAutomata::automataStateCount =0; 		// counts the number of states, added to FSA
int FinalStateAutomata::automataTransitionCount =0;	// counts the number of transition, added to FSA

/* Constructor for FSA*/
FinalStateAutomata :: FinalStateAutomata()
{

	stateList = new State* [listLength];			// a list of element state, including all states of FSA
	transitionList = new Transition* [listLength];	// a list of element transition, including all transitions of FSA
	for(int i=0; i<listLength; i++)					// initialisation
		{
			stateList[i] = NULL;
			transitionList[i] = NULL;
		}
}

/* Destructor for FSA*/
FinalStateAutomata::~FinalStateAutomata()
{
	for(int i=0; i<listLength; i++)
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
	delete transitionList;
}

/* Add a new state to FSA
 * Parameters: a string, containing the name of added state
 *
 * find the first empty place in list and store the new state there, increase couter, then return*/
void FinalStateAutomata::addState(string stateName)		
{
	State *newState = new State(stateName);

	for(int i=0; i<listLength; i++)
	{
		if(stateList[i] == NULL)
		{
			stateList[i] = newState;
			automataStateCount++;
			return;
		}

	}
	cout << "Statelist is full." << endl;
	delete newState;
}

/* Add a new state to FSA
 * Parameters: a state element, initialized in the calling class
 *
 * for explanation look at method above*/
void FinalStateAutomata::addState(State *stateName)
{

	for(int i=0; i<listLength; i++)
	{
		if(stateList[i] == NULL)
		{
			stateList[i] = stateName;
			automataStateCount++;
			return;
		}

	}
	cout << "Statelist is full." << endl;
	delete stateName;
}
/* Remove state from FSA
 * Parameters: a string, containing the name of removable state */
void FinalStateAutomata::removeState(string stateName)		
{
	/* search State with parameters name in stateList, by checking only the elements, that aren't empty,
	 * when found the element free it and set it to null afterwards, so that it can be reused, decrease
	 * counter*/
	for(int i = 0; i< listLength;i++)
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

	}
	/* Cause a state has been removed, it is necessary, that you remove all transitions, that uses
	 * this state, same way as removing the state*/
	for (int i = 0;i<listLength;i++)
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
	}
}

/* Output of all states
 *
 * for each state element in stateList, that isn't null, output the state, meaning giving it name
 * to console */
void FinalStateAutomata::outputStateList( )
{
	cout<<"StateList:"<< endl;
	for(int idx=0; idx<listLength; idx++)
	{
		if(stateList[idx]!=NULL)
		{
			cout << stateList[idx]->output() << endl;
		}
	}
}

/* Output the names of all startStates
 *
 * for each state element in stateList, that isn't null, check there property of startState,
 * if it's true, then output there name on console*/
void FinalStateAutomata::getStartState()
{
	cout<<endl;
	cout<<"Start States:"<< endl;
	for (int i = 0; i<listLength;i++)
	{
		if(stateList[i]!= NULL)
		{
			if(stateList[i]->startState == true)
			{
				cout << stateList[i]->output() << endl;
			}
		}

	}
	cout<<endl;
}

/* Output the names of all finalStates
 *
 * for each state element in stateList, that isn't null, check there property of startState,
 * if it's true, then output there name on console*/
void FinalStateAutomata::getFinalState()
{
	cout<<endl;
	cout<<"Final States:"<< endl;
	for (int i = 0; i<listLength;i++)
	{
		if(stateList[i]!= NULL)
		{
			if(stateList[i]->finalState == true)
			{
				cout << stateList[i]->output() << endl;
			}
		}

	}
	cout<<endl;
}

/* Add a transition
 * Parameters: 3 strings, containing the state, the transition starts with (beginingState),
 * the name of connection between the two states (edge)
 * and the state, the transition ends with(finalState)*/
void FinalStateAutomata::addTransition(string beginingState,string edge, string finalState)
{
	bool begining = false;
	bool final = false;
	State *pBegining;
	State *pFinal;
	// check whether the states off added transition still exist, if one state exist, set it boolean to true
	for(int i=0; i<listLength; i++)
		{
			if(stateList[i] != NULL)
			{
				if(stateList[i]->name ==beginingState)
					{
						begining = true;
						pBegining = stateList[i];
					}
				if(stateList[i]->name == finalState)
				{
					final = true;
					pFinal = stateList[i];
				}
			}
		}
	// if the states doesn't exist, add them to the FSA, cause we don't want a transition added that never can be used
	if(begining == false)
	{
		addState(beginingState);
	}
	if (final == false)
	{
		addState(finalState);
	}
	/* if one or both states didn't exist and had to been added, then recursively repeat the
	 * addTransition method with the same values, so that the states can be found in stateList now,
	 * so you don't want to add two transition so return after recursively repetition
	*/
	if(begining== false || final == false)
	{
		addTransition(beginingState, edge, finalState);
		return;
	}
	/* after both states had been found in transition list start adding the transition and storing it
	 * at the first empty place of transitionListk, so with the method implemented till now it's possible
	 * to save one transition more than once, that's maybe critical and maybe has to be fixed*/
	Transition *newTransition = new Transition(*pBegining,*pFinal,edge);

	for(int i=0; i<listLength; i++)
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

}

/* Add a transition
 * Parameters: a string containing the transition as following "beginningState edge finalState"
 *
 * deviding the parameters string into three strings for geting the startState, edge and finalState,
 * then using the method above for adding a new transition to transitionList, managing strings is a bit
 * complicated by C++*/
void FinalStateAutomata::addTransition(string input)
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
void FinalStateAutomata::removeTransition(string beginingState,string edge, string finalState)
{
	for(int i = 0; i< listLength;i++)
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
	}
}

/* Output of all transitions
 *
 * for each transition element in transitionList, that isn't null, output the transition,
 * meaning giving a string, structured like "starState edge finalState" to console*/
void FinalStateAutomata::outputTransitionList( )
{
	cout<<"TransitionList:"<< endl;
	for(int idx=0; idx<listLength; idx++)
	{
		if(transitionList[idx]!=NULL)
		{
			cout << transitionList[idx]->output() << endl;
		}

	}
}

void FinalStateAutomata::read(string p_szFileName)
{
	ifstream ifsFile;
	ifsFile.open(p_szFileName.c_str(), ios.in);
	string szLine;
	bool bStates;
	bool bTransitions;
  
	while(getline(ifsFile, szLine))
	{
	if(strcmp(szLine.c_str(), "<States>")) {
		bStates = true;
    }
    if(strcmp(szLine.c_str(), "</States>")) {
		bStates = false;
    }
    if(strcmp(szLine.c_str(), "<Transitions>")) {
		bTransitions = true;
    }
  }
}

void FinalStateAutomata::write(string p_szFileName)
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

	for(int idx=0; idx<State::stateCount; idx++)
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
	}
	  
	ofsFile << "</States>\n";

	if(stateStart != NULL) {
		ofsFile << "<StartState>\n";
		ofsFile << stateStart->name << endl;
		ofsFile << "</StartState>\n";
	}
	
	if(stateFinal != NULL) {
		ofsFile << "<FinalState\n";
		ofsFile << stateFinal->name << endl;
		ofsFile << "</FinalState>\n";
	}

	ofsFile << "<Transitions>\n";
	  
	for(int idx=0; idx<Transition.transitionCount; idx++)
	{
		if(transitionList[idx] == NULL) {
			continue;
		}
		ofsFile << transitionList[idx]->output() << endl;
	}

	ofsFile << "</Transitions>\n";
	  
	ofsFile.close();
}

/* Testing an edge
 * Parameters: a string containing the name of the edge, that has to be tested
 *
 * for each transition element in transitionList, that isn't null, comparing there edge to the
 * parameter, if it matches, output the transition to console*/
void FinalStateAutomata::testEdge(string testEdge)
{
	cout<<endl;
	cout<<"Following transitions include the edge '"<< testEdge <<"':"<<endl;
	for (int i=0; i<listLength; i++)
	{
		if(transitionList[i]!= NULL)
		{
			if (transitionList[i]->edge == testEdge)
			{
				cout << transitionList[i]->output() << endl;
			}
		}
	}
	cout<<endl;
}



