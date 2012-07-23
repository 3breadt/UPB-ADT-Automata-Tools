/**
 * @file FSA_GroupElement.hpp
 * Contains the definition of the GroupElement class.
 */


#ifndef FSA_GROUPELEMENT_HPP_
#define FSA_GROUPELEMENT_HPP_

#include <iostream>
#include <vector>
#include "FSA_State.hpp"

using namespace std;

class GroupElement{
private:
	State* stState;
	vector<string> vecTargetGroups;

public:
	GroupElement();
	GroupElement(State* p_stState);
	void addGroupToTargetVector(string p_szGroupName);
	void removeGroupFromTargetVector(string p_szGroupName);
	State* getState();
	void setState(State* p_stState);
	vector<string>* getTargetGroups();
	void clearTargetGroups();
};

#endif /* FSA_GROUPELEMENT_HPP_ */
