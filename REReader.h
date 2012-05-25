/*
 * REReader.h
 *
 *  Created on: 25.05.2012
 *      Author: Daniel Dreibrodt, Konstantin Steinmiller
 */

using namespace std;

#include "RegularExpression.h"

#ifndef REREADER_H_
#define REREADER_H_

/**
 * @brief Handles parsing of regular expressions.
 *
 * This class can handle files and strings and builds RegularExpression objects
 * corresponding to the regular expressions defined in the given files or strings.
 *
 * @author Daniel Dreibrodt, Konstantin Steinmiller
 **/
class REReader {

public:
	static RegularExpression *read(string filename);
	static RegularExpression *parse(char string[], int len);
};

#endif /* REREADER_H_ */
