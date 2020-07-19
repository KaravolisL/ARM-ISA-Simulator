/////////////////////////////////
/// @file MovUT.cpp
///
/// @brief Unit Test for MOV Instruction
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
/// MovRegTest Function
////////////////////////////////
bool MovRegTest()
{
    instructionStr = "MOV R0, R1";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    UNIT_ASSERT(myProc.GetProcessRegisters().genRegs[0] == 1);
    delete pInstruction;

    return true;
}

////////////////////////////////
/// MovLiteralTest Function
////////////////////////////////
bool MovLiteralTest()
{
    instructionStr = "MOV R0, #0xFF";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    UNIT_ASSERT(myProc.GetProcessRegisters().genRegs[0] == 0xFF);
    delete pInstruction;

    return true;
}

////////////////////////////////
/// MovsTest Function
////////////////////////////////
bool MovsTest()
{
    instructionStr = "MOVS R0, #0";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    UNIT_ASSERT(myProc.GetProcessRegisters().GetZeroFlag());
    UNIT_ASSERT(!myProc.GetProcessRegisters().GetNegativeFlag());
    delete pInstruction;

    instructionStr = "MOVS R0, #0xFFFFFFFF";

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
bool MovUT()
{
    UnitTest unitTest("MOV Instruction Unit Test");
    unitTest.SetSetup(setup);

    unitTest.AddSubTest(MovRegTest);
    unitTest.AddSubTest(MovLiteralTest);
    unitTest.AddSubTest(MovsTest);

    return unitTest.Run();
}