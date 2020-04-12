/////////////////////////////////
/// @file Process.hpp
///
/// @brief Declarations for the Process
/// class
///
/// @details This class is used to
/// represent a program written by the user
///
/// @author Luke Karavolis
/////////////////////////////////
#ifndef PROCESS_HPP
#define PROCESS_HPP

// SYSTEM INCLUDES
#include <stdint.h> // For standard types

// C PROJECT INCLUDES
// (none)

// C++ PROJECT INCLUDES
#include "DLB.hpp" // For DLB
#include "Registers.hpp" // For Registers struct
#include "Stack.hpp" // For Stack

// FORWARD DECLARATIONS
// (None)

////////////////////////////////
/// @class Process
///
/// @brief Declarations for the 
/// Process class
////////////////////////////////
class Process
{
public:
    /////////////////////////////////////
    /// Constructor
    /////////////////////////////////////
    Process() :
        m_processStack(Stack<uint32_t>()),
        m_processRegisters(Registers()),
        m_labelDictionary(DLB<uint32_t>()),
        m_constantsDictionary(DLB<uint32_t>())
    {}

    ////////////////////////////////
    /// METHOD NAME: Initialize
    ///
    /// @brief Initializes the process given
    /// code in a file
    ///
    /// @param filename     Name of file containing assembly code
    ////////////////////////////////
    void Initialize(const char* filename);

    ////////////////////////////////
    /// METHOD NAME: Execute
    ///
    /// @brief Begins execution of instructions
    ////////////////////////////////
    void Execute();

    ////////////////////////////////
    /// METHOD NAME: Step
    ///
    /// @brief Executes the next instruction
    ////////////////////////////////
    void Step();

protected:


private:

    /// Stack associated with this process
    Stack<uint32_t> m_processStack;

    /// Registers associated with this process
    Registers m_processRegisters;

    /// Dictionary connecting labels and their line numbers
    DLB<uint32_t> m_labelDictionary;

    /// Dictionary used for defined constants
    DLB<uint32_t> m_constantsDictionary;

};


#endif