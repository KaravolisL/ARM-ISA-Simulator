/////////////////////////////////
/// @file BicUT.cpp
///
/// @brief Unit Test for BIC Instruction
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
/// BicRegsTest Function
////////////////////////////////
bool BicRegsTest()
{
    instructionStr = "BIC R0, R5, R1";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    UNIT_ASSERT(myProc.GetProcessRegisters().genRegs[0] == 0b0100);
    delete pInstruction;

    instructionStr = "BIC R7, R9";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    UNIT_ASSERT(myProc.GetProcessRegisters().genRegs[7] == 0b0110);
    delete pInstruction;

    return true;
}

////////////////////////////////
/// BicLiterals Function
////////////////////////////////
bool BicLiterals()
{
    instructionStr = "BIC R0, R5, #0xB";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    UNIT_ASSERT(myProc.GetProcessRegisters().genRegs[0] == 0b0100);
    delete pInstruction;

    instructionStr = "BIC R10, #0xF";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    UNIT_ASSERT(myProc.GetProcessRegisters().genRegs[10] == 0x0);
    delete pInstruction;

    return true;
}

////////////////////////////////
/// BicsTest Function
////////////////////////////////
bool BicsTest()
{
    // Reset registers
    setup();

    instructionStr = "BICS R1, R1";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    UNIT_ASSERT(myProc.GetProcessRegisters().GetZeroFlag());
    UNIT_ASSERT(!myProc.GetProcessRegisters().GetNegativeFlag());
    delete pInstruction;

    // "MOV" R5, #0xFFFFFFFF
    myProc.GetProcessRegisters().genRegs[5] = 0xFFFFFFFF;

    instructionStr = "BICS R5, #0xF";

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
bool BicUT()
{
    UnitTest bicInstructionUT("BIC Instruction Unit Test");
    bicInstructionUT.SetSetup(setup);

    bicInstructionUT.AddSubTest(BicRegsTest);
    bicInstructionUT.AddSubTest(BicLiterals);
    bicInstructionUT.AddSubTest(BicsTest);

    return bicInstructionUT.Run();
}