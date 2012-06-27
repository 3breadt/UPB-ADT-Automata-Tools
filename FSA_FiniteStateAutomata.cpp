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
	vecFinalStates.clear();
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
			//break;
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

vector<State*>* FiniteStateAutomata::getStateList()
{
	return &vecStateList;
}

vector<State*>* FiniteStateAutomata::getFinalStates()
{
	// remove all states which are not final anymore
	FiniteStateAutomata::removeFinalStates();

	// search the state list for all states that are final, add them to the final states vector
	for(std::vector<State*>::iterator it = vecStateList.begin(); it != vecStateList.end(); ++it) {
		if((*it)->bFinalState == true) {
			// only add if they're not in the vector already
			if(!FiniteStateAutomata::isInFinalStatesVector((*it)->szName)) {
				vecFinalStates.push_back(*it);
			}
		}
	}
	return &vecFinalStates;
}

void FiniteStateAutomata::removeFinalStates()
{
	// remove all states which are not final anymore
	for(std::vector<State*>::iterator it = vecFinalStates.begin(); it != vecFinalStates.end(); ++it) {
		if((*it)->bFinalState == false) {
			vecFinalStates.erase(it);
			FiniteStateAutomata::removeFinalStates();
			break;
		}
	}
}

/**
 * Private function for checking if a final state is in the final states vector.
 * @param p_szStateName Name of the final state to check.
 * @return True if the state is in the vector, false if not.
 */
bool FiniteStateAutomata::isInFinalStatesVector(string p_szStateName)
{
	for(std::vector<State*>::iterator it = vecFinalStates.begin(); it != vecFinalStates.end(); ++it) {
		if((*it)->szName == p_szStateName) {
			return true;
		}
	}
	return false;
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

void FiniteStateAutomata::addTransition(State *p_stBeginningState, string p_szEdge, State *p_stFinalState)
{
	/*bool bBeginning = false;
	bool bFinal = false;
	State *pBeginning;
	State *pFinal;
	// check whether the states off added transition still exist, if one state exist, set it boolean to true
	for(std::vector<State*>::iterator it = vecStateList.begin(); it != vecStateList.end(); ++it) {
		if((*it)->szName == p_stBeginningState->szName) {
			bBeginning = true;
			pBeginning = *it;
		}
		if((*it)->szName == p_stFinalState->szName) {
			bFinal = true;
			pFinal = *it;
		}
	}
	
	// if the states don't exist, add them to the FSA, cause we don't want a transition added that never can be used
	if(bBeginning == false)
	{
		addState(p_stBeginningState);
	}
	if (bFinal == false)
	{
		addState(p_stFinalState);
	}*/
	/* if one or both states didn't exist and had to been added, then recursively repeat the
	 * addTransition method with the same values, so that the states can be found in stateList now,
	 * so you don't want to add two transition so return after recursively repetition
	*/
	/*if(bBeginning == false || bFinal == false)
	{
		addTransition(p_stBeginningState, p_szEdge, p_stFinalState);
		return;
	}*/
	/* after both states had been found in transition list start adding the transition and storing it
	 * at the first empty place of transitionListk, so with the method implemented till now it's possible
	 * to save one transition more than once, that's maybe critical and maybe has to be fixed*/
	Transition *newTransition = new Transition(*p_stBeginningState, *p_stFinalState, p_szEdge);

	vecTransitionList.push_back(newTransition);
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

vector<Transition*>* FiniteStateAutomata::getTransitions()
{
	return &vecTransitionList;
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
		if(szLine == "<FinalStates>") {
			bFinalState = true;
			continue;
		}
		if(szLine == "</FinalStates>") {
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
					(*it)->setFinalState(true);
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
					(*it)->setStartState(true);
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
	}
	  
	ofsFile << "</States>\n";

	if(stateStart != NULL) {
		ofsFile << "<StartState>\n";
		ofsFile << stateStart->szName << endl;
		ofsFile << "</StartState>\n";
	}
	
	ofsFile << "<FinalStates>\n";

	for(std::vector<State*>::iterator it = vecFinalStates.begin(); it != vecFinalStates.end(); ++it) {
		
		ofsFile << (*it)->szName << endl;
	}
	ofsFile << "</FinalStates>\n";

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

FiniteStateAutomata* FiniteStateAutomata::fsaConvertNEAtoDEA()
{
	FiniteStateAutomata *fsaDEA = new FiniteStateAutomata();
	State *stStartState = this->getStartState();
	vector<string> vecEdges = getEdgesFromTransitionList();
	vector<StateConverter*> vecStateConverters;

	State *stNewStartState = new State();
	stNewStartState->szName = "S0";
	stNewStartState->bFinalState = stStartState->bFinalState;
	stNewStartState->bStartState = stStartState->bStartState;

	StateConverter *scNewStartState = new StateConverter(stNewStartState);
	scNewStartState->addReferencedState(stStartState);
	scNewStartState->checkForFinalState();
	vecStateConverters.push_back(scNewStartState);

	int idx = 0;
	int iStateCounter = 1;
	while(vecStateConverters.size() > idx) {
		for(std::vector<string>::iterator itedge = vecEdges.begin(); itedge != vecEdges.end(); ++itedge) {

			vector<State*>* vecTargetStates = new vector<State*>();
			for(std::vector<State*>::iterator itref = vecStateConverters[idx]->vecReferencedStates.begin(); itref != vecStateConverters[idx]->vecReferencedStates.end(); ++itref) {
				getTargetStatesForEdge(*itedge, *itref, vecTargetStates);
			}
			
			std::stringstream szstream;
			szstream << "S" << iStateCounter;
			string szStateName = szstream.str();
			StateConverter *scNewStateConverter = new StateConverter(szStateName, vecTargetStates);
			scNewStateConverter->checkForFinalState();
			if(!isInStateConverterList(scNewStateConverter, &vecStateConverters) && (vecTargetStates->size() > 0)) {
				vecStateConverters.push_back(scNewStateConverter);
				iStateCounter++;
			}
			StateConverter* scTargetStateConverter = getEqualStateConverterFromConverterList(scNewStateConverter, &vecStateConverters);
			if(scTargetStateConverter != NULL) {
				fsaDEA->addTransition(vecStateConverters[idx]->getConvertedState(), *itedge, scTargetStateConverter->getConvertedState());
			}
		}
		idx++;
	}

	setStateListFromStateConverterList(fsaDEA->getStateList(), &vecStateConverters);
	fsaDEA->getFinalStates();
	return fsaDEA;
}

void FiniteStateAutomata::setStateListFromStateConverterList(vector<State*>* p_vecStateList, vector<StateConverter*>* p_vecStateConverterList)
{
	for(std::vector<StateConverter*>::iterator itconv = p_vecStateConverterList->begin(); itconv != p_vecStateConverterList->end(); ++itconv) {
		p_vecStateList->push_back((*itconv)->getConvertedState());
	}
}

void FiniteStateAutomata::getTargetStatesForEdge(string p_szEdge, State* p_stStateToCheck, vector<State*>* p_vecTargetStates)
{
	for(std::vector<Transition*>::iterator ittrans = vecTransitionList.begin(); ittrans != vecTransitionList.end(); ++ittrans) {
		if((*ittrans)->getBeginningState()->output() == p_stStateToCheck->output() && (*ittrans)->getEdgeName() == p_szEdge) {
			p_vecTargetStates->push_back((*ittrans)->getFinishState());
		}
	}
}

bool FiniteStateAutomata::isInStateConverterList(StateConverter* p_scStateConverter, vector<StateConverter*>* p_vecStateConverterList)
{
	for(std::vector<StateConverter*>::iterator it = p_vecStateConverterList->begin(); it != p_vecStateConverterList->end(); ++it) {
		if(p_scStateConverter->getReferencedStates()->size() != (*it)->getReferencedStates()->size()) {
			continue;
		} else {
			if((*it)->equalsReferncedStates(p_scStateConverter)) {
				return true;
			}
		}
	}
	return false;
}

StateConverter* FiniteStateAutomata::getEqualStateConverterFromConverterList(StateConverter* p_scStateConverter, vector<StateConverter*>* p_vecStateConverterList)
{
	for(std::vector<StateConverter*>::iterator it = p_vecStateConverterList->begin(); it != p_vecStateConverterList->end(); ++it) {
		if(p_scStateConverter->getReferencedStates()->size() != (*it)->getReferencedStates()->size()) {
			continue;
		} else {
			if((*it)->equalsReferncedStates(p_scStateConverter)) {
				return *it;
			}
		}
	}
	return NULL;
}

vector<string> FiniteStateAutomata::getEdgesFromTransitionList()
{
	vector<string> vecEdges;
	for(std::vector<Transition*>::iterator it = vecTransitionList.begin(); it != vecTransitionList.end(); ++it) {
		bool bFound = false;
		string szEdge;
		if(vecEdges.empty()) {
			vecEdges.push_back((*it)->szEdge);
			continue;
		}
		for(std::vector<string>::iterator itedge = vecEdges.begin(); itedge != vecEdges.end(); itedge++) {
			szEdge = *itedge;
			if((*it)->szEdge == szEdge) {
				bFound = true;
			}
		}
		if(!bFound) {
			vecEdges.push_back((*it)->szEdge);
		}
	}
	return vecEdges;
}



