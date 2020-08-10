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
#include <catch2/catch.hpp>
#include "InstructionBase.hpp"
#include "InstructionBuilder.hpp"
#include "Process.hpp"

TEST_CASE("EOR Instruction", "[instruction][ArithAndLogic]")
{
    Process myProc = Process();
    InstructionBuilder& builder = InstructionBuilder::GetInstance();
    InstructionBase* pInstruction = nullptr;
    std::string instructionStr;

    uint32_t a = GENERATE(take(5, random(INT32_MIN, INT32_MAX)));
    uint32_t b = GENERATE(take(5, random(INT32_MIN, INT32_MAX)));

    SECTION("Xor two registers")
    {
        instructionStr = "EOR R0, R1, R2";

        myProc.GetProcessRegisters().genRegs[1] = a;
        myProc.GetProcessRegisters().genRegs[2] = b;

        pInstruction = builder.BuildInstruction(instructionStr, &myProc);
        pInstruction->Execute(myProc.GetProcessRegisters());
        REQUIRE(myProc.GetProcessRegisters().genRegs[0] == (a ^ b));
        delete pInstruction;
    }

    SECTION("Xor with a register")
    {
        instructionStr = "EOR R0, R1";

        myProc.GetProcessRegisters().genRegs[0] = a;
        myProc.GetProcessRegisters().genRegs[1] = b;

        pInstruction = builder.BuildInstruction(instructionStr, &myProc);
        pInstruction->Execute(myProc.GetProcessRegisters());
        REQUIRE(myProc.GetProcessRegisters().genRegs[0] == (a ^ b));
        delete pInstruction;
    }

    SECTION("Xor a register and a literal")
    {
        instructionStr = "EOR R0, R1, #" + std::to_string(b);

        myProc.GetProcessRegisters().genRegs[1] = a;

        pInstruction = builder.BuildInstruction(instructionStr, &myProc);
        pInstruction->Execute(myProc.GetProcessRegisters());
        REQUIRE(myProc.GetProcessRegisters().genRegs[0] == (a ^ b));
        delete pInstruction;
    }

    SECTION("Xor with a literal")
    {
        instructionStr = "EOR R0, #" + std::to_string(b);

        myProc.GetProcessRegisters().genRegs[0] = a;

        pInstruction = builder.BuildInstruction(instructionStr, &myProc);
        pInstruction->Execute(myProc.GetProcessRegisters());
        REQUIRE(myProc.GetProcessRegisters().genRegs[0] == (a ^ b));
        delete pInstruction;
    }

    SECTION("EORS Test")
    {
        myProc.GetProcessRegisters().genRegs[1] = 1;
        myProc.GetProcessRegisters().genRegs[2] = 2;

        instructionStr = "EORS R1, R1";

        pInstruction = builder.BuildInstruction(instructionStr, &myProc);
        pInstruction->Execute(myProc.GetProcessRegisters());
        REQUIRE(myProc.GetProcessRegisters().GetZeroFlag());
        REQUIRE(!myProc.GetProcessRegisters().GetNegativeFlag());
        delete pInstruction;

        instructionStr = "EORS R2, #0xFFFFFFFF";

        pInstruction = builder.BuildInstruction(instructionStr, &myProc);
        pInstruction->Execute(myProc.GetProcessRegisters());
        REQUIRE(!myProc.GetProcessRegisters().GetZeroFlag());
        REQUIRE(myProc.GetProcessRegisters().GetNegativeFlag());
        delete pInstruction;
    }
}
