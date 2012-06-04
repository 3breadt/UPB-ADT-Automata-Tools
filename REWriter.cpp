/*
 * REWriter.cpp
 *
 *  Created on: 04.06.2012
 *      Author: daniel
 */

#include "REWriter.hpp"
#include "RegularExpression.hpp"
#include "RETreeNode.hpp"

/**
 * Creates a string representation of the given regular expression.
 * @param re The regular expression.
 * @return The string representation of the regular expression.
 */
string REWriter::writeToString(RegularExpression *re) {
	RETreeNode *root = re->getTreeRoot();
	return writeToString(root);
}

/**
 * Converts a regular expression tree to a string by performing
 * an inorder tree walk.
 * @param The node of the regular expression tree.
 * @return The string representation of the regular expression specified by the given node.
 */
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
