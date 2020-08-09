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
#include <ios> // For ios_base
#include <iostream>

// C PROJECT INCLUDES
// (none)

// C++ PROJECT INCLUDES
#include "DLB.hpp" // For DLB
#include "Registers.hpp" // For Registers struct

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
    // Allow ProcessInitializers to access private members
    friend class ProcessInitializer;

    /////////////////////////////////////
    /// Constructor
    /////////////////////////////////////
    Process() :
        m_processRegisters(Registers()),
        m_labelDictionary(DLB<uint32_t>()),
        m_constantsDictionary(DLB<uint32_t>()),
        m_pFileIterator(nullptr)
    {}

    /////////////////////////////////////
    /// Deconstructor
    /////////////////////////////////////
    ~Process();

    ////////////////////////////////
    /// METHOD NAME: Initialize
    ///
    /// @brief Initializes the process given
    /// code in a file
    ///
    /// @param fileName     Name of file containing assembly code
    ////////////////////////////////
    void Initialize(const char* fileName);

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
    ///
    /// @return Whether program has reached the end
    ////////////////////////////////
    bool Step();

    ////////////////////////////////
    /// METHOD NAME: PrintSummary
    ///
    /// @brief Prints information regarding the
    /// values held in registers
    ////////////////////////////////
    void PrintSummary(std::ios_base& (*func)(std::ios_base&) = &std::dec) const
    {
        for (int i = 0; i < 13; i++)
        {
            std::cout << "R" << std::dec << i << " = " << (*func) << m_processRegisters.genRegs[i] << '\n';
        }
        std::cout << "LR = " << (*func) << m_processRegisters.LR << '\n';
        std::cout << "PC = " << (*func) << m_processRegisters.PC << '\n';
        std::cout << "SP = " << (*func) << m_processRegisters.SP << '\n';
        std::cout << "CPSR = " << (*func) << m_processRegisters.CPSR << '\n';
    }

    ////////////////////////////////
    /// METHOD NAME: GetConstantsDictionary
    ///
    /// @return Constants dictionary
    ////////////////////////////////
    DLB<uint32_t>& GetConstantsDictionary() { return m_constantsDictionary; }
    const DLB<uint32_t>& GetConstantsDictionary() const { return m_constantsDictionary; }

    ////////////////////////////////
    /// METHOD NAME: GetLabelDictionary
    ///
    /// @return Label dictionary
    ////////////////////////////////
    DLB<uint32_t>& GetLabelDictionary() { return m_labelDictionary; }
    const DLB<uint32_t>& GetLabelDictionary() const { return m_labelDictionary; }

    ////////////////////////////////
    /// METHOD NAME: GetProcessRegisters
    ///
    /// @return Process registers
    ////////////////////////////////
    Registers& GetProcessRegisters() { return m_processRegisters; }
    const Registers& GetProcessRegisters() const { return m_processRegisters; }

    ////////////////////////////////
    /// METHOD NAME: GetFileIterator
    ///
    /// @return File Iterator
    ////////////////////////////////
    Io::FileIterator* GetFileIterator() { return m_pFileIterator; }
    const Io::FileIterator* GetFileIterator() const { return m_pFileIterator; }

    ////////////////////////////////
    /// METHOD NAME: SetFileIterator
    ///
    /// @param[in] pFileIterator
    ////////////////////////////////
    void SetFileIterator(Io::FileIterator* pFileIterator) { m_pFileIterator = pFileIterator; }

protected:


private:

    /// Registers associated with this process
    Registers m_processRegisters;

    /// Dictionary connecting labels and their line numbers
    DLB<uint32_t> m_labelDictionary;

    /// Dictionary used for defined constants
    DLB<uint32_t> m_constantsDictionary;

    /// File Iterator used during execution
    Io::FileIterator* m_pFileIterator;

    ////////////////////////////////
    /// Copy Constructer
    ////////////////////////////////
    Process(Process const&);

    ////////////////////////////////
    /// Assignment operator
    ////////////////////////////////
    Process& operator=(Process const&);

};


#endif