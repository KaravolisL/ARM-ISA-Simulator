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
    m_keywordDict.Insert("PROC", Io::LineType::LABEL_AND_PROC);

    // Instructions
    m_instructionDict.Insert("ADD", OpCode::ADD);
    m_instructionDict.Insert("SUB", OpCode::SUB);
    m_instructionDict.Insert("AND", OpCode::AND);
    m_instructionDict.Insert("ORR", OpCode::ORR);
    m_instructionDict.Insert("BIC", OpCode::BIC);
    m_instructionDict.Insert("EOR", OpCode::EOR);
    m_instructionDict.Insert("MOV", OpCode::MOV);
    m_instructionDict.Insert("LSL", OpCode::LSL);
    m_instructionDict.Insert("LSR", OpCode::LSR);
    m_instructionDict.Insert("B", OpCode::B);
    m_instructionDict.Insert("BL", OpCode::BL);
    m_instructionDict.Insert("BX", OpCode::BX);
    m_instructionDict.Insert("BLX", OpCode::BLX);
    m_instructionDict.Insert("POP", OpCode::POP);
    m_instructionDict.Insert("PUSH", OpCode::PUSH);
    m_instructionDict.Insert("LDM", OpCode::LDM);
    m_instructionDict.Insert("STM", OpCode::STM);
    m_instructionDict.Insert("CMP", OpCode::CMP);
    m_instructionDict.Insert("CMN", OpCode::CMN);

    // Conditional codes dictionary
    m_conditionalCodeDict.Insert("EQ", ConditionalCode::EQ);
    m_conditionalCodeDict.Insert("NE", ConditionalCode::NE);
    m_conditionalCodeDict.Insert("GT", ConditionalCode::GT);
    m_conditionalCodeDict.Insert("LT", ConditionalCode::LT);
    m_conditionalCodeDict.Insert("GE", ConditionalCode::GE);
    m_conditionalCodeDict.Insert("LE", ConditionalCode::LE);
    m_conditionalCodeDict.Insert("CS", ConditionalCode::CS);
    m_conditionalCodeDict.Insert("HS", ConditionalCode::CS);
    m_conditionalCodeDict.Insert("CC", ConditionalCode::CC);
    m_conditionalCodeDict.Insert("LO", ConditionalCode::CC);
    m_conditionalCodeDict.Insert("MI", ConditionalCode::MI);
    m_conditionalCodeDict.Insert("PL", ConditionalCode::PL);
    m_conditionalCodeDict.Insert("AL", ConditionalCode::AL);
    m_conditionalCodeDict.Insert("NV", ConditionalCode::NV);
    m_conditionalCodeDict.Insert("VS", ConditionalCode::VS);
    m_conditionalCodeDict.Insert("VC", ConditionalCode::VC);
    m_conditionalCodeDict.Insert("HI", ConditionalCode::HI);
    m_conditionalCodeDict.Insert("LS", ConditionalCode::LS);

    // Instructions + appendages
    SLList<std::string> instructionList = m_instructionDict.GetKeys();
    SLList<std::string> conditionalCodeList = m_conditionalCodeDict.GetKeys();

    for (SLList<std::string>::SLListIterator it = instructionList.GetBegin();
         it != instructionList.GetEnd(); it++)
    {
        // For every instruction, add the base, base + s, base + conditional, base + s + conditional
        m_keywordDict.Insert(*it, Io::LineType::INSTRUCTION);
        m_keywordDict.Insert(*it + 'S', Io::LineType::INSTRUCTION);
        for (SLList<std::string>::SLListIterator condIt = conditionalCodeList.GetBegin();
             condIt != conditionalCodeList.GetEnd(); condIt++)
        {
            m_keywordDict.Insert(*it + *condIt, Io::LineType::INSTRUCTION);
            m_keywordDict.Insert(*it + *condIt + 'S', Io::LineType::INSTRUCTION);
        }
    }
    
    LOG_INFO("Keyword dictionary initialized");
}

////////////////////////////////
/// METHOD NAME: KeywordDict::Get
////////////////////////////////
Io::LineType KeywordDict::Get(std::string& keyword) const
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