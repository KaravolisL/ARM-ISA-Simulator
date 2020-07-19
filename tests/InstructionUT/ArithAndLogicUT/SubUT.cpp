/////////////////////////////////
/// @file SubUT.cpp
///
/// @brief Unit Test for SUB Instruction
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
/// SubRegsTest Function
////////////////////////////////
bool SubRegsTest()
{
    instructionStr = "SUB R0, R2, R1";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    UNIT_ASSERT(myProc.GetProcessRegisters().genRegs[0] == 1);
    delete pInstruction;

    instructionStr = "SUB R0, R1";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    UNIT_ASSERT(myProc.GetProcessRegisters().genRegs[0] == 0);
    delete pInstruction;

    return true;
}

////////////////////////////////
/// SubLiterals Function
////////////////////////////////
bool SubLiterals()
{
    instructionStr = "SUB R0, R11, #0xA";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    UNIT_ASSERT(myProc.GetProcessRegisters().genRegs[0] == 1);
    delete pInstruction;

    instructionStr = "SUB R5, #0x4";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    UNIT_ASSERT(myProc.GetProcessRegisters().genRegs[5] == 1);
    delete pInstruction;

    return true;
}

////////////////////////////////
/// SubsTest Function
////////////////////////////////
bool SubsTest()
{
    // Reset registers
    setup();

    instructionStr = "SUBS R10, #10";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    UNIT_ASSERT(myProc.GetProcessRegisters().GetNegativeFlag() == false);
    UNIT_ASSERT(myProc.GetProcessRegisters().GetZeroFlag() == true);
    UNIT_ASSERT(myProc.GetProcessRegisters().GetCarryFlag() == true);
    UNIT_ASSERT(myProc.GetProcessRegisters().GetOverflowFlag() == false);
    delete pInstruction;

    instructionStr = "SUBS R9, #6";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    UNIT_ASSERT(myProc.GetProcessRegisters().GetNegativeFlag() == false);
    UNIT_ASSERT(myProc.GetProcessRegisters().GetZeroFlag() == false);
    UNIT_ASSERT(myProc.GetProcessRegisters().GetCarryFlag() == true);
    UNIT_ASSERT(myProc.GetProcessRegisters().GetOverflowFlag() == false);
    delete pInstruction;

    instructionStr = "SUBS R10, #16";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    UNIT_ASSERT(myProc.GetProcessRegisters().GetNegativeFlag() == true);
    UNIT_ASSERT(myProc.GetProcessRegisters().GetZeroFlag() == false);
    UNIT_ASSERT(myProc.GetProcessRegisters().GetCarryFlag() == false);
    UNIT_ASSERT(myProc.GetProcessRegisters().GetOverflowFlag() == false);
    delete pInstruction;

    instructionStr = "SUBS R0, #0";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
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
bool SubUT()
{
    UnitTest unitTest("SUB Instruction Unit Test");
    unitTest.SetSetup(setup);

    unitTest.AddSubTest(SubRegsTest);
    unitTest.AddSubTest(SubLiterals);
    unitTest.AddSubTest(SubsTest);

    return unitTest.Run();
}