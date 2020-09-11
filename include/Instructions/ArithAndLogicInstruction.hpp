/////////////////////////////////
/// @file ArithAndLogicInstruction.hpp
///
/// @brief Declaration of ArithAndLogicInstruction class
///
/// @author Luke Karavolis
/////////////////////////////////
#ifndef ARITH_AND_LOGIC_INSTRUCTION_HPP
#define ARITH_AND_LOGIC_INSTRUCTION_HPP

// SYSTEM INCLUDES
// (None)

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "InstructionBase.hpp" // For InstructionBase
#include "Registers.hpp" // For Register

// FORWARD DECLARATIONS
// (None)

////////////////////////////////
/// @class ArithAndLogicInstruction
///
/// @brief Derived class for arithmetic
/// and logic instructions
////////////////////////////////
class ArithAndLogicInstruction : public InstructionBase
{
public:

    /////////////////////////////////////
    /// @brief Constructs a new ArithAndLogicInstruction object
    ///
    /// @param[in] opCode Opcode of the instruction
    /////////////////////////////////////
    ArithAndLogicInstruction(OpCode opCode) :
        InstructionBase(opCode),
        m_pDestination(nullptr),
        m_argument1(0),
        m_argument2(0),
        m_pOperation(nullptr),
        m_sFlag(false)
    {};

    ////////////////////////////////
    /// @brief Executes the given operation
    /// on the arguments and places the result
    /// into the destination
    ///
    /// @param[in,out] rProcessRegisters    Registers associated with process
    ////////////////////////////////
    void Execute(Registers& rProcessRegisters);

    /////////////////////////////////////
    /// @brief Sets the Destination member
    /// 
    /// @param[in] pDestination Pointer to the destination register
    /////////////////////////////////////
    void SetDestination(Register* pDestination) { m_pDestination = pDestination; }

    ////////////////////////////////
    /// @brief Voiding the destination will actually
    /// just make the destination the member variable
    /// itself. This is done if the result of an 
    /// operation is not wanted.
    ////////////////////////////////
    void VoidDestination() { m_pDestination = reinterpret_cast<Register*>(&m_pDestination); }

    /////////////////////////////////////
    /// @brief Sets the Argument1 member
    /// 
    /// @param[in] argument1 First operand
    /////////////////////////////////////
    void SetArgument1(const Register argument1) { m_argument1 = argument1; }

    /////////////////////////////////////
    /// @brief Gets the Argument1 member
    ///
    /// @return Reference to first operand
    /////////////////////////////////////
    Register& GetArgument1() { return m_argument1; }

    /////////////////////////////////////
    /// @brief Sets the Argument2 member
    ///
    /// @param[in] argument2 Second operand
    /////////////////////////////////////
    void SetArgument2(const Register argument2) { m_argument2 = argument2; }

    /////////////////////////////////////
    /// @brief Gets the Argument2 member
    ///
    /// @return Reference to second operand
    /////////////////////////////////////
    Register& GetArgument2() { return m_argument2; }

    /////////////////////////////////////
    /// @brief Sets the Operation member
    ///
    /// @param[in] pOperation Operation of the instruction
    /////////////////////////////////////
    void SetOperation(Register (*pOperation)(Register, Register)) { m_pOperation = pOperation; }

    /////////////////////////////////////
    /// @brief Sets the sFlag member
    /////////////////////////////////////
    void SetSFlag() { m_sFlag = true; }

protected:

private:

    /// Pointer to the destination
    Register* m_pDestination;

    /// First Argument
    Register m_argument1;

    /// Second argument
    Register m_argument2;

    /// Operation to be done with arguments
    Register (*m_pOperation)(Register, Register);

    /// Whether instruction should set the process flags
    bool m_sFlag;

    ////////////////////////////////
    /// @brief Copy Constructer
    ////////////////////////////////
    ArithAndLogicInstruction(ArithAndLogicInstruction const&);

    ////////////////////////////////
    /// @brief Assignment operator
    ////////////////////////////////
    ArithAndLogicInstruction& operator=(ArithAndLogicInstruction const&);

};

#endif