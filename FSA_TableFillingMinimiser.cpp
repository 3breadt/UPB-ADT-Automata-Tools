/*
 * FSA_TableFillingMinimiser.cpp
 *
 *  Created on: 5 juil. 2012
 *      Author: yessine
 */

#include <cstdlib>
#include "FSA_TableFillingMinimiser.h"

#define DISTINGUISHABLE 9

using namespace std;

int getNumberOfStates(FiniteStateAutomata* pAutomat)
{
	return pAutomat->getStateList()->size();
}

void TableFillingFSAMinimiser::minimize(FiniteStateAutomata* pAutomat)
{
	int numberOfStates;
	//TODO: convert States names to numbers (corresponding to index in State list )  (or is it necessary? ) : no I worked with the index in the stateList
	//TODO:remove unreachable States
	//getNumberOfStates
	numberOfStates = getNumberOfStates(pAutomat);

	vector< vector<int> > minTable (numberOfStates , vector<int>(numberOfStates));

	//TODO:initialise Minimizing Table
	initMinimizingTable(pAutomat, &minTable);
	printMinTable(&minTable);
	fillMinimizingTable(&minTable, pAutomat);
	printMinTable(&minTable);
}

void TableFillingFSAMinimiser::printMinTable(vector< vector<int> > * pMinTable)
{
	for(unsigned int i=0; i < pMinTable->size() ; i++ )
	{
		for(unsigned int j=0; j < i ; j++) //j < (*pMinTable)[i].size()
		{
			cout << (*pMinTable)[i][j] << "   " ;
			if (j == i-1) //(*pMinTable)[i].size()-1)
			{
				cout << endl;
			}
		}
	}

}

void TableFillingFSAMinimiser::initMinimizingTable(FiniteStateAutomata* pAutomat, vector< vector<int> >* pMinTable)
{
	vector<State*>* pStates = pAutomat->getStateList();
	bool stateIsFinal;

	/**intialise Table*/
	for(unsigned int i=0; i < pMinTable->size() ; ++i )
	{
		for(unsigned int j=0; j < i ; ++j) //(*pMinTable)[i].size()
		{
				(*pMinTable)[i][j]= 0 ;
		}
	}

	/**accepting states and rejecting states are distiguishable*/
	for(unsigned int i = 0; i <pStates->size() ; i++)  // until size/2 maybe better
	{
		stateIsFinal = (*pStates)[i]->isFinalState() ;
		for(unsigned int j = 0; j <pStates->size() ; j++)
		{
			if(i != j)
			{
				if((*pStates)[j]->isFinalState() != stateIsFinal)
				{
					(*pMinTable)[i][j]= DISTINGUISHABLE;
				}
			}
		}
	}
}

int TableFillingFSAMinimiser::getIndexOfState(State* pState, FiniteStateAutomata* pAutomat)
{
	vector<State*>* pAutomatStates;

	pAutomatStates = pAutomat->getStateList();

	for(unsigned int i=0; i< pAutomatStates->size(); i++)
	{
		if(pState->compare((*pAutomatStates)[i]) == 0)
		{
			return i;
		}
	}
	cerr << "State " << pState->getName() <<" not found: cannot continue minimization" << endl ;
	exit(1);
	return 0;
}
/**
 * @brief search for every State that leads to the State with index stateIndex , through a Transition input
 * @param stateIndex
 * @param input
 * @param pAutomat
 * @param pOutputVector
 */
void TableFillingFSAMinimiser::searchForPredecessorState(int stateIndex, string input, FiniteStateAutomata* pAutomat, vector<int>* pOutputVector)
{
	vector<Transition*>* pAutomatTransitions;
	vector<State*>* pAutomatStates;
	State* pTempValidState;
	int    tempValidStateIndex;

	pAutomatTransitions = pAutomat->getTransitions();
	pAutomatStates = pAutomat->getStateList();

	for(unsigned int i=0 ; i < pAutomatTransitions->size() ; i++)
	{
		if((*pAutomatTransitions)[i]->getFinishState()->compare((*pAutomatStates)[i]) == 0
				&& (*pAutomatTransitions)[i]->getEdgeName().compare(input) == 0)
		{
			pTempValidState = (*pAutomatTransitions)[i]->getBeginningState() ;
			tempValidStateIndex = getIndexOfState(pTempValidState, pAutomat );

			if(!existInVector(pOutputVector, tempValidStateIndex ))
			{
				pOutputVector->push_back(tempValidStateIndex);
			}
			searchForPredecessorState(tempValidStateIndex, input, pAutomat, pOutputVector);
		}
	}
}

bool TableFillingFSAMinimiser::existInVector(vector<int>* pVector, int element)
{
	for (unsigned int i =0 ; i < pVector->size() ; i++)
	{
		if((*pVector)[i] == element)
		{
			return true;
		}
	}
	return false ;
}

void printVector(vector<int>* v)
{
	cout << "****Printing Vector*******" << endl;
	for(unsigned int i = 0 ; i < v->size() ; i++ )
	{
		cout << (*v)[i] << "     " ;
		if(i== v->size() -1)
		{
			cout << endl;
		}
	}
}

void TableFillingFSAMinimiser::fillMinimizingTable(vector< vector<int> > * pMinTable , FiniteStateAutomata* pAutomat)
{
	int changeFlag = 1; // 1 if table changed
	while(changeFlag == 1)
	{
		int k =0 ;
		cout << "entered while loop " << k++ <<endl;
		changeFlag = 0;
		for(unsigned int i=0; i < pMinTable->size() ; i++ )
		{
			for(unsigned int j=0; j < i ; j++)
			{
				if((*pMinTable)[i][j] == DISTINGUISHABLE)
				{
					cout << "Distinguishable" << endl;

					vector<int> predecessorStatesOfI(getNumberOfStates(pAutomat));
					vector<int> predecessorStatesOfJ(getNumberOfStates(pAutomat));

					//every element in I is distiguishable to every element in J
					predecessorStatesOfI.push_back(i);
					printVector(&predecessorStatesOfI);
					predecessorStatesOfJ.push_back(j);
					printVector(&predecessorStatesOfJ);     // 0 in vector is not good!!!! because there is a state 0!!!  moreover: i>1 ??
					/*****************************************
					//TODO: all inputs!!! (total FSA)

					searchForPredecessorState(i,"1", pAutomat, &predecessorStatesOfI );
					searchForPredecessorState(j,"1", pAutomat, &predecessorStatesOfJ );

					for(unsigned int i=0; i < predecessorStatesOfI.size() ; i++ )
					{
						for(unsigned int j=0; j < predecessorStatesOfJ.size() ; j++)
						{
							int elementInMinTable = (*pMinTable)[predecessorStatesOfI[i]][predecessorStatesOfJ[j]] ;
							if(elementInMinTable == 0)
							{
								changeFlag = 1;
							}
							(*pMinTable)[predecessorStatesOfI[i]][predecessorStatesOfJ[j]] = DISTINGUISHABLE ;

						}
					}
					******************************************/
				}
			}
		}
	}
}
