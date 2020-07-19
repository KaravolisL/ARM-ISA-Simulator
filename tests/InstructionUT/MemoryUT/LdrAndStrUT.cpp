/////////////////////////////////
/// @file LdrAndStrUT.cpp
///
/// @brief Unit Test for STR and LDR Instructions
///
/// @author Luke Karavolis
/////////////////////////////////

// SYSTEM INCLUDES
#include <iostream>

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "UnitTest.hpp"
#include "Process.hpp"
#include "InstructionBuilder.hpp"
#include "InstructionBase.hpp"
#include "KeywordDict.hpp"
#include "MemoryApi.hpp"
#include "MemoryConstants.hpp"

////////////////////////////////
/// Test Objects
////////////////////////////////
static Process myProc = Process();
static InstructionBuilder& builder = InstructionBuilder::GetInstance();
static InstructionBase* pInstruction = nullptr;
static std::string instructionStr;
static const uint32_t memAddress = 0x20000000;

////////////////////////////////
/// Setup Function
////////////////////////////////
static void setup()
{
    for (int i = 0; i < 13; i++)
    {
        myProc.GetProcessRegisters().genRegs[i] = i;
    }

    myProc.GetConstantsDictionary().Insert("str", memAddress);

    KeywordDict::GetInstance().Initialize();

    Memory::MemoryApi::Initialize();
}

////////////////////////////////
/// StrTest Function
////////////////////////////////
bool StrTest()
{
    myProc.GetProcessRegisters().genRegs[0] = memAddress;

    instructionStr = "STR R2, str";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    UNIT_ASSERT(Memory::MemoryApi::ReadWord(memAddress) == 2);
    delete pInstruction;

    instructionStr = "STR R3, [R0, #4]";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    UNIT_ASSERT(Memory::MemoryApi::ReadWord(memAddress + 4) == 3);
    UNIT_ASSERT(myProc.GetProcessRegisters().genRegs[0] == memAddress);
    delete pInstruction;

    instructionStr = "STR R4, [R0, #8]!";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    UNIT_ASSERT(Memory::MemoryApi::ReadWord(memAddress + 8) == 4);
    UNIT_ASSERT(myProc.GetProcessRegisters().genRegs[0] == memAddress + 8);
    delete pInstruction;

    myProc.GetProcessRegisters().genRegs[0] = memAddress + 12;
    instructionStr = "STR R5, [R0], #4";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    UNIT_ASSERT(Memory::MemoryApi::ReadWord(memAddress + 12) == 5);
    UNIT_ASSERT(myProc.GetProcessRegisters().genRegs[0] == memAddress + 16);
    delete pInstruction;

    instructionStr = "STR R6, [R0]";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    UNIT_ASSERT(Memory::MemoryApi::ReadWord(memAddress + 16) == 6);
    UNIT_ASSERT(myProc.GetProcessRegisters().genRegs[0] == memAddress + 16);
    delete pInstruction;

    return true;
}

////////////////////////////////
/// LdrTest Function
////////////////////////////////
bool LdrTest()
{
    // Invalidate registers
    for (int i = 0; i < 13; i++)
    {
        myProc.GetProcessRegisters().genRegs[i] = 0xBEEFC0DE;
    }
    myProc.GetProcessRegisters().genRegs[0] = memAddress;

    instructionStr = "LDR R2, =str";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    UNIT_ASSERT(myProc.GetProcessRegisters().genRegs[2] == 2);
    delete pInstruction;

    instructionStr = "LDR R3, [R0, #4]";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    UNIT_ASSERT(myProc.GetProcessRegisters().genRegs[3] == 3);
    UNIT_ASSERT(myProc.GetProcessRegisters().genRegs[0] == memAddress);
    delete pInstruction;

    instructionStr = "LDR R4, [R0, #8]!";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    UNIT_ASSERT(myProc.GetProcessRegisters().genRegs[4] == 4);
    UNIT_ASSERT(myProc.GetProcessRegisters().genRegs[0] == memAddress + 8);
    delete pInstruction;

    myProc.GetProcessRegisters().genRegs[0] = memAddress + 12;
    instructionStr = "LDR R5, [R0], #4";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    UNIT_ASSERT(myProc.GetProcessRegisters().genRegs[5] == 5);
    UNIT_ASSERT(myProc.GetProcessRegisters().genRegs[0] == memAddress + 16);
    delete pInstruction;

    instructionStr = "LDR R6, [R0]";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    UNIT_ASSERT(myProc.GetProcessRegisters().genRegs[6] == 6);
    UNIT_ASSERT(myProc.GetProcessRegisters().genRegs[0] == memAddress + 16);
    delete pInstruction;

    return true;
}

////////////////////////////////
/// Main Function
////////////////////////////////
bool LdrAndStrUT()
{
    UnitTest loadAndStoreTest("LDR And STR Unit Test");
    loadAndStoreTest.SetSetup(setup);

    loadAndStoreTest.AddSubTest(StrTest);
    loadAndStoreTest.AddSubTest(LdrTest);

    return loadAndStoreTest.Run();
}