/*
 * Reader.h
 *
 *  Created on: 7 juin 2012
 *      Author: yessine
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
