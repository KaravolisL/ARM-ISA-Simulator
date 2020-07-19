/////////////////////////////////
/// @file EorUT.cpp
///
/// @brief Unit Test for EOR Instruction
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
/// EorRegsTest Function
////////////////////////////////
bool EorRegsTest()
{
    instructionStr = "EOR R0, R5, R7";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    UNIT_ASSERT(myProc.GetProcessRegisters().genRegs[0] == 2);
    delete pInstruction;

    instructionStr = "EOR R8, R9";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    UNIT_ASSERT(myProc.GetProcessRegisters().genRegs[8] == 1);
    delete pInstruction;

    return true;
}

////////////////////////////////
/// EorLiterals Function
////////////////////////////////
bool EorLiterals()
{
    instructionStr = "EOR R0, R5, #0xF";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    UNIT_ASSERT(myProc.GetProcessRegisters().genRegs[0] == 10);
    delete pInstruction;

    instructionStr = "EOR R1, #0x13";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    UNIT_ASSERT(myProc.GetProcessRegisters().genRegs[1] == 0x12);
    delete pInstruction;

    return true;
}

////////////////////////////////
/// EorsTest Function
////////////////////////////////
bool EorsTest()
{
    // Reset registers
    setup();

    instructionStr = "EORS R1, R1";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    UNIT_ASSERT(myProc.GetProcessRegisters().GetZeroFlag());
    UNIT_ASSERT(!myProc.GetProcessRegisters().GetNegativeFlag());
    delete pInstruction;

    instructionStr = "EORS R2, #0xFFFFFFFF";

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
bool EorUT()
{
    UnitTest unitTest("EOR Instruction Unit Test");
    unitTest.SetSetup(setup);

    unitTest.AddSubTest(EorRegsTest);
    unitTest.AddSubTest(EorLiterals);
    unitTest.AddSubTest(EorsTest);

    return unitTest.Run();
}