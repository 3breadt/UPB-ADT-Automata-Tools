/*
 * Substitution.cpp
 *
 *  Created on: 7 juin 2012
 *      Author: yessine
 */

#include <stdlib.h>
#include <iostream>
#include <sstream>
#include "RG_Substitution.h"

Substitution::Substitution()
{
	#ifdef DEBUG
	cout << "****Substitution constructor called: constructing substitution" << endl ;
	#endif
}

Substitution::~Substitution()
{
	#ifdef DEBUG
	cout << "**Substitution destructor called" << endl ;
	#endif
}

void Substitution::decode(DynArray<string> referenceTerminals, DynArray<string> referenceNonTerminals)
{
	stringstream stream;
	flaggedString fString;

	stream << this->rawString;
	#ifdef DEBUG
	cout << "Substitution rawString is :" << this->rawString << endl ;
	#endif

	while (!stream.eof()) {
		stream >> fString.s;

		#ifdef DEBUG
		cout << "fString.s is :" << fString.s  <<endl ;
		#endif

		if (referenceTerminals.exist(fString.s))
		{
			fString.isTerminal = 1;
			this->decodedSubstitution.add(fString);
		}
		else if (referenceNonTerminals.exist(fString.s))
		{
			fString.isTerminal = 0;
			this->decodedSubstitution.add(fString);
		}
		else
		{
			cerr << "ERROR: String is neither a Terminal nor a NonTerminal" << endl;
			exit(1);
		}

	}
}

void Substitution::setRawString(string s)
{
	this->rawString = s ;
}





