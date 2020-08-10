/////////////////////////////////
/// @file BlUT.cpp
///
/// @brief Unit Test for BL Instruction
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

TEST_CASE("BL Instruction", "[instruction][FlowCtrl]")
{
    Process myProc = Process();
    InstructionBuilder& builder = InstructionBuilder::GetInstance();
    InstructionBase* pInstruction = nullptr;
    std::string instructionStr;

    myProc.GetProcessRegisters().PC = 5;

    myProc.GetLabelDictionary().Insert("MyLabel", 10);

    Io::FileIterator* pFileIterator = new Io::FileIterator("TestFile.txt");
    myProc.SetFileIterator(pFileIterator);

    SECTION("Branch and link test")
    {
        instructionStr = "BL MyLabel";

        pInstruction = builder.BuildInstruction(instructionStr, &myProc);
        pInstruction->Execute(myProc.GetProcessRegisters());
        REQUIRE(myProc.GetProcessRegisters().PC == 10);
        REQUIRE(myProc.GetProcessRegisters().LR == 6);
        delete pInstruction;

        instructionStr = "BL BadLabel";

        REQUIRE_THROWS_AS(builder.BuildInstruction(instructionStr, &myProc), InvalidSyntaxException);
    }
}
