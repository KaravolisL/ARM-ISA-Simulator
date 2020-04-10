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

/// Standard includes
// (none)

/// C Project includes
// (none)

/// C++ Project includes
#include "Registers.hpp" // For Registers struct
#include "Stack.hpp" // For Stack

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
    Process();

    ////////////////////////////////
    /// METHOD NAME: Execute
    ///
    /// @brief Begins execution of instructions
    ////////////////////////////////
    void Execute();

protected:


private:

    /// Stack associated with this process
    Stack<uint32_t> m_processStack;

    /// Registers associated with this process
    Registers m_processRegisters;

    /// Dictionary connecting labels and their line numbers
    // DLB<int> m_labelDictionary;

};


#endif