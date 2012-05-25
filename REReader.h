/*
 * REReader.h
 *
 *  Created on: 25.05.2012
 *      Author: daniel
 */

using namespace std;

#ifndef REREADER_H_
#define REREADER_H_

class REReader {
public:
	static RegularExpression *read(string filename);
	static RegularExpression *parse(char string[], int len);
};

#endif /* REREADER_H_ */
