/////////////////////////////////
/// @file BlUT.cpp
///
/// @brief Unit Test for BL Instruction
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
/// BranchAndLinkTest Function
////////////////////////////////
void BranchAndLinkTest()
{
    instructionStr = "BL MyLabel";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    assert(myProc.GetProcessRegisters().PC == 10);
    assert(myProc.GetProcessRegisters().LR == 6);
    delete pInstruction;

    instructionStr = "BL BadLabel";

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
}

////////////////////////////////
/// Main Function
////////////////////////////////
int main(int argc, char* argv[])
{
    setup();

    BranchAndLinkTest();

    teardown();

    std::cout << "BL Instruction Unit Test Complete: SUCCESS";
    return 0;
}