/*
 * @file RegularExpression.cpp
 * @author Daniel Dreibrodt, Konstantin Steinmiller
 */

#include "RegularExpression.hpp"

const string RegularExpression::re_orOp = "|";
const string RegularExpression::re_andOp = ".";
const string RegularExpression::re_starOp = "*";
const string RegularExpression::re_lParen = "(";
const string RegularExpression::re_rParen = ")";

RegularExpression::RegularExpression() {
	p_treeRoot = NULL;
}

RegularExpression::~RegularExpression() {
	if(p_treeRoot != NULL)
		delete p_treeRoot;
}

void RegularExpression::setTreeRoot(RETreeNode *p_tR) {
	p_treeRoot = p_tR;
}

RETreeNode *RegularExpression::getTreeRoot() {
	return p_treeRoot;
}

