/**
 * @file RE_TreeNode.hpp
 * Definition of the regular expression tree node class.
 * @author Daniel Dreibrodt, Konstantin Steinmiller
 */

#ifndef RETREENODE_H_
#define RETREENODE_H_

#include <string>
#include "FSA_FiniteStateAutomaton.hpp"

using namespace std;

/**
 * @brief Represents nodes in the regular expression tree.
 *
 * A node can either be an operator or a literal. Operator nodes
 * link to one or two nodes which act as operands.
 * @author Daniel Dreibrodt, Konstantin Steinmiller
 */
class RETreeNode {

public:
	RETreeNode(string c);
	virtual ~RETreeNode();
	bool isOperator();
	RETreeNode *getLeft();
	RETreeNode *getRight();
	void setLeft(RETreeNode *p_l);
	void setRight(RETreeNode *p_r);
	string getContent();
	void setContent(string c);
	bool isEmpty();
	void simplify();
	RETreeNode *clone();
	FiniteStateAutomaton *toFSA(int *labelNum);
	string toString();

private:
	//Contains the operand or the value of the literal represented by this node.
	string content;
	//Left and right operands of an operator node
	RETreeNode *p_left, *p_right;
};

#endif /* RETREENODE_H_ */
