/*
 * Production.cpp
 *
 *  Created on: 7 juin 2012
 *      Author: yessine
 */


#include "RG_Production.h"

#include <sstream>

Production::Production()
{
	#ifdef DEBUG
	cout << "****Production constructor called: constructing Production" << endl ;
	#endif

}
Production::~Production()
{
	#ifdef DEBUG
	cout << "**Production destructor called: destructing Production" << endl ;
	#endif
}

void Production::setSubstitution(Substitution* subs)
{
	this->right = subs;
}

void Production::setLeftSide(string s)
{
	this->left = s ;
}

Substitution* Production::getSubstitution()
{
	return this->right ;
}

void Production::readProductionFromLine(string line, string productionArrow)
{
	stringstream stream;
	string       wordString;

	stream << line;
	while(!stream.eof())
	{
		stream >> wordString ;
		if(wordString.compare(productionArrow)==0)
		{
			string rawSubstitutionString = "";
			while(!stream.eof())
			{
				stream >> wordString;
				rawSubstitutionString += wordString  ;
				if(!stream.eof())
				{
					rawSubstitutionString += " ";
				}
			}
			this->getSubstitution()->setRawString(rawSubstitutionString);
		}
		else
		{
			this->setLeftSide(wordString);
		}

	}
}






