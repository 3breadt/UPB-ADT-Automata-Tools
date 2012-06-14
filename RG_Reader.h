/**
 * @file RG_Substitution.h
 * @author Yacine Smaoui, Florian Hemmelgarn
 *
 * @brief Definition of the Reader class
 */

#ifndef READER_H_
#define READER_H_

#include "RG_Grammar.h"



class RGReader
{
private:
	string fileName;
public:
	RGReader(string fileName);
	~RGReader();

	Grammar* Read();
	void setFileName(string fileName);
};


#endif /* READER_H_ */
