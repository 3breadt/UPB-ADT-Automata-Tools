/*
 * @file REReader.cpp
 * @author Daniel Dreibrodt, Konstantin Steinmiller
 */

#include "REReader.hpp"
#include "RETreeNode.hpp"
#include <cstring>
#include <string>
#include <iostream>
#include <fstream>

/**
 * Reads a file and parses the regular expression in it.
 * The file must contain only a single line, which in turn contains the regular expression.
 * @see RegularExpression
 * @author Daniel Dreibrodt, Konstantin Steinmiller
 * @return The regular expression defined in the given file.
 */
RegularExpression *REReader::read(string filename) {
	ifstream file (filename.c_str());
	string str((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
	return parse(str.c_str(), str.length());
}

/**
 * Parses a string and returns the represented regular expression.
 * @author Daniel Dreibrodt, Konstantin Steinmiller
 * @return The regular expression defined in the given string.
 */
RegularExpression *REReader::parse(const char *string, int len) {
	RegularExpression *re = new RegularExpression();
	int pos = 0;
	re->setTreeRoot(parseNode(string, &pos, len));
	return re;
}

/**
 * Parses a regular expression string and builds a regular expression
 * tree. The root node of that tree is returned.
 * @param left The left subtree
 * @param string The regular expression string
 * @param pos The position of the parser in the regular expression
 * @param len The length of the whole regular expression string
 */
RETreeNode *REReader::parseNode(RETreeNode *left, const char string[], int *pos, int len) {
	if(*pos>=len) {
		//end of string reached
		return left;
	}
    switch(string[*pos]) {
    	case '(' : {
    		throw "Read '(' but that is not allowed there!";
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

RETreeNode *REReader::parseNode(const char string[], int *pos, int len) {
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
    		throw "Read ')' but that is not allowed there!";
    		break;
    	}
    	case '|' : {
    		throw "Read '|' but that is not allowed there!";
    		break;
    	}
    	case '.' : {
    		throw "Read '.' but that is not allowed there!";
    		break;
    	}
    	case '*' : {
    		throw "Read '*' but that is not allowed there!";
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

RETreeNode *REReader::parseLiteral(const char str[], int *pos, int len) {
	string s = "";
	while(1) {
		s += str[*pos];
		(*pos)++;
		if(*pos >= len) {
			break;
		}
		if(str[*pos] == '.' || str[*pos] =='|' || str[*pos] == '*' || str[*pos] == '(' || str[*pos] == ')') {
			break;
		}
	}
	return new RETreeNode(s);
}
