/////////////////////////////////
/// @file AddUT.cpp
///
/// @brief Unit Test for ADD Instruction
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
/// AddRegsTest Function
////////////////////////////////
bool AddRegsTest()
{
    std::string instructionStr = "ADD R0, R1, R2";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    UNIT_ASSERT(myProc.GetProcessRegisters().genRegs[0] == 3);
    delete pInstruction;

    instructionStr = "ADD R0, R1";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    UNIT_ASSERT(myProc.GetProcessRegisters().genRegs[0] == 4);
    delete pInstruction;

    return true;
}

////////////////////////////////
/// AddLiterals Function
////////////////////////////////
bool AddLiterals()
{
    std::string instructionStr = "ADD R0, R1, #0xA";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    UNIT_ASSERT(myProc.GetProcessRegisters().genRegs[0] == 11);
    delete pInstruction;

    instructionStr = "ADD R1, #0x11";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    UNIT_ASSERT(myProc.GetProcessRegisters().genRegs[1] == 18); 
    delete pInstruction;

    return true;   
}

////////////////////////////////
/// AddsTest Function
////////////////////////////////
bool AddsTest()
{
    // Reset registers
    setup();

    std::string instructionStr = "ADDS R0, R0";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    UNIT_ASSERT(myProc.GetProcessRegisters().GetZeroFlag());
    UNIT_ASSERT(!myProc.GetProcessRegisters().GetNegativeFlag());
    UNIT_ASSERT(!myProc.GetProcessRegisters().GetCarryFlag());
    UNIT_ASSERT(!myProc.GetProcessRegisters().GetOverflowFlag());
    delete pInstruction;

    instructionStr = "ADDS R0, #-2";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    UNIT_ASSERT(!myProc.GetProcessRegisters().GetZeroFlag());
    UNIT_ASSERT(myProc.GetProcessRegisters().GetNegativeFlag());
    UNIT_ASSERT(!myProc.GetProcessRegisters().GetCarryFlag());
    UNIT_ASSERT(!myProc.GetProcessRegisters().GetOverflowFlag());
    delete pInstruction;

    instructionStr = "ADDS R10, #0xFFFFFFFF";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    UNIT_ASSERT(!myProc.GetProcessRegisters().GetZeroFlag());
    UNIT_ASSERT(!myProc.GetProcessRegisters().GetNegativeFlag());
    UNIT_ASSERT(myProc.GetProcessRegisters().GetCarryFlag());
    UNIT_ASSERT(!myProc.GetProcessRegisters().GetOverflowFlag());
    delete pInstruction;

    // "MOV" R1, #0x40000000
    myProc.GetProcessRegisters().genRegs[1] = 0x40000000;

    instructionStr = "ADDS R1, #0x40000000";

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
bool AddUT()
{
    UnitTest addInstructionUT("ADD Instruction Unit Test");
    addInstructionUT.SetSetup(setup);

    addInstructionUT.AddSubTest(AddRegsTest);
    addInstructionUT.AddSubTest(AddLiterals);
    addInstructionUT.AddSubTest(AddsTest);
    
    return addInstructionUT.Run();
}