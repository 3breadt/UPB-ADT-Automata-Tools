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

class REWriter {
public:
	static string writeToString(RegularExpression *re);
private:
	static string writeToString(RETreeNode *rn);
};

#endif /* REWRITER_HPP_ */
