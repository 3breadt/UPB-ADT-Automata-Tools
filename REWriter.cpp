/*
 * REWriter.cpp
 *
 *  Created on: 04.06.2012
 *      Author: daniel
 */

#include "REWriter.hpp"
#include "RegularExpression.hpp"
#include "RETreeNode.hpp"
#include <fstream>

/**
 * Creates a string representation of the given regular expression.
 * @param re The regular expression.
 * @return The string representation of the regular expression.
 * @author Daniel Dreibrodt
 */
string REWriter::writeToString(RegularExpression *re) {
	RETreeNode *root = re->getTreeRoot();
	return writeToString(root);
}

/**
 * Writes a string representation of the given regular expression into a file.
 * @param re The regular expression.
 * @author Daniel Dreibrodt
 */
void REWriter::writeToFile(RegularExpression *re, const char *filename) {
	ofstream file(filename, std::ios_base::binary);
	file << writeToString(re);
	file.close();
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

	if(rn->isEmpty()) {
		s += "<epsilon>";
	} else {
		s += rn->getContent();
	}

	if(rn->isOperator()) {
		if(rn->getRight() != NULL) {
			s += writeToString(rn->getRight());
		}
		s += ")";
	}

	return s;
}
