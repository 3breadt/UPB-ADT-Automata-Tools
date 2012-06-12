/*
 * main.cpp
 *
 *  Created on: 7 juin 2012
 *      Author: yessine
 */


/*
 * testingDynArray.cpp
 *
 *  Created on: 28 mai 2012
 *      Author: yessine
 */

#include "../Header/DynArray.h"
#include "../Header/Reader.h"
#include "../Header/Grammar.h"

#include <iostream>
using namespace std ;



int main()
{
	Grammar *grammar;
	Reader reader("./Source/data.txt") ;

	grammar = reader.Read();

	cout << "*************** Printing Results ****************" << endl;

	cout << "Grammar Start symbol" << endl;
	cout << grammar->getStartSymbol() << endl;

	cout << "Grammar Terminals" << endl;
	grammar->getTerminals().printArray();

	cout << "Grammar NonTerminals"  << endl;
	grammar->getNonTerminals().printArray();

	cout << "Productions array Length " << grammar->getProductions().getLength()  << endl;
	for(unsigned int i=0 ; i< grammar->getProductions().getLength() ; i++)
	{
		cout << "ProdsLength " << grammar->getProductions().getLength()  << endl;
		cout << "RawString[ " << i <<" ]" << endl;
		cout<< (grammar->getProductions())[i]->getSubstitution()->rawString  << endl;
		cout << "Left Side of Production: " <<  (grammar->getProductions())[i]->left << endl;
		for(unsigned int j=0 ; j<(grammar->getProductions())[i]->getSubstitution()->decodedSubstitution.getLength() ; j++)
		{
			cout << "RawString[ " << i  << " ] Substitution[ "<< j <<" ]" << endl;
			cout << ((grammar->getProductions())[i]->getSubstitution()->decodedSubstitution)[j].s << endl ;
			cout << "Flag : " << ((grammar->getProductions())[i]->getSubstitution()->decodedSubstitution)[j].isTerminal <<endl;

		}
	}


	cout << "*************** Printing Results- ended ****************" << endl;

	//free memory
	for(unsigned int i=0 ; i< grammar->getProductions().getLength() ; i++)
	{
		delete grammar->getProductions()[i]->right ;
		delete grammar->getProductions()[i];
	}




}



