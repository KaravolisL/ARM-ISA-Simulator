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

    ////////////////////////////////
    /// Constructor
    ////////////////////////////////
    ArithAndLogicInstruction(OpCode opCode) :
        InstructionBase(opCode),
        m_pDestination(nullptr),
        m_argument1(0),
        m_argument2(0),
        m_pOperation(nullptr),
        m_sFlag(false)
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
    void Execute(Registers& rProcessRegisters);

    ////////////////////////////////
    /// METHOD NAME: SetDestination
    ////////////////////////////////
    void SetDestination(Register* pDestination) { m_pDestination = pDestination; }

    ////////////////////////////////
    /// METHOD NAME: VoidDestination
    ///
    /// @note Voiding the destination will actually
    /// just make the destination the member variable
    /// itself. This is done if the result of an 
    /// operation is not wanted.
    ////////////////////////////////
    void VoidDestination() { m_pDestination = reinterpret_cast<Register*>(&m_pDestination); }

    ////////////////////////////////
    /// METHOD NAME: SetArgument1
    ////////////////////////////////
    void SetArgument1(const Register argument1) { m_argument1 = argument1; }

    ////////////////////////////////
    /// METHOD NAME: GetArgument1
    ////////////////////////////////
    Register& GetArgument1() { return m_argument1; }

    ////////////////////////////////
    /// METHOD NAME: SetArgument2
    ////////////////////////////////
    void SetArgument2(const Register argument2) { m_argument2 = argument2; }

    ////////////////////////////////
    /// METHOD NAME: GetArgument2
    ////////////////////////////////
    Register& GetArgument2() { return m_argument2; }

    ////////////////////////////////
    /// METHOD NAME: SetOperation
    ////////////////////////////////
    void SetOperation(Register (*pOperation)(Register, Register)) { m_pOperation = pOperation; }

    ////////////////////////////////
    /// METHOD NAME: SetSFlag
    ////////////////////////////////
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
    /// Copy Constructer
    ////////////////////////////////
    ArithAndLogicInstruction(ArithAndLogicInstruction const&);

    ////////////////////////////////
    /// Assignment operator
    ////////////////////////////////
    ArithAndLogicInstruction& operator=(ArithAndLogicInstruction const&);

};

#endif