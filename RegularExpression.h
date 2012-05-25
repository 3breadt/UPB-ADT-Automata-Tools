/*
 * RegularExpression.h
 *
 *  Created on: 25.05.2012
 *      Author: daniel
 */

#ifndef REGULAREXPRESSION_H_
#define REGULAREXPRESSION_H_

using namespace std;

class RegularExpression {
public:
	RegularExpression();
	virtual ~RegularExpression();
	void setTreeRoot(RETreeNode *p_tR);

	const string re_orOp = "|";
	const string re_andOp = ".";
	const string re_repeatOp = "*";
	const string re_lParen = "(";
	const string re_rParen = ")";


	/**
	 * Checks whether a given string is a valid operator in the
	 * regular expression syntax
	 * @author Daniel Dreibrodt, Konstantin Steinmiller
	 */
	static inline bool isOperator(string s) {
		return s.compare(re_andOp)
			|| s.compare(re_orOp)
			|| s.compare(re_repeatOp)
			|| s.compare(re_lParen)
			|| s.compare(re_rParen);
	}

private:
	//Contains the root of the expression tree
	RETreeNode *p_treeRoot;
};

#endif /* REGULAREXPRESSION_H_ */
