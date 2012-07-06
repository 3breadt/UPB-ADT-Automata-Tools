#include "FSA_Group.hpp"

using namespace std;

Group::Group(FiniteStateAutomata* p_fsaAutomata)
{
	fsaAutomata = p_fsaAutomata;
	vecAutomataEdges = fsaAutomata->getEdgesFromTransitionList();
}

Group::Group(FiniteStateAutomata* p_fsaAutomata, string p_szName)
{
	fsaAutomata = p_fsaAutomata;
	vecAutomataEdges = fsaAutomata->getEdgesFromTransitionList();
	szName = p_szName;
}

void Group::addElementToGroup(GroupElement* p_geElement)
{
	vecElements.push_back(p_geElement);
}

void Group::removeElementFromGroup(GroupElement* p_geElement)
{
	for(std::vector<GroupElement*>::iterator it = vecElements.begin(); it != vecElements.end(); ++it) {
		if((*it)->getState()->output() == p_geElement->getState()->output()) {
			vecElements.erase(it);
			break;
		}
	}
}

string Group::getName()
{
	return szName;
}

void Group::setName(string p_szName)
{
	szName = p_szName;
}

bool Group::compareElements(GroupElement* p_geElementA, GroupElement* p_geElementB)
{
	for(int idx = 0; idx < vecAutomataEdges.size() ; idx++) {
	
		string szGroupA = p_geElementA->getTargetGroups()->at(idx);
		string szGroupB = p_geElementB->getTargetGroups()->at(idx);
		
		if(szGroupA != szGroupB) {
			return false;
		}
	}
	return true;
}

vector<GroupElement*>* Group::getElements()
{
	return &vecElements;
}

vector<string>* Group::getEdges()
{
	return &vecAutomataEdges;
}