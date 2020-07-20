/////////////////////////////////
/// @file BlxUT.cpp
///
/// @brief Unit Test for BLX Instruction
///
/// @author Luke Karavolis
/////////////////////////////////

// SYSTEM INCLUDES
// (None)

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "UnitTest.hpp"
#include "Process.hpp"
#include "FileIterator.hpp"
#include "InstructionBuilder.hpp"
#include "InstructionBase.hpp"

////////////////////////////////
/// Test Objects
////////////////////////////////
static Process myProc = Process();
static InstructionBuilder& builder = InstructionBuilder::GetInstance();
static InstructionBase* pInstruction = nullptr;
static std::string instructionStr;

////////////////////////////////
/// Setup Function
////////////////////////////////
static void setup()
{
    myProc.GetProcessRegisters().PC = 5;
    myProc.GetProcessRegisters().LR = 10;
    myProc.GetProcessRegisters().genRegs[1] = 15;

    myProc.GetLabelDictionary().Insert("MyLabel", 20);

    Io::FileIterator* pFileIterator = new Io::FileIterator("TestFile.txt");
    myProc.SetFileIterator(pFileIterator);
}

////////////////////////////////
/// BranchExchangeAndLinkTest Function
////////////////////////////////
bool BranchExchangeAndLinkTest()
{
    instructionStr = "BLX LR";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    UNIT_ASSERT(myProc.GetProcessRegisters().PC == 10);
    UNIT_ASSERT(myProc.GetProcessRegisters().LR == 6);
    delete pInstruction;

    instructionStr = "BLX R1";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    UNIT_ASSERT(myProc.GetProcessRegisters().PC == 15);
    UNIT_ASSERT(myProc.GetProcessRegisters().LR == 11);
    delete pInstruction;

    instructionStr = "BLX MyLabel";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    UNIT_ASSERT(myProc.GetProcessRegisters().PC == 20);
    UNIT_ASSERT(myProc.GetProcessRegisters().LR == 16);
    delete pInstruction;

    return true;
}

////////////////////////////////
/// Main Function
////////////////////////////////
bool BlxUT()
{
    UnitTest unitTest("BLX Instruction Unit Test");
    unitTest.SetSetup(setup);

    unitTest.AddSubTest(BranchExchangeAndLinkTest);

    return unitTest.Run();
}