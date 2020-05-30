/////////////////////////////////
/// @file LineParserUT.cpp
///
/// @brief Unit Test for LineParser
///
/// @author Luke Karavolis
/////////////////////////////////

// SYSTEM INCLUDES
#include <assert.h>
#include <iostream>

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "LineParser.hpp"  // Test class
#include "KeywordDict.hpp" // For KeywordDict class
#include "List.hpp" // For List

////////////////////////////////
/// Test Objects
////////////////////////////////
// Strings are placed in order of LineType enum
std::string lines[] = {" INCLUDE exampleFile.s ;My comment",
                       "Label",
                       "ADD R1, R2, R3",
                       "; Just a comment",
                       "CONSTANT_NAME EQU 0x500" };
DLB<uint32_t> constants = DLB<uint32_t>();

////////////////////////////////
/// Setup Function
////////////////////////////////
void setup()
{
    // Initialize the Keyword dictionary
    KeywordDict::GetInstance().Initialize();

    // Add a constant for testing
    constants.Insert("myConstant", 5);
}

////////////////////////////////
/// GetLineTypeTest Function
////////////////////////////////
void GetLineTypeTest()
{
    for (int i = 0 ; i < 5; i++)
    {
        // Construct a line parser using the ith line
        Io::LineParser lineParser(&lines[i]);

        Io::LineType lineType = lineParser.GetLineType();
        std::cout << "lineType = " << lineType << '\n';
        assert(lineType == i);
    }
}

////////////////////////////////
/// GetFileNameTest Function
////////////////////////////////
void GetFileNameTest()
{
    Io::LineParser lineParser(&lines[0]);

    std::string fileName;
    lineParser.GetFileName(fileName);

    assert(fileName == "exampleFile.s");
}

////////////////////////////////
/// GetLabelTest Function
////////////////////////////////
void GetLabelTest()
{
    Io::LineParser lineParser(&lines[4]);

    std::string label;
    lineParser.GetLabel(label);

    assert(label == "CONSTANT_NAME");
}

////////////////////////////////
/// GetValueTest Function
////////////////////////////////
void GetValueTest()
{
    Io::LineParser lineParser(&lines[4]);

    int value = lineParser.GetValue(constants);
    std::cout << value << '\n';

    assert(value == 1280);

    std::string newLine("CONSTANT EQU (0x5 << 2)");
    Io::LineParser lineParser1(&newLine);

    value = lineParser1.GetValue(constants);
    std::cout << value << '\n';
    assert(value == 20);

    newLine = std::string("constant EQU ( myConstant )");
    Io::LineParser lineParser2(&newLine);

    value = lineParser2.GetValue(constants);
    std::cout << value << '\n';
    assert(value == 5);

    newLine = std::string("constant EQU ( 0x2 << myConstant )");
    Io::LineParser lineParser3(&newLine);

    value = lineParser3.GetValue(constants);
    std::cout << value << '\n';
    assert(value == 64);

    newLine = std::string("constant EQU ( myConstant << myConstant )");
    Io::LineParser lineParser4(&newLine);

    value = lineParser4.GetValue(constants);
    std::cout << value << '\n';
    assert(value == 160);

    newLine = std::string("constant EQU ( -20 )");
    Io::LineParser lineParser5(&newLine);

    value = lineParser5.GetValue(constants);
    std::cout << value << '\n';
    assert(value == -20);
}

////////////////////////////////
/// TokenizeTest Function
////////////////////////////////
void TokenizeTest()
{
    std::string instruction = "R1, R2, R3";
    Io::LineParser lineParser(&instruction);
    List<std::string> arguments;

    lineParser.Tokenize(arguments);

    int i = 0;
    std::cout << arguments[i] << '\n';
    assert(arguments[i++] == "R1");
    std::cout << arguments[i] << '\n';
    assert(arguments[i++] == "R2");
    std::cout << arguments[i] << '\n';
    assert(arguments[i] == "R3");
}

////////////////////////////////
/// LabelAndInstructionTest Function
////////////////////////////////
void LabelAndInstructionTest()
{
    std::string line = "myLabel ADD R1, R3";
    Io::LineParser lineParser(&line);

    assert(lineParser.GetLineType() == Io::LineType::LABEL_AND_INSTRUCTION);
    
    std::string label;
    lineParser.GetLabel(label);
    assert(label == "myLabel");

    std::string instruction;
    lineParser.GetInstruction(instruction);
    assert(instruction == "ADD");
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

    GetLineTypeTest();
    GetFileNameTest();
    GetLabelTest();
    GetValueTest();
    TokenizeTest();
    LabelAndInstructionTest();

    teardown();

    std::cout << "LineParser Unit Test Complete: SUCCESS";
    return 0;
}