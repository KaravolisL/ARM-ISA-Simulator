/////////////////////////////////
/// @file BlxUT.cpp
///
/// @brief Unit Test for BLX Instruction
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
    myProc.GetProcessRegisters().LR = 10;
    myProc.GetProcessRegisters().genRegs[1] = 15;

    myProc.GetLabelDictionary().Insert("MyLabel", 20);

    std::ofstream myOStream("TestFile.txt", std::ofstream::out);
    myOStream << "Test Line";
    myOStream.close();

    Io::FileIterator* pFileIterator = new Io::FileIterator("TestFile.txt");
    myProc.SetFileIterator(pFileIterator);

    KeywordDict::GetInstance().Initialize();
}

////////////////////////////////
/// BranchExchangeAndLinkTest Function
////////////////////////////////
void BranchExchangeAndLinkTest()
{
    instructionStr = "BLX LR";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    assert(myProc.GetProcessRegisters().PC == 10);
    assert(myProc.GetProcessRegisters().LR == 6);
    delete pInstruction;

    instructionStr = "BLX R1";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    assert(myProc.GetProcessRegisters().PC == 15);
    assert(myProc.GetProcessRegisters().LR == 11);
    delete pInstruction;

    instructionStr = "BLX MyLabel";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    assert(myProc.GetProcessRegisters().PC == 20);
    assert(myProc.GetProcessRegisters().LR == 16);
    delete pInstruction;
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

    BranchExchangeAndLinkTest();

    teardown();

    std::cout << "BLX Instruction Unit Test Complete: SUCCESS";
    return 0;
}