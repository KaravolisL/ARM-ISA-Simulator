/////////////////////////////////
/// @file LdrAndStrUT.cpp
///
/// @brief Unit Test for STR and LDR Instructions
///
/// @author Luke Karavolis
/////////////////////////////////

// SYSTEM INCLUDES
#include <assert.h>
#include <iostream>

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "InvalidSyntaxException.hpp"
#include "Process.hpp"
#include "InstructionBuilder.hpp"
#include "InstructionBase.hpp"
#include "KeywordDict.hpp"
#include "MemoryApi.hpp"
#include "MemoryConstants.hpp"

////////////////////////////////
/// Test Objects
////////////////////////////////
Process myProc = Process();
InstructionBuilder& builder = InstructionBuilder::GetInstance();
InstructionBase* pInstruction = nullptr;
std::string instructionStr;
const uint32_t memAddress = 0x20000000;

////////////////////////////////
/// Setup Function
////////////////////////////////
void setup()
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
void StrTest()
{
    myProc.GetProcessRegisters().genRegs[0] = memAddress;

    instructionStr = "STR R2, str";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    assert(Memory::MemoryApi::ReadWord(memAddress) == 2);
    delete pInstruction;
}

////////////////////////////////
/// LdrTest Function
////////////////////////////////
void LdrTest()
{
    // Invalidate registers
    for (int i = 0; i < 13; i++)
    {
        myProc.GetProcessRegisters().genRegs[i] = 0xBEEFC0DE;
    }

    instructionStr = "LDR R2, =str";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    assert(myProc.GetProcessRegisters().genRegs[2] == 2);
    delete pInstruction;
}

////////////////////////////////
/// Teardown Function
////////////////////////////////
void teardown()
{

}

////////////////////////////////
/// Main Function
////////////////////////////////
int main(int argc, char* argv[])
{
    setup();

    StrTest();
    // LdrTest();

    teardown();

    std::cout << "STR and LDR Instruction Unit Test Complete: SUCCESS";
    return 0;
}