/*
 * REWriter.hpp
 *
 *  Created on: 04.06.2012
 *      Author: daniel
 */

#ifndef REWRITER_HPP_
#define REWRITER_HPP_

#include "RegularExpression.hpp"

using namespace std;

/**
 * @brief Writes regular expressions to strings and files.
 * @author Daniel Dreibrodt
 **/
class REWriter {
public:
	static string writeToString(RegularExpression *re);
	static void writeToFile(RegularExpression *re, const char* filename);
private:
	static string writeToString(RETreeNode *rn);
};

#endif /* REWRITER_HPP_ */
