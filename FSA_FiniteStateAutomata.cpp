/**
 * FiniteStateAutomata.cpp
 *
 *  Created on: May 25, 2012
 *      Author: fabiani
 */

#include "FSA_FiniteStateAutomata.hpp"
#include "FSA_Group.hpp"
#include "FSA_GroupElement.hpp"
#include "RG_Grammar.h"
#include<string>
#include<cstring>
#include<iostream>
#include<fstream>
#include<vector>

using namespace std;

/** Constructor for FSA*/
FiniteStateAutomata :: FiniteStateAutomata()
{
}

/** Destructor for FSA*/
FiniteStateAutomata::~FiniteStateAutomata()
{
	vecStateList.clear();
	vecTransitionList.clear();
	vecFinalStates.clear();
}

/** 
 * Add a new state to FSA.
 * @param: p_szStateName Name of added state.
 * @author: fabiani, andreasb
 */
void FiniteStateAutomata::addState(string p_szStateName)		
{
	State *stNewState = new State(p_szStateName);
	addState(stNewState);
}

/** 
 * Add a new state to FSA.
 * @param *p_stNewState Pointer of type state direction to the added state.
 * @author fabiani, andreasb
 */
void FiniteStateAutomata::addState(State *p_stNewState)
{
	vecStateList.push_back(p_stNewState);
}
/** 
 * Remove state from FSA.
 * @param: p_szStateName Name of the removable state.
 * @author: fabiani,andreasb
 */
void FiniteStateAutomata::removeState(string p_szStateName)		
{

	for(std::vector<State*>::iterator it = vecStateList.begin(); it != vecStateList.end(); ++it) {
		if((*it)->szName == p_szStateName) {
			vecStateList.erase(it);
			break;
		}
	}
}

/** 
 * Output of all states.
 * @author fabiani, andreasb
 */
void FiniteStateAutomata::outputStateList( )
{
	cout<<"StateList:"<< endl;

	for(std::vector<State*>::iterator it = vecStateList.begin(); it != vecStateList.end(); ++it) {
		cout << (*it)->output() << endl;
	}
}

/** 
 * Output the names of all startStates
 * @author fabiani, andreasb
 */
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

/** 
 * Output the names of all finalStates .
 * @author fabiani, andreasb
 */
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

/**
 * Searches the state list for a state with the given name for existance.
 * @param p_szName Name of the state to search for.
 * @return True if a state with the given name exists in the state list, false if not.
 * @author skowelek, fabiani
 */
bool FiniteStateAutomata::bStateExists(string p_szName)
{
	for(std::vector<State*>::iterator it = vecStateList.begin(); it != vecStateList.end(); ++it) {
		if((*it)->szName == p_szName) {
			return true;
		}
	}
	return false;
}

/**
 * Searches the state list for a state with the given name, and returns a pointer to that state.
 * @param p_szName Name of the state to search for.
 * @return A pointer to the state if it has been found, NULL if not.
 * @author skowelek, fabiani
 */
State* FiniteStateAutomata::getState(string p_szName)
{
	for(std::vector<State*>::iterator it = vecStateList.begin(); it != vecStateList.end(); ++it) {
		if((*it)->szName == p_szName) {
			return *it;
		}
	}
	return NULL;
}

/**
 * Returns the start state of this automaton.
 * @return The start state of this automaton.
 * @author skowelek, fabiani
 */
State* FiniteStateAutomata::getStartState()
{
	for(std::vector<State*>::iterator it = vecStateList.begin(); it != vecStateList.end(); ++it) {
		if((*it)->bStartState == true) {
			return *it;
		}
	}
	return NULL;
}

/**
 * Returns the state vector.
 * @return The state vector.
 * @author skowelek, fabiani
 */
vector<State*>* FiniteStateAutomata::getStateList()
{
	return &vecStateList;
}

/**
 * Returns the final states vector. Additionally, it updates the vector on everytime by
 * calling FiniteStateAutomata::removeFinalStates to remove non-final states and checks
 * the state vector for final states that are not in the vector.
 * @return The final states vector.
 * @author skowelek
 */
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

/**
 * Removes all states from the final states vector which are not final (anymore).
 * @author skowelek
 */
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
 * @author skowelek
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

/** 
 * Add a transition to transitionlist.
 * @param p_szBeginningState Name of the first state of transition,
 *		  p_szEdge Name of the transition edge,
 *		  p_szFinalState Name of the second state of transition.
 * @author fabiani, andreasb
 */
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

/** 
 * Add a transition to transitionlist.
 * @param p_szInput String that includes the whole transition ("beginingState edge finalState").
 * @author fabiani, andreasb
 */
void FiniteStateAutomata::addTransition(string p_szInput)
{
	string szBeginningState, szEdge, szFinalState;
	char *pstr,*pTeilString;
	pstr = new char [p_szInput.size()+1];
	strcpy(pstr,p_szInput.c_str());
	pTeilString = strtok(pstr," ");
	char *pInput[3];
	for(int idx=0; idx<3;idx++)
		 {
			 pInput[idx]= pTeilString;
			 pTeilString = strtok(NULL, " ");
		 }
	szBeginningState = pInput[0];
	szEdge = pInput[1];
	szFinalState = pInput[2];

	addTransition(szBeginningState, szEdge, szFinalState);
}

/** 
 * Add a transition to transitionlist.
 * @param *p_stBeginningState Pointer of type state (begining state of transition),
 *		   p_szEdge Name of the edge,
 *		  *p_stFinalState Pointer of type state (final state of transition).
 * @author fabiani, andreasb
 */
void FiniteStateAutomata::addTransition(State *p_stBeginningState, string p_szEdge, State *p_stFinalState)
{
	Transition *newTransition = new Transition(*p_stBeginningState, *p_stFinalState, p_szEdge);

	vecTransitionList.push_back(newTransition);
}

/**
 * Remove a transition
 * @param p_szBeginningState Name of the transitions beginning state,
 *		  p_szEdge Name of the transitions edge,
 *		  p_szFinalState Name of the transitions final state.
 * @author fabiani, andreasb
 */
void FiniteStateAutomata::removeTransition(string p_szBeginningState, string p_szEdge, string p_szFinalState)
{

	for(std::vector<Transition*>::iterator it = vecTransitionList.begin(); it != vecTransitionList.end(); ++it) {
		if((*it)->stBeginning.szName == p_szBeginningState && (*it)->stFinish.szName == p_szFinalState && (*it)->szEdge == p_szEdge) {
			vecTransitionList.erase(it);
		}
	}
}

/** 
 * Output of all transitions
 * @author fabiani, andreasb
 */
void FiniteStateAutomata::outputTransitionList( )
{
	cout<<"TransitionList:"<< endl;

	for(std::vector<Transition*>::iterator it = vecTransitionList.begin(); it != vecTransitionList.end(); ++it) {
		cout << (*it)->output() << endl;
	}
}

/**
 * Getter for the transitionlist
 * @return vector<Transition*>* Pointer of type vector<Transition*>
 * @author skowelek
 */
vector<Transition*>* FiniteStateAutomata::getTransitions()
{
	return &vecTransitionList;
}

/**
 * Reads data for this automata from a file, and adjusts all objects (setting the lists etc).
 * @param p_szFileName Path and name of the file.
 * @author skowelek
 */
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
        szLine.erase(szLine.find_last_not_of(" \n\r\t")+1); //trim white-spaces at end of line
        
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

/**
 * Writes the data of the automata into a textfile.
 * @param p_szFileName Path and name of the file.
 * @author skowelek
 */
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

/**
 * Prints the transition that includes the testedge.
 * @param p_szTestEdge Name of the testedge
 * @author fabiani
 */
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

/**
 * Converts this finite state automata into a new deterministic finite state automata.
 * There is no check if this automata is already deterministic,
 * the conversion is done no matter what.
 * @return A pointer to the new finite state automata.
 * @author skowelek
 */
FiniteStateAutomata* FiniteStateAutomata::fsaConvertNEAtoDEA()
{
	FiniteStateAutomata *fsaDEA = new FiniteStateAutomata();
	State *stStartState = this->getStartState();

	// get all existing edges (from this automata)
	vector<string> vecEdges = getEdgesFromTransitionList();
	vector<StateConverter*> vecStateConverters;

	// Set the new automatas start state to a new state equivalent to the old automatas start state
	State *stNewStartState = new State();
	stNewStartState->szName = "S0";
	stNewStartState->bFinalState = stStartState->bFinalState;
	stNewStartState->bStartState = stStartState->bStartState;

	// Create a new StateConverter containing the new start state, and adds a reference
	// to the old automaton's start state.
	StateConverter *scNewStartState = new StateConverter(stNewStartState);
	scNewStartState->addReferencedState(stStartState);
	vecStateConverters.push_back(scNewStartState);

	int idx = 0;
	int iStateCounter = 1;

	// for each item in the StateConverters vector (this vector increases in size while in this loop, hence no foreach loop)
	while(vecStateConverters.size() > idx) {

		// for each existing edge (from this automaton)
		for(std::vector<string>::iterator itedge = vecEdges.begin(); itedge != vecEdges.end(); ++itedge) {

			// get all states that are reachable by the current edge
			vector<State*>* vecTargetStates = new vector<State*>();
			for(std::vector<State*>::iterator itref = vecStateConverters[idx]->vecReferencedStates.begin(); itref != vecStateConverters[idx]->vecReferencedStates.end(); ++itref) {
				setTargetStatesForEdge(*itedge, *itref, vecTargetStates);
			}
			
			// Create the name for the new state
			std::stringstream szstream;
			szstream << "S" << iStateCounter;
			string szStateName = szstream.str();

			// get a new StateConverter representing all States reachable through the current edge as a single State
			StateConverter *scNewStateConverter = new StateConverter(szStateName, vecTargetStates);
			
			// make the StateConverter's State final if any of the referenced States are final
			scNewStateConverter->checkForFinalState();
			StateConverter* scTargetStateConverter;

			// if a StateConverter equal to the new StateConverter doesn't exist in the
			// StateConverters vector, add it and increase the state counter (used for naming)
			if(!isInStateConverterList(scNewStateConverter, &vecStateConverters) && (vecTargetStates->size() > 0)) {
				vecStateConverters.push_back(scNewStateConverter);
				scTargetStateConverter = getEqualStateConverterFromConverterList(scNewStateConverter, &vecStateConverters);
				iStateCounter++;
			}
			// else get the equal StateConverter from the vector and delete the new StateConverter,
			// as it is not needed anymore
			else {
				scTargetStateConverter = getEqualStateConverterFromConverterList(scNewStateConverter, &vecStateConverters);
				delete scNewStateConverter;
			}
			// add a transition to from the current StateConverter to the targeted (new) StateConverter
			if(scTargetStateConverter != NULL) {
				fsaDEA->addTransition(vecStateConverters[idx]->getConvertedState(), *itedge, scTargetStateConverter->getConvertedState());
			}
		}
		idx++;
	}

	// Create the State vector for the new automaton from the StateConverter vector
	setStateListFromStateConverterList(fsaDEA->getStateList(), &vecStateConverters);

	// fill the final states vector
	fsaDEA->getFinalStates();

	return fsaDEA;
}



/**
 * Creates a vector of States from the given vector of StateConverters.
 * @param p_vecStateList Vector in which to save the States.
 * @param p_vecStateConverterList Vector of StateConverters which contain the States for the target vector.
 * @author skowelek
 */
void FiniteStateAutomata::setStateListFromStateConverterList(vector<State*>* p_vecStateList, vector<StateConverter*>* p_vecStateConverterList)
{
	for(std::vector<StateConverter*>::iterator itconv = p_vecStateConverterList->begin(); itconv != p_vecStateConverterList->end(); ++itconv) {
		p_vecStateList->push_back((*itconv)->getConvertedState());
	}
}

/**
 * Saves all the States which are targeted by an edge from a specific State in the given vector.
 * More than one State means that the automata is non-deterministic.
 * @param p_szEdge Which edge to check.
 * @param p_stStateToCheck Which State to check.
 * @param p_vecTargetStates Vector in which to save the target States.
 * @author skowelek
 */
void FiniteStateAutomata::setTargetStatesForEdge(string p_szEdge, State* p_stStateToCheck, vector<State*>* p_vecTargetStates)
{
	for(std::vector<Transition*>::iterator ittrans = vecTransitionList.begin(); ittrans != vecTransitionList.end(); ++ittrans) {
		if((*ittrans)->getBeginningState()->output() == p_stStateToCheck->output() && (*ittrans)->getEdgeName() == p_szEdge) {
			p_vecTargetStates->push_back((*ittrans)->getFinishState());
		}
	}
}

/**
 * Checks if a StateConverter equal to the given StateConverter exists in the given vector.
 * @param p_scStateConverter StateConverter to do the check for.
 * @param p_vecStateConverterList Vector that may or may not contain the given StateConverter.
 * @return True if an equal StateConverter exists, false if not.
 * @author skowelek
 */
bool FiniteStateAutomata::isInStateConverterList(StateConverter* p_scStateConverter, vector<StateConverter*>* p_vecStateConverterList)
{
	for(std::vector<StateConverter*>::iterator it = p_vecStateConverterList->begin(); it != p_vecStateConverterList->end(); ++it) {
		if(p_scStateConverter->getReferencedStates()->size() != (*it)->getReferencedStates()->size()) {
			continue;
		} else {
			if((*it)->equalsReferencedStates(p_scStateConverter)) {
				return true;
			}
		}
	}
	return false;
}

/**
 * Checks if a StateConverter equal to the given StateConverter exists in the given vector,
 * and returns a pointer to that StateConverter.
 * @param p_scStateConverter StateConverter to do the check for.
 * @param p_vecStateConverterList Vector that may or may not contain the given StateConverter.
 * @return A pointer to the given StateConverter, or NULL if no equal StateConverter exists.
 * @author skowelek
 */
StateConverter* FiniteStateAutomata::getEqualStateConverterFromConverterList(StateConverter* p_scStateConverter, vector<StateConverter*>* p_vecStateConverterList)
{
	for(std::vector<StateConverter*>::iterator it = p_vecStateConverterList->begin(); it != p_vecStateConverterList->end(); ++it) {
		if(p_scStateConverter->getReferencedStates()->size() != (*it)->getReferencedStates()->size()) {
			continue;
		} else {
			if((*it)->equalsReferencedStates(p_scStateConverter)) {
				return *it;
			}
		}
	}
	return NULL;
}

/**
 * Gets all edge names from this automata's transition vector.
 * @return A vector containing all the edge names.
 * @author skowelek
 */
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

/**
 * Minimizes this FSA using Moore's algorithm.
 * @return The minimized FSA.
 * @author skowelek, fabiani
 */
FiniteStateAutomata* FiniteStateAutomata::minimize()
{
	vector<Group*> vecGroups;
	Group* gRejectingStates = new Group(this, "G0");
	Group* gAcceptingStates = new Group(this, "G1");

	vecGroups.push_back(gRejectingStates);
	vecGroups.push_back(gAcceptingStates);

	for(std::vector<State*>::iterator it = vecStateList.begin(); it != vecStateList.end(); ++it) {
		GroupElement* geElement = new GroupElement(*it);
		if((*it)->bFinalState) {
			gAcceptingStates->addElementToGroup(geElement);
		} else {
			gRejectingStates->addElementToGroup(geElement);
		}
	}

	setTargetGroups(&vecGroups);
	vector<Group*> vecNewGroups;
	int iGroupCounter = 0;
	int iGroupSizeNew = vecNewGroups.size();
	int iGroupSize = vecGroups.size();
	while(iGroupSizeNew != iGroupSize) {
	
		for(std::vector<Group*>::iterator itgroup = vecGroups.begin(); itgroup != vecGroups.end(); ++itgroup) {
			std::stringstream szstream;
			szstream << "G" << iGroupCounter;
			string szGroupName = szstream.str();
			Group* gNewGroup = new Group(this, szGroupName);
			vecNewGroups.push_back(gNewGroup);
			iGroupCounter++;
			gNewGroup->addElementToGroup((*itgroup)->getElements()->at(0));
			int iGroupStart = findGroupByGroupName(szGroupName, &vecNewGroups);
			for(std::vector<GroupElement*>::iterator itel = (*itgroup)->getElements()->begin(); itel != (*itgroup)->getElements()->end(); ++itel) {
				bool bIsAdded = false;
				for(int idx = iGroupStart; idx < vecNewGroups.size(); idx++) {
					if((*itgroup)->compareElements(*itel, vecNewGroups.at(idx)->getElements()->at(0))) {
						if((*itel)->getState()->output() != vecNewGroups.at(idx)->getElements()->at(0)->getState()->output()) {
							vecNewGroups.at(idx)->addElementToGroup((*itel));
						}
						bIsAdded = true;
						break;
					}
				}
				if(!bIsAdded) {
					std::stringstream szstream;
					szstream << "G" << iGroupCounter;
					string szSubGroupName = szstream.str();
					Group* gNewGroup = new Group(this, szSubGroupName);
					vecNewGroups.push_back(gNewGroup);
					iGroupCounter++;
					gNewGroup->addElementToGroup((*itel));
				}
			}
		}
		iGroupSizeNew = vecNewGroups.size();
		iGroupSize = vecGroups.size();
		if(iGroupSizeNew != iGroupSize) {
			vecGroups = vecNewGroups;
			vecNewGroups.clear();
			setTargetGroups(&vecGroups);
		}
		iGroupCounter = 0;
	}

	FiniteStateAutomata* fsaNew = new FiniteStateAutomata();
	for(std::vector<Group*>::iterator itgroup = vecGroups.begin(); itgroup != vecGroups.end(); ++itgroup) {
		State* stNewState = new State((*itgroup)->getName());
		for(std::vector<GroupElement*>::iterator itel = (*itgroup)->getElements()->begin(); itel != (*itgroup)->getElements()->end(); ++itel) {
			if((*itel)->getState()->bFinalState) {
				stNewState->setFinalState(true);
			}
			if((*itel)->getState()->bStartState) {
				stNewState->setStartState(true);
			}
		}
		fsaNew->addState(stNewState);
	}

	vector<string> vecEdges = getEdgesFromTransitionList();
	for(std::vector<Group*>::iterator itgroup = vecGroups.begin(); itgroup != vecGroups.end(); ++itgroup) {
		for(std::vector<GroupElement*>::iterator itel = (*itgroup)->getElements()->begin(); itel != (*itgroup)->getElements()->end(); ++itel) {
			for(int idx = 0; idx < vecEdges.size(); idx++) {
				State* stStart = fsaNew->getState((*itgroup)->getName());
				State* stFinish = fsaNew->getState((*itel)->getTargetGroups()->at(idx));
				string szEdge = vecEdges.at(idx);
				fsaNew->addTransition(stStart, szEdge, stFinish);
			}
		}
	}
	fsaNew->getFinalStates();

	return fsaNew;
}

/**
 * Searches the given group vector for a specific group by name, and returns the index of
 * this group (i.e. where the group is located in the vector).
 * @param p_szGroupName Name of the group to search for.
 * @param p_vecGroups Vector to search.
 * @return The index of the group, or -1 if the group hasn't been found.
 * @author skowelek, fabiani
 */
int FiniteStateAutomata::findGroupByGroupName(string p_szGroupName, vector<Group*>* p_vecGroups)
{
	int iCounter = 0;
	for(std::vector<Group*>::iterator it = p_vecGroups->begin(); it != p_vecGroups->end(); ++it) {
		if((*it)->getName() == p_szGroupName) {
			return iCounter;
			break;
		} else {
			iCounter++;
		}
	}
	return -1;
}

/**
 * Searches the given group vector for a group element whose state is equal to the given state,
 * and returns the name of the group containing this element.
 * @param p_stState State to search for.
 * @param p_vecGroups Groups to search for the specific element.
 * @return The name of the group containing the element, or an empty string if no equal state was found.
 * @author skowelek, fabiani
 */
string FiniteStateAutomata::getTargetGroupName(State* p_stState, vector<Group*>* p_vecGroups)
{
	for(std::vector<Group*>::iterator it = p_vecGroups->begin(); it != p_vecGroups->end(); ++it) {
		for(std::vector<GroupElement*>::iterator itel = (*it)->getElements()->begin(); itel != (*it)->getElements()->end(); ++itel) {
			if((*itel)->getState()->output() == p_stState->output()) {
				return (*it)->getName();
			}
		}
	}
	return "";
}

/**
 * Sets the target groups (i.e. the groups reachable through the specific edges) for each
 * group element of all groups. Used in the minimize function.
 * @param p_vecGroups Vector containing all groups containing all group elements to set the target groups for.
 * @author skowelek, fabiani
 */
void FiniteStateAutomata::setTargetGroups(vector<Group*>* p_vecGroups)
{
	vector<string>* vecEdges = p_vecGroups->at(0)->getEdges();
	for(std::vector<Group*>::iterator it = p_vecGroups->begin(); it != p_vecGroups->end(); ++it) {
		for(std::vector<GroupElement*>::iterator itel = (*it)->getElements()->begin(); itel != (*it)->getElements()->end(); ++itel) {
			(*itel)->clearTargetGroups();
			for(std::vector<string>::iterator ited = vecEdges->begin(); ited != vecEdges->end(); ++ited) {
				vector<State*> vecState;
				setTargetStatesForEdge(*ited, (*itel)->getState(), &vecState);
				if(vecState.at(0) == NULL) {
					(*itel)->addGroupToTargetVector("");
				} else {
					(*itel)->addGroupToTargetVector(getTargetGroupName(vecState.at(0), p_vecGroups));
				}
			}
		}
	}
}

/**
 * Converts this FSA to Regular Grammar.
 * @returns A new instance of grammar.
 * @author fabiani
 */
Grammar* FiniteStateAutomata::convertToGrammar()
{
	Grammar *graConverted = new Grammar();
	FiniteStateAutomata *fsaActual = this;
	State *stTemp;

	vector<Transition*>* vecTransitionList = fsaActual->getTransitions();
	DynArray<string> arTemp;

	stTemp = fsaActual->getStartState();
	graConverted->setStartSymbol(stTemp->output());
	if(stTemp->isFinalState() == true)
	{
		Substitution suTemp= *new Substitution();
		Production prTemp = *new Production();
		suTemp.setRawString("epsilon");
		prTemp.setLeftSide(stTemp->output());
		prTemp.setSubstitution(&suTemp);
		graConverted->addProduction(&prTemp);
	}

	for(std::vector<Transition*>::iterator it = vecTransitionList->begin(); it != vecTransitionList->end(); ++it)
	{
		arTemp = graConverted->getNonTerminals();
		if(!arTemp.exist((*it)->getBeginningState()->output()))
		{
			graConverted->addNonTerminal((*it)->getBeginningState()->output());
		}
		if(!arTemp.exist((*it)->getFinishState()->output()))
		{
			graConverted->addNonTerminal((*it)->getFinishState()->output());
		}
		arTemp = graConverted->getTerminals();
		if(!arTemp.exist((*it)->getEdgeName()))
		{
			graConverted->addTerminal((*it)->getEdgeName());
		}

		Substitution *suTemp = new Substitution();
		Production *prTemp = new Production();
		suTemp->setRawString((*it)->getEdgeName() + " " + (*it)->getFinishState()->output());
		prTemp->setLeftSide((*it)->getBeginningState()->output());
		prTemp->setSubstitution(suTemp);
		suTemp->decode(graConverted->getTerminals(), graConverted->getNonTerminals());
		graConverted->addProduction(prTemp);
		if((*it)->getFinishState()->isFinalState() == true)
		{
			Substitution *suTemp = new Substitution();
			Production *prTemp = new Production();
			suTemp->setRawString((*it)->getEdgeName());
			prTemp->setLeftSide((*it)->getBeginningState()->output());
			prTemp->setSubstitution(suTemp);
			suTemp->decode(graConverted->getTerminals(), graConverted->getNonTerminals());
			graConverted->addProduction(prTemp);
		}
	}
	return graConverted;
}
