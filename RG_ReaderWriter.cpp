/**
 * @file RG_Substitution.h
 * @author Yacine Smaoui, Florian Hemmelgarn
 *
 * @brief Implementation of the Reader class
 */

#include "RG_ReaderWriter.h"
#include "RG_Production.h"

#include "RG_Substitution.h"

#include <fstream>
#include <sstream>

#include <iostream>  //For debugging
#include <stdlib.h>

using namespace std;

#define   STARTSYMBOL  0
#define   TERMINALS    1
#define   NONTERMINALS 2
#define   PRODUCTIONS  3

/**
 * @brief RGReaderWriter Constructor with the full path of the file to read from as a parameter
 * @param filename full path of the file to read from.
 */
RGReaderWriter::RGReaderWriter(string filename) : fileName(filename)
{
/*
	cout << "****Reader constructor called" << endl ;
*/

}
/**
 * @brief Destructor
 */
RGReaderWriter::~RGReaderWriter()
{
/*
	cout << "**Reader destructor called" << endl ;
*/
}

/**
 * @brief read a Grammar from a text file.
 * @return the read Grammar.
 */
Grammar* RGReaderWriter::Read()
{
	Grammar* grammar = new Grammar();
	int tag= -1;
	ifstream file (fileName.c_str());
	string line = "";

/*
	cout << "filename: " << fileName.c_str() << endl ;
*/

	if(!file)
	{
		cerr << "Sorry, can't open file" << endl;
		exit(1);
	}
	while(!file.eof())
	{
		getline(file,line);
/*
		cout << "line: " << line << endl ;
*/
		if(lineIsTag(line))
		{
/*
			cout << "line is Tag : " << line << endl ;
*/
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

/*
			cout << "line is not a Tag: " << line << endl ;
			cout << "TagCode: " << tag << endl;
*/

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

/**
 * @brief checks if the line (given as a parameter) is a tag
 * different sections in the text file are distinguished by tags, for example [Productions] , [Terminals] ...
 * @param s the line in a string form.
 * @return result of test
 */
int RGReaderWriter::lineIsTag(string s)
{
	if (s.compare("[Start]") == 0 || s.compare("[Terminals]")==0 || s.compare("[NonTerminals]")==0 || s.compare("[Productions]")==0 )
	{
		return 1;
	}
	return 0;
}

/**
 * @brief write the Grammar g into a file
 *
 * Before calling, set a new FileName for the reader if needed.
 *
 * @param g the Grammar to write
 */
void RGReaderWriter::write(Grammar* g)
{
	ofstream oFile (fileName.c_str());

	if(!oFile)
	{
		cerr << "Sorry, can't open file for writing!";
		exit(1);
	}
	oFile << "[Start]" << endl;
	oFile << g->getStartSymbol() << endl;
	oFile << "[Terminals]" << endl;
	for(unsigned int i=0; i< g->getTerminals().getLength() ; i++ )
	{
		oFile << (g->getTerminals())[i] << endl;
	}
	oFile << "[NonTerminals]" << endl;
	for(unsigned int i=0; i<g->getNonTerminals().getLength(); i++)
	{
		oFile << (g->getNonTerminals())[i] << endl;
	}
	oFile << "[Productions]" << endl;
	for(unsigned int i=0; i<g->getProductions().getLength()-1; i++)
	{
		oFile << (g->getProductions())[i]->toString() << endl;
	}
	oFile << (g->getProductions())[g->getProductions().getLength()-1]->toString() ;
}

/**
 * @brief gives a new path of a new file to read/write from/to.
 * @param fileName
 */
void RGReaderWriter::setFileName(string fileName )
{
	this->fileName = fileName ;
}
