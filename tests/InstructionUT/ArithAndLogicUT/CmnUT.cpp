/////////////////////////////////
/// @file CmnUT.cpp
///
/// @brief Unit Test for CMN Instruction
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
    for (int i = 0; i < 13; i++)
    {
        myProc.GetProcessRegisters().genRegs[i] = i;
    }
}

////////////////////////////////
/// CmnTest Function
////////////////////////////////
bool CmnTest()
{
    instructionStr = "CMN R0, R0";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    UNIT_ASSERT(myProc.GetProcessRegisters().GetZeroFlag());
    UNIT_ASSERT(!myProc.GetProcessRegisters().GetNegativeFlag());
    UNIT_ASSERT(!myProc.GetProcessRegisters().GetCarryFlag());
    UNIT_ASSERT(!myProc.GetProcessRegisters().GetOverflowFlag());
    delete pInstruction;

    instructionStr = "CMN R0, #-2";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    UNIT_ASSERT(myProc.GetProcessRegisters().genRegs[0] == 0);
    UNIT_ASSERT(!myProc.GetProcessRegisters().GetZeroFlag());
    UNIT_ASSERT(myProc.GetProcessRegisters().GetNegativeFlag());
    UNIT_ASSERT(!myProc.GetProcessRegisters().GetCarryFlag());
    UNIT_ASSERT(!myProc.GetProcessRegisters().GetOverflowFlag());
    delete pInstruction;

    instructionStr = "CMN R10, #0xFFFFFFFF";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    UNIT_ASSERT(!myProc.GetProcessRegisters().GetZeroFlag());
    UNIT_ASSERT(!myProc.GetProcessRegisters().GetNegativeFlag());
    UNIT_ASSERT(myProc.GetProcessRegisters().GetCarryFlag());
    UNIT_ASSERT(!myProc.GetProcessRegisters().GetOverflowFlag());
    delete pInstruction;

    // "MOV" R1, #0x40000000
    myProc.GetProcessRegisters().genRegs[1] = 0x40000000;

    instructionStr = "CMN R1, #0x40000000";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    UNIT_ASSERT(!myProc.GetProcessRegisters().GetZeroFlag());
    UNIT_ASSERT(myProc.GetProcessRegisters().GetNegativeFlag());
    UNIT_ASSERT(!myProc.GetProcessRegisters().GetCarryFlag());
    UNIT_ASSERT(myProc.GetProcessRegisters().GetOverflowFlag());
    delete pInstruction;

    return true;
}

////////////////////////////////
/// Main Function
////////////////////////////////
bool CmnUT()
{
    UnitTest unitTest("CMN Instruction Unit Test");
    unitTest.SetSetup(setup);

    unitTest.AddSubTest(CmnTest);

    return unitTest.Run();
}