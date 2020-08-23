/////////////////////////////////
/// @file LoggerUT.cpp
///
/// @brief Unit Test for Logger
///
/// @author Luke Karavolis
/////////////////////////////////

// SYSTEM INCLUDES
#include <sstream>

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include <catch2/catch.hpp>
#include "Logger.hpp"  // Test class

TEST_CASE("Test Logging Capabilites", "[debug]")
{
    LOG_INFO("Test INFO Log");
    LOG_DEBUG("Test DEBUG Log");
    LOG_ERROR("Test ERROR Log");
    LOG_USER("Test USER Log");

    std::ifstream logFile("Debug.log", std::ifstream::in);
    std::string line;
    std::stringstream stream;

    std::getline(logFile, line);
    stream << "INFO: LoggerUT.cpp : " << __PRETTY_FUNCTION__ << " : Line 21 : Test INFO Log";
    REQUIRE(line == stream.str());
    stream.str("");
    std::getline(logFile, line);
    stream << "DEBUG: LoggerUT.cpp : " << __PRETTY_FUNCTION__ << " : Line 22 : Test DEBUG Log";
    REQUIRE(line == stream.str());
    stream.str("");
    std::getline(logFile, line);
    stream << "ERROR: LoggerUT.cpp : " << __PRETTY_FUNCTION__ << " : Line 23 : Test ERROR Log";
    REQUIRE(line == stream.str());
    stream.str("");
    std::getline(logFile, line);
    stream << "USER: LoggerUT.cpp : " << __PRETTY_FUNCTION__ << " : Line 24 : Test USER Log";
    REQUIRE(line == stream.str());
    stream.str("");

    Logger::GetInstance().Close();
}
