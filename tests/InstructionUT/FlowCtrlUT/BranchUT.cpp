/////////////////////////////////
/// @file BranchUT.cpp
///
/// @brief Unit Test for Branch Instruction
///
/// @author Luke Karavolis
/////////////////////////////////

// SYSTEM INCLUDES
#include <assert.h>
#include <iostream>

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "InvalidSyntaxException.hpp"
#include "Process.hpp"
#include "FileIterator.hpp"
#include "InstructionBuilder.hpp"
#include "InstructionBase.hpp"
#include "KeywordDict.hpp"

////////////////////////////////
/// Test Objects
////////////////////////////////
Process myProc = Process();
InstructionBuilder& builder = InstructionBuilder::GetInstance();
InstructionBase* pInstruction = nullptr;
std::string instructionStr;

////////////////////////////////
/// Setup Function
////////////////////////////////
void setup()
{
    myProc.GetProcessRegisters().PC = 5;

    myProc.GetLabelDictionary().Insert("MyLabel", 10);

    std::ofstream myOStream("TestFile.txt", std::ofstream::out);
    myOStream << "Test Line";
    myOStream.close();

    Io::FileIterator* pFileIterator = new Io::FileIterator("TestFile.txt");
    myProc.SetFileIterator(pFileIterator);

    KeywordDict::GetInstance().Initialize();
}

////////////////////////////////
/// BranchTest Function
////////////////////////////////
void BranchTest()
{
    instructionStr = "B MyLabel";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    assert(myProc.GetProcessRegisters().PC == 10);

    instructionStr = "B BadLabel";
    try
    {
        pInstruction = builder.BuildInstruction(instructionStr, &myProc);
        pInstruction->Execute(myProc.GetProcessRegisters());
        assert(false);
    }
    catch (const InvalidSyntaxException& e)
    {
        std::cout << e.what();
    }
}

////////////////////////////////
/// Teardown Function
////////////////////////////////
void teardown()
{
    delete pInstruction;
}

////////////////////////////////
/// Main Function
////////////////////////////////
int main(int argc, char* argv[])
{
    setup();

    BranchTest();

    teardown();

    std::cout << "Branch Instruction Unit Test Complete: SUCCESS";
    return 0;
}