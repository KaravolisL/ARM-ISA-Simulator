/////////////////////////////////
/// @file BxUT.cpp
///
/// @brief Unit Test for BX Instruction
///
/// @author Luke Karavolis
/////////////////////////////////

// SYSTEM INCLUDES
// (None)

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "UnitTest.hpp"
#include "InvalidSyntaxException.hpp"
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

    Io::FileIterator* pFileIterator = new Io::FileIterator("TestFile.txt");
    myProc.SetFileIterator(pFileIterator);
}

////////////////////////////////
/// BranchExchangeTest Function
////////////////////////////////
bool BranchExchangeTest()
{
    instructionStr = "BX LR";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    UNIT_ASSERT(myProc.GetProcessRegisters().PC == 10);
    delete pInstruction;

    instructionStr = "BX R1";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    UNIT_ASSERT(myProc.GetProcessRegisters().PC == 15);
    delete pInstruction;

    instructionStr = "BX MyLabel";

    try
    {
        pInstruction = builder.BuildInstruction(instructionStr, &myProc);
        pInstruction->Execute(myProc.GetProcessRegisters());
        UNIT_ASSERT(false);
    }
    catch(const InvalidSyntaxException& e)
    {
        std::cerr << e.what() << '\n';
    }

    return true;
}

////////////////////////////////
/// Main Function
////////////////////////////////
bool BxUT()
{
    UnitTest unitTest("BX Instruction Unit Test");
    unitTest.SetSetup(setup);

    unitTest.AddSubTest(BranchExchangeTest);

    return unitTest.Run();
}