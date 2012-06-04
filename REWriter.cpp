/*
 * REWriter.cpp
 *
 *  Created on: 04.06.2012
 *      Author: daniel
 */

#include "REWriter.hpp"
#include "RegularExpression.hpp"
#include "RETreeNode.hpp"

string REWriter::writeToString(RegularExpression *re) {
	RETreeNode *root = re->getTreeRoot();
	return writeToString(root);
}

string REWriter::writeToString(RETreeNode *rn) {
	string s = "";
	if(rn->isOperator()) {
		s += "(";
		if(rn->getLeft() != NULL) {
			s += writeToString(rn->getLeft());
		}
	}

	s += rn->getContent();

	if(rn->isOperator()) {
		if(rn->getRight() != NULL) {
			s += writeToString(rn->getRight());
		}
		s += ")";
	}

	return s;
}
