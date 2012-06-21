/**
 * @file RG_Production.h
 * @author Yacine Smaoui, Florian Hemmelgarn
 *
 * @brief Definition of the Production class
 */

#ifndef PRODUCTION_H_
#define PRODUCTION_H_

#include <iostream>

#include "RG_Substitution.h"

using namespace std;

#define   PRODUCTIONARROW  "-->"

/**
 * @class Production
 * @brief Represents a Production as an element of a Context-Free Grammar
 *
 * When a Production is used in a context-free Grammar,
 * it substitutes the left side with what is in the right Side.
 * The structure of this class is based on this function.
 */
class Production
{
public:
	Production();
	~Production();

private:

	string left;
	Substitution* right;

public:
	void setSubstitution(Substitution* subs);
	void setLeftSide(string s);
	Substitution* getSubstitution();
	void readProductionFromLine(string line, string productionArrow);
	void printProduction();
	string toString();
	string getLeftSide();
};



#endif /* PRODUCTION_H_ */
