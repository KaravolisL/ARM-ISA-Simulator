/////////////////////////////////
/// @file OrrUT.cpp
///
/// @brief Unit Test for ORR Instruction
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
static void setup()
{
    for (int i = 0; i < 13; i++)
    {
        myProc.GetProcessRegisters().genRegs[i] = i;
    }
}

////////////////////////////////
/// OrrRegsTest Function
////////////////////////////////
bool OrrRegsTest()
{
    instructionStr = "ORR R0, R1, R2";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    UNIT_ASSERT(myProc.GetProcessRegisters().genRegs[0] == 3);
    delete pInstruction;

    instructionStr = "ORR R0, R4";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    UNIT_ASSERT(myProc.GetProcessRegisters().genRegs[0] == 7);
    delete pInstruction;

    return true;
}

////////////////////////////////
/// OrrLiterals Function
////////////////////////////////
bool OrrLiterals()
{
    instructionStr = "ORR R0, R5, #0xF";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    UNIT_ASSERT(myProc.GetProcessRegisters().genRegs[0] == 15);
    delete pInstruction;

    instructionStr = "ORR R1, #0x12";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    UNIT_ASSERT(myProc.GetProcessRegisters().genRegs[1] == 0x13);
    delete pInstruction;

    return true;
}

////////////////////////////////
/// OrrsTest Function
////////////////////////////////
bool OrrsTest()
{
    // Reset registers
    setup();

    instructionStr = "ORRS R1, R2, #0x80000000";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    UNIT_ASSERT(myProc.GetProcessRegisters().GetNegativeFlag());
    delete pInstruction;

    instructionStr = "ORRS R0, #0";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    UNIT_ASSERT(myProc.GetProcessRegisters().GetZeroFlag());
    UNIT_ASSERT(!myProc.GetProcessRegisters().GetNegativeFlag());
    delete pInstruction;

    return true;
}

////////////////////////////////
/// Main Function
////////////////////////////////
bool OrrUT()
{
    UnitTest unitTest("ORR Instruction Unit Test");
    unitTest.SetSetup(setup);

    unitTest.AddSubTest(OrrRegsTest);
    unitTest.AddSubTest(OrrLiterals);
    unitTest.AddSubTest(OrrsTest);

    return unitTest.Run();
}