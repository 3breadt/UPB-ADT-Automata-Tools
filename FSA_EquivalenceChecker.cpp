#include "FSA_FiniteStateAutomata.hpp"
#include "FSA_EquivalenceChecker.hpp"

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
    dfa2 = dfa2->fsaConvertNEAtoDEA();
    dfa2 = dfa2->minimize();
    
    for(vector<Transition*>::iterator it = dfa1->getTransitions()->begin(); it != dfa1->getTransitions()->end(); ++it) {
        Transition *currentTrans = *it;
		//Add transition to transitionsFromState map
		transitionsFromState1[currentTrans->getBeginningState()->output()].push_back(currentTrans);
	}
    
    for(vector<Transition*>::iterator it = dfa2->getTransitions()->begin(); it != dfa2->getTransitions()->end(); ++it) {
        Transition *currentTrans = *it;
		//Add transition to transitionsFromState map
		transitionsFromState2[currentTrans->getBeginningState()->output()].push_back(currentTrans);
	}
}

/**
 * Performs the equivalence check.
 * @return Whether the two automata are equal.
 * @author Daniel Dreibrodt
 **/
bool FSAEquivalenceChecker::check() {    
    if(dfa1->getStateList()->size() != dfa2->getStateList()->size()) {
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
    if(matchingStates.find(s1->output()) != matchingStates.end()) {
        //A counterpart to s1 has already been found        
        //Check whether it is the same as s2
        return s1->output().compare(s2->output()) == 0;
    }
    
    //Check whether finality matches
    if(s1->isFinalState() != s2->isFinalState())
        return false;
    
    map<string, Transition*> labelToTrans1, labelToTrans2;
    
    vector<Transition*> t1 = transitionsFromState1[s1->output()];
    vector<Transition*> t2 = transitionsFromState2[s2->output()];
    
    if(t1.size() != t2.size())
        return false;
    
    unsigned int i;
    for(i=0; i < t1.size(); i++) {
        labelToTrans1[t1[i]->getEdgeName()] = t1[i];
        labelToTrans2[t2[i]->getEdgeName()] = t2[i];
    }
    
    //assume equivalence
    matchingStates[s1->output()] = s2->output();
    
    //For each transition from s1, find corresponding one from s2
    for(i=0; i < t1.size(); i++) {
        string label = t1[i]->getEdgeName();
        Transition* counterpartTransition = labelToTrans2[label];
        if(counterpartTransition == NULL) {
            matchingStates.erase(s1->output());
            return false;
        }

        bool equal = checkStateEquivalence(t1[i]->getFinishState(), counterpartTransition->getFinishState());
        
        if(!equal) {
            matchingStates.erase(s1->output());
            return false;
        }
    }
    
    return true;
}
