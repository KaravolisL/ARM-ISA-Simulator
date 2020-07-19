/////////////////////////////////
/// @file UnitTest.hpp
///
/// @brief Declarations of the UnitTest class
///
/// @author Luke Karavolis
/////////////////////////////////
#ifndef UNIT_TEST_HPP
#define UNIT_TEST_HPP

// SYSTEM INCLUDES
// (None)

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "List.hpp" // For List

// FORWARD DECLARATIONS
typedef bool (*SubTestFunction)(void);

/// Macro to be used as asserts in unit tests
#define UNIT_ASSERT( expr ) if (!(expr)) { return false; }
#define UNIT_ASSERT_MSG( expr, msg) if (!(expr)) { std::cout << msg << std::endl; return false; }

////////////////////////////////
/// @class UnitTest
///
/// @brief Class used to facilitate construction
/// and execution of a unit test
////////////////////////////////
class UnitTest
{
public:

    ////////////////////////////////
    /// Constructor
    ////////////////////////////////
    UnitTest(const char* pTestName) :
        m_SubTestList(List<SubTestFunction>()),
        m_Setup([](void) {}),
        m_Teardown([](void) {}),
        m_pTestName(pTestName)
    {}

    ////////////////////////////////
    /// METHOD NAME: SetSetup
    ////////////////////////////////
    void SetSetup(void (*setup)(void))
    {
        m_Setup = setup;
    }

    ////////////////////////////////
    /// METHOD NAME: AddSubTest
    ////////////////////////////////
    void AddSubTest(SubTestFunction subTest)
    {
        m_SubTestList.Append(subTest);
    }

    ////////////////////////////////
    /// METHOD NAME: SetTeardown
    ////////////////////////////////
    void SetTeardown(void (*teardown)(void))
    {
        m_Teardown = teardown;
    }

    ////////////////////////////////
    /// METHOD NAME: Run
    ////////////////////////////////
    bool Run()
    {
        std::cout << "*****Running " << m_pTestName << "*****\n";

        m_Setup();

        uint16_t passes = 0;
        int i;
        for (i = 0; i < m_SubTestList.GetLength(); i++)
        {
            bool result = m_SubTestList[i]();
            if (result)
            {
                passes++;
            }
        }

        m_Teardown();

        std::cout << "*****" << m_pTestName << " Results*****\n";
        std::cout << "Tests run: " << i << '\n';
        std::cout << "Tests passed: " << passes << '\n';
        std::cout << "Tests expected: " << m_SubTestList.GetLength() << '\n';

        if (passes != m_SubTestList.GetLength())
        {
            std::cout << "*****" << m_pTestName << " FAILED*****\n";
        }
        else
        {
            std::cout << "*****" << m_pTestName << " PASSED*****\n";
        }

        return (passes == m_SubTestList.GetLength());
    }

protected:

private:

    /// List of unit test main functions
    List<SubTestFunction> m_SubTestList;

    /// Setup function
    void (*m_Setup)(void);

    /// Teardown function
    void (*m_Teardown)(void);

    /// Name of the test suite
    const char* m_pTestName;

    ////////////////////////////////
    /// Copy Constructer
    ////////////////////////////////
    UnitTest(UnitTest const&);

    ////////////////////////////////
    /// Assignment operator
    ////////////////////////////////
    UnitTest& operator=(UnitTest const&);
};

#endif