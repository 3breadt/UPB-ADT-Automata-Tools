/**
 * @file RG_Substitution.h
 * @author Yacine Smaoui, Florian Hemmelgarn
 *
 * @brief Definition of the Reader class. Allows to read from a file.
 */

#ifndef READER_H_
#define READER_H_

#include "RG_Grammar.h"


/**
 * @class RGReaderWriter
 * @brief provides methods to read/write a Grammar from/to a text file
 */
class RGReaderWriter
{
private:
	string fileName;
public:
	RGReaderWriter(string fileName);
	~RGReaderWriter();

	Grammar* Read();
	void write(Grammar* g);
	void setFileName(string fileName);
private:
	int lineIsTag(string s);
};


#endif /* READER_H_ */
