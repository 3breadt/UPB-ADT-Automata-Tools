/**
 * @file RG_Production.cpp
 * @author Yacine Smaoui, Florian Hemmelgarn
 *
 * @brief Implementation of the Production class
 */

#include "RG_Production.h"

#include <sstream>

/**
 * @brief Constructor
 */
Production::Production()
{
	#ifdef DEBUG
	cout << "****Production constructor called: constructing Production" << endl ;
	#endif

}

/**
 * @brief Destructor
 */
Production::~Production()
{
	#ifdef DEBUG
	cout << "**Production destructor called: destructing Production" << endl ;
	#endif
}

/**
 * @brief A setter Method to set the Production's Substitution (the right Side).
 * @param subs a pointer on a Substitution Object.
 */
void Production::setSubstitution(Substitution* subs)
{
	this->right = subs;
}

/**
 * @brief A setter Method to set the Production's left Side.
 * @param s A Non-Terminal Symbol.
 */
void Production::setLeftSide(string s)
{
	this->left = s ;
}

/**
 * @brief A getter Method
 * @return a pointer on the Production's Substitution.
 */
Substitution* Production::getSubstitution()
{
	return this->right ;
}

/**
 * @brief called by the Reader
 *
 * Separates the read Production line into a left side string and a right side string.
 *
 * @param line a string containing the whole Production (directly read from file).
 * @param productionArrow the Separating Symbol between the left and right Side of a production
 */
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
/**
 * @brief returns a string form of the Production
 * @return Production as a string
 */
string Production::toString()
{
	return this->left + " " + PRODUCTIONARROW + " " + this->getSubstitution()->toString() ;
}
/**
 *@brief prints the Production
 */
void Production::printProduction()
{
	//cout << this->left << " --> " << this->getSubstitution()->toString() << endl;
	cout << this->toString() << endl;
}




