#ifndef __UTILS_H
#define __UTILS_H


/***********************************************
* CSE678 Object Oriented Design
*
* Spring 2021
*
* Authors: Steve Brunjes, Zach Demers, Leo Garza
* Group 6
*
* File: utils.h
*
* Data Defined: namespace timing
*               enum class LogLevel
*
* Description: Provides a space for commonly
*              used data and functions, while
*              protecting them with a namespace.
*
***********************************************/


#include <chrono>		// for timing
#include <string>		// for to_string function
#include <exception>    // std::exception

// Set of shorthands for timing purposes
namespace timing {
	
	typedef std::chrono::high_resolution_clock clock;
	typedef clock::time_point                  hack;

	static hack now() { 
		return clock::now(); 
	}

	static double duration_us(hack aStartTime, hack aEndTime = now()) {
		return std::chrono::duration<double,std::micro>(aEndTime-aStartTime).count();
	}
}

// Enum class to define the level of logging
enum class LogLevel
{
	Pass_Fail,
	Pass_Fail_with_error_message,
	Pass_Fail_with_test_duration,
	Pass_Fail_with_error_message_and_test_duration
};


/** FormatTimeString - private
	* Description: Formats the time string. Scales the units to report units in 1000x incraments.
	*              seconds, milli, micro, nano
	* Parameter 0: The time to scale
	* Return: The formated string
	*/
static std::string FormatTimeString(double dDurration)
{
	std::string rtn = "";

	if (dDurration > 1000000) //scale to seconds
	{
		rtn = std::to_string(dDurration / 1000000) + " seconds";
	}
	else if (dDurration > 1000) //scale to milliseconds
	{
		rtn = std::to_string(dDurration / 1000) + " milliseconds";
	}
	else if (dDurration < 1) //scale to nanoseconds
	{
		rtn = std::to_string(dDurration * 1000) + " nanoseconds";
	}
	else //microseconds
	{
		rtn = std::to_string(dDurration) + " microseconds";
	}

	return rtn;
}



#endif // !__UTILS_H
