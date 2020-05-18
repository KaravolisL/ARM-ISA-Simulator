/////////////////////////////////
/// @file MemoryManager.hpp
///
/// @brief Declarations for MemoryManager class
///
/// @details This class is responsible for 
/// cooridinating operations with memory
///
/// @author Luke Karavolis
/////////////////////////////////
#ifndef MEMORY_MANAGER_HPP
#define MEMORY_MANAGER_HPP

// SYSTEM INCLUDES
#include <fstream>
#include <exception>

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "Assert.hpp" // For ASSERT

// FORWARD DECLARATIONS
// (None)

namespace Memory
{

////////////////////////////////
/// @class MemoryManager
///
/// @brief Class responsible for managing
/// memory operations 
////////////////////////////////
class MemoryManager
{
public:

    ////////////////////////////////
    /// METHOD NAME: GetInstance
    ////////////////////////////////
    static MemoryManager& GetInstance()
    {
        /// Singleton instance
        static MemoryManager* instance = new MemoryManager();
        return *instance;
    }

    ////////////////////////////////
    /// METHOD NAME: Initialize
    ///
    /// @brief initializes the memory file
    /// by writing zeros.
    ////////////////////////////////
    void Initialize();

    ////////////////////////////////
    /// METHOD NAME: ReadWord
    ///
    /// @brief Reads a word from the given
    /// address and return it
    ///
    /// @param[in] address  Address to which to read
    /// @return Data at given address
    ////////////////////////////////
    uint32_t ReadWord(uint32_t address);

    ////////////////////////////////
    /// METHOD NAME: WriteWord
    ///
    /// @brief Writes a word of data to the given address
    ///
    /// @param[in] address  Address to which to read
    /// @param[in] data     Data which to write
    ////////////////////////////////
    void WriteWord(uint32_t address, uint32_t data);

    ////////////////////////////////
    /// @struct MemoryException
    ////////////////////////////////
    struct MemoryException : public std::exception
    {
        const char* what() const throw()
        {
            return "Memory Exception";
        }
    };

protected:

private:

    /// Name of the memory file
    const char* MEMORY_FILE_NAME = "Memory.txt";

    /// File input stream
    std::fstream m_memoryFile;

    /// Lower bound of process memory
    const uint32_t GLOBAL_LOWER_BOUND = 0x20000000;

    /// Lower bound of heap memory
    const uint32_t HEAP_LOWER_BOUND = 0x20008000;

    /// Stack "upper" bound
    const uint32_t STACK_UPPER_BOUND = 0x30008000;

    /// Upper bound of process memory. Also bottom of stack
    const uint32_t GLOBAL_UPPER_BOUND = 0x20004000;

    /// Number of words per row of the memory file
    static const uint16_t WORDS_PER_ROW = 16;

    // Number of hex characters in a word
    static const uint16_t CHARACTERS_PER_WORD = 8;

    // Address plus two characters on each side then each word plus a character following it plus a new line character
    static const uint32_t CHARACTERS_PER_LINE = 2 + CHARACTERS_PER_WORD + 2 + (WORDS_PER_ROW * (CHARACTERS_PER_WORD + 1)) + 2;

    ////////////////////////////////
    /// METHOD NAME: GoToAddress
    ///
    /// @brief Seeks the file stream
    /// to a given memory address
    ///
    /// @param[in] address  Address to which to go
    ////////////////////////////////
    void GoToAddress(uint32_t address);

    ////////////////////////////////
    /// METHOD NAME: ValidateAddress
    ///
    /// @brief Validates that the given
    /// address is within the bounds
    ///
    /// @param[in] address  Address to validate
    /// @throw MemoryException
    ////////////////////////////////
    void ValidateAddress(uint32_t address);

    ////////////////////////////////
    /// Constructor
    ///
    /// @note Private to ensure singleton
    ////////////////////////////////
    MemoryManager() :
        m_memoryFile(std::fstream(MEMORY_FILE_NAME, std::fstream::in | std::fstream::out | std::fstream::trunc))
    {
        ASSERT(m_memoryFile.is_open(), "File did not open");
    }

    ////////////////////////////////
    /// Deconstructor
    ////////////////////////////////
    ~MemoryManager()
    {
        m_memoryFile.close();
    }

    ////////////////////////////////
    /// Copy Constructer
    ////////////////////////////////
    MemoryManager(MemoryManager const&);

    ////////////////////////////////
    /// Assignment operator
    ////////////////////////////////
    MemoryManager& operator=(MemoryManager const&);

};

} // Memory

#endif