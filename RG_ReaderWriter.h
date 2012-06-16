/**
 * @file RG_Substitution.h
 * @author Yacine Smaoui, Florian Hemmelgarn
 *
 * @brief Definition of the Reader class. Allows to read from a file.
 */

#ifndef READER_H_
#define READER_H_

#include "RG_Grammar.h"



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
};


#endif /* READER_H_ */
