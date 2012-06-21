/*
 * FSA_ConvertFsaToRg.hpp
 *
 *  Created on: Jun 21, 2012
 *      Author: fabiani
 */

#ifndef FSA_CONVERTFSATORG_HPP_
#define FSA_CONVERTFSATORG_HPP_

#include "FSA_FiniteStateAutomata.hpp"
#include "RG_Grammar.h"
#include <iostream>
#include <vector>

using namespace std;

class ConvertFsaToRg{
public:
	ConvertFsaToRg();
	Grammar* convert(FiniteStateAutomata *fsaToConvert);

};

#endif /* FSA_CONVERTFSATORG_HPP_ */
