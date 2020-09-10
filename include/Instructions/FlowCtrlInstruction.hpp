/////////////////////////////////
/// @file FlowCtrlInstruction.hpp
///
/// @brief Declaration of FlowCtrlInstruction class
///
/// @author Luke Karavolis
/////////////////////////////////
#ifndef FLOW_CTRL_INSTRUCTION_HPP
#define FLOW_CTRL_INSTRUCTION_HPP

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
/// @class FlowCtrlInstruction
///
/// @brief Derived class for flow control instructions
////////////////////////////////
class FlowCtrlInstruction : public InstructionBase
{
public:

    /////////////////////////////////////
    /// @brief Constructs a new FlowCtrlInstruction object
    ///
    /// @param[in] opCode Opcode of instruction
    /////////////////////////////////////
    FlowCtrlInstruction(OpCode opCode) :
        InstructionBase(opCode),
        m_linkFlag(false),
        m_newPC(0)
    {};

    ////////////////////////////////
    /// @brief Executes a branch instruction
    /// and optionally links and/or exchanges
    ///
    /// @param[in,out] rProcessRegisters    Registers associated with process
    ////////////////////////////////
    void Execute(Registers& rProcessRegisters);

    /////////////////////////////////////
    /// @brief Sets the NewPC member
    ///
    /// @param[in] newPC New PC value
    /////////////////////////////////////
    void SetNewPC(Register newPC) { m_newPC = newPC; }

    /////////////////////////////////////
    /// @brief Sets the LinkFlag member
    /////////////////////////////////////
    void SetLinkFlag() { m_linkFlag = true; }

protected:

private:

    /// Whether this instruction should set the link register
    bool m_linkFlag;

    /// Value for the next PC value
    Register m_newPC;

    ////////////////////////////////
    /// @brief Copy Constructer
    ////////////////////////////////
    FlowCtrlInstruction(FlowCtrlInstruction const&);

    ////////////////////////////////
    /// @brief Assignment operator
    ////////////////////////////////
    FlowCtrlInstruction& operator=(FlowCtrlInstruction const&);

};

#endif