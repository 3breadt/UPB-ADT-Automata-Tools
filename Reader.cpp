/*
 * Reader.cpp
 *
 *  Created on: 7 juin 2012
 *      Author: yessine
 */


#include "../Header/Reader.h"
#include "../Header/Production.h"

#include "../Header/Substitution.h"

#include <fstream>
#include <sstream>

#include <iostream>  //For debugging
#include <stdlib.h>

using namespace std;

#define   STARTSYMBOL  0
#define   TERMINALS    1
#define   NONTERMINALS 2
#define   PRODUCTIONS  3

#define   PRODUCTIONARROW  "-->"

//Prototypes
int _lineIsTag(string s);

Reader::Reader(string filename) : fileName(filename)
{
	cout << "****Reader constructor called" << endl ;
}

Reader::~Reader()
{
	cout << "**Reader destructor called" << endl ;
}

Grammar* Reader::Read()
{
	Grammar* grammar = new Grammar();
	int tag= -1;
	ifstream file (fileName.c_str());
	string line = "";

	cout << "filename: " << fileName.c_str() << endl ;

	if(!file)
	{
		cerr << "Sorry, can't open file" << endl;
		exit(1);
	}
	while(!file.eof())
	{
		getline(file,line);
		cout << "line: " << line << endl ;
		if(_lineIsTag(line))
		{
			cout << "line is Tag : " << line << endl ;
			if(line.compare("[Start]")==0)
			{
				tag = STARTSYMBOL ;
			}
			else if(line.compare("[Terminals]")==0)
			{
				tag = TERMINALS ;
			}
			else if(line.compare("[NonTerminals]")==0)
			{
				tag = NONTERMINALS ;
			}
			else if(line.compare("[Productions]")==0)
			{
				tag = PRODUCTIONS ;
			}

		}
		else
		{

			cout << "line is not a Tag: " << line << endl ;
			cout << "TagCode: " << tag << endl;
			if(tag == STARTSYMBOL)
			{
				grammar->setStartSymbol(line) ;
			}
			else if(tag == TERMINALS)
			{
				grammar->addTerminal(line);
			}
			else if(tag == NONTERMINALS)
			{
				grammar->addNonTerminal(line);
			}
			else if (tag == PRODUCTIONS)
			{
				Substitution* substitution = new Substitution();
				Production*   production = new Production();
				production->setSubstitution(substitution);
				production->readProductionFromLine(line,PRODUCTIONARROW);
				grammar->addProduction(production);
			}

		}

	}
	file.close();

	grammar->processGrammarProductions();

	return grammar;
}

int _lineIsTag(string s)
{
	if (s.compare("[Start]") == 0 || s.compare("[Terminals]")==0 || s.compare("[NonTerminals]")==0 || s.compare("[Productions]")==0 )
	{
		return 1;
	}
	return 0;
}
