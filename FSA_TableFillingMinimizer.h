/**
 * @file FSA_TableFillingMinimizer.h
 * @author Yacine Smaoui
 *
 * @brief implementation of the Table filling algorithm to minimize a finite states automaton
 */

#ifndef FSA_TABLEFILLINGMINIMISER_H_
#define FSA_TABLEFILLINGMINIMISER_H_

#include "FSA_FiniteStateAutomaton.hpp"

/**
 * @struct StatesPair
 * @brief defines properties of a pair of States
 * @author Yacine Smaoui
 */
struct StatesPair {

	bool areDistinguishable;
	vector<StatesPair*> dependencies;

};

/**
 * @class TableFillingFSAMinimizer
 *
 * @brief a class providing methods to minimize an FSA with the table filling algorithm.
 * @author Yacine Smaoui
 */
class TableFillingFSAMinimizer
{
private:
	static void printStringVector(vector<string>* pVector);
	static void printIntVector(vector<int>* v);
	static int getNumberOfStates(FiniteStateAutomaton* pAutomat);
	static int getIndexOfState(State* pState, FiniteStateAutomaton* pAutomat);
	static bool existInIntVector(vector<int>* pVector, int element);
	static bool existInStringVector(vector<string>* pVector, string element);
	static vector<string> getInputListForState(int stateIndex, FiniteStateAutomaton* pAutomat);


	static void searchForPredecessorState(int stateIndex, string input, FiniteStateAutomaton* pAutomat, vector<int>* pOutputVector);
	static int getNextStateIndex(int stateIndex, string input, FiniteStateAutomaton* pAutomat);


	/** these methods are written for one method to implement this Algorithm, but this method doesn't work correctly */
	static void initMinimizingTable(FiniteStateAutomaton* pAutomat, vector< vector<int> >* pMinTable);
	static void printMinTable(vector< vector<int> > * minTable);
	static void fillMinimizingTable(vector< vector<int> > * minTable ,vector<string>* Allinputs, FiniteStateAutomaton* pAutomat );
	static int markDistiguishableStates(vector< vector<int> > * pMinTable, vector<int>* pPredecessorsOfI, vector<int>* pPredecessorsOfJ );

	/** with these the second method is implemented, it does work and construct a correct MinTable*/
	static void initMinimizingTableStruct(FiniteStateAutomaton* pAutomat, vector< vector<StatesPair> >* pMinTable);
	static void printMinTableStruct( vector< vector<StatesPair> > * pMinTable);
	static void fillMinimizingTableStruct(vector< vector<StatesPair> > * minTable ,vector<string>* Allinputs, FiniteStateAutomaton* pAutomat );
	static void mergeStates(vector< vector<StatesPair> > * minTable, FiniteStateAutomaton* pAutomat);
	static void removeRedundantStates(FiniteStateAutomaton* pAutomat);
	static void removeRedundantTransitions(FiniteStateAutomaton* pAutomat);

public:
	static void minimize(FiniteStateAutomaton* pAutomat);
};


#endif /* FSA_TABLEFILLINGMINIMISER_H_ */
