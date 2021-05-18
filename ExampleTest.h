/***********************************************
* CSE678 Object Oriented Design
*
* Spring 2021
*
* Authors: Steve Brunjes, Zach Demers, Leo Garza
* Group 6
*
* File: ExampleTest.h
*
* Description: Defines and implements examples
*              of callable objects for use as
*              test cases for test harness.
*
***********************************************/

#ifndef __EXAMPLE_TEST_H
#define __EXAMPLE_TEST_H


/** AddFunctor
 * A templated functor whose operator() returns true or false based
 * on _A + _B == _Ans.
*/
template<typename T>
class AddFunctor {
	T _A, _B, _Ans;

public:
	AddFunctor(T A, T B, T Ans) : _A{ A }, _B{ B }, _Ans{ Ans } {}
	bool operator()() {
		return _A + _B == _Ans;
	}
};

/** SubFunctor
 * A templated functor whose operator() returns true or false based
 * on _A - _B == _Ans.
*/
template<typename T>
class SubFunctor {
	T _A, _B, _Ans;

public:
	SubFunctor(T A, T B, T Ans) : _A{ A }, _B{ B }, _Ans{ Ans } {}
	bool operator()() {
		return _A - _B == _Ans;
	}
};

/** MulFunctor
 * A templated functor whose operator() returns true or false based
 * on _A * _B == _Ans.
*/
template<typename T>
class MulFunctor {
	T _A, _B, _Ans;

public:
	MulFunctor(T A, T B, T Ans) : _A{ A }, _B{ B }, _Ans{ Ans } {}
	bool operator()() {
		return _A * _B == _Ans;
	}
};

/** DivFunctor
 * A templated functor whose operator() returns true or false based
 * on _A / _B == _Ans.  This also throws a divide by zero exception
 * in the case where _B is equal to zero.
*/
template<typename T>
class DivFunctor {
	T _A, _B, _Ans;

public:
	DivFunctor(T A, T B, T Ans) : _A{ A }, _B{ B }, _Ans{ Ans } {}
	bool operator()() {
		if (_B == 0) {
			throw std::exception("Divide by zero exception");
		}
		return _A / _B == _Ans;
	}
};


#endif // !__EXAMPLE_TEST_H