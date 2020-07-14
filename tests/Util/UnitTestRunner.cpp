/////////////////////////////////
/// @file UnitTestRunner.cpp
///
/// @brief Implementation of UnitTestRunner
///
/// @copydetail UnitTestRunner
///
/// @author Luke Karavolis
/////////////////////////////////

// SYSTEM INCLUDES
#include <assert.h> // For assert

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "UnitTestRunner.hpp" // Header for class

////////////////////////////////
/// METHOD NAME: UnitTestRunner::RegisterTest
////////////////////////////////
void UnitTestRunner::RegisterTest(bool (*func)(void))
{
    m_UnitTestList.Append(func);
}

////////////////////////////////
/// METHOD NAME: UnitTestRunner::Run
////////////////////////////////
void UnitTestRunner::Run()
{
    uint16_t actual = 0;
    int i;
    for (i = 0; i < m_UnitTestList.GetLength(); i++)
    {
        bool result = m_UnitTestList[i]();
        if (result)
        {
            actual++;
        }
    }

    std::cout << "Tests run: " << i << '\n';
    std::cout << "Tests passed: " << actual << '\n';
    std::cout << "Tests expects: " << m_UnitTestList.GetLength() << '\n';
    assert(actual == m_UnitTestList.GetLength());
}