/**
 * @mainpage Automata Tools
 *
 * This library implements finite state automata (deterministic and non-deterministic),
 * regular expressions and regular grammar related functions.
 *
 * The library is developed as part of the lecture "Verlässliches Programmieren in C/C++"
 * of the department <a href="http://adt.uni-paderborn.de/">Angewandte Datentechnik</a>
 * at the <a href="http://www.upb.de">Uni Paderborn</a>.
 **/

#include <iostream>
#include <string>
#include "RegularExpression.hpp"
#include "REReader.hpp"
#include "REWriter.hpp"

using namespace std;

int main(int argc, const char* argv[] ) {
	string filename = argv[0];
	RegularExpression *re = REReader::read(filename);
	string output = REWriter::writeToString(re);
	cout << output << "\n";
}


