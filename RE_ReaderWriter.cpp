/**
 * @file REReaderWriter.cpp
 * Implementation of the reader and writer class for regular expressions.
 * @author Daniel Dreibrodt, Konstantin Steinmiller
 */

#include "RE_ReaderWriter.hpp"
#include "RE_TreeNode.hpp"
#include <cstring>
#include <string>
#include <iostream>
#include <fstream>

/**
 * Reads a file and parses the regular expression in it.
 * The file must contain only a single line, which in turn contains the regular expression.
 * @param filename The path to the input file. The path is relative to the working directory, but can also be defined absolutely.
 * @see RegularExpression
 * @author Daniel Dreibrodt, Konstantin Steinmiller
 * @return The regular expression defined in the given file.
 */
RegularExpression *REReaderWriter::read(string filename) {
	ifstream file (filename.c_str());
	string str((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
	return new RegularExpression(str);
}

/**
 * Parses a string and returns the represented regular expression.
 * @author Daniel Dreibrodt, Konstantin Steinmiller
 * @return The regular expression defined in the given string.
 * @param str The null-terminated string representing the regular expression.
 */
RegularExpression *REReaderWriter::parse(const char str[]) {
	string s = str;
	return new RegularExpression(s);
}

/**
 * Parses a regular expression string and builds a regular expression
 * tree. The root node of that tree is returned.
 * @param string The regular expression string.
 * @param pos The position of the parser in the regular expression.
 * @param len The length of the whole regular expression string.
 * @return The root node of the expression tree.
 * @author Daniel Dreibrodt, Konstantin Steinmiller
 */
RETreeNode *REReaderWriter::parseNode(const char string[], int *pos, int len) {
	if(*pos>=len) {
		//end of string reached
		return NULL;
	}
    switch(string[*pos]) {
    	case '(' : {
    		(*pos)++;
    		RETreeNode *groupNode = parseNode(string, pos, len);
    		return parseNode(groupNode, string, pos, len);
    		break;
    	}
    	case ')' : {
    		throw "Read ')' but that is not allowed here!";
    		break;
    	}
    	case '|' : {
    		throw "Read '|' but that is not allowed here!";
    		break;
    	}
    	case '.' : {
    		throw "Read '.' but that is not allowed here!";
    		break;
    	}
    	case '*' : {
    		throw "Read '*' but that is not allowed here!";
    		break;
    	}
    	case ' ' : {
    		(*pos)++;
    		return parseNode(string, pos, len);
    		break;
    	}
    	default : {
    		RETreeNode *lit = parseLiteral(string,pos,len);
			return parseNode(lit, string, pos, len);
    		break;
    	}
    }
}

/**
 * Parses part of a regular expression string and builds a regular expression
 * tree with the given left subtree. The root node of the new tree is returned.
 * @param left The left subtree.
 * @param string The regular expression string.
 * @param pos The position of the parser in the regular expression.
 * @param len The length of the whole regular expression string.
 * @return The new root node of the expression tree.
 * @author Daniel Dreibrodt, Konstantin Steinmiller
 */
RETreeNode *REReaderWriter::parseNode(RETreeNode *left, const char string[], int *pos, int len) {
	if(*pos>=len) {
		//end of string reached, return last known tree root
		return left;
	}
    switch(string[*pos]) {
    	case '(' : {
    		throw "Read '(' but that is not allowed here!";
    		break;
    	}
    	case ')' : {
    		(*pos)++;
    		return left;
    		break;
    	}
    	case '|' : {
    		RETreeNode *opNode = new RETreeNode("|");
    		(*pos)++;
    		opNode->setLeft(left);
    		opNode->setRight(parseNode(string, pos, len));
    		return opNode;
    		break;
    	}
    	case '.' : {
    		RETreeNode *opNode = new RETreeNode(".");
			(*pos)++;
			opNode->setLeft(left);
			opNode->setRight(parseNode(string, pos, len));
			return opNode;
    		break;
    	}
    	case '*' : {
    		RETreeNode *opNode = new RETreeNode("*");
			(*pos)++;
			opNode->setLeft(left);

			return parseNode(opNode, string, pos, len);
    		break;
    	}
    	case ' ' : {
    		(*pos)++;
    		return parseNode(left, string, pos, len);
    		break;
    	}
    	default : {
    		RETreeNode *lit = parseLiteral(string,pos,len);
    		return parseNode(lit, string, pos, len);
    		break;
    	}
    }
}

/**
 * Parses a literal from a regular expression string.
 * The literal is built by reading from the start position until an illegal character is found.
 * Illegal characters are spaces and operators.
 * @param str The input string
 * @param pos The parsing position
 * @param len The input string length
 * @return A node containing the literal.
 */
RETreeNode *REReaderWriter::parseLiteral(const char str[], int *pos, int len) {
	string s = "";
	while(1) {
		s += str[*pos];
		(*pos)++;
		if(*pos >= len) {
			break;
		}
		//Spaces and operators are not allowed in literals
		if(str[*pos] == ' ' || str[*pos] == '.' || str[*pos] =='|' || str[*pos] == '*' || str[*pos] == '(' || str[*pos] == ')') {
			break;
		}
	}
	return new RETreeNode(s);
}

/**
 * Creates a string representation of the given regular expression.
 * @param re The regular expression.
 * @return The string representation of the regular expression.
 * @author Daniel Dreibrodt
 */
string REReaderWriter::writeToString(RegularExpression *re) {
	RETreeNode *root = re->getTreeRoot();
	return writeToString(root);
}

/**
 * Writes a string representation of the given regular expression into a file.
 * @param re The regular expression.
 * @param filename The path to the output file.
 * @author Daniel Dreibrodt
 */
void REReaderWriter::writeToFile(RegularExpression *re, const char *filename) {
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
string REReaderWriter::writeToString(RETreeNode *rn) {
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
