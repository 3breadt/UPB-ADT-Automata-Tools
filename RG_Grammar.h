/*
 * Grammar.h
 *
 *  Created on: 7 juin 2012
 *      Author: yessine
 */

#ifndef GRAMMAR_H_
#define GRAMMAR_H_

#include <iostream>

#include "RG_DynArray.h"
#include "RG_Production.h"

using namespace std;

class Grammar
{
public:
	Grammar();
	~Grammar();

private:
	DynArray<string> Terminals;
	DynArray<string> NonTerminals;

	DynArray<Production*> Productions;   //composition

	string StartSymbol;

public:
	void addProduction(Production* prod);
	void setStartSymbol(string s);
	void addTerminal (string s);
	void addNonTerminal(string s);
	void processGrammarProductions();

	DynArray<string> getTerminals();
	DynArray<string> getNonTerminals();
	string getStartSymbol();
	DynArray<Production*> getProductions();

};


#endif /* GRAMMAR_H_ */
