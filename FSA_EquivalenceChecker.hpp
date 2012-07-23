/**
 * @file FSA_EquivalenceChecker.hpp
 * Contains the definition of the FSAEquivalenceChecker class.
 */

#ifndef AutomataTools_FSA_EquivalenceChecker_h
#define AutomataTools_FSA_EquivalenceChecker_h

#include "FSA_FiniteStateAutomaton.hpp"
#include <map>

namespace std {
    
    /**
     * Checks whether two automata represent the same regular language.
     * @author Daniel Dreibrodt
     **/
    class FSAEquivalenceChecker {
    public:
        static bool checkEquivalence(FiniteStateAutomaton *fsa1, FiniteStateAutomaton *fsa2);
    private:
        //Instantiation can only be performed by the helper method checkEquivalence
        FSAEquivalenceChecker(FiniteStateAutomaton *fsa1, FiniteStateAutomaton *fsa2);
        bool check();
        FiniteStateAutomaton *dfa1, *dfa2;
        map<string, string> matchingStates;
        map<string, vector<Transition*> > transitionsFromState1, transitionsFromState2;
        bool checkStateEquivalence(State *s1, State *s2);
    };
    
} /* namespace std */

#endif
