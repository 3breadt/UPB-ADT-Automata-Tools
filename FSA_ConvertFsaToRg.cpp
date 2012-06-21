/*
 * FSA_ConvertFsaToRg.cpp
 *
 *  Created on: Jun 21, 2012
 *      Author: fabiani
 */

#include "FSA_ConvertFsaToRg.hpp"
#include <vector>
#include "RG_Grammar.h"

using namespace std;

ConvertFsaToRg::ConvertFsaToRg()
{

}

Grammar* ConvertFsaToRg::convert(FiniteStateAutomata *fsaToConvert)
{
	Grammar *graConverted = new Grammar();
	FiniteStateAutomata fsaActual = *fsaToConvert;
	State *stTemp;


	vector<Transition*>* vecTransitionList = fsaActual.getTransitions();
	DynArray<string> arTemp;

	stTemp = fsaActual.getStartState();
	graConverted->setStartSymbol(stTemp->output());
	if(stTemp->isFinalState() == true)
	{
		Substitution suTemp= *new Substitution();
		Production prTemp = *new Production();
		suTemp.setRawString("epsilon");
		prTemp.setLeftSide(stTemp->output());
		prTemp.setSubstitution(&suTemp);
		graConverted->addProduction(&prTemp);
	}

	for(std::vector<Transition*>::iterator it = vecTransitionList->begin(); it != vecTransitionList->end(); ++it)
	{
		Substitution suTemp = *new Substitution();
		Production prTemp = *new Production();
		suTemp.setRawString((*it)->getEdgeName() + (*it)->getFinishState()->output());
		prTemp.setLeftSide((*it)->getBeginningState()->output());
		prTemp.setSubstitution(&suTemp);
		graConverted->addProduction(&prTemp);

		arTemp = graConverted->getNonTerminals();
		if(!arTemp.exist((*it)->getBeginningState()->output()))
		{
			graConverted->addNonTerminal((*it)->getBeginningState()->output());
		}
		if(!arTemp.exist((*it)->getFinishState()->output()))
		{
			graConverted->addNonTerminal((*it)->getFinishState()->output());
		}
		arTemp = graConverted->getTerminals();
		if(!arTemp.exist((*it)->getEdgeName()))
		{
			graConverted->addTerminal((*it)->getEdgeName());
		}
		if((*it)->getFinishState()->isFinalState() == true)
		{
			suTemp.setRawString((*it)->getEdgeName());
			prTemp.setLeftSide((*it)->getBeginningState()->output());
			prTemp.setSubstitution(&suTemp);
			graConverted->addProduction(&prTemp);
		}

	}
return graConverted;
}
