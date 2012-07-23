/**
 * @file FSA_FSAtoREConverter.cpp
 * Contains the implementation of the FSAtoREConverter class.
 */

#include "FSA_FSAtoREConverter.hpp"
#include "FSA_Transition.hpp"
#include "FSA_State.hpp"
#include <vector>
#include <map>
#include <string>
#include "RE_RegularExpression.hpp"
#include "RE_TreeNode.hpp"

namespace std {


/**
 * @brief Converts a FSA to a regular expression using Brzozowski's algebraic method.
 * The method was implemented according to information found at
 * http://cs.stackexchange.com/questions/2016/how-to-convert-finite-automata-to-regular-expressions .
 * This algorithm was then adapted to the existing data structures and improved.
 * @param fsa The FSA to convert.
 * @return A regular expression equivalent to the given automaton.
 * @author Daniel Dreibrodt
 */
RegularExpression *FSAtoREConverter::toRE(FiniteStateAutomaton *fsa) {
    fsa = fsa->fsaConvertNEAtoDEA();
    fsa = fsa->minimize();
    
	vector<State*> *states = fsa->getStateList();
	vector<Transition*> *transitions = fsa->getTransitions();

	//create hash-maps to easily find transitions to/from states
	map<string, vector<Transition*> > transitionsFromState;
	map<string, vector<Transition*> > transitionsToState;    
    
	for(vector<Transition*>::iterator it = transitions->begin(); it != transitions->end(); ++it) {
        Transition *currentTrans = *it;
		//Add transition to transitionsFromState map
        //transitionsFromState.insert(make_pair(currentTrans->getBeginningState(), currentTrans);
		transitionsFromState[currentTrans->getBeginningState()->getName()].push_back(currentTrans);
		//Add transition to transitionsToState map
		transitionsToState[currentTrans->getFinishState()->getName()].push_back(currentTrans);
	}

	///// BRZOZOWSKI ALGORITHM /////
    
    int m,n,i,j;
    
    //m is the number of states
	m = (int)states->size();
    
    //b[n] holds the regular expression that describes how a final state can be reached from state n
	RETreeNode* b[m];
    //a is a matrix that holds all transitions
    //If there is a transition from state 0 to state 1 with the symbol x
    //then a[0][1]=x

	RETreeNode* a[m][m];
    
	//Make sure that start state comes first in state vector
	if(!(states->at(0)->isStartState())) {
		State *firstState = states->at(0);
		for(i=1;i<m;i++) {
			State *currentState = states->at(i);
			if(currentState->isStartState()) {
				(*states)[0] = currentState;
				(*states)[i] = firstState;
				break;
			}
		}
	}

	for(i=0;i<m;i++) {
		//Build b
		State *currentState = states->at(i);
		if(currentState->isFinalState()) {
			b[i] = new RETreeNode("");
		} else {
			b[i] = NULL;
		}
        
		//Build a 
		vector<Transition*> *transFromCurrentState = &(transitionsFromState[currentState->getName()]);
		for(j=0;j<m;j++) {
			a[i][j] = NULL;
            State *targetState = states->at(j);
            
			for(vector<Transition*>::iterator it = transFromCurrentState->begin(); it != transFromCurrentState->end(); ++it) {
				Transition *currentTransition = *it;                
                
				if(currentTransition->getFinishState()->getName() == targetState->getName()) {
					//If several transitions from currentState to targetState exist
					//create a boolean "or" regular expression tree node
					if(a[i][j] == NULL) {
						a[i][j] = new RETreeNode(currentTransition->getEdgeName());
					}
					else {
						RETreeNode *orNode = new RETreeNode(RegularExpression::re_orOp);
						orNode->setRight(a[i][j]->clone());
						orNode->setLeft(new RETreeNode(currentTransition->getEdgeName()));
						a[i][j] = orNode;
                        
					}
				}
			}
		}
	}
    
	for(n=m-1;n>=0;n--) {
		//B[n] := star(A[n,n]) . B[n]
        bool foundNNLoop = false; //Addition to original algorithm
        if(a[n][n]!=NULL) {
            foundNNLoop = true;
            //Loops mean repetition -> star operator
            RETreeNode* bnStarNode = new RETreeNode(RegularExpression::re_starOp);        
            bnStarNode->setLeft(a[n][n]->clone());
            if(b[n]==NULL) {
                b[n] = bnStarNode;
            } else {
                //combine with already existing regex
                RETreeNode* bnAndNode = new RETreeNode(RegularExpression::re_andOp);
                bnAndNode->setRight(bnStarNode);
                bnAndNode->setLeft(b[n]);
                b[n] = bnAndNode;
            }
        }

        //if no loop has been found yet, there exists none for state n
        //thus the following part does not need to be executed
        if(foundNNLoop) {
            for(j=0;j<n;j++) {
                //A[n,j] := star(A[n,n]) . A[n,j];
                RETreeNode* anjStarNode = new RETreeNode(RegularExpression::re_starOp);        
                anjStarNode->setLeft(a[n][n]->clone());
                if(a[n][j]==NULL) {
                    a[n][j] = anjStarNode;
                } else {
                    RETreeNode* anjAndNode = new RETreeNode(RegularExpression::re_andOp);
                    anjAndNode->setRight(anjStarNode);
                    anjAndNode->setLeft(a[n][j]);
                    a[n][j] = anjAndNode;
                }                
            }
        }
		for(i=0;i<n;i++) {
			//B[i] += A[i,n] . B[n]
            RETreeNode* newBiNode = NULL;
            if(a[i][n]!=NULL && b[n]!=NULL) {
                newBiNode = new RETreeNode(RegularExpression::re_andOp);
                newBiNode->setLeft(a[i][n]->clone());
                newBiNode->setRight(b[n]->clone());
            } else if(a[i][n]!=NULL) {
                newBiNode = a[i][n]->clone();
            } else if(b[n]!=NULL) {
                newBiNode = b[n]->clone();            }
			if(b[i]!=NULL && newBiNode != NULL) {
				RETreeNode* biOrNode = new RETreeNode(RegularExpression::re_orOp);
				biOrNode->setLeft(b[i]);
				biOrNode->setRight(newBiNode);
				b[i] = biOrNode;
			} else {
				b[i] = newBiNode;
			}
            
			for(j=0;j<n;j++) {
				//A[i,j] += A[i,n] . A[n,j]
               
                RETreeNode* newAijNode = NULL;
                if(a[i][n]!=NULL && a[n][j]!=NULL) {
                    newAijNode = new RETreeNode(RegularExpression::re_andOp);
                    newAijNode->setLeft(a[i][n]->clone());
                    newAijNode->setRight(a[n][j]->clone());
                } else if(a[i][n]!=NULL) {
                    newAijNode = a[i][n]->clone();
                } else if(a[n][j]!=NULL) {
                    newAijNode = a[n][j]->clone();
                }
                if(a[i][j]!=NULL && newAijNode != NULL) {
                    RETreeNode* aijOrNode = new RETreeNode(RegularExpression::re_orOp);
                    aijOrNode->setLeft(a[i][j]);
                    aijOrNode->setRight(newAijNode);
                    a[i][j] = aijOrNode;                    
                } else {
                    a[i][j] = newAijNode;
                }                
			}
		}
	}
     
	RETreeNode* root = b[0];
    root->simplify();
    
    //Free memory
    for(i=0;i<m;i++) {
        for(j=0;j<m;j++) {
            delete a[i][j];
        }
    }
    for(i=1;i<m;i++) {
        delete b[i];
    }
    
	return new RegularExpression(root);
}

}