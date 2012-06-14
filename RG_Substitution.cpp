/**
 * @file RG_Substitution.cpp
 * @author Yacine Smaoui, Florian Hemmelgarn
 *
 * @brief Implementation of the Substitution class
 */

#include <stdlib.h>
#include <iostream>
#include <sstream>
#include "RG_Substitution.h"

/**
 * Contructor
 */
Substitution::Substitution()
{
	#ifdef DEBUG
	cout << "****Substitution constructor called: constructing substitution" << endl ;
	#endif
}

/**
 * Destructor
 */
Substitution::~Substitution()
{
	#ifdef DEBUG
	cout << "**Substitution destructor called" << endl ;
	#endif
}

/**
 * @brief Decomposes the rawString into Terminals and Non-Terminals
 *
 * the Terminals and Non-Terminals arrays are given here as a reference
 * to find out wich symbols in the Substitution are Terminals and wich are not
 *
 * @param referenceTerminals    [in] the whole Terminal array of the Grammar
 * @param referenceNonTerminals [in] the whole Non-Terminal array of the Grammar
 */
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

/**
 * @brief A setter method to set the RawString of the Substitution.
 * @param s the Substitution in string form.
 */
void Substitution::setRawString(string s)
{
	this->rawString = s ;
}

string Substitution::getRawString()
{
	return this->rawString ;
}

DynArray<flaggedString>* Substitution::getDecodedSubstitution()
{
	return &(this->decodedSubstitution);
}

string Substitution::toString()
{
	int decodedSubstitutionArrayLength;
	string s ="";
	decodedSubstitutionArrayLength = this->getDecodedSubstitution()->getLength() ;

	for(int i=0 ; i < decodedSubstitutionArrayLength-1; i++)
	{
		s += (*(this->getDecodedSubstitution()))[i].s + " ";
	}
	s += (*(this->getDecodedSubstitution()))[decodedSubstitutionArrayLength-1].s;

	return s ;


}




