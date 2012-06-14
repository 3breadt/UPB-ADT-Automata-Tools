/*
 * Substitution.h
 *
 *  Created on: 7 juin 2012
 *      Author: yessine
 */

#ifndef SUBSTITUTION_H_
#define SUBSTITUTION_H_

#include <string>
#include "RG_DynArray.h"

using namespace std;

struct flaggedString {

	string s;
	int isTerminal;

};

class Substitution
{
public:
	Substitution();
	~Substitution();

	void decode(DynArray<string> referenceTerminals, DynArray<string> referenceNonTerminals);
	void setRawString(string s);


public:

	string rawString;
	DynArray<flaggedString> decodedSubstitution;

};


#endif /* SUBSTITUTION_H_ */
