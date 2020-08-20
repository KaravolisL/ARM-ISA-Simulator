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
    LOG_INFO("Test INFO Log");
    LOG_DEBUG("Test DEBUG Log");
    LOG_ERROR("Test ERROR Log");
    LOG_USER("Test USER Log");

    std::ifstream logFile("Debug.log", std::ifstream::in);
    std::string line;

    std::getline(logFile, line);
    assert(line == "INFO: LoggerUT.cpp : void LogTest() : Line 36 : Test INFO Log");
    std::getline(logFile, line);
    assert(line == "DEBUG: LoggerUT.cpp : void LogTest() : Line 37 : Test DEBUG Log");
    std::getline(logFile, line);
    assert(line == "ERROR: LoggerUT.cpp : void LogTest() : Line 38 : Test ERROR Log");
    std::getline(logFile, line);
    assert(line == "USER: LoggerUT.cpp : void LogTest() : Line 39 : Test USER Log");
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