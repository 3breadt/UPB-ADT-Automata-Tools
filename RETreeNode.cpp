/*
 * @file RETreeNode.cpp
 * @author Daniel Dreibrodt, Konstantin Steinmiller
 */
#include <stddef.h>
#include <string>
#include "RETreeNode.hpp"
#include "RegularExpression.hpp"

using namespace std;

/**
 * Creates a new node in the regular expression tree.
 * @author Daniel Dreibrodt, Konstantin Steinmiller
 * @param c The content of the node. This is either an operator or a literal.
 */
RETreeNode::RETreeNode(string c) {
	content = c;
}

RETreeNode::~RETreeNode() {
	// TODO Auto-generated destructor stub
}

/**
 * Gets the content of the node. This is either an operator or a literal.
 * @author Daniel Dreibrodt, Konstantin Steinmiller
 * @return Node content.
 */
string RETreeNode::getContent() {
	return content;
}

/**
 * Sets the content of the node. This can either be an operator or a literal.
 * Note that you cannot change a node type by giving an operator node a literal value
 * or vice versa.
 * @author Daniel Dreibrodt, Konstantin Steinmiller
 */
void RETreeNode::setContent(string c) {
	if(!isOperator() && RegularExpression::isOperator(c))
		throw "Cannot change a terminal to an operator.";
	if(isOperator() && !RegularExpression::isOperator(c))
		throw "Cannot change an operator to a terminal.";
	content = c;
}

/**
 * Checks whether the given node represents an operator.
 * @author Daniel Dreibrodt, Konstantin Steinmiller
 * @return Returns true only if a child node is present and the content of the node is a valid operator.
 */
bool RETreeNode::isOperator() {
	return (p_left != NULL && RegularExpression::isOperator(content));
}

/**
 * Gets the left operand of this operator. Literals have no left operand.
 * @return Left operand.
 * @author Daniel Dreibrodt, Konstantin Steinmiller
 */
RETreeNode *RETreeNode::getLeft() {
	return p_left;
}

/**
 * Gets the right operand of this operator. Literals have no right operand.
 * @return Right operand.
 * @author Daniel Dreibrodt, Konstantin Steinmiller
 */
RETreeNode *RETreeNode::getRight() {
	return p_right;
}

/**
 * Sets the left operand of this operator. Literals can have no left operand.
 * @param p_l Left operand.
 * @author Daniel Dreibrodt, Konstantin Steinmiller
 */
void RETreeNode::setLeft(RETreeNode *p_l) {
	if(isOperator())
		p_left = p_l;
	else
		throw "Node does not represent an operator. Cannot add children.";
}

/**
 * Sets the right operand of this operator. Literals can have no right operand.
 * @param p_r Right operand.
 * @author Daniel Dreibrodt, Konstantin Steinmiller
 */
void RETreeNode::setRight(RETreeNode *p_r) {
	if(isOperator())
		p_right = p_r;
	else
		throw "Node does not represent an operator. Cannot add children.";
}


