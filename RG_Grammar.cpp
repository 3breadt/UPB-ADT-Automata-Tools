/**
 * @file RG_Grammar.cpp
 * @author Yacine Smaoui, Florian Hemmelgarn
 *
 * @brief implementation of the Context Free Grammar class
 */

#include "RG_Grammar.h"
#include <stdlib.h>

#define DEBUG

/**
 * @brief Contructor.
 */
Grammar::Grammar()
{
	#ifdef DEBUG
	cout << "****Grammar constructor called" << endl ;
	#endif

}

/**
 * @brief Destructor
 */
Grammar::~Grammar()
{
	#ifdef DEBUG
	cout << "**Grammar destructor called: destructing Grammar" << endl ;
	#endif
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
		#ifdef DEBUG
		cout << "substitution decoded" << endl ;
		#endif
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

void Grammar::checkIfRegular()
{
	for(unsigned int i=0 ; i < this->getProductions().getLength(); i++ ) // For every Production
	{
		/**
		 * check if the First Symbol of the Substitution is a Terminal
		 */
		if(this->getProductions()[i]->getSubstitution()->symbolIsTerminal(0) != 1  /*TODO and not <epsilon> */ ) //First Symbol in Substitution is not a Terminal
		{
			this->isRegular = 0 ;
#ifdef DEBUG
			this->getProductions()[i]->printProduction();
			cout << "Grammar is not regular: First Substitution Symbol of Production "<<i<<" is not a Terminal" << endl;
#endif
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
#ifdef DEBUG
				this->getProductions()[i]->printProduction();
			cout << "Grammar is not regular: Substitution of Production "<<i<<" doesn't correspond to regular grammar form" << endl;
#endif
				return;
			}
		}
	}
}

void Grammar::initConvert()
{
	this->checkIfRegular();
	if(this->isRegular == 0)
	{
		cerr << "Grammar is not Regular, cannot Convert" << endl ;
		exit(1);
	}
}
