/////////////////////////////////
/// @file KeywordDict.hpp
///
/// @brief Declarations for KeywordDict class
///
/// @author Luke Karavolis
/////////////////////////////////
#ifndef KEYWORD_DICT_HPP
#define KEYWORD_DICT_HPP

// SYSTEM INCLUDES
// (None)

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "DLB.hpp" // For DLB class
#include "HashMap.hpp" // For HashMap
#include "LineTypes.hpp" // For LineType enum
#include "OpCodes.hpp" // For OpCode enum
#include "ConditionalCode.hpp" // For ConditionalCode enum

// FORWARD DECLARATIONS
// (None)

////////////////////////////////
/// @class KeywordDict
///
/// @brief Class containing dictionary of keywords
///
/// @details This class contains a dictionary
/// containing the relationship keyword:constant
/// It's used to determine whether a given string is
/// a keyword. If so, what kind.
////////////////////////////////
class KeywordDict
{
public:

    /////////////////////////////////////
    /// @brief Gets the singleton instance
    /// 
    /// @return KeywordDict instance
    /////////////////////////////////////
    static KeywordDict& GetInstance()
    {
        /// Singleton instance
        static KeywordDict* instance = new KeywordDict();
        return *instance;
    }

    ////////////////////////////////
    /// @brief Adds keywords to the dictionary
    /// at startup time
    ////////////////////////////////
    void Initialize();

    ////////////////////////////////
    /// @brief Retrieves a keyword from dictionary
    ///
    /// @param[in] rKeyword      Keyword to search in dictionary for
    ////////////////////////////////
    Io::LineType Get(std::string& rKeyword) const;

    ////////////////////////////////
    /// @brief Checks whether keyword is in the dictionary
    ///
    /// @param[in] rKeyword      Keyword to search in dictionary for
    /// @return Whether keyword is in the dictionary
    ////////////////////////////////
    bool Contains(std::string& rKeyword) const { return m_keywordDict.Contains(rKeyword); }

    /////////////////////////////////////
    /// @brief Gets the InstructionDict member
    /// 
    /// @return Instruction dictionary
    /////////////////////////////////////
    const HashMap<OpCode>& GetInstructionDict() const { return m_instructionDict; }

    /////////////////////////////////////
    /// @brief Gets the ConditionalCodeDict member
    /// 
    /// @return Conditional code dictionary
    /////////////////////////////////////
    const HashMap<ConditionalCode>& GetConditionalCodeDict() const { return m_conditionalCodeDict; }

protected:

private:

    /// DLB to hold keyword:value pairs
    DLB<Io::LineType> m_keywordDict;

    /// HashMap to hold instruction:OpCode pairs
    HashMap<OpCode> m_instructionDict;

    /// Size used when initializing the HashMap
    static const uint8_t INSTRUCTION_DICT_SIZE = 43;

    /// HashMap containing pairs of conditional codes : CondCodeEnum
    HashMap<ConditionalCode> m_conditionalCodeDict;

    /// Number of conditional codes
    static const uint8_t NUMBER_OF_COND_CODES = 18;

    /////////////////////////////////////
    /// @brief Constructs a new KeywordDict object
    /// 
    /// @note Private to ensure singleton
    /////////////////////////////////////
    KeywordDict() :
        m_keywordDict(DLB<Io::LineType>()),
        m_instructionDict(HashMap<OpCode>(INSTRUCTION_DICT_SIZE)),
        m_conditionalCodeDict(HashMap<ConditionalCode>(NUMBER_OF_COND_CODES))
    {}

    ////////////////////////////////
    /// @brief Copy Constructer
    ////////////////////////////////
    KeywordDict(KeywordDict const&);

    ////////////////////////////////
    /// @brief Assignment operator
    ////////////////////////////////
    KeywordDict& operator=(KeywordDict const&);

};

#endif