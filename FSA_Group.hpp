#ifndef FSA_GROUP_HPP_
#define FSA_GROUP_HPP_

#include <iostream>
#include <vector>
#include "FSA_FiniteStateAutomata.hpp"
#include "FSA_State.hpp"
#include "FSA_GroupElement.hpp"

using namespace std;

class Group{
private:
	string szName;
	FiniteStateAutomata* fsaAutomata;
	vector<string> vecAutomataEdges;
	vector<GroupElement*> vecElements;

public:
	Group(FiniteStateAutomata* p_fsaAutomata);
	Group(FiniteStateAutomata* p_fsaAutomata, string p_szName);
	void addElementToGroup(GroupElement* p_geElement);
	void removeElementFromGroup(GroupElement* p_geElement);
	string getName();
	void setName(string p_szName);
	bool compareElements(GroupElement* p_geElementA, GroupElement* p_geElementB);
	vector<GroupElement*>* getElements();
	vector<string>* getEdges();
};

#endif /* FSA_GROUP_HPP_ */
