/////////////////////////////////
/// @file MemoryConstants.hpp
///
/// @brief Constants pertinent to a process's memory
///
/// @author Luke Karavolis
/////////////////////////////////
#ifndef MEMORY_CONSTANTS_HPP
#define MEMORY_CONSTANTS_HPP

// SYSTEM INCLUDES
#include <stdint.h> // For standard types

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
// (None)

// FORWARD DECLARATIONS
// (None)

namespace Memory
{

/// Lower bound of process memory
const uint32_t GLOBAL_LOWER_BOUND = 0x20000000;

/// Lower bound of heap memory
const uint32_t HEAP_LOWER_BOUND = 0x20003A00;

/// Heap upper bound
const uint32_t HEAP_UPPER_BOUND = 0x20003C00;

/// Size of heap
const uint32_t HEAP_SIZE = HEAP_UPPER_BOUND - HEAP_LOWER_BOUND;

/// Stack "upper" bound
const uint32_t STACK_UPPER_BOUND = 0x20003C00;

/// Stack "lower" bound
const uint32_t STACK_LOWER_BOUND = 0x20004000;

/// Size of stack
const uint32_t STACK_SIZE = STACK_LOWER_BOUND - STACK_UPPER_BOUND;

/// Upper bound of process memory. Also bottom of stack
const uint32_t GLOBAL_UPPER_BOUND = 0x20004000;

/// A word is 4 bytes
const uint8_t WORD_SIZE_IN_BYTES = 4;

} // Memory

#endif