/////////////////////////////////
/// @file LdmAndStmUT.cpp
///
/// @brief Unit Test for STM and LDM Instructions
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

    myProc.GetProcessRegisters().SP = Memory::STACK_LOWER_BOUND;

    KeywordDict::GetInstance().Initialize();

    Memory::MemoryApi::Initialize();
}

////////////////////////////////
/// StmTest Function
////////////////////////////////
void StmTest()
{
    instructionStr = "STMDB SP! {R0, R2}";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    assert(Memory::MemoryApi::ReadWord(myProc.GetProcessRegisters().SP) == 2);
    delete pInstruction;

    myProc.GetProcessRegisters().genRegs[5] = memAddress;

    instructionStr = "STMIB R5, {R1, R6-R9}";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    assert(Memory::MemoryApi::ReadWord(myProc.GetProcessRegisters().SP) == 2);
    assert(myProc.GetProcessRegisters().genRegs[5] = memAddress);
    delete pInstruction;
}

////////////////////////////////
/// LdmTest Function
////////////////////////////////
void LdmTest()
{
    // Invalidate registers
    for (int i = 0; i < 13; i++)
    {
        myProc.GetProcessRegisters().genRegs[i] = 0xBEEFC0DE;
    }

    instructionStr = "LDM SP! {R0, R2}";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    assert(myProc.GetProcessRegisters().genRegs[0] == 0);
    assert(myProc.GetProcessRegisters().genRegs[2] == 2);
    delete pInstruction;

    myProc.GetProcessRegisters().genRegs[5] = memAddress + sizeof(uint32_t) * 5;

    instructionStr = "LDMDA R5! {R1, R6-R9}";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    assert(myProc.GetProcessRegisters().genRegs[1] == 1);
    assert(myProc.GetProcessRegisters().genRegs[6] == 6);
    assert(myProc.GetProcessRegisters().genRegs[7] == 7);
    assert(myProc.GetProcessRegisters().genRegs[8] == 8);
    assert(myProc.GetProcessRegisters().genRegs[9] == 9);
    delete pInstruction;

    assert(myProc.GetProcessRegisters().genRegs[5] == memAddress);
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

    StmTest();
    LdmTest();

    teardown();

    std::cout << "STM and LDM Instruction Unit Test Complete: SUCCESS";
    return 0;
}