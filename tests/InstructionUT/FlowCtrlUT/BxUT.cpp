/////////////////////////////////
/// @file BxUT.cpp
///
/// @brief Unit Test for BX Instruction
///
/// @author Luke Karavolis
/////////////////////////////////

// SYSTEM INCLUDES
// (None)

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include <catch2/catch.hpp>
#include "InvalidSyntaxException.hpp"
#include "Process.hpp"
#include "FileIterator.hpp"
#include "InstructionBuilder.hpp"
#include "InstructionBase.hpp"

TEST_CASE("BX Instruction", "[instruction][FlowCtrl]")
{
    Process myProc = Process();
    InstructionBuilder& builder = InstructionBuilder::GetInstance();
    InstructionBase* pInstruction = nullptr;
    std::string instructionStr;

    myProc.GetProcessRegisters().PC = 5;
    myProc.GetProcessRegisters().LR = 10;
    myProc.GetProcessRegisters().genRegs[1] = 15;

    Io::FileIterator* pFileIterator = new Io::FileIterator("TestFile.txt");
    myProc.SetFileIterator(pFileIterator);

    // Needed to avoid EmptyStackException
    myProc.GetMetadata().GetCallStack().Push("DummyFunction");

    SECTION("Branch exchange with link register")
    {
        instructionStr = "BX LR";

        pInstruction = builder.BuildInstruction(instructionStr, &myProc);
        pInstruction->Execute(myProc.GetProcessRegisters());
        REQUIRE(myProc.GetProcessRegisters().PC == 10);
        delete pInstruction;
    }

    SECTION("Branch exchange with register")
    {
        instructionStr = "BX R1";

        pInstruction = builder.BuildInstruction(instructionStr, &myProc);
        pInstruction->Execute(myProc.GetProcessRegisters());
        REQUIRE(myProc.GetProcessRegisters().PC == 15);
        delete pInstruction;
    }

    SECTION("Invalid syntax")
    {
        instructionStr = "BX MyLabel";

        REQUIRE_THROWS_AS(builder.BuildInstruction(instructionStr, &myProc), InvalidSyntaxException);
    }
}
