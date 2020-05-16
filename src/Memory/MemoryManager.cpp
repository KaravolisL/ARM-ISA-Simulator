/////////////////////////////////
/// @file MemoryManager.cpp
///
/// @brief Implementation of MemoryManager class
///
/// @copydetail MemoryManager
///
/// @author Luke Karavolis
/////////////////////////////////

// SYSTEM INCLUDES
#include <string>
#include <iostream>

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "MemoryManager.hpp" // Header for class
#include "Logger.hpp" // For LOG_INFO

namespace Memory
{

////////////////////////////////
/// METHOD NAME: Memory::MemoryManager::Initialize
////////////////////////////////
void MemoryManager::Initialize()
{
    LOG_INFO("MemoryManager Initialized");
}

} // Memory