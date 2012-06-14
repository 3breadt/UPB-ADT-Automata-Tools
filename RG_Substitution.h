/**
 * @file RG_Substitution.h
 * @author Yacine Smaoui, Florian Hemmelgarn
 *
 * @brief Definition of the Substitution class
 */

#ifndef SUBSTITUTION_H_
#define SUBSTITUTION_H_

#include <string>
#include "RG_DynArray.h"

using namespace std;

/**
 * @struct flaggedString
 * @brief defines a string with a flag to specify if it is a terminal or not.
 */
struct flaggedString {

	string s;
	int isTerminal;

};

/**
 * @class Substitution
 * @brief defines the right side of a Production in a Grammar
 *
 * composed of:
 *  A RawString : the substitution in a string form without any editing.
 *  and a DecodedSubstitution: a DynArray containing the different Terminals and Non-Terminals composing the Substitution
 */
class Substitution
{
public:
	Substitution();
	~Substitution();

	void decode(DynArray<string> referenceTerminals, DynArray<string> referenceNonTerminals);
	void setRawString(string s);


public:

	/** the substitution in a string form without any editing  */
	string rawString;
	/** a DynArray containing the different Terminals and Non-Terminals composing the Substitution */
	DynArray<flaggedString> decodedSubstitution;

};


#endif /* SUBSTITUTION_H_ */
