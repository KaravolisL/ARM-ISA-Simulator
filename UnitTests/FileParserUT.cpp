/////////////////////////////////
/// @file FileParserUT.cpp
///
/// @brief Unit Test for FileParser
///
/// @author Luke Karavolis
/////////////////////////////////

// SYSTEM INCLUDES
#include <assert.h>
#include <iostream>
#include <string>

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "FileParser.hpp"  // Test class

////////////////////////////////
/// Test Objects
////////////////////////////////
Io::FileParser fileParser("../Example Programs/main.s");
std::string testString = "INCLUDE constants.s   ; My comment";

////////////////////////////////
/// Setup Function
////////////////////////////////
void setup()
{

}

////////////////////////////////
/// StripCommentTest Function
////////////////////////////////
void StripCommentTest()
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
int main(int argc, char* argv[])
{
    setup();

    StripCommentTest();

    teardown();

    std::cout << "FileParser Unit Test Complete: SUCCESS";
    return 0;
}