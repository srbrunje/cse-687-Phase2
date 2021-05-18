/***********************************************
* CSE678 Object Oriented Design
*
* Spring 2021
*
* Authors: Steve Brunjes, Zach Demers, Leo Garza
* Group 6
*
* File: main.cpp
*
* Description: Main program for testing the test
*              harness contained in this project.
*
***********************************************/

#include <iostream>       // input/output to terminal
#include "TestManager.h"  // TestManager class
#include "ExampleTest.h"  // AddFunctor, SubFunctor, MulFunctor, DivFunctor


int main() {

	//======================================================
	// TEST HARNESS SETUP
	//======================================================
	
	// -- Construct a TestManager for interacting with
	TestManager mgr;

	// -- Set the mgr's output options
	//mgr.SetOutputFile("output.txt"); // Define your output here using either relative or absolute paths
	mgr.SetOutputStream(std::cout);


	//======================================================
	// TEST MATH WITH INTEGERS
	//======================================================
	
	// -- Define functors to be used
	AddFunctor<int> iAdd(4, 0, 4); // should PASS 4 + 0 == 4
	SubFunctor<int> iSub(4, 0, 4); // should PASS 4 - 0 == 4
	MulFunctor<int> iMul(4, 0, 4); // should FAIL 4 * 0 != 4
	DivFunctor<int> iDiv(4, 0, 4); // should FAIL with divide by zero exception

	// -- Functors
	mgr.CreateTest(iAdd, LogLevel::Pass_Fail, "Add: 4+0=4", "Error: this should have worked");
	mgr.CreateTest(iSub, LogLevel::Pass_Fail_with_error_message, "Sub: 4-0=4","You shouldn't see this error message");
	mgr.CreateTest(iMul, LogLevel::Pass_Fail_with_error_message_and_test_duration, "Mul: 4*0=4");
	mgr.CreateTest(iDiv, LogLevel::Pass_Fail_with_error_message_and_test_duration, "Div: 4/0=4");

	// -- Lambdas
	mgr.CreateTest([] { return 1 + 2 == 3; }, LogLevel::Pass_Fail_with_error_message, "Lambda 1+2=3");
	mgr.CreateTest([] { return 17 - 32 == 5; }, LogLevel::Pass_Fail_with_error_message_and_test_duration, "Lambda 17-32=5");


	//======================================================
	// TEST MATH WITH DOUBLES
	//======================================================
	
	// -- Define functors to be used
	AddFunctor<double> dAdd(1.23, 0.00, 0.00); // should FAIL 1.23 + 0 != 0
	SubFunctor<double> dSub(1.23, 0.00, 0.00); // should FAIL 1.23 - 0 != 0
	MulFunctor<double> dMul(1.23, 0.00, 0.00); // should PASS 1.23 * 0 == 0
	DivFunctor<double> dDiv(1.23, 0.00, 0.00); // should FAIL with divide by zero exception

	// -- Functors
	mgr.CreateTest(dAdd, LogLevel::Pass_Fail, "Add: 1.23+0.00=0.00");
	mgr.CreateTest(dSub, LogLevel::Pass_Fail_with_error_message, "Sub: 1.23-0.00=0.00","This should FAIL");
	mgr.CreateTest(dMul, LogLevel::Pass_Fail_with_test_duration, "Mul: 1.23*0.00=0.00");
	mgr.CreateTest(dDiv, LogLevel::Pass_Fail_with_error_message_and_test_duration, "Div: 1.23/0.00=0.00");

	// -- Lambdas
	mgr.CreateTest([] { return 1.5 * 0.0 == 0.0; }, LogLevel::Pass_Fail_with_error_message, "Lambda 1.5*0.0=0.0");
	mgr.CreateTest([] { return 1.2 * 3.4 == 5.6; }, LogLevel::Pass_Fail_with_error_message_and_test_duration, "Lambda 1.2*3.4=5.6");



	//======================================================
	// TEST EXECUTION AND RESULT REPORTING
	//======================================================
	
	// -- Execute the tests
	mgr.ExecuteTests();

	// -- Report the results
	mgr.ReportResults();

	return 0;
}
