/*
 * Grammar.cpp
 *
 *  Created on: 7 juin 2012
 *      Author: yessine
 */

#include "RG_Grammar.h"

Grammar::Grammar()
{
	#ifdef DEBUG
	cout << "****Grammar constructor called" << endl ;
	#endif

}

Grammar::~Grammar()
{
	#ifdef DEBUG
	cout << "**Grammar destructor called: destructing Grammar" << endl ;
	#endif
}

void Grammar::addProduction(Production* prod)
{
	this->Productions.add(prod);
}

void Grammar::setStartSymbol(string s)
{
	this->StartSymbol = s ;
}

void Grammar::addTerminal(string s)
{
	this->Terminals.add(s);
}

void Grammar::addNonTerminal(string s)
{
	this->NonTerminals.add(s);
}

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

DynArray<string> Grammar::getTerminals()
{
	return this->Terminals ;
}

DynArray<string> Grammar::getNonTerminals()
{
	return this->NonTerminals ;
}

string Grammar::getStartSymbol()
{
	return this->StartSymbol ;
}

DynArray<Production*> Grammar::getProductions()
{
	return this->Productions;
}

