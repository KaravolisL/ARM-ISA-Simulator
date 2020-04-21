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

////////////////////////////////
/// Test Objects
////////////////////////////////
std::string lines[] = {" INCLUDE exampleFile.s ;My comment",
                       "Label",
                       "ADD R1, R2, R3",
                       "; Just a comment" };

////////////////////////////////
/// Setup Function
////////////////////////////////
void setup()
{

}

////////////////////////////////
/// GetLineTypeTest Function
////////////////////////////////
void GetLineTypeTest()
{
    for (int i = 0 ; i < 1; i++)
    {
        // Construct a line parser using the ith line
        Io::LineParser lineParser(lines[i]);

        Io::LineParser::LineType lineType = lineParser.GetLineType();
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