/////////////////////////////////
/// @file AndUT.cpp
///
/// @brief Unit Test for AND Instruction
///
/// @author Luke Karavolis
/////////////////////////////////

// SYSTEM INCLUDES
// (None)

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "UnitTest.hpp"
#include "InstructionBase.hpp"
#include "InstructionBuilder.hpp"
#include "Process.hpp"

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
void setup()
{
    for (int i = 0; i < 13; i++)
    {
        myProc.GetProcessRegisters().genRegs[i] = i;
    }
}

////////////////////////////////
/// AndRegTest Function
////////////////////////////////
bool AndRegTest()
{
    instructionStr = "AND R1, R2, R3";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    UNIT_ASSERT(myProc.GetProcessRegisters().genRegs[1] == 2);
    delete pInstruction;

    instructionStr = "AND R4, R5";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    UNIT_ASSERT(myProc.GetProcessRegisters().genRegs[4] == 4);
    delete pInstruction;

    return true;
}

////////////////////////////////
/// AndLiteralTest Function
////////////////////////////////
bool AndLiteralTest()
{
    instructionStr = "AND R7, #3";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    UNIT_ASSERT(myProc.GetProcessRegisters().genRegs[7] == 3);
    delete pInstruction;

    return true;
}

////////////////////////////////
/// AndsTest Function
////////////////////////////////
bool AndsTest()
{
    instructionStr = "ANDS R3, #0";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    UNIT_ASSERT(myProc.GetProcessRegisters().GetZeroFlag());
    UNIT_ASSERT(!myProc.GetProcessRegisters().GetNegativeFlag());
    delete pInstruction;

    // "MOV" R5, #0xFFFFFFFF
    myProc.GetProcessRegisters().genRegs[5] = 0xFFFFFFFF;

    instructionStr = "ANDS R5, #0xFFFF0000";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    UNIT_ASSERT(!myProc.GetProcessRegisters().GetZeroFlag());
    UNIT_ASSERT(myProc.GetProcessRegisters().GetNegativeFlag());
    delete pInstruction;

    return true;
}

////////////////////////////////
/// Main Function
////////////////////////////////
bool AndUT()
{
    UnitTest andInstructionUT("AND Instruction Unit Test");
    andInstructionUT.SetSetup(setup);

    andInstructionUT.AddSubTest(AndRegTest);
    andInstructionUT.AddSubTest(AndLiteralTest);
    andInstructionUT.AddSubTest(AndsTest);

    return andInstructionUT.Run();
}