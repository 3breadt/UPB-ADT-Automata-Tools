/*
 * REReader.h
 *
 *  Created on: 25.05.2012
 *      Author: Daniel Dreibrodt, Konstantin Steinmiller
 */

using namespace std;

#include "RegularExpression.hpp"

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
	static RegularExpression *parse(const char string[], int len);

private:
	static RETreeNode *parseNode(const char string[], int *pos, int len);
	static RETreeNode *parseNode(RETreeNode *left, const char string[], int *pos, int len);
	static RETreeNode *parseLiteral(const char str[], int *pos, int len);
};

#endif /* REREADER_H_ */
