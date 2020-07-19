/////////////////////////////////
/// @file LslUT.cpp
///
/// @brief Unit Test for LSL Instruction
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
/// LslRegsTest Function
////////////////////////////////
bool LslRegsTest()
{
    instructionStr = "LSL R0, R1, R2";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    UNIT_ASSERT(myProc.GetProcessRegisters().genRegs[0] == 4);
    delete pInstruction;

    instructionStr = "LSL R2, R3";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    UNIT_ASSERT(myProc.GetProcessRegisters().genRegs[2] == 16);
    delete pInstruction;

    return true;
}

////////////////////////////////
/// LslLiterals Function
////////////////////////////////
bool LslLiterals()
{
    instructionStr = "LSL R0, R3, #0xF";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    UNIT_ASSERT(myProc.GetProcessRegisters().genRegs[0] == 0x18000);
    delete pInstruction;

    instructionStr = "LSL R1, #0x13";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    UNIT_ASSERT(myProc.GetProcessRegisters().genRegs[1] == 0x80000);
    delete pInstruction;

    return true;
}

////////////////////////////////
/// LslsTest Function
////////////////////////////////
bool LslsTest()
{
    // Reset registers
    setup();

    instructionStr = "LSLS R0, R1";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    UNIT_ASSERT(myProc.GetProcessRegisters().GetZeroFlag());
    UNIT_ASSERT(!myProc.GetProcessRegisters().GetNegativeFlag());
    UNIT_ASSERT(!myProc.GetProcessRegisters().GetCarryFlag());
    delete pInstruction;

    // "MOV" R2, #0x40000000
    myProc.GetProcessRegisters().genRegs[2] = 0xC0000000;

    instructionStr = "LSLS R2, #1";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    UNIT_ASSERT(!myProc.GetProcessRegisters().GetZeroFlag());
    UNIT_ASSERT(myProc.GetProcessRegisters().GetNegativeFlag());
    UNIT_ASSERT(myProc.GetProcessRegisters().GetCarryFlag());
    delete pInstruction;

    return true;
}

////////////////////////////////
/// Main Function
////////////////////////////////
bool LslUT()
{
    UnitTest unitTest("LSL Instruction Unit Test");
    unitTest.SetSetup(setup);

    unitTest.AddSubTest(LslRegsTest);
    unitTest.AddSubTest(LslLiterals);
    unitTest.AddSubTest(LslsTest);

    return unitTest.Run();
}