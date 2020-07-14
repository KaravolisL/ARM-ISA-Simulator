/////////////////////////////////
/// @file UnitTestRunner.hpp
///
/// @brief Declarations of the UnitTestRunner class
///
/// @author Luke Karavolis
/////////////////////////////////
#ifndef UNIT_TEST_RUNNER_HPP
#define UNIT_TEST_RUNNER_HPP

// SYSTEM INCLUDES
// (None)

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "List.hpp" // For List

// FORWARD DECLARATIONS
// (None)

////////////////////////////////
/// @class UnitTestRunner
///
/// @brief Class used to facilitate grouping
/// and execution of multiple unit tests in a suite
////////////////////////////////
class UnitTestRunner
{
public:

    ////////////////////////////////
    /// Constructor
    ////////////////////////////////
    UnitTestRunner() :
        m_UnitTestList(List<bool (*func)(void)>())
    {}

    ////////////////////////////////
    /// METHOD NAME: RegisterTest
    ////////////////////////////////
    void RegisterTest(bool (*func)(void));

    ////////////////////////////////
    /// METHOD NAME: Run
    ////////////////////////////////
    void Run();

protected:

private:

    /// List of unit test main functions
    List<bool (*func)(void)> m_UnitTestList;

};

#endif