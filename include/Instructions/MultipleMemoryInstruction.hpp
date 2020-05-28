/////////////////////////////////
/// @file MultipleMemoryInstruction.hpp
///
/// @brief Declaration of MultipleMemoryInstruction class
///
/// @author Luke Karavolis
/////////////////////////////////
#ifndef MULITPLE_MEMORY_INSTRUCTION_BASE_HPP
#define MULTIPLE_MEMORY_INSTRUCTION_BASE_HPP

// SYSTEM INCLUDES
// (None)

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "InstructionBase.hpp" // For InstructionBase
#include "Registers.hpp" // For Register
#include "List.hpp" // For List

// FORWARD DECLARATIONS
// (None)

////////////////////////////////
/// @class MultipleMemoryInstruction
///
/// @brief Derived class for memory
/// instructions that perform multiple accesses
////////////////////////////////
class MultipleMemoryInstruction : public InstructionBase
{
public:

    ////////////////////////////////
    /// Constructor
    ////////////////////////////////
    MultipleMemoryInstruction(OpCode opCode) :
        InstructionBase(opCode),
        // m_addressingMode(AddressingMode::INVALID),
        m_pAddressRegister(nullptr),
        m_registerList(List<Register*>()),
        m_updateFlag(false)
    {};

    ////////////////////////////////
    /// METHOD NAME: Execute
    ///
    /// @brief Executes the given operation
    /// on the arguments and places the result
    /// into the destination
    ///
    /// @param[in,out] rProcessRegisters    Registers associated with process
    ////////////////////////////////
    void Execute(Registers& rProcessRegisters) {};

    void Execute(const SLList<std::string>& rArguments, Process& rProcess) {}

    ////////////////////////////////
    /// METHOD NAME: GetRegisterList
    ////////////////////////////////
    List<Register*>& GetRegisterList() { return m_registerList; }

protected:

private:

    /// Mode of addressing for the instruction
    // AddressingMode m_addressingMode;

    /// Pointer to the register holding the base address
    Register* m_pAddressRegister;

    /// List of registers to be operated on
    List<Register*> m_registerList;

    /// Whether m_pAddressRegister should be updated
    bool m_updateFlag;

    ////////////////////////////////
    /// Copy Constructer
    ////////////////////////////////
    MultipleMemoryInstruction(MultipleMemoryInstruction const&);

    ////////////////////////////////
    /// Assignment operator
    ////////////////////////////////
    MultipleMemoryInstruction& operator=(MultipleMemoryInstruction const&);

};

#endif