#include "FSA_FiniteStateAutomata.hpp"
#include "FSA_EquivalenceChecker.hpp"
#include <set>
#include <map>
#include <vector>

/**
 * @brief Checks the equivalence of two given finite state automata.
 * The performed algorithm is based on the JFLAP implementation found in automata.graph.DFAEqualityChecker coded by Susan H. Rodger.
 * @param fsa1 The one automaton.
 * @param fsa2 The other automaton.
 * @return Whether fsa1 accepts the same language as fsa2.
 * @author Daniel Dreibrodt
 **/
bool FSAEquivalenceChecker::checkEquivalence(FiniteStateAutomata *fsa1, FiniteStateAutomata *fsa2) {
    FSAEquivalenceChecker *checker = new FSAEquivalenceChecker(fsa1, fsa2);
    return checker->check();
}

/**
 * Creates a new equivalence checker object which will work on deterministic, minimized
 * copies of the given automata.
 * @param fsa1 The one automaton.
 * @param fsa2 The other automaton.
 * @author Daniel Dreibrodt
 **/
FSAEquivalenceChecker::FSAEquivalenceChecker(FiniteStateAutomata *fsa1, FiniteStateAutomata *fsa2) {
    dfa1 = fsa1->fsaConvertNEAtoDEA();
    dfa1 = dfa1->minimize();
    
    dfa2 = fsa2->fsaConvertNEAtoDEA();    
    dfa2 = dfa2->minimize();
    
#ifdef DEBUG
    cout << "FSA 1:\n";
    
    dfa1->printStartState();
    dfa1->printFinalState();
    dfa1->outputStateList();
    dfa1->outputTransitionList();
    
    cout << "\nFSA 2:\n";
    
    dfa2->printStartState();
    dfa2->printFinalState();
    dfa2->outputStateList();
    dfa2->outputTransitionList();
#endif
    
    for(vector<Transition*>::iterator it = dfa1->getTransitions()->begin(); it != dfa1->getTransitions()->end(); ++it) {
        Transition *currentTrans = *it;
		//Add transition to transitionsFromState map
		transitionsFromState1[currentTrans->getBeginningState()->getName()].push_back(currentTrans);
	}
    
    for(vector<Transition*>::iterator it = dfa2->getTransitions()->begin(); it != dfa2->getTransitions()->end(); ++it) {
        Transition *currentTrans = *it;
		//Add transition to transitionsFromState map
		transitionsFromState2[currentTrans->getBeginningState()->getName()].push_back(currentTrans);
	}
    
}

/**
 * Performs the equivalence check.
 * @return Whether the two automata are equal.
 * @author Daniel Dreibrodt
 **/
bool FSAEquivalenceChecker::check() {    
    if(dfa1->getStateList()->size() != dfa2->getStateList()->size()) {
#ifdef DEBUG
        cout << "State lists have differing size\n";
#endif
        return false;
    }
    
    return checkStateEquivalence(dfa1->getStartState(), dfa2->getStartState());
}

/**
 * Checks whether the given states are equal
 * For this all transitions from the states are considered and it is checked
 * whether the target states for the same input symbols are equal.
 * @return Whether the two states are equal.
 * @author Daniel Dreibrodtx
 **/
bool FSAEquivalenceChecker::checkStateEquivalence(State *s1, State *s2) {
    map<string,string>::iterator foundMatch = matchingStates.find(s1->getName());
    if(foundMatch != matchingStates.end()) {
        //A counterpart to s1 has already been found        
        //Check whether it is the same as s2
        if((*foundMatch).second != s2->getName()) {
#ifdef DEBUG
            cout << "Couterparts do not match: " << (*foundMatch).second << "!=" << s2->getName() << "\n";
#endif
            return false;
        }
        else return true;
    }
    
    //Check whether finality matches
    if(s1->isFinalState() != s2->isFinalState()) {
        return false;
    }
    
    map<string, Transition*> labelToTrans1, labelToTrans2;
    
    vector<Transition*> t1 = transitionsFromState1[s1->getName()];
    vector<Transition*> t2 = transitionsFromState2[s2->getName()];
    
    if(t1.size() != t2.size())
        return false;
    
    unsigned int i;
    for(i=0; i < t1.size(); i++) {
        labelToTrans1[t1[i]->getEdgeName()] = t1[i];
        labelToTrans2[t2[i]->getEdgeName()] = t2[i];
    }
    
    //assume equivalence
    matchingStates[s1->getName()] = s2->getName();
    
    //For each transition from s1, find corresponding one from s2
    for(i=0; i < t1.size(); i++) {
        string label = t1[i]->getEdgeName();
        Transition* counterpartTransition = labelToTrans2[label];
        if(counterpartTransition == NULL) {
            matchingStates.erase(s1->getName());
            return false;
        }

        bool equal = checkStateEquivalence(t1[i]->getFinishState(), counterpartTransition->getFinishState());
        
        if(!equal) {
            matchingStates.erase(s1->getName());
            return false;
        }
    }
    
    return true;
}
