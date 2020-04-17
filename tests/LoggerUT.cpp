/////////////////////////////////
/// @file LoggerUT.cpp
///
/// @brief Unit Test for Logger
///
/// @author Luke Karavolis
/////////////////////////////////

// SYSTEM INCLUDES
#include <assert.h>
#include <iostream>

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "Logger.hpp"  // Test class

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
/// LogTest Function
////////////////////////////////
void LogTest()
{
    Logger::GetInstance().Log("Test INFO log", Logger::LogLevel::INFO);
    Logger::GetInstance().Log("Test DEBUG log", Logger::LogLevel::DEBUG);
    Logger::GetInstance().Log("Test ERROR log", Logger::LogLevel::ERROR);
}

////////////////////////////////
/// Teardown Function
////////////////////////////////
void teardown()
{
    Logger::GetInstance().Close();
}

////////////////////////////////
/// Main Function
////////////////////////////////
int main(int argc, char* argv[])
{
    setup();

    LogTest();

    teardown();

    std::cout << "Logger Unit Test Complete: SUCCESS";
    return 0;
}