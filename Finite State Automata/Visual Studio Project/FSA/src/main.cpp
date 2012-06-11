/*
 * main.cpp
 *
 *  Created on: 29.05.2012
 *      Author: andy
 */

#include<iostream>
#include<cstring>
#include<string>
#include"FinalStateAutomata.hpp"
#include"Transition.hpp"
#include"State.hpp"



using namespace std;

int main()
{
	FinalStateAutomata test;
	test.addState("one");
	test.addState("two");

	test.outputStateList();


	State *testState;
	State *doof = new State("test2",false,true);

	State alphaState("alpha");
	alphaState.setStartState();
	testState = &alphaState;

	test.addState(testState);
	test.addState(doof);

	test.addTransition("three","edge","four");
	test.addTransition("two edge1 one");

	test.outputTransitionList();
	test.testEdge("edge");
	cout<<"StateList nach Transitions einfuegung."<< endl;
	test.outputStateList();

	test.getFinalState();
	test.getStartState();

	test.removeState("two");

	test.write("blabla.txt");

	test.outputStateList();
	test.outputTransitionList();

	return 0;
}
