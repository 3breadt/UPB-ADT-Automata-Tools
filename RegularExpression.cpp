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
	// TODO Auto-generated constructor stub

}

RegularExpression::~RegularExpression() {
	// TODO Auto-generated destructor stub
}

void RegularExpression::setTreeRoot(RETreeNode *p_tR) {
	p_treeRoot = p_tR;
}

RETreeNode *RegularExpression::getTreeRoot() {
	return p_treeRoot;
}

