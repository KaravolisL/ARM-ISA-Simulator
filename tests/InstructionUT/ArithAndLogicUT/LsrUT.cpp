/////////////////////////////////
/// @file LsrUT.cpp
///
/// @brief Unit Test for LSR Instruction
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
/// LsrRegsTest Function
////////////////////////////////
bool LsrRegsTest()
{
    instructionStr = "LSR R0, R8, R2";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    UNIT_ASSERT(myProc.GetProcessRegisters().genRegs[0] == 2);
    delete pInstruction;

    instructionStr = "LSR R8, R3";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    UNIT_ASSERT(myProc.GetProcessRegisters().genRegs[8] == 1);
    delete pInstruction;

    return true;
}

////////////////////////////////
/// LsrLiterals Function
////////////////////////////////
bool LsrLiterals()
{
    instructionStr = "LSR R0, R10, #0x2";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    UNIT_ASSERT(myProc.GetProcessRegisters().genRegs[0] == 2);
    delete pInstruction;

    instructionStr = "LSR R12, #0x3";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    UNIT_ASSERT(myProc.GetProcessRegisters().genRegs[12] == 1);
    delete pInstruction;

    return true;
}

////////////////////////////////
/// LsrsTest Function
////////////////////////////////
bool LsrsTest()
{
    // Reset registers
    setup();

    instructionStr = "LSRS R0, R1";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    UNIT_ASSERT(myProc.GetProcessRegisters().GetZeroFlag());
    UNIT_ASSERT(!myProc.GetProcessRegisters().GetNegativeFlag());
    UNIT_ASSERT(!myProc.GetProcessRegisters().GetCarryFlag());
    delete pInstruction;

    instructionStr = "LSRS R7, #2";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    UNIT_ASSERT(!myProc.GetProcessRegisters().GetZeroFlag());
    UNIT_ASSERT(!myProc.GetProcessRegisters().GetNegativeFlag());
    UNIT_ASSERT(myProc.GetProcessRegisters().GetCarryFlag());
    delete pInstruction;

    return true;
}

////////////////////////////////
/// Main Function
////////////////////////////////
bool LsrUT()
{
    UnitTest unitTest("LSR Instruction Unit Test");
    unitTest.SetSetup(setup);

    unitTest.AddSubTest(LsrRegsTest);
    unitTest.AddSubTest(LsrLiterals);
    unitTest.AddSubTest(LsrsTest);

    return unitTest.Run();
}