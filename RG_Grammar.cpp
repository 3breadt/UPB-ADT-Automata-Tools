/**
 * @file RG_Grammar.cpp
 * @author Yacine Smaoui, Florian Hemmelgarn
 *
 * @brief implementation of the Context Free Grammar class
 */

#include "RG_Grammar.h"

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

