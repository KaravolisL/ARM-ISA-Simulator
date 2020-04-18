/////////////////////////////////
/// @file FileIteratorUT.cpp
///
/// @brief Unit Test for FileIterator
///
/// @author Luke Karavolis
/////////////////////////////////

// SYSTEM INCLUDES
#include <assert.h>
#include <iostream>
#include <fstream>

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "FileIterator.hpp"  // Test class

////////////////////////////////
/// Test Objects
////////////////////////////////
std::ofstream myOStream("TestFile.txt", std::ofstream::out);
Io::FileIterator myFileIterator("TestFile.txt");

////////////////////////////////
/// Setup Function
////////////////////////////////
void setup()
{
    for (int i = 1; i < 11; i++)
    {
        myOStream << "Line Number " << i << "\n";
    }
    myOStream.close();
}

////////////////////////////////
/// NextTest Function
////////////////////////////////
void NextTest()
{
    int i = 1;
    while(myFileIterator.HasNext())
    {
        std::string line = myFileIterator.Next();
        std::string expectedLine = "Line Number " + std::to_string(i++);
        std::cout << line.c_str() << "\n";
        // The last line will be blank because of the \n when writing the file
        assert(line == expectedLine || line == "");
    }

    try
    {
        myFileIterator.Next();
        assert(false);
    }
    catch(const Io::FileIterator::EndOfFileException& e)
    {
        std::cerr << e.what() << '\n';
    }
    
}

////////////////////////////////
/// GoToLineTest Function
////////////////////////////////
void GoToLineTest()
{
    std::string line = myFileIterator.GoToLine(5);
    std::string expectedLine = "Line Number 5";
    assert(line == expectedLine);

    try
    {
        myFileIterator.GoToLine(100);
        assert(false);
    }
    catch(const Io::FileIterator::EndOfFileException& e)
    {
        std::cerr << e.what() << '\n';
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

    NextTest();
    GoToLineTest();

    teardown();

    std::cout << "FileIterator Unit Test Complete: SUCCESS";
    return 0;
}