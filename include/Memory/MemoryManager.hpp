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
// (None)

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
// (None)

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

protected:

private:

    ////////////////////////////////
    /// Constructor
    ///
    /// @note Private to ensure singleton
    ////////////////////////////////
    MemoryManager() {}

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