/////////////////////////////////
/// @file KeywordDict.cpp
///
/// @brief Implementation of KeywordDict class
///
/// @copydetail KeywordDict
///
/// @author Luke Karavolis
/////////////////////////////////

// SYSTEM INCLUDES
#include <string>
#include <iostream>

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "KeywordDict.hpp" // Header for class
#include "InstructionRepository.hpp" // For InstructionRepository
#include "LineTypes.hpp" // For LineTypes enum
#include "Logger.hpp" // For LOG_INFO

////////////////////////////////
/// METHOD NAME: KeywordDict::Initialize
////////////////////////////////
void KeywordDict::Initialize()
{
    // Directives
    m_keywordDict.Insert("INCLUDE", Io::LineType::INCLUDE);
    m_keywordDict.Insert("ALIGN", Io::LineType::ALIGN);
    m_keywordDict.Insert("END", Io::LineType::END);
    m_keywordDict.Insert("ENDP", Io::LineType::ENDP);
    m_keywordDict.Insert("AREA", Io::LineType::AREA);
    m_keywordDict.Insert("EXPORT", Io::LineType::EXPORT);
    m_keywordDict.Insert("ENTRY", Io::LineType::ENTRY);
    m_keywordDict.Insert("EQU", Io::LineType::EQU);
    m_keywordDict.Insert("DCB", Io::LineType::DCB);

    // Instructions
    SLList<std::string> instructionList = InstructionRepository::GetInstance().GetInstructionStrings();

    for (SLList<std::string>::SLListIterator it = instructionList.GetBegin();
         it != instructionList.GetEnd(); it++)
    {
        m_keywordDict.Insert(*it, Io::LineType::INSTRUCTION);
    }

    // The following instructions are not implemented yet :(
    m_keywordDict.Insert("LDR", Io::LineType::INSTRUCTION);
    m_keywordDict.Insert("LSL", Io::LineType::INSTRUCTION);
    m_keywordDict.Insert("SUBS", Io::LineType::INSTRUCTION);
    m_keywordDict.Insert("STR", Io::LineType::INSTRUCTION);
    m_keywordDict.Insert("BEQ", Io::LineType::INSTRUCTION);

    LOG_INFO("Keyword dictionary initialized");
}

////////////////////////////////
/// METHOD NAME: KeywordDict::Get
////////////////////////////////
Io::LineType KeywordDict::Get(std::string& keyword)
{
    Io::LineType lineType;
    try
    {
        lineType = m_keywordDict.Get(keyword);
    }
    catch(const DLB<Io::LineType>::KeyNotFoundException& e)
    {
        // If the keyword is not found, it's a label
        lineType = Io::LineType::LABEL;
    }
    return lineType;
}