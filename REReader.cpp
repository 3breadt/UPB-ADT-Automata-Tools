/*
 * @file REReader.cpp
 * @author Daniel Dreibrodt, Konstantin Steinmiller
 */

#include "REReader.h"
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
	ifstream file;
	file.open(filename.c_str(), ios::in);
	char buffer[1024];
	if(file.good()) {
		file.read(buffer, 1024);
		int pos = file.tellg();
		file.close();
		return REReader::parse(buffer, pos);
	} else {
		file.close();
		throw "File could not be opened!";
	}
}

/**
 * Parses a string and returns the represented regular expression.
 * @author Daniel Dreibrodt, Konstantin Steinmiller
 * @return The regular expression defined in the given string.
 */
RegularExpression *REReader::parse(char string[], int len) {
	//TODO
	return NULL;
}
