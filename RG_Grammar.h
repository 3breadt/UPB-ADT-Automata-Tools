/**
 * @file RG_Grammar.h
 * @author Yacine Smaoui, Florian Hemmelgarn
 *
 * @brief Definition of the Grammar class
 */
#ifndef GRAMMAR_H_
#define GRAMMAR_H_

#include <iostream>

#include "RG_DynArray.h"
#include "RG_Production.h"

using namespace std;

/**
 * @class Grammar
 * @brief Represents a Context Free Grammar (or Regular Grammar)
 *
 * A context Free Grammar is defined through its Terminals, Non-Terminals and the Start Symbol.
 * For this purpose, the chosen container class is a Dynamic Array defined in DynArray.h
 */
class Grammar
{
public:
	Grammar();
	~Grammar();

private:
	/** a Dynamic array container to store the Terminals of the Grammar   */
	DynArray<string> Terminals;
	/** a Dynamic array container to store the NonTerminals of the Grammar */
	DynArray<string> NonTerminals;
	/** a dynamic array container to store the Productions of the Grammar */
	DynArray<Production*> Productions;   //composition
	/** the Start symbol of the Grammar */
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
