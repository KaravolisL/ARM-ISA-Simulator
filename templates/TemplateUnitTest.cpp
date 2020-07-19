/////////////////////////////////
/// @file <FILENAME>
///
/// @brief Unit Test for <CLASS NAME>
///
/// @author <Author Name>
/////////////////////////////////

// SYSTEM INCLUDES
// (None)

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "UnitTest.hpp"
#include "<TEST FILE>"  // Test class

////////////////////////////////
/// Test Objects
////////////////////////////////

////////////////////////////////
/// Setup Function
////////////////////////////////
void setup()
{

}

////////////////////////////////
/// <TEST NAME>Test Function
////////////////////////////////
bool sampleTest()
{

}

////////////////////////////////
/// Teardown Function
////////////////////////////////
void teardown()
{

}

////////////////////////////////
/// Main Function
////////////////////////////////
bool unitTestName()
{
    UnitTest nameOfUnitTest("<TEST CLASS> Unit Test");
    nameOfUnitTest.SetSetup(setup);
    nameOfUnitTest.SetTeardown(teardown);

    nameOfUnitTest.AddSubTest(sampleTest);

    return nameOfUnitTest.Run();
}