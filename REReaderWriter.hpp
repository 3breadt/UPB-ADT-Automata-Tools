/*
 * REReaderWriter.hpp
 *
 *  Created on: 25.05.2012
 *      Author: Daniel Dreibrodt, Konstantin Steinmiller
 */

using namespace std;

#include "RegularExpression.hpp"

#ifndef REREADER_H_
#define REREADER_H_

/**
 * @brief Handles reading and writing of regular expressions.
 *
 * This class can read files and strings and builds RegularExpression objects
 * corresponding to the regular expressions defined in the given files or strings.
 *
 * It also can write regular expressions to strings and files.
 *
 * @author Daniel Dreibrodt, Konstantin Steinmiller
 **/
class REReaderWriter {

public:
	static RegularExpression *read(string filename);
	static RegularExpression *parse(const char string[], int len);
	static string writeToString(RegularExpression *re);
	static void writeToFile(RegularExpression *re, const char* filename);

private:
	static RETreeNode *parseNode(const char string[], int *pos, int len);
	static RETreeNode *parseNode(RETreeNode *left, const char string[], int *pos, int len);
	static RETreeNode *parseLiteral(const char str[], int *pos, int len);
	static string writeToString(RETreeNode *rn);
};

#endif /* REREADER_H_ */
