/**
 * @file FSA_FSAtoREConverter.hpp
 * Contains the definition of the FSAtoREConverter class.
 */

#ifndef FSA_FSATORECONVERTER_HPP_
#define FSA_FSATORECONVERTER_HPP_

#include "RE_RegularExpression.hpp"
#include "FSA_FiniteStateAutomaton.hpp"

/**
 * Converts Finite State Automata to Regular Expressions.
 * @author Daniel Dreibrodt
 **/
class FSAtoREConverter {
public:
	static RegularExpression *toRE(FiniteStateAutomaton *fsa);
};

#endif /* FSA_FSATORECONVERTER_HPP_ */
