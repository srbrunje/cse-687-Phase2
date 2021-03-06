/***********************************************
* CSE678 Object Oriented Design
*
* Spring 2021
*
* Authors: Steve Brunjes, Zach Demers, Leo Garza
* Group 6
*
* File: Logger.h
*
* Description: Implements a class that is used
*              for logging output to a file
*              and/or a stream.
*
***********************************************/

#include "Logger.h"		// Logger class declarations
#include <iostream>		// std::cout
#include <fstream>		// std::ofstream


/** Default Constructor - public
* Description: Constructs a Logger with given settings.  If left to defaults, it will
*    only output to the default std::ostream.  If a path to an output file is given,
*    it will output to that path and will only output to the stream if bOutputToStream
*    is set to true.
* Paramter 0: a path to an output file (defaults to an empty string)
* Paramter 1: a flag stating if choosing to output to stream also (defaults to false)
* Return: nothing
*/
Logger::Logger(const std::string& aPathToOutputFile,
	const bool bOutputToStream)
{
	_outputStream = &std::cout; // default to std::cout until specified otherwise
	if (aPathToOutputFile.empty()) {
		// Default behavior
		SetOutputToFile(false);
		SetOutputToStream(true);
		SetOutputFile("");
	}
	else {
		// Customized behavior
		SetOutputToFile(true);
		SetOutputToStream(bOutputToStream);
		SetOutputFile(aPathToOutputFile);
	}
}

/** SetOutputToFile - public
 * Description: Sets the _outputToFile PMV to the given boolean
 * Parameter 0: a boolean containing the logic to print to a file or not
 * Return: nothing
*/
void Logger::SetOutputToFile(const bool bOutputToFile)
{
	_outputToFile = bOutputToFile;
}

/** SetOutputToStream - public
 * Description: Sets the _outputToStream PMV to the given boolean
 * Parameter 0: a boolean containing the logic to print to a stream or not
 * Return: nothing
*/
void Logger::SetOutputToStream(const bool bOutputToStream)
{
	_outputToStream = bOutputToStream;

	// If attempting to output to a stream with a bad _outputStream, default to std::cout
	if (_outputToStream && (_outputStream == nullptr || !_outputStream->good()) ) {
		_outputStream = &std::cout;
	}
}

/** SetOutputFile - public
 * Description: Sets the _outputFile PMV to the given string
 * Parameter 0: a string containing the absolute path to the file where output is
 *    desired to be logged in
 * Return: nothing
*/
bool Logger::SetOutputFile(const std::string& aPathToFile)
{
	if (   aPathToFile.find("../") != std::string::npos	// found "../"
		|| aPathToFile.find(":/") == std::string::npos) // did NOT find ":/"
	{
		// presuming using a relative path
		_outputFile = std::filesystem::relative(aPathToFile);
	}
	else {
		// presuming using an absolute path
		_outputFile = std::filesystem::path(aPathToFile);
	}

	// Automatically set _outputToFile to true if the given path is valid
	_outputToFile = std::filesystem::exists(_outputFile);
	return _outputToFile; // return whether or not path was valid
}

/** SetOutputStream - public
 * Description: Sets the _outputStream PMV to a pointer to the given ostream
 * Parameter 0: an ostream where output is desired to be logged
 * Return: nothing
*/
void Logger::SetOutputStream(std::ostream& aOutputStream)
{
	_outputStream = &aOutputStream;          // set the stream value
	_outputToStream = _outputStream->good(); // will output if stream does not contain error bits
}



/** IsOutputtingToFile - public
 * Description: Returns the _outputToFile boolean PMV
 * Parameters: none
 * Return: boolean (_outputToFile PMV)
*/
bool Logger::IsOutputtingToFile() const
{
	return _outputToFile;
}

/** IsOutputtingToStream - public
 * Description: Returns the _outputToStream boolean PMV
 * Parameters: none
 * Return: boolean (_outputToStream PMV)
*/
bool Logger::IsOutputtingToStream() const
{
	return _outputToStream;
}

/** GetOutputFile - public
 * Description: Returns the _outputFile string PMV containing the absolute
 *    path to where output data is logged
 * Parameters: none
 * Return: string (_outputFile PMV)
*/
std::string Logger::GetOutputFile() const
{
	return _outputFile.string();
}

/** GetOutputStream - public
 * Description: Returns the _outputStream ostream pointer PMV containing the
 *    ostream where data is being logged
 * Parameters: none
 * Return: ostream pointer (_outputStream PMV)
*/
std::ostream* Logger::GetOutputStream() const
{
	return _outputStream;
}



/** LogResult - public
 * Description: Logs data retrieved from a TestResult to the appropriate logging outputs
 * Parameter 0: a pointer to a TestResult containing data to be logged
 * Return: nothing
*/
void Logger::LogResult(const TestResult& aTestResult)
{
	// a string to contain the data from the TestResult
	std::string msg = "Test: " + aTestResult.GetName() + "\n"; 

	TestResult::Status status = aTestResult.GetStatus(); // shorthand
	if (status == TestResult::Status::PASS) {
		msg += "Pass/Fail: PASS\n";
	}
	else if (  status == TestResult::Status::FAIL
			|| status == TestResult::Status::FAIL_EXC) 
	{
		msg += "Pass/Fail: FAIL\n";
	}
	else { //if (status == TestResult::Status::NOT_RUN)
		// Cannot log result, test has not finished yet
		// TODO: determine if std::cerr is where errors like this should actually go
		std::cerr << "Unable to log results of test " << aTestResult.GetName()
			<< ".  Test has not finished yet.\n";
	}

	// Get the LogLevel-appropriate data and append that to the message
	LogLevel ll = aTestResult.GetLogLevel(); // shorthand
	if (   ll == LogLevel::Pass_Fail_with_error_message
		|| ll == LogLevel::Pass_Fail_with_error_message_and_test_duration)
	{
		// Record the error messages from the TestResult
		msg += "Errors: " + aTestResult.GetErrorMessage() + '\n';
	}
	if (   ll == LogLevel::Pass_Fail_with_test_duration
		|| ll == LogLevel::Pass_Fail_with_error_message_and_test_duration)
	{
		// Record the timing data from the TestResult		
		msg += "Timing: " + FormatTimeString(aTestResult.GetDuration()) + "\n";		
	}
	msg += '\n'; // append one final new line for clarity
	
	// Call LogMessage() with the result's output as the message to maintain one
	// means of outputting rather than duplicating code
	LogMessage(msg);
}

/** LogMessage - public
 * Description: Logs a given message to the appropriate logging outputs
 * Parameter 0: a message to log in the form of a string
 * Return: nothing
*/
void Logger::LogMessage(const std::string& aMessage)
{
	if (_outputToFile) {
		// Outputting to file
		std::ofstream ofs;
		ofs.open(_outputFile, std::ios::app);
		if (ofs.is_open()) {
			ofs << aMessage;	// log the message to the file
			ofs.close();		// close the file immediately
		}
		else {
			std::cerr << "Unable to open file for logging: bad file path or file already open.\n"
				<< "File path: " << _outputFile << '\n';
		}
	}

	if (_outputToStream) {
		// Outputting to stream
		(*_outputStream) << aMessage;
	}
}

/** ClearContents - public
 * Description: Clears the contents currently contained in the output file
 *    if there is one
 * Parameters: none
 * Return: nothing
*/
void Logger::ClearContents()
{
	// Ensure the output file exists
	if (std::filesystem::exists(_outputFile)) {
		std::ofstream ofs;     // open a file stream
		ofs.open(_outputFile); // opens file and overwrites contents
		ofs.close();           // closes file
		// Since no new contents were added, the file is now blank
	}
}
