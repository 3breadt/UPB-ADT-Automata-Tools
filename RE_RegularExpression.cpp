/**
 * @file RegularExpression.cpp
 * Implementation of the regular expression class.
 * @author Daniel Dreibrodt, Konstantin Steinmiller
 */

#include "RE_RegularExpression.hpp"
#include "RE_ReaderWriter.hpp"
#include "FSA_FiniteStateAutomata.hpp";

const string RegularExpression::re_orOp = "|";
const string RegularExpression::re_andOp = ".";
const string RegularExpression::re_starOp = "*";
const string RegularExpression::re_lParen = "(";
const string RegularExpression::re_rParen = ")";

/**
 * Constructs a new regular expression from an existing
 * regular expression tree.
 * @param p_tR The regular expression tree root.
 * @author Daniel Dreibrodt, Konstantin Steinmiller
 */
RegularExpression::RegularExpression(RETreeNode *p_tR) {
	p_treeRoot = p_tR;
}

/**
 * Constructs a new regular expression from a string.
 * @param regex The regular expression string.
 * @author Daniel Dreibrodt, Konstantin Steinmiller
 */
RegularExpression::RegularExpression(string regex) {
	int pos = 0;
	p_treeRoot = REReaderWriter::parseNode(regex.c_str(), &pos, regex.length());
}

RegularExpression::~RegularExpression() {
	if(p_treeRoot != NULL)
		delete p_treeRoot;
}

/**
 * Changes the root node of the regular expression tree.
 * @param p_tR New root node of the regular expression tree.
 * @author Daniel Dreibrodt, Konstantin Steinmiller
 */
void RegularExpression::setTreeRoot(RETreeNode *p_tR) {
	p_treeRoot = p_tR;
}

/**
 * Returns the root node of the regular expression tree.
 * @return The root node of the regular expression tree.
 * @author Daniel Dreibrodt, Konstantin Steinmiller
 */
RETreeNode *RegularExpression::getTreeRoot() {
	return p_treeRoot;
}

/**
 * @brief Converts the regular expression to a finite state automaton.
 * At the moment that automaton is non-deterministic.
 * Future versions will directly produce a minimized, deterministic FSA.
 * @return A finite state automaton representing this regular expression.
 */
FiniteStateAutomata *RegularExpression::toFSA() {
	int labelCounter = 1;
	FiniteStateAutomata *ndfsa = p_treeRoot->toFSA(&labelCounter);
	//TODO convert to DFSA
	//TODO minimize DFSA
	return ndfsa;
}
