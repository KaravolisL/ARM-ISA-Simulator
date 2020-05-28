/////////////////////////////////
/// @file PushUT.cpp
///
/// @brief Unit Test for PUSH Instruction
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

////////////////////////////////
/// Test Objects
////////////////////////////////
Process myProc = Process();
InstructionBuilder& builder = InstructionBuilder::GetInstance();
InstructionBase* pInstruction = nullptr;
std::string instructionStr;

////////////////////////////////
/// Setup Function
////////////////////////////////
void setup()
{
    for (int i = 0; i < 13; i++)
    {
        myProc.GetProcessRegisters().genRegs[i] = i;
    }

    KeywordDict::GetInstance().Initialize();
}

////////////////////////////////
/// PushTest Function
////////////////////////////////
void PushTest()
{
    instructionStr = "PUSH {R0}";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    assert(myProc.GetProcessStack().Peek() == 0);
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

    PushTest();

    teardown();

    std::cout << "PUSH Instruction Unit Test Complete: SUCCESS";
    return 0;
}