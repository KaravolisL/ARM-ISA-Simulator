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

protected:

private:

    /// Name of the memory file
    const char* MEMORY_FILE_NAME = "Memory.txt";

    /// File input stream
    std::fstream m_memoryFile;

    /// Lower bound of process memory
    const uint32_t m_globalLowerBound = 0x20000000;

    /// Lower bound of heap memory
    const uint32_t m_heapLowerBound = 0x20008000;

    /// Stack "upper" bound
    const uint32_t m_stackUpperBound = 0x30008000;

    /// Upper bound of process memory. Also bottom of stack
    const uint32_t m_globalUpperBound = 0x40000000;

    ////////////////////////////////
    /// Constructor
    ///
    /// @note Private to ensure singleton
    ////////////////////////////////
    MemoryManager() :
        m_memoryFile(std::fstream(MEMORY_FILE_NAME))
    {
        ASSERT(m_memoryFile.is_open(), "File did not open");
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