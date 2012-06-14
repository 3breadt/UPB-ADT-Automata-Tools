/*
 * Production.h
 *
 *  Created on: 7 juin 2012
 *      Author: yessine
 */

#ifndef PRODUCTION_H_
#define PRODUCTION_H_

#include <iostream>

#include "RG_Substitution.h"

using namespace std;

class Production
{
public:
	Production();
	~Production();

public:

	string left;
	Substitution* right;   // a composition

public:
	void setSubstitution(Substitution* subs);
	void setLeftSide(string s);
	Substitution* getSubstitution();
	void readProductionFromLine(string line, string productionArrow);
};



#endif /* PRODUCTION_H_ */
