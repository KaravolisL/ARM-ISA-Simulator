/////////////////////////////////
/// @file FlowCtrlTestSuite.cpp
///
/// @author Luke Karavolis
/////////////////////////////////
#define CATCH_CONFIG_RUNNER

// SYSTEM INCLUDES
// (None)

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "KeywordDict.hpp" // For KeywordDict
#include <catch2/catch.hpp>

int main(int argc, char* argv[])
{
    std::ofstream myOStream("TestFile.txt", std::ofstream::out);
    myOStream << "Test Line";
    myOStream.close();
  
    KeywordDict::GetInstance().Initialize();

    int result = Catch::Session().run(argc, argv);

    return result;
}
