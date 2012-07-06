#include "FSA_GroupElement.hpp"

using namespace std;

GroupElement::GroupElement()
{
	stState = NULL;
}

GroupElement::GroupElement(State *p_stState)
{
	this->stState = p_stState;
}

void GroupElement::addGroupToTargetVector(string p_szGroupName)
{
	vecTargetGroups.push_back(p_szGroupName);
}

void GroupElement::removeGroupFromTargetVector(string p_szGroupName)
{
	for(std::vector<string>::iterator it = vecTargetGroups.begin(); it != vecTargetGroups.end(); ++it) {
		if((*it) == p_szGroupName) {
			vecTargetGroups.erase(it);
			break;
		}
	}
}

State* GroupElement::getState()
{
	return stState;
}

void GroupElement::clearTargetGroups() {
	vecTargetGroups.clear();
}

void GroupElement::setState(State* p_stState)
{
	stState = p_stState;
}

vector<string>* GroupElement::getTargetGroups()
{
	return &vecTargetGroups;
}