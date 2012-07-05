#ifndef AutomataTools_FSA_EquivalenceChecker_h
#define AutomataTools_FSA_EquivalenceChecker_h

#include "FSA_FiniteStateAutomata.hpp"
#include <map>

namespace std {
    
    class FSAEquivalenceChecker {
    public:
        static bool checkEquivalence(FiniteStateAutomata *fsa1, FiniteStateAutomata *fsa2);
    private:
        //Instantiation can only be performed by the helper method checkEquivalence
        FSAEquivalenceChecker(FiniteStateAutomata *fsa1, FiniteStateAutomata *fsa2);
        bool check();
        FiniteStateAutomata *dfa1, *dfa2;
        map<string, string> matchingStates;
        map<string, vector<Transition*> > transitionsFromState1, transitionsFromState2;
        bool checkStateEquivalence(State *s1, State *s2);
    };
    
} /* namespace std */

#endif
