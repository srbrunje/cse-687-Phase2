# CSE 687 Object Oriented Design Course Project

# Phase 1
Initial design and architecture laid out.
=======
### Team Members
* Steven Brunjes
* Zach Demers
* Leo Garza


## Project Summary
This project is being made in fulfillment of Syracuse University's course, CSE 687 Object Oriented Design, where the team of students have been asked to develop a test harness in the C++ programming language.  The project was split into four phases, as described below.

### Phases
1. Architecture & Design
2. Test Harness Development
3. Multiple Test Capability
4. Remote Operation Capability

At this point, Phase 1 has been completed and Phase 2 is nearing its end.

## Phase 1: Architecture & Design
In this first phase, the team was required to develop an architecture and design of the test harness, prior to writing any code.  The diagrams below are the result.

The architecture chosen should abstract all lower-level functionality away from the user by allowing them to simply interface with the `TestManager` portion.  This allows the user to create tests, execute them, and log their results to a file, stream, or both.



![Phase1-Architecture](https://user-images.githubusercontent.com/62311700/117557812-f6cfa480-b044-11eb-8222-d18e5e05968a.png)

*Figure 1: Phase 1 Architecture Diagram*

The above architecture provides the high-view understanding of the system, while the below design explains the lower-level class diagram.

![Phase1-Design](https://user-images.githubusercontent.com/62311700/117557826-2aaaca00-b045-11eb-9c4c-3ddb13bba686.png)

*Figure 2: Phase 1 Design Diagram*




## Phase 2: Test Harness Development
In this phase, the team's instructions were to implement the design created during Phase 1, and the result can be seen in this repository at the commit title Phase 2 in the `main` branch.

During the implementation, a few small changes had to be made from the original design as can be seen in the following diagram.  Specifically, the following changes were made:

### Modifications
1. The data type holding the output logging file's file path at `Logger::_outputFile` was changed from a `std::string` to a `std::filesystem::path` to allow for relative and absolute path entries and for simpler path validation checks.  *Note:* this modification requires the use of C++17.

### Additions
1. The private member variable `TestManager::_numExc` was added to hold the number of tests that threw a `std::exception` to help describe (especially in the case of running numerous tests) what sorts of failures may have occurred.
2. Along those lines, the `Status` `enum` added a member `FAIL_EXC` that explains when a test resulted in a failure due to an exception being thrown.
3. The private member variable `TestClass::_errorMessage` was added to enable a user to provide a specified error message in the case of a test failing, while providing a default message if none is given or displaying any exception(s) thrown if necessary.
4. The public member function `Logger::ClearContents()` was added to enable simply clearing the output file contents prior to doing another run.


![Phase2-Design](https://user-images.githubusercontent.com/62311700/117557817-fe8f4900-b044-11eb-956c-6fa47cec0c00.png)

*Figure 3: Phase 2 design diagram with modifications/additions since Phase 1 highlighted in bold and underline*

The resulting program provides a fully-functional test harness able to test a variable sized set of callable objects (functors, lambdas, etc.) and to output their results to a specified file, stream or both.  This nearly fulfills the overall requirements listed below, but will place the project in a good place for expanding on with further enhancements as the course progresses.


## Phase 3: Multiple Test Capability
*To be developed by or before 31 May 2021.*

## Phase 4: Remote Operation Capability
*To be developed by or before 21 June 2021.*
