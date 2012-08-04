/**
 * @file RG_Grammar.cpp
 * @author Yacine Smaoui, Florian Hemmelgarn
 *
 * @brief implementation of the Grammar class
 */

#include "RG_Grammar.h"
#include "FSA_FSAtoREConverter.hpp"
#include <stdlib.h>
#include <sstream>

/**
 * @brief Constructor.
 */
Grammar::Grammar()
{

	//cout << "****Grammar constructor called" << endl ;


}

/**
 * @brief Destructor
 */
Grammar::~Grammar()
{

	//cout << "**Grammar destructor called: destructing Grammar" << endl ;

}

/**
 * @brief adds a production to the Grammar's Productions container.
 * @param prod a pointer on a Production Object.
 */
void Grammar::addProduction(Production* prod)
{
	this->Productions.add(prod);
}

/**
 * @brief A Setter Method for the Start Symbol.
 * @param s the Start Symbol.
 */
void Grammar::setStartSymbol(string s)
{
	this->StartSymbol = s ;
}

/**
 * @brief adds a Terminal Symbol to the Grammar's Terminals container.
 * @param s a Terminal Symbol.
 */
void Grammar::addTerminal(string s)
{
	this->Terminals.add(s);
}

/**
 * @brief adds a Non-Terminal Symbol to the Grammars's Terminals container.
 * @param s
 */
void Grammar::addNonTerminal(string s)
{
	this->NonTerminals.add(s);
}

/**
 * @brief processes the Grammar Productions
 *
 * This is the last called method in RG_Reader.read() .
 * the read method stores a Production at first as a whole string, and this Method decompose it
 * into a left side and its substitution in the right side
 */
void Grammar::processGrammarProductions()
{
	unsigned int i;
	for(i=0; i<this->Productions.getLength(); i++)
	{
		Productions[i]->getSubstitution()->decode(this->Terminals, this->NonTerminals);
/*
		cout << "substitution decoded" << endl ;
*/
	}
}

/**
 * @brief a getter Method
 * @return all the Grammar Terminals stored in a DynArray
 */
DynArray<string> Grammar::getTerminals()
{
	return this->Terminals ;
}

/**
 * @brief a getter Method
 * @return all the Grammar Non-Terminals stored in a DynArray
 */
DynArray<string> Grammar::getNonTerminals()
{
	return this->NonTerminals ;
}

/**
 * @brief a getter Method
 * @return the Start Symbol of the Grammar
 */
string Grammar::getStartSymbol()
{
	return this->StartSymbol ;
}

/**
 * @brief a getter Method
 * @return all the Grammar Productions stored in a DynArray
 */
DynArray<Production*> Grammar::getProductions()
{
	return this->Productions;
}

/**
 * @brief checks if the Grammar is regular or not. the information is stored in isRegular .
 *
 * we use in the project a right-linear regular Grammar.
 *
 * a Grammar is said to be right-linear if every production in P is of the form:
 *
 * A --> x B  or
 *
 * A --> x
 *
 * where A and B are Non-Terminals
 * and x is any string of Terminals or the empty string
 *
 */
void Grammar::checkIfRegular()
{
	this->isRegular = 1 ;
	for(unsigned int i=0 ; i < this->getProductions().getLength(); i++ ) // For every Production
	{
		/**
		 * check if the First Symbol of the Substitution is a Terminal
		 */
		if(this->getProductions()[i]->getSubstitution()->symbolIsTerminal(0) != 1 ) //First Symbol in Substitution is not a Terminal
		{
			this->isRegular = 0 ;
/*
			this->getProductions()[i]->printProduction();
			cout << "Grammar is not regular: First Substitution Symbol of Production "<<i<<" is not a Terminal" << endl;
*/
			return;
		}

		/**
		 * check if the Form of the Substitution corresponds to a Regular Grammar Form
		 */
		for(int j=1 ; j< this->getProductions()[i]->getSubstitution()->getDecodedSubstitutionLength(); j++) // For every symbol in a Substitution
		{
			if(this->getProductions()[i]->getSubstitution()->symbolIsTerminal(j) == 0  //the actual symbol is not a Terminal
					&& this->getProductions()[i]->getSubstitution()->getDecodedSubstitutionLength()-1 > j) // there is more symbols after this NonTerminal
			{
				this->isRegular = 0 ;
/*
				this->getProductions()[i]->printProduction();
			cout << "Grammar is not regular: Substitution of Production "<<i<<" doesn't correspond to regular grammar form" << endl;
*/
				return;
			}
		}
	}
}
/**
 * @brief a getter method
 * @return how many Productions in the Grammar
 */
int Grammar::getNumberOfProductions()
{
	return this->getProductions().getLength() ;
}
/**
 * @brief a getter method
 * @param index Productions are stored in a Dynamic Array, index is the index of the needed Production
 * @return
 */
Production* Grammar::getProduction(int index)
{
	return this->getProductions()[index];
}

/**
 * @brief compares the startSymbol of the Grammar with the parameter symbol
 * @param symbol is one string used in the grammar
 * @return
 */
int Grammar::isStartSymbol(string symbol)
{
	if(this->getStartSymbol().compare(symbol)==0)
	{
		return 1;
	}
	return 0;
}

/**
 * @brief checks if Grammar is a regular Grammar, if it is not the conversion cannot be proceeded.
 */
void Grammar::initConvert()
{
	this->checkIfRegular();
	cout<< "IS REGULAR? :" << this->isRegular<< endl;
	if(this->isRegular == 0)
	{
		cerr << "Grammar is not Regular, cannot Convert" << endl ;
		exit(1);
	}
}
/**
 * @brief converts a Regular Grammar to a Finite States Automaton
 *
 *
 *
 * @return the FSA
 */
FiniteStateAutomaton* Grammar::convertToFSA()
{
	this->initConvert();

	FiniteStateAutomaton* automat = new FiniteStateAutomaton();

	/**First end of the Transition */
	State* pFromState;

	for(int i=0; i< this->getNumberOfProductions() ; i++)
	{
		Production*    pProd = this->getProduction(i);
		Substitution*  pSubs = pProd->getSubstitution();
		string leftSide    = pProd->getLeftSide();

		if (!automat->bStateExists(leftSide))
		{
			automat->addState(leftSide);
		}
		if (this->isStartSymbol(leftSide))
		{
			automat->getState(leftSide)->setStartState(true);
		}
		pFromState = automat->getState(leftSide);

		/** if Production has the form: A --> <epsilon> */
		if(pSubs->getSymbolstring(0).compare(EMPTY_STRING) == 0)
		{
			pFromState->setFinalState(true);
		}
		else
		{
			int substitutionlength= pSubs->getDecodedSubstitutionLength();

			/** For every symbol in the Substitution */
			for(int j=0 ; j < substitutionlength; j++)
			{
				/** the current symbol is a Terminal */
				if(pSubs->symbolIsTerminal(j))
				{
					/** the current Symbol is the last one in the Substitution, and it is a Terminal */
					if(j+1 == substitutionlength )
					{
						if (!automat->bStateExists("endState"))
						{
							automat->addState("endState");
							automat->getState("endState")->setFinalState(true);
						}
						automat->addTransition(pFromState->output(),pSubs->getSymbolstring(j),"endState");
					}
					/** the current symbol is not the last one in the substitution */
					else
					{
						/** the next symbol in the Substitution is a NonTerminal */
						if(!pSubs->symbolIsTerminal(j+1))
						{
							if (!automat->bStateExists(pSubs->getSymbolstring(j+1)))
							{
								automat->addState(pSubs->getSymbolstring(j+1));
							}
							automat->addTransition(pFromState->output(),pSubs->getSymbolstring(j),pSubs->getSymbolstring(j+1));
						}
						/** the next symbol in the Substitution is a Terminal */
						else
						{
							stringstream ss;
							string stateName;
							ss << "TransitionState" << i << j ;
							ss >> stateName ;
							automat->addState(stateName);
							automat->addTransition(pFromState->output(),pSubs->getSymbolstring(j),stateName);
							pFromState = automat->getState(stateName);
						}
					}

				}
			}
		}
		
	}
	automat->getFinalStates();
	FiniteStateAutomaton* deterministic_automat = automat->fsaConvertNEAtoDEA();
	delete automat;

	return deterministic_automat;

}

/**
 * @brief converts a Grammar to a regular expression
 *
 * uses the conversion from FSA to RE
 *
 * @return
 */
/*****************************************
RegularExpression* Grammar::convertToRE()
{
	this->initConvert();

	return FSAtoREConverter::toRE(this->convertToFSA());

}
******************************************/

