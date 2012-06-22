/*
 * FSA_FSAtoREConverter.hpp
 *
 *  Created on: 21.06.2012
 *      Author: daniel
 */

#ifndef FSA_FSATORECONVERTER_HPP_
#define FSA_FSATORECONVERTER_HPP_

#include "RE_RegularExpression.hpp"
#include "FSA_FiniteStateAutomata.hpp"

namespace std {

class FSAtoREConverter {
public:
	static RegularExpression *toRE(FiniteStateAutomata *fsa);
};

} /* namespace std */
#endif /* FSA_FSATORECONVERTER_HPP_ */
