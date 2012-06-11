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
	try {
		RegularExpression *re = REReader::read(argv[1]);
		string output = REWriter::writeToString(re);
		cout << output << "\n";
	} catch(int i) {
		cout << "Error: " << i << "\n";
	} catch(char const* c) {
		cout << "Error: " << c << "\n";
	} catch(string & s) {
		cout << "Error: " << s << "\n";
	}

}


