/////////////////////////////////
/// @file CmpUT.cpp
///
/// @brief Unit Test for CMPInstruction
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
/// CompareTest Function
////////////////////////////////
bool CompareTest()
{
    instructionStr = "CMP R10, #10";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    UNIT_ASSERT(myProc.GetProcessRegisters().genRegs[10] == 10);
    UNIT_ASSERT(myProc.GetProcessRegisters().GetNegativeFlag() == false);
    UNIT_ASSERT(myProc.GetProcessRegisters().GetZeroFlag() == true);
    UNIT_ASSERT(myProc.GetProcessRegisters().GetCarryFlag() == true);
    UNIT_ASSERT(myProc.GetProcessRegisters().GetOverflowFlag() == false);
    delete pInstruction;

    instructionStr = "CMP R10, #6";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    UNIT_ASSERT(myProc.GetProcessRegisters().genRegs[10] == 10);
    UNIT_ASSERT(myProc.GetProcessRegisters().GetNegativeFlag() == false);
    UNIT_ASSERT(myProc.GetProcessRegisters().GetZeroFlag() == false);
    UNIT_ASSERT(myProc.GetProcessRegisters().GetCarryFlag() == true);
    UNIT_ASSERT(myProc.GetProcessRegisters().GetOverflowFlag() == false);
    delete pInstruction;

    instructionStr = "CMP R10, #16";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    UNIT_ASSERT(myProc.GetProcessRegisters().genRegs[10] == 10);
    UNIT_ASSERT(myProc.GetProcessRegisters().GetNegativeFlag() == true);
    UNIT_ASSERT(myProc.GetProcessRegisters().GetZeroFlag() == false);
    UNIT_ASSERT(myProc.GetProcessRegisters().GetCarryFlag() == false);
    UNIT_ASSERT(myProc.GetProcessRegisters().GetOverflowFlag() == false);
    delete pInstruction;

    // "MOV" R1, #0
    myProc.GetProcessRegisters().genRegs[1] = 0;

    instructionStr = "CMP R0, R1";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    UNIT_ASSERT(myProc.GetProcessRegisters().genRegs[0] == 0);
    UNIT_ASSERT(myProc.GetProcessRegisters().genRegs[1] == 0);
    UNIT_ASSERT(myProc.GetProcessRegisters().GetNegativeFlag() == false);
    UNIT_ASSERT(myProc.GetProcessRegisters().GetZeroFlag() == true);
    UNIT_ASSERT(myProc.GetProcessRegisters().GetCarryFlag() == true);
    UNIT_ASSERT(myProc.GetProcessRegisters().GetOverflowFlag() == false);
    delete pInstruction;

    return true;
}

////////////////////////////////
/// Main Function
////////////////////////////////
bool CmpUT()
{
    UnitTest unitTest("CMP Instruction Unit Test");
    unitTest.SetSetup(setup);

    unitTest.AddSubTest(CompareTest);

    return unitTest.Run();
}