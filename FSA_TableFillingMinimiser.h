/*
 * FSA_TableFillingMinimiser.h
 *
 *  Created on: 5 juil. 2012
 *      Author: yessine
 */

#ifndef FSA_TABLEFILLINGMINIMISER_H_
#define FSA_TABLEFILLINGMINIMISER_H_

#include "FSA_FiniteStateAutomata.hpp"


struct StatesPair {

	bool areDistinguishable;
	vector<StatesPair*> dependencies;

};


class TableFillingFSAMinimiser
{
private:

	static int getIndexOfState(State* pState, FiniteStateAutomata* pAutomat);
public:
	//int isUnreachable(State* s , FiniteStateAutomata* a);
	static bool existInIntVector(vector<int>* pVector, int element);
	static bool existInStringVector(vector<string>* pVector, string element);
	static vector<string> getInputListForState(int stateIndex, FiniteStateAutomata* pAutomat);
	static void minimize(FiniteStateAutomata* pAutomat);
	static void searchForPredecessorState(int stateIndex, string input, FiniteStateAutomata* pAutomat, vector<int>* pOutputVector);
	static int getNextStateIndex(int stateIndex, string input, FiniteStateAutomata* pAutomat);
	static void removeRedundantStates(FiniteStateAutomata* pAutomat);
	static void removeRedundantTransitions(FiniteStateAutomata* pAutomat);

	/** these are written for one method to implement this Algorithm, but this method doesn't work correctly */
	static void initMinimizingTable(FiniteStateAutomata* pAutomat, vector< vector<int> >* pMinTable);
	static void printMinTable(vector< vector<int> > * minTable);
	static void fillMinimizingTable(vector< vector<int> > * minTable ,vector<string>* Allinputs, FiniteStateAutomata* pAutomat );

	/** with these the second method is implemented, it does work and construct a correct MinTable*/
	static void initMinimizingTableStruct(FiniteStateAutomata* pAutomat, vector< vector<StatesPair> >* pMinTable);
	static void printMinTableStruct( vector< vector<StatesPair> > * pMinTable);
	static void fillMinimizingTableStruct(vector< vector<StatesPair> > * minTable ,vector<string>* Allinputs, FiniteStateAutomata* pAutomat );
	static void mergeStates(vector< vector<StatesPair> > * minTable, FiniteStateAutomata* pAutomat);
};


#endif /* FSA_TABLEFILLINGMINIMISER_H_ */
