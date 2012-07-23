/**
 * @file FSA_GroupElement.cpp
 * Contains the implementation of the GroupElement class.
 */


#include "FSA_GroupElement.hpp"
#include <string>

using namespace std;

/**
 * Standard constructor.
 */
GroupElement::GroupElement()
{
	stState = NULL;
}

/**
 * Creates a new group element and sets the element's state to the given state.
 * @param p_stState State to use for the group element.
 * @author skowelek, fabiani
 */
GroupElement::GroupElement(State *p_stState)
{
	this->stState = p_stState;
}

/**
 * Adds a group (name) to the target groups vector of this element.
 * @param p_szGroupName Name of the group.
 * @author skowelek, fabiani
 */
void GroupElement::addGroupToTargetVector(string p_szGroupName)
{
	vecTargetGroups.push_back(p_szGroupName);
}

/**
 * Removes a group (name) from the target groups vector of this element.
 * @param p_szGroupName Name of the group.
 * @author skowelek, fabiani
 */
void GroupElement::removeGroupFromTargetVector(string p_szGroupName)
{
	for(std::vector<string>::iterator it = vecTargetGroups.begin(); it != vecTargetGroups.end(); ++it) {
		if((*it) == p_szGroupName) {
			vecTargetGroups.erase(it);
			break;
		}
	}
}

/**
 * Returns the state object of this element.
 * @return The state object of this element.
 * @author skowelek, fabiani
 */
State* GroupElement::getState()
{
	return stState;
}

/**
 * Clears the target groups vector of this element.
 * @author skowelek, fabiani
 */
void GroupElement::clearTargetGroups() {
	vecTargetGroups.clear();
}

/**
 * Sets the state object of this element to the given state.
 * @param p_stState The state object to set the state to.
 * @author skowelek, fabiani
 */
void GroupElement::setState(State* p_stState)
{
	stState = p_stState;
}

/**
 * Returns the target groups vector.
 * @return The target groups vector.
 * @author skowelek, fabiani
 */
vector<string>* GroupElement::getTargetGroups()
{
	return &vecTargetGroups;
}