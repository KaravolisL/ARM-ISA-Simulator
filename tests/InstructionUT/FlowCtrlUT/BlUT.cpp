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
/// BranchAndLinkTest Function
////////////////////////////////
bool BranchAndLinkTest()
{
    instructionStr = "BL MyLabel";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    UNIT_ASSERT(myProc.GetProcessRegisters().PC == 10);
    UNIT_ASSERT(myProc.GetProcessRegisters().LR == 6);
    delete pInstruction;

    instructionStr = "BL BadLabel";

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
bool BlUT()
{
    UnitTest unitTest("BL Instruction Unit Test");
    unitTest.SetSetup(setup);

    unitTest.AddSubTest(BranchAndLinkTest);

    return unitTest.Run();
}