/**
 * @file FSA_Group.hpp
 * Contains the definition of the Group class.
 */

#ifndef FSA_GROUP_HPP_
#define FSA_GROUP_HPP_

#include <iostream>
#include <vector>
#include "FSA_FiniteStateAutomaton.hpp"
#include "FSA_State.hpp"
#include "FSA_GroupElement.hpp"

using namespace std;

class Group{
private:
	string szName;
	FiniteStateAutomaton* fsaAutomata;
	vector<string> vecAutomataEdges;
	vector<GroupElement*> vecElements;

public:
	Group(FiniteStateAutomaton* p_fsaAutomata);
	Group(FiniteStateAutomaton* p_fsaAutomata, string p_szName);
	void addElementToGroup(GroupElement* p_geElement);
	void removeElementFromGroup(GroupElement* p_geElement);
	string getName();
	void setName(string p_szName);
	bool compareElements(GroupElement* p_geElementA, GroupElement* p_geElementB);
	vector<GroupElement*>* getElements();
	vector<string>* getEdges();
};

#endif /* FSA_GROUP_HPP_ */
