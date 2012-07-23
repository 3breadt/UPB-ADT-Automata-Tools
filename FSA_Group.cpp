/**
 * @file FSA_Group.cpp
 * Contains the implementation of the Group class.
 */
#include "FSA_Group.hpp"

using namespace std;

/**
 * Standard constructor. Gets the edges of the automaton and saves them to the automata edges vector. 
 * @param p_fsaAutomata A reference to the  automata this group belongs to.
 * @author skowelek, fabiani
 */
Group::Group(FiniteStateAutomaton* p_fsaAutomata)
{
	fsaAutomata = p_fsaAutomata;
	vecAutomataEdges = fsaAutomata->getEdgesFromTransitionList();
}

/**
 * Constructor. Gets the edges of the automaton, saves them to the automata edges vector 
 * and sets the name of the group to the given name.
 * @param p_fsaAutomata A reference to the  automata this group belongs to.
 * @param p_szName Name for this group.
 * @author skowelek, fabiani
 */
Group::Group(FiniteStateAutomaton* p_fsaAutomata, string p_szName)
{
	fsaAutomata = p_fsaAutomata;
	vecAutomataEdges = fsaAutomata->getEdgesFromTransitionList();
	szName = p_szName;
}

/**
 * Adds a group element to the elements vector.
 * @param p_geElement Group element to add to the vector.
 * @author skowelek, fabiani
 */
void Group::addElementToGroup(GroupElement* p_geElement)
{
	vecElements.push_back(p_geElement);
}

/**
 * Removes a group element from the elements vector.
 * @param p_geElement Group element to remove from the vector.
 * @author skowelek, fabiani
 */
void Group::removeElementFromGroup(GroupElement* p_geElement)
{
	for(std::vector<GroupElement*>::iterator it = vecElements.begin(); it != vecElements.end(); ++it) {
		if((*it)->getState()->output() == p_geElement->getState()->output()) {
			vecElements.erase(it);
			break;
		}
	}
}

/**
 * Returns the name of this group.
 * @return The name of this group.
 * @author skowelek, fabiani
 */
string Group::getName()
{
	return szName;
}

/**
 * Sets the name of this group.
 * @param p_szName The name of this group.
 * @author skowelek, fabiani
 */
void Group::setName(string p_szName)
{
	szName = p_szName;
}

/**
 * Compares two group elements by their target groups.
 * @param p_geElementA First element of the comparison.
 * @param p_geElementB Second element of the comparison.
 * @return True if the elements have the same target groups (in same order), false if not
 * @author skowelek, fabiani
 */
bool Group::compareElements(GroupElement* p_geElementA, GroupElement* p_geElementB)
{
	for(unsigned int idx = 0; idx < vecAutomataEdges.size() ; idx++) {
	
		string szGroupA = p_geElementA->getTargetGroups()->at(idx);
		string szGroupB = p_geElementB->getTargetGroups()->at(idx);
		
		if(szGroupA != szGroupB) {
			return false;
		}
	}
	return true;
}

/**
 * Returns the elements vector of this group.
 * @return The elements vector of this group.
 * @author skowelek, fabiani
 */
vector<GroupElement*>* Group::getElements()
{
	return &vecElements;
}

/**
 * Returns the automata edges vector of this group.
 * @return The automata edges vector of this group.
 * @author skowelek, fabiani
 */
vector<string>* Group::getEdges()
{
	return &vecAutomataEdges;
}
