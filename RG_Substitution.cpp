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
/*
	cout << "****Substitution constructor called: constructing substitution" << endl ;
*/
}

/**
 * Destructor
 */
Substitution::~Substitution()
{
/*
	cout << "**Substitution destructor called" << endl ;
*/
}

/**
 * @brief Decomposes the rawString into Terminals and Non-Terminals
 *
 * the Terminals and Non-Terminals arrays are given here as a reference
 * to find out wich symbols in the Substitution are Terminals and wich are not
 *
 * ATTENTION! : this method is to call as a last step, after reading/adding all Terminals, nonTerminals and productions of a grammar
 * all it does is Take the right side of a production in a string form, and decompose it in a sequence of Terminals and nonTerminals.
 *
 * @param referenceTerminals    [in] the whole Terminal array of the Grammar
 * @param referenceNonTerminals [in] the whole Non-Terminal array of the Grammar
 */
void Substitution::decode(DynArray<string> referenceTerminals, DynArray<string> referenceNonTerminals)
{
	stringstream stream;
	flaggedString fString;

	stream << this->rawString;
/*
	cout << "Substitution rawString is :" << this->rawString << endl ;
*/

	while (!stream.eof()) {
		stream >> fString.s;

/*
		cout << "fString.s is :" << fString.s  <<endl ;
*/

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

/**
 * @brief returns the Substitution as it's read from a file or given manually ( a string form)
 * @return rawString
 */
string Substitution::getRawString()
{
	return this->rawString ;
}

/**
 * @brief returns a pointer on the decoded substitution.
 * @return
 */
DynArray<flaggedString>* Substitution::getDecodedSubstitution()
{
	return &(this->decodedSubstitution);
}

/**
 * @brief converts the decoded substitution into a string (for example to be printed into a file..)
 * @return
 */
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

/**
 * @brief returns the symbol index in the decoded substitution.
 * @param index
 * @return
 */
flaggedString Substitution::getSymbol(int index)
{
	return (*(this->getDecodedSubstitution()))[index] ;
}

/**
 * @brief checks if the symbol at the index "index" is a Terminal.
 * @param index
 * @return
 */
int Substitution::symbolIsTerminal(int index)
{
	return this->getSymbol(index).isTerminal ;
}
/**
 * @brief returns the symbol at the index "index" in a string form.
 * @param index
 * @return
 */
string Substitution::getSymbolstring(int index)
{
	return this->getSymbol(index).s ;
}

/**
 * @brief returns the length of the decodedSubstitution in terms of symbols.
 * @return
 */
int Substitution::getDecodedSubstitutionLength()
{
	return this->getDecodedSubstitution()->getLength();
}


