/*
 * FSA_TableFillingMinimiser.h
 *
 *  Created on: 5 juil. 2012
 *      Author: yessine
 */

#ifndef FSA_TABLEFILLINGMINIMISER_H_
#define FSA_TABLEFILLINGMINIMISER_H_

#include "FSA_FiniteStateAutomata.hpp"

class TableFillingFSAMinimiser
{
private:

	static int getIndexOfState(State* pState, FiniteStateAutomata* pAutomat);
public:
	//int isUnreachable(State* s , FiniteStateAutomata* a);
	static bool existInVector(vector<int>* pVector, int element);
	static vector<string> getInputListForState(int stateIndex, FiniteStateAutomata* pAutomat);
	static void minimize(FiniteStateAutomata* pAutomat);
	static void initMinimizingTable(FiniteStateAutomata* pAutomat, vector< vector<int> >* pMinTable);
	static void printMinTable(vector< vector<int> > * minTable);
	static void searchForPredecessorState(int stateIndex, string input, FiniteStateAutomata* pAutomat, vector<int>* pOutputVector);
	static void fillMinimizingTable(vector< vector<int> > * minTable , FiniteStateAutomata* pAutomat );
};


#endif /* FSA_TABLEFILLINGMINIMISER_H_ */
