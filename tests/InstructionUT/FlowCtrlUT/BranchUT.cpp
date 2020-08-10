/////////////////////////////////
/// @file BranchUT.cpp
///
/// @brief Unit Test for Branch Instruction
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

TEST_CASE("B Instruction", "[instruction][FlowCtrl]")
{
    Process myProc = Process();
    InstructionBuilder& builder = InstructionBuilder::GetInstance();
    InstructionBase* pInstruction = nullptr;
    std::string instructionStr;

    myProc.GetProcessRegisters().PC = 5;

    myProc.GetLabelDictionary().Insert("MyLabel", 10);

    Io::FileIterator* pFileIterator = new Io::FileIterator("TestFile.txt");
    myProc.SetFileIterator(pFileIterator);

    SECTION("Branch test")
    {
        instructionStr = "B MyLabel";

        pInstruction = builder.BuildInstruction(instructionStr, &myProc);
        pInstruction->Execute(myProc.GetProcessRegisters());
        REQUIRE(myProc.GetProcessRegisters().PC == 10);
        delete pInstruction;

        instructionStr = "B BadLabel";

        REQUIRE_THROWS_AS(builder.BuildInstruction(instructionStr, &myProc), InvalidSyntaxException);
    }
}
