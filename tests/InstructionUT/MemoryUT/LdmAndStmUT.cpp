/////////////////////////////////
/// @file LdmAndStmUT.cpp
///
/// @brief Unit Test for STM and LDM Instructions
///
/// @author Luke Karavolis
/////////////////////////////////

// SYSTEM INCLUDES
// (None)

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "UnitTest.hpp"
#include "InvalidSyntaxException.hpp"
#include "Process.hpp"
#include "InstructionBuilder.hpp"
#include "InstructionBase.hpp"
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

    myProc.GetProcessRegisters().SP = Memory::STACK_LOWER_BOUND;
}

////////////////////////////////
/// StmTest Function
////////////////////////////////
bool StmTest()
{
    instructionStr = "STMDB SP! {R0, R2}";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    UNIT_ASSERT(Memory::MemoryApi::ReadWord(myProc.GetProcessRegisters().SP) == 2);
    delete pInstruction;

    myProc.GetProcessRegisters().genRegs[5] = memAddress;

    instructionStr = "STMIB R5, {R1, R6-R9}";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    UNIT_ASSERT(Memory::MemoryApi::ReadWord(myProc.GetProcessRegisters().SP) == 2);
    UNIT_ASSERT(myProc.GetProcessRegisters().genRegs[5] = memAddress);
    delete pInstruction;

    return true;
}

////////////////////////////////
/// LdmTest Function
////////////////////////////////
bool LdmTest()
{
    // Invalidate registers
    for (int i = 0; i < 13; i++)
    {
        myProc.GetProcessRegisters().genRegs[i] = 0xBEEFC0DE;
    }

    instructionStr = "LDM SP! {R0, R2}";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    UNIT_ASSERT(myProc.GetProcessRegisters().genRegs[0] == 0);
    UNIT_ASSERT(myProc.GetProcessRegisters().genRegs[2] == 2);
    delete pInstruction;

    myProc.GetProcessRegisters().genRegs[5] = memAddress + sizeof(uint32_t) * 5;

    instructionStr = "LDMDA R5! {R1, R6-R9}";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    UNIT_ASSERT(myProc.GetProcessRegisters().genRegs[1] == 1);
    UNIT_ASSERT(myProc.GetProcessRegisters().genRegs[6] == 6);
    UNIT_ASSERT(myProc.GetProcessRegisters().genRegs[7] == 7);
    UNIT_ASSERT(myProc.GetProcessRegisters().genRegs[8] == 8);
    UNIT_ASSERT(myProc.GetProcessRegisters().genRegs[9] == 9);
    delete pInstruction;

    UNIT_ASSERT(myProc.GetProcessRegisters().genRegs[5] == memAddress);

    return true;
}

////////////////////////////////
/// Main Function
////////////////////////////////
bool LdmAndStmUT()
{
    UnitTest ldmAndStmUnitTest("STM and LDM Unit Test");
    ldmAndStmUnitTest.SetSetup(setup);

    ldmAndStmUnitTest.AddSubTest(StmTest);
    ldmAndStmUnitTest.AddSubTest(LdmTest);

    return ldmAndStmUnitTest.Run();
}