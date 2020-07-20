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
#include "UnitTest.hpp"
#include "InvalidSyntaxException.hpp"
#include "Process.hpp"
#include "FileIterator.hpp"
#include "InstructionBuilder.hpp"
#include "InstructionBase.hpp"

////////////////////////////////
/// Test Objects
////////////////////////////////
static Process myProc = Process();
static InstructionBuilder& builder = InstructionBuilder::GetInstance();
static InstructionBase* pInstruction = nullptr;
static std::string instructionStr;

////////////////////////////////
/// Setup Function
////////////////////////////////
static void setup()
{
    myProc.GetProcessRegisters().PC = 5;

    myProc.GetLabelDictionary().Insert("MyLabel", 10);

    Io::FileIterator* pFileIterator = new Io::FileIterator("TestFile.txt");
    myProc.SetFileIterator(pFileIterator);
}

////////////////////////////////
/// BranchTest Function
////////////////////////////////
bool BranchTest()
{
    instructionStr = "B MyLabel";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    UNIT_ASSERT(myProc.GetProcessRegisters().PC == 10);
    delete pInstruction;

    instructionStr = "B BadLabel";
    try
    {
        pInstruction = builder.BuildInstruction(instructionStr, &myProc);
        pInstruction->Execute(myProc.GetProcessRegisters());
        UNIT_ASSERT(false);
    }
    catch (const InvalidSyntaxException& e)
    {
        std::cout << e.what();
    }

    return true;
}

////////////////////////////////
/// Main Function
////////////////////////////////
bool BranchUT()
{
    UnitTest unitTest("B Instruction Unit Test");
    unitTest.SetSetup(setup);

    unitTest.AddSubTest(BranchTest);

    return unitTest.Run();
}