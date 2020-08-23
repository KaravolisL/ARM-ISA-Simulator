/////////////////////////////////
/// @file BlxUT.cpp
///
/// @brief Unit Test for BLX Instruction
///
/// @author Luke Karavolis
/////////////////////////////////

// SYSTEM INCLUDES
// (None)

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include <catch2/catch.hpp>
#include "Process.hpp"
#include "FileIterator.hpp"
#include "InstructionBuilder.hpp"
#include "InstructionBase.hpp"

TEST_CASE("BLX Instruction", "[instruction][FlowCtrl]")
{
    Process myProc = Process();
    InstructionBuilder& builder = InstructionBuilder::GetInstance();
    InstructionBase* pInstruction = nullptr;
    std::string instructionStr;

    myProc.GetProcessRegisters().PC = 5;
    myProc.GetProcessRegisters().LR = 10;
    myProc.GetProcessRegisters().genRegs[1] = 15;

    myProc.GetLabelDictionary().Insert("MyLabel", 20);

    Io::FileIterator* pFileIterator = new Io::FileIterator("TestFile.txt");
    myProc.SetFileIterator(pFileIterator);

    // Needed to avoid EmptyStackException
    myProc.GetMetadata().GetCallStack().Push("DummyFunction");

    SECTION("Branch, Link, and Exchange with LR")
    {
        instructionStr = "BLX LR";

        pInstruction = builder.BuildInstruction(instructionStr, &myProc);
        pInstruction->Execute(myProc.GetProcessRegisters());
        REQUIRE(myProc.GetProcessRegisters().PC == 10);
        REQUIRE(myProc.GetProcessRegisters().LR == 6);
        delete pInstruction;
    }

    SECTION("Branch, Link, and Exchange with register")
    {
        instructionStr = "BLX R1";

        pInstruction = builder.BuildInstruction(instructionStr, &myProc);
        pInstruction->Execute(myProc.GetProcessRegisters());
        REQUIRE(myProc.GetProcessRegisters().PC == 15);
        REQUIRE(myProc.GetProcessRegisters().LR == 6);
        delete pInstruction;
    }

    SECTION("Branch, Link, and Exchange with label")
    {
        instructionStr = "BLX MyLabel";

        pInstruction = builder.BuildInstruction(instructionStr, &myProc);
        pInstruction->Execute(myProc.GetProcessRegisters());
        REQUIRE(myProc.GetProcessRegisters().PC == 20);
        REQUIRE(myProc.GetProcessRegisters().LR == 6);
        delete pInstruction;
    }
}
