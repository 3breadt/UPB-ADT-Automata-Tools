/**
 * @file RegularExpression.hpp
 * Definition of the regular expression class.
 * @author Daniel Dreibrodt, Konstantin Steinmiller
 */

#ifndef REGULAREXPRESSION_H_
#define REGULAREXPRESSION_H_

#include <string>
#include "RE_TreeNode.hpp"
#include "FSA_FiniteStateAutomaton.hpp"
#include "RG_Grammar.h"

using namespace std;

/**
 * @brief This class represents regular expressions.
 *
 * Regular expressions are stored in objects of this class. The underlying data structure
 * is an expression tree. Operators are stored in nodes that have their operands as children.
 * Literals are stored in the leafs of the expression tree.
 *
 * Valid operators are:
 *
 * <ul>
 * <li><b>|</b> - boolean or - Either the preceding or the following operand have to occur</li>
 * <li><b>.</b> - and/concatenation - The preceding element has to be followed by the next element.</li>
 * <li><b>*</b> - star quantifier - The preceding element can occur zero or more times</li>
 * <li><b>(</b> - opening parenthesis - Starts a group, used to express precedence</li>
 * <li><b>)</b> - closing parenthesis - Closes a group, used to express precedence</li>
 * </ul>
 *
 * Valid literals are all strings that do not contain spaces or operators.
 *
 * The empty literal is represented by <i>&lt;epsilon&gt;</i>.
 * @author Daniel Dreibrodt, Konstantin Steinmiller
 * @see RETreeNode
 */
class RegularExpression {
public:
	RegularExpression(RETreeNode *p_tR);
	RegularExpression(string regex);
	virtual ~RegularExpression();
	void setTreeRoot(RETreeNode *p_tR);
	RETreeNode *getTreeRoot();
	FiniteStateAutomaton *toFSA();
	Grammar *toRG();
	string toString();

	/** String representation of the boolean or operator **/
	static const string re_orOp;
	/** String representation of the concatenation operator **/
	static const string re_andOp;
	/** String representation of the star operator (preceding element occurs zero or more times) **/
	static const string re_starOp;
	/** String representation of the opening parenthesis **/
	static const string re_lParen;
	/** String representation of the closing parenthesis **/
	static const string re_rParen;

	/**
	 * Checks whether a given string is a valid operator in the
	 * regular expression syntax
	 * @author Daniel Dreibrodt, Konstantin Steinmiller
	 */
	static inline bool isOperator(string s) {
		return s == RegularExpression::re_andOp
			|| s == RegularExpression::re_orOp
			|| s == RegularExpression::re_starOp
			|| s == RegularExpression::re_lParen
            || s == RegularExpression::re_rParen;
	}

private:
	//Contains the root of the expression tree
	RETreeNode *p_treeRoot;
};

#endif /* REGULAREXPRESSION_H_ */
