/*
 * Reader.h
 *
 *  Created on: 7 juin 2012
 *      Author: yessine
 */

#ifndef READER_H_
#define READER_H_

#include "Grammar.h"



class Reader
{
private:
	string fileName;
public:
	Reader(string fileName);
	~Reader();

	Grammar* Read();
	void setFileName(string fileName);
};


#endif /* READER_H_ */
