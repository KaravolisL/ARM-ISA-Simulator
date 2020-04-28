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
namespace Io
{
    class FileIterator;
}

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
        m_constantsDictionary(DLB<uint32_t>()),
        m_pFileIterator(nullptr)
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
    /// METHOD NAME: PrepareForExecution
    ///
    /// @brief Following initialization, the process needs
    /// to be prepared for execution. This includes setting
    /// up registers, the stack, and file iterators
    ///
    /// @param filename     Name of file containing main
    ////////////////////////////////
    void PrepareForExecution(const char* filename);

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

    ////////////////////////////////
    /// METHOD NAME: GetConstantsDictionary
    ///
    /// @return Constants dictionary
    ////////////////////////////////
    DLB<uint32_t>& GetConstantsDictionary() { return m_constantsDictionary; }

    ////////////////////////////////
    /// METHOD NAME: GetProcessStack
    ///
    /// @return Process Stack
    ////////////////////////////////
    Stack<Register>& GetProcessStack() { return m_processStack; }

    ////////////////////////////////
    /// METHOD NAME: GetProcessRegisters
    ///
    /// @return Process registers
    ////////////////////////////////
    Registers& GetProcessRegisters() { return m_processRegisters; }

    ////////////////////////////////
    /// METHOD NAME: GetFileIterator
    ///
    /// @return File Iterator
    ////////////////////////////////
    Io::FileIterator* GetFileIterator() { return m_pFileIterator; }

protected:


private:

    /// Stack associated with this process
    Stack<Register> m_processStack;

    /// Registers associated with this process
    Registers m_processRegisters;

    /// Dictionary connecting labels and their line numbers
    DLB<uint32_t> m_labelDictionary;

    /// Dictionary used for defined constants
    DLB<uint32_t> m_constantsDictionary;

    /// File Iterator used during execution
    Io::FileIterator* m_pFileIterator;

};


#endif