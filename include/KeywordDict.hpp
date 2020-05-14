/////////////////////////////////
/// @file KeywordDict.hpp
///
/// @brief Declarations for KeywordDict class
///
/// @details This class contains a dictionary
/// containing the relationship keyword:constant
/// It's used to determine whether a given string is
/// a keyword. If so, what kind.
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
#include "LineTypes.hpp" // For LineType enum

// FORWARD DECLARATIONS
// (None)

////////////////////////////////
/// @class KeywordDict
///
/// @brief Class containing dictionary of keywords
////////////////////////////////
class KeywordDict
{
public:

    ////////////////////////////////
    /// METHOD NAME: GetInstance
    ////////////////////////////////
    static KeywordDict& GetInstance()
    {
        /// Singleton instance
        static KeywordDict* instance = new KeywordDict();
        return *instance;
    }

    ////////////////////////////////
    /// METHOD NAME: Initialize
    ///
    /// @brief Adds keywords to the dictionary
    /// at startup time
    ////////////////////////////////
    void Initialize();

    ////////////////////////////////
    /// METHOD NAME: Get
    ///
    /// @param[in] rKeyword      Keyword to search in dictionary for
    ////////////////////////////////
    Io::LineType Get(std::string& rKeyword) const;

    ////////////////////////////////
    /// METHOD NAME: Contains
    ///
    /// @param[in] rKeyword      Keyword to search in dictionary for
    /// @return Whether keyword is in the dictionary
    ////////////////////////////////
    bool Contains(std::string& rKeyword) const { return m_keywordDict.Contains(rKeyword); }

protected:

private:

    /// DLB to hold keyword:value pairs
    DLB<Io::LineType> m_keywordDict;

    ////////////////////////////////
    /// Constructor
    ///
    /// @note Private to ensure singleton
    ////////////////////////////////
    KeywordDict() :
        m_keywordDict(DLB<Io::LineType>())
    {}

    ////////////////////////////////
    /// Copy Constructer
    ////////////////////////////////
    KeywordDict(KeywordDict const&);

    ////////////////////////////////
    /// Assignment operator
    ////////////////////////////////
    KeywordDict& operator=(KeywordDict const&);

};

#endif