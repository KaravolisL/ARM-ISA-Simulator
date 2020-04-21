/////////////////////////////////
/// @file LineParserUT.cpp
///
/// @brief Unit Test for LineParser
///
/// @author Luke Karavolis
/////////////////////////////////

// SYSTEM INCLUDES
#include <assert.h>
#include <iostream>

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "LineParser.hpp"  // Test class
#include "KeywordDict.hpp" // For KeywordDict class

////////////////////////////////
/// Test Objects
////////////////////////////////
// Strings are placed in order of LineType enum
std::string lines[] = {" INCLUDE exampleFile.s ;My comment",
                       "Label",
                       "ADD R1, R2, R3",
                       "; Just a comment",
                       "CONSTANT_NAME EQU 0x500" };

////////////////////////////////
/// Setup Function
////////////////////////////////
void setup()
{
    // Initialize the Keyword dictionary
    KeywordDict::GetInstance().Initialize();
}

////////////////////////////////
/// GetLineTypeTest Function
////////////////////////////////
void GetLineTypeTest()
{
    for (int i = 0 ; i < 5; i++)
    {
        // Construct a line parser using the ith line
        Io::LineParser lineParser(lines[i]);

        Io::LineType lineType = lineParser.GetLineType();
        std::cout << "lineType = " << lineType << '\n';
        assert(lineType == i);
    }
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
int main(int argc, char* argv[])
{
    setup();

    GetLineTypeTest();

    teardown();

    std::cout << "LineParser Unit Test Complete: SUCCESS";
    return 0;
}