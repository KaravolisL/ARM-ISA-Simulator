/////////////////////////////////
/// @file UnitTestSuite.hpp
///
/// @brief Declarations of the UnitTestSuite class
///
/// @author Luke Karavolis
/////////////////////////////////
#ifndef UNIT_TEST_SUITE_HPP
#define UNIT_TEST_SUITE_HPP

// SYSTEM INCLUDES
// (None)

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "List.hpp" // For List

// FORWARD DECLARATIONS
typedef bool (*UnitTestFunction)(void);

////////////////////////////////
/// @class UnitTestSuite
///
/// @brief Class used to facilitate grouping
/// and execution of multiple unit tests in a suite
////////////////////////////////
class UnitTestSuite
{
public:

    ////////////////////////////////
    /// Constructor
    ////////////////////////////////
    UnitTestSuite(const char* SuiteName) :
        m_UnitTestList(List<UnitTestFunction>()),
        m_pSuiteName(SuiteName),
        m_pSuiteSetup([]() {})
    {}

    ////////////////////////////////
    /// METHOD NAME: SetSetup
    ////////////////////////////////
    void SetSetup(void (*setupFunction)(void))
    {
        m_pSuiteSetup = setupFunction;
    }

    ////////////////////////////////
    /// METHOD NAME: AddTest
    ////////////////////////////////
    void AddTest(UnitTestFunction test)
    {
        m_UnitTestList.Append(test);
    }

    ////////////////////////////////
    /// METHOD NAME: Run
    ////////////////////////////////
    bool Run()
    {
        std::cout << "*****Running " << m_pSuiteName << "*****\n";

        m_pSuiteSetup();

        uint16_t passes = 0;
        uint32_t i;
        for (i = 0; i < m_UnitTestList.GetLength(); i++)
        {
            bool result = m_UnitTestList[i]();
            if (result)
            {
                passes++;
            }
        }

        std::cout << "*****" << m_pSuiteName << " Results*****\n";
        std::cout << "Tests run: " << i << '\n';
        std::cout << "Tests passed: " << passes << '\n';
        std::cout << "Tests expected: " << m_UnitTestList.GetLength() << '\n';

        if (passes != m_UnitTestList.GetLength())
        {
            std::cout << "*****" << m_pSuiteName << " FAILED*****\n";
        }
        else
        {
            std::cout << "*****" << m_pSuiteName << " PASSED*****\n";
        }
        
        return (passes == m_UnitTestList.GetLength());
    }

protected:

private:

    /// List of unit test main functions
    List<UnitTestFunction> m_UnitTestList;

    /// Name of the test suite
    const char* m_pSuiteName;

    /// Setup function for suite
    void (*m_pSuiteSetup)(void);

    ////////////////////////////////
    /// Copy Constructer
    ////////////////////////////////
    UnitTestSuite(UnitTestSuite const&);

    ////////////////////////////////
    /// Assignment operator
    ////////////////////////////////
    UnitTestSuite& operator=(UnitTestSuite const&);

};

#endif