/*
 * FSA_ConvertFsaToRg.cpp
 *
 *  Created on: Jun 21, 2012
 *      Author: fabiani
 */

#include "FSA_ConvertFsaToRg.hpp"
#include <vector>

using namespace std;

ConvertFsaToRg::ConvertFsaToRg()
{

}

Grammar* ConvertFsaToRg::convert(FiniteStateAutomata *fsaToConvert)
{
	Grammar graConverted = new Grammar();
	FiniteStateAutomata fsaActual = &fsaToConvert;
	State stTemp;


	vector<Transition*> vecTransitionList = fsaActual.getTransitions();
	DynArray<string> arTemp;

	stTemp = fsaActual.getStartState();
	graConverted.setStartSymbol(stTemp.szName);
	if(stTemp.bFinalState == true)
	{
		Substitution suTemp= new Substitution();
		Production prTemp = new Production();
		suTemp.setRawString("epsilon");
		prTemp.setLeftSide(stTemp.szName);
		prTemp.setSubstitution(&suTemp);
		graConverted.addProduction(&prTemp);
	}

	for(std::vector<Transition*>::iterator it = vecTransitionList.begin(); it != vecTransitionList.end(); ++it)
	{
		Substitution suTemp= new Substitution();
		Production prTemp = new Production();
		suTemp.setRawString((*it)->szEdge + (*it)->stFinish.szName);
		prTemp.setLeftSide((*it)->stBeginning.szName);
		prTemp.setSubstitution(&suTemp);
		graConverted.addProduction(&prTemp);

		arTemp = graConverted.getNonTerminals();
		if(!arTemp.exist((*it)->stBeginning.szName))
		{
			graConverted.addNonTerminal((*it)->stBeginning.szName);
		}
		if(!arTemp.exist((*it)->stFinish.szName))
		{
			graConverted.addNonTerminal((*it)->stFinish.szName);
		}
		arTemp = graConverted.getTerminals();
		if(!arTemp.exist((*it)->szEdge))
		{
			graConverted.addTerminal((*it)->szEdge);
		}
		if((*it)->stFinish.bFinalState == true)
		{
			suTemp.setRawString((*it)->szEdge);
			prTemp.setLeftSide((*it)->stBeginning.szName);
			prTemp.setSubstitution(&suTemp);
			graConverted.addProduction(&prTemp);
		}

	}
return &graConverted;
}
