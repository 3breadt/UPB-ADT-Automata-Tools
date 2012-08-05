/**
 * @file FSA_TableFillingMinimizer.cpp
 * @author Yacine Smaoui
 *
 * @brief implementation of the Table filling algorithm to minimize a finite states automaton
 */

#include <cstdlib>
#include "FSA_TableFillingMinimizer.h"

#define DISTINGUISHABLE 9
#define ELEMENT_ON_DIAG_MINTABLE 8
#define ELEMENT_TREATED 7

#define ERROR_STATE_NOT_FOUND 999

using namespace std;

/**
 * @brief the main function to call to use the Table filling Algorithm for minimization
 * steps in this implementation:
 *
 * 1)initialization of the minimization table
 * 2)filling the minimization table by finding the distinguishable pairs of states
 * 3)merging the distinguishable states in one equivalent state
 *
 * 4) finally the automat is written in a text file to see result.
 *
 * @param pAutomat the FSA to minimize
 * @author Yacine Smaoui
 */
void TableFillingFSAMinimizer::minimize(FiniteStateAutomaton* pAutomat)
{
	vector<string> allInputs;

	int numberOfStates;
	//getNumberOfStates
	numberOfStates = getNumberOfStates(pAutomat);

	allInputs= pAutomat->getEdgesFromTransitionList();

	//vector< vector<int> > minTable (numberOfStates , vector<int>(numberOfStates));
	vector<vector<StatesPair> > minTable (numberOfStates, vector<StatesPair>(numberOfStates));

	initMinimizingTableStruct(pAutomat, &minTable);
	printMinTableStruct(&minTable);
	fillMinimizingTableStruct(&minTable,&allInputs, pAutomat);
	printMinTableStruct(&minTable);
	mergeStates(&minTable,pAutomat);
	pAutomat->write("Beispieldateien/FSA-exampleFromMinimisingDocument_TotalFSA_minimized.txt");
}

/**
 * @brief a method to print to contents of the minimization table used in this algorithm
 * @param pMinTable
 * @author Yacine Smaoui
 */
void TableFillingFSAMinimizer::printMinTableStruct(vector< vector<StatesPair> > * pMinTable)
{
	for(unsigned int i=1; i < pMinTable->size() ; i++ )
		{
			cout << "(" << i << ")" ;
			for(unsigned int j=0; j < i ; j++)
			{
				if((*pMinTable)[i][j].areDistinguishable)
				{
					cout << "D" << "   " ;
				}
				else
				{
					cout << "N" << "   " ;
				}
				if (j == i-1)
				{
					cout << endl;
				}
			}
		}
}


/**
 * @brief Initializing the minimization table, by marking all pairs of one accepting state and one rejecting state as distiguishable pairs of states
 * @param pAutomat
 * @param pMinTable
 * @author Yacine Smaoui
 */
void TableFillingFSAMinimizer::initMinimizingTableStruct(FiniteStateAutomaton* pAutomat, vector< vector<StatesPair> >* pMinTable)
{
	vector<State*>* pStates = pAutomat->getStateList();
	bool stateIsFinal;

	/**intialise Table*/
	for(unsigned int i=0; i < pMinTable->size() ; ++i )
	{
		for(unsigned int j=0; j < i ; ++j) //(*pMinTable)[i].size()
		{
				(*pMinTable)[i][j].areDistinguishable= 0 ;
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
					(*pMinTable)[i][j].areDistinguishable = 1;
				}
			}
		}
	}

}

/**
 * @brief filling the Minimization Table by finding all distiguishable pairs of states using the algorithm.
 * @param pMinTable the minimization table
 * @param pAllInputs the inputs of all transitions in this FSA
 * @param pAutomat the Automat to minimize
 * @author Yacine Smaoui
 */
void TableFillingFSAMinimizer::fillMinimizingTableStruct(vector< vector<StatesPair> > * pMinTable , vector<string>* pAllInputs,  FiniteStateAutomaton* pAutomat)
{
	/** For every element in minTable*/
	for(unsigned int i=1; i < pMinTable->size() ; i++ )
	{
		for(unsigned int j=0; j < i ; j++)
		{
			/**if it is not marked as distinguishable*/
			if(!(*pMinTable)[i][j].areDistinguishable)
			{
				/** for every input */
				for(unsigned int inputCounter = 0 ; inputCounter < pAllInputs->size(); inputCounter++)
				{
					string input = (*pAllInputs)[inputCounter];
					/**get the next States of i, and j */
					int stateFollowingI = getNextStateIndex(i,input,pAutomat);
					int stateFollowingJ = getNextStateIndex(j,input,pAutomat);
					if(stateFollowingI == ERROR_STATE_NOT_FOUND || stateFollowingJ == ERROR_STATE_NOT_FOUND)
					{
						cerr << "State not found, cannot proceed" << endl;
					}

					if(stateFollowingI < stateFollowingJ)
					{
						int temp = stateFollowingI;
						stateFollowingI = stateFollowingJ;
						stateFollowingJ = temp;
					}

					StatesPair* pReferenceToIJ = (&((*pMinTable)[i][j]));

					if(!(*pMinTable)[stateFollowingI][stateFollowingJ].areDistinguishable)
					{
						/** add (i,j) to the dependencies of the following pair of states */
						(*pMinTable)[stateFollowingI][stateFollowingJ].dependencies.push_back(pReferenceToIJ);
					}
					else
					{
						/** Mark (i,j) as distinguishable..  */
						pReferenceToIJ->areDistinguishable = 1 ;

						/**..and recursively mark all of its dependencies */
						for(unsigned dependenciesCounter = 0 ; dependenciesCounter < pReferenceToIJ->dependencies.size(); dependenciesCounter++)
						{
							if(pReferenceToIJ->dependencies.size()>0)
							{
								pReferenceToIJ->dependencies[dependenciesCounter]->areDistinguishable =1 ;
							}
						}
					}
				}
			}
		}
	}
}

/**
 * @brief removes all states doubles in the given FSA
 * @param pAutomat
 * @author Yacine Smaoui
 */
void TableFillingFSAMinimizer::removeRedundantStates(FiniteStateAutomaton* pAutomat)
{
	vector<State*>* pAutomatStates;
	pAutomatStates = pAutomat->getStateList();


	for(unsigned int i= 0 ; i< pAutomatStates->size() ; i++ )
	{
		for(unsigned int j=i+1 ; j<pAutomatStates->size(); j++)
		{
			if((*pAutomatStates)[i]->compare((*pAutomatStates)[j]) == 0)
			{
				pAutomatStates->erase(pAutomatStates->begin()+j);
			}
		}
	}
}

/**
 * @brief removes all Transitions doubles in the given FSA
 * @param pAutomat
 * @author Yacine Smaoui
 */
void TableFillingFSAMinimizer::removeRedundantTransitions(FiniteStateAutomaton* pAutomat)
{
	vector<Transition*>* pAutomatTransitions;
	pAutomatTransitions = pAutomat->getTransitions();


	for(unsigned int i= 0 ; i< pAutomatTransitions->size() ; i++ )
	{
		for(unsigned int j=i+1 ; j<pAutomatTransitions->size(); j++)
		{
			if((*pAutomatTransitions)[i]->compare((*pAutomatTransitions)[j]) == 0)
			{
				pAutomatTransitions->erase(pAutomatTransitions->begin()+j);
			}
		}
	}
}

/**
 * @brief merges every pair of equivalent states into one state
 *
 * steps:
 * 1) for every distinguishable pair of states, change the name and properties of both states, so that they become equal states
 * the result of 1) is an FSA with redundant states and Transitions
 * 2)remove all redundant states
 * 3) remove all redundant transitions
 *
 *
 * NB: what is not dealt with in this version of the merge method is:
 * the transitivity of the relation "distinguishable": that means, if more than two states are equivalent.
 *
 * @param pMinTable
 * @param pAutomat
 * @author Yacine Smaoui
 */
void TableFillingFSAMinimizer::mergeStates(vector< vector<StatesPair> > * pMinTable, FiniteStateAutomaton* pAutomat)
{
	vector<Transition*>* pAutomatTransitions;
	pAutomatTransitions = pAutomat->getTransitions();
	vector<State*>* pAutomatStates;
	pAutomatStates = pAutomat->getStateList();

	/**search for equivalent states in minTable*/
	for(unsigned int i=1; i < pMinTable->size() ; i++ )
	{
		for(unsigned int j=0; j < i ; j++)
		{

			if(!(*pMinTable)[i][j].areDistinguishable)
			{
				string newName =  (*pAutomatStates)[i]->getName() +","+(*pAutomatStates)[j]->getName();

				for(unsigned transitionsCounter=0; transitionsCounter < pAutomatTransitions->size(); transitionsCounter++)
				{
					State* beginnigState = (*pAutomatTransitions)[transitionsCounter]->getBeginningState();
					State* finishState = (*pAutomatTransitions)[transitionsCounter]->getFinishState();
					if(beginnigState->compare((*pAutomatStates)[i])==0
							|| beginnigState->compare((*pAutomatStates)[j]) == 0)
					{
						beginnigState->setName(newName);
						if((*pAutomatStates)[i]->isFinalState() || (*pAutomatStates)[j]->isFinalState() )
						{
							beginnigState->setFinalState(true);
						}
						if((*pAutomatStates)[i]->isStartState() || (*pAutomatStates)[j]->isStartState() )
						{
							beginnigState->setStartState(true);
						}
					}
					if(finishState->compare((*pAutomatStates)[i])==0
							|| finishState->compare((*pAutomatStates)[j]) == 0)
					{
						finishState->setName(newName);
						if((*pAutomatStates)[i]->isFinalState() || (*pAutomatStates)[j]->isFinalState() )
						{
							finishState->setFinalState(true);
						}
						if((*pAutomatStates)[i]->isStartState() || (*pAutomatStates)[j]->isStartState() )
						{
							finishState->setStartState(true);
						}
					}
				}

				if((*pAutomatStates)[i]->isFinalState() || (*pAutomatStates)[j]->isFinalState() )
				{
					(*pAutomatStates)[i]->setFinalState(true);
					(*pAutomatStates)[j]->setFinalState(true);
				}

				if((*pAutomatStates)[i]->isStartState() || (*pAutomatStates)[j]->isStartState() )
				{
					(*pAutomatStates)[i]->setStartState(true);
					(*pAutomatStates)[j]->setStartState(true);
				}
				(*pAutomatStates)[i]->setName(newName);
				(*pAutomatStates)[j]->setName(newName);

			}
		}
	}
	removeRedundantStates(pAutomat);
	removeRedundantTransitions(pAutomat);
}

/**
 * @brief returns the next state to "StateIndex" for the given "input" in the FSA "pAutomat"
 * @param stateIndex
 * @param input
 * @param pAutomat
 * @return
 * @author Yacine Smaoui
 */
int TableFillingFSAMinimizer::getNextStateIndex(int stateIndex, string input, FiniteStateAutomaton* pAutomat)
{
	vector<Transition*>* pAutomatTransitions;
	vector<State*>* pAutomatStates;
	State* pTempValidState;

	pAutomatTransitions = pAutomat->getTransitions();
	pAutomatStates = pAutomat->getStateList();
	unsigned int automatTransitionsSize = pAutomatTransitions->size() ;
	for(unsigned int i=0 ; i < automatTransitionsSize ; i++)
	{
		int compareResult = (*pAutomatTransitions)[i]->getBeginningState()->compare((*pAutomatStates)[stateIndex]);
		if(compareResult == 0
				&& (*pAutomatTransitions)[i]->getEdgeName().compare(input) == 0)
		{
			pTempValidState = (*pAutomatTransitions)[i]->getFinishState();
			return getIndexOfState(pTempValidState, pAutomat );
		}
	}
	return ERROR_STATE_NOT_FOUND;
}

int TableFillingFSAMinimizer::getNumberOfStates(FiniteStateAutomaton* pAutomat)
{
	return pAutomat->getStateList()->size();
}

/*=======================================================================================================================================================*/
/*=======================================================================================================================================================*/
/*===================The following Methods were used at first to implement the algorithm in one way but it didn't wowrk correctly========================*/
/*===================They are not deleted just in case someone can find the error and improve it========================================================*/
/*=======================================================================================================================================================*/
/*=======================================================================================================================================================*/

/**
 * @brief a method to print to contents of the minimization table used in this algorithm
 * @param pMinTable
 * @author Yacine Smaoui
 */
void TableFillingFSAMinimizer::printMinTable(vector< vector<int> > * pMinTable)
{
	for(unsigned int i=1; i < pMinTable->size() ; i++ )
	{
		cout << "(" << i << ")" ;
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

/**
 * @brief Initializing the minimization table, by marking all pairs of one accepting state and one rejecting state as distiguishable pairs of states
 * @param pAutomat
 * @param pMinTable
 * @author Yacine Smaoui
 */
void TableFillingFSAMinimizer::initMinimizingTable(FiniteStateAutomaton* pAutomat, vector< vector<int> >* pMinTable)
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

/**
 * @brief filling the Minimization Table by finding all distinguishable pairs of states using the algorithm.
 * @param pMinTable the minimization table
 * @param pAllInputs the inputs of all transitions in this FSA
 * @param pAutomat the Automaton to minimize
 * @author Yacine Smaoui
 */
int TableFillingFSAMinimizer::getIndexOfState(State* pState, FiniteStateAutomaton* pAutomat)
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
 * @brief search for every State that leads to the State with index stateIndex , through a sequence of "input"
 *
 * for example:  A -1-> B -1-> C-1-> D
 * A,B and C are the predecessor States of D with the input 1
 *
 * @param stateIndex
 * @param input
 * @param pAutomat
 * @param pOutputVector
 * @author Yacine Smaoui
 */
void TableFillingFSAMinimizer::searchForPredecessorState(int stateIndex, string input, FiniteStateAutomaton* pAutomat, vector<int>* pOutputVector)
{
	vector<Transition*>* pAutomatTransitions;
	vector<State*>* pAutomatStates;
	State* pTempValidState;
	int    tempValidStateIndex;

	pAutomatTransitions = pAutomat->getTransitions();
	pAutomatStates = pAutomat->getStateList();
	unsigned int automatTransitionsSize = pAutomatTransitions->size() ;
	for(unsigned int i=0 ; i < automatTransitionsSize ; i++)
	{
		int compareResult = (*pAutomatTransitions)[i]->getFinishState()->compare((*pAutomatStates)[stateIndex]);
		if(compareResult == 0
				&& (*pAutomatTransitions)[i]->getEdgeName().compare(input) == 0)
		{
			pTempValidState = (*pAutomatTransitions)[i]->getBeginningState() ;
			tempValidStateIndex = getIndexOfState(pTempValidState, pAutomat );

			if(!existInIntVector(pOutputVector, tempValidStateIndex ))
			{
				pOutputVector->push_back(tempValidStateIndex);
			}
		//	searchForPredecessorState(tempValidStateIndex, input, pAutomat, pOutputVector);
		}
	}
}

/**
 * @brief mark as distiguishable all the pairs of states such as one is in pPredecessorsOfI and the other in pPredecessorsOfJ
 * @param pMinTable
 * @param pPredecessorsOfI
 * @param pPredecessorsOfJ
 * @return 1 if changes to MinTable are made, 0 if no changes are made
 * @author Yacine Smaoui
 */
int TableFillingFSAMinimizer::markDistiguishableStates(vector< vector<int> > * pMinTable, vector<int>* pPredecessorsOfI, vector<int>* pPredecessorsOfJ )
{
	int changeIsMade = 0;
	/** For every pair of elements in pPredecessorsOfI and pPredecessorsOfJ */
	for(unsigned int i = 0; i < pPredecessorsOfI->size(); i++)
	{
		for(unsigned int j = 0; j < pPredecessorsOfJ->size(); j++)
		{
			/**get Element in MinTable*/
			int elementInMinTable;
			if(pPredecessorsOfI[i] == pPredecessorsOfJ[j])
			{
				elementInMinTable = ELEMENT_ON_DIAG_MINTABLE;
			}
			else
			{

				 if((*pPredecessorsOfI)[i] > (*pPredecessorsOfJ)[j])
				{
					 elementInMinTable = (*pMinTable)[(*pPredecessorsOfI)[i]][(*pPredecessorsOfJ)[j]];
				}
				 else
				 {
					 elementInMinTable = (*pMinTable)[(*pPredecessorsOfJ)[j]][(*pPredecessorsOfI)[i]];
				 }
			}

			/**Mark distiguishable states */
			if(elementInMinTable == 0)
			{
				(*pMinTable)[(*pPredecessorsOfI)[i]][(*pPredecessorsOfJ)[j]] = DISTINGUISHABLE ;
				(*pMinTable)[(*pPredecessorsOfJ)[j]][(*pPredecessorsOfI)[i]] = DISTINGUISHABLE ;

				changeIsMade = 1 ;
			}
			else
			{
				//no change
			}
		}
	}
	return changeIsMade;
}

/**
 * @brief filling the Minimization Table by finding all distiguishable pairs of states using the algorithm.
 * @param pMinTable the minimization table
 * @param pAllInputs the inputs of all transitions in this FSA
 * @param pAutomat the Automat to minimize
 * @author Yacine Smaoui
 */
void TableFillingFSAMinimizer::fillMinimizingTable(vector< vector<int> > * pMinTable , vector<string>* pAllInputs,  FiniteStateAutomaton* pAutomat)
{
	unsigned int minTableSize = pMinTable->size();
	int numberOfStates = getNumberOfStates(pAutomat);
	vector< vector<int> > doneTable (numberOfStates , vector<int>(numberOfStates));

	vector<int> predecessorStatesOfI;
	vector<int> predecessorStatesOfJ;

	/**intialise DoneTable*/
	for(unsigned int i=0; i < doneTable.size() ; ++i )
	{
		for(unsigned int j=0; j < i ; ++j) //(*pMinTable)[i].size()
		{
				doneTable[i][j]= 0 ;
		}
	}


	/**for every pair of states (i,j) */
	for(unsigned int i=0; i < minTableSize ; i++ )
	{
		for(unsigned int j=0; j < i ; j++)
		{
			int changeIsMade = 0;
			/** if the pair is a pair of distinguishable states, and not already treated */
			bool distinguishable = (*pMinTable)[i][j] == DISTINGUISHABLE ;
			bool treated = doneTable[i][j] == ELEMENT_TREATED;
			if(distinguishable && !treated)
			{
				/** for every input */
				for(unsigned int inputsCounter =0 ; inputsCounter < pAllInputs->size(); inputsCounter++)
				{
					/** Add State indexes to Predecessors vectors */
					predecessorStatesOfI.push_back(i);
					predecessorStatesOfJ.push_back(j);

					string input = (*pAllInputs)[inputsCounter];

					searchForPredecessorState(i,input, pAutomat, &predecessorStatesOfI );
					searchForPredecessorState(j,input, pAutomat, &predecessorStatesOfJ );
					cout<< "======================================" << endl;
					printIntVector(&predecessorStatesOfI);
					cout << "-------------------------------------" <<endl;
					printIntVector(&predecessorStatesOfJ);
					cout<< "======================================" << endl;

					changeIsMade = markDistiguishableStates(pMinTable,&predecessorStatesOfI, &predecessorStatesOfJ);
					if(changeIsMade)
					{
						printMinTable(pMinTable);
					}

					predecessorStatesOfI.clear();
					predecessorStatesOfJ.clear();
				}

				doneTable[i][j] = ELEMENT_TREATED;

				if(changeIsMade)
				{
					i=0;
					j=0;
				}
			}

		}
	}

}




/*=======================================================================================================================================================*/
/*=======================================================================================================================================================*/
/*===================The following Methods are just used to help doing some simple tasks: print, search,...==============================================*/
/*=======================================================================================================================================================*/
/*=======================================================================================================================================================*/
/**
 *
 * @param pVector
 * @param element
 * @return
 * @author Yacine Smaoui
 */
bool TableFillingFSAMinimizer::existInIntVector(vector<int>* pVector, int element)
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
/**
 *
 * @param pVector
 * @param element
 * @return
 * @author Yacine Smaoui
 */
bool TableFillingFSAMinimizer::existInStringVector(vector<string>* pVector, string element)
{
	for (unsigned int i =0 ; i < pVector->size() ; i++)
	{
		if((*pVector)[i].compare(element) == 0 )
		{
			return true;
		}
	}
	return false ;
}
/**
 *
 * @param v
 * @author Yacine Smaoui
 */
void TableFillingFSAMinimizer::printIntVector(vector<int>* v)
{
	for(unsigned int i = 0 ; i < v->size() ; i++ )
	{
		cout << (*v)[i] << "     " ;
		if(i== v->size() -1)
		{
			cout << endl;
		}
	}
}

/**
 *
 * @param pVector
 * @author Yacine Smaoui
 */
void TableFillingFSAMinimizer::printStringVector(vector<string>* pVector)
{

	cout << "Printing input vector" << endl;

	cout << "Size:  " << pVector->size() << endl;
	for( unsigned int i = 0; i< pVector->size(); i++)
	{
		cout << (*pVector)[i] << "    " ;
		if (i == pVector->size() -1)
		{
			cout << endl;
		}
	}

}

