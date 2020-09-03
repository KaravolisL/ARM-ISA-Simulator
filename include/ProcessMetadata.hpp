/////////////////////////////////
/// @file ProcessMetadata.hpp
///
/// @brief Declarations of the ProcessMetadata class
///
/// @author Luke Karavolis
/////////////////////////////////
#ifndef PROCESS_METADATA_HPP
#define PROCESS_METADATA_HPP

// SYSTEM INCLUDES
// (None)

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "Stack.hpp" // For Stack

// FORWARD DECLARATIONS
// (None)

////////////////////////////////
/// @class ProcessMetadata
///
/// @brief Data class for properties of a process
/// that can be collected during execution
////////////////////////////////
class ProcessMetadata
{
public:

    ////////////////////////////////
    /// Constructor
    ////////////////////////////////
    ProcessMetadata() :
        m_CallStack(Stack<std::string>())
    {}

    ////////////////////////////////
    /// METHOD NAME: GetCallStack
    ////////////////////////////////
    Stack<std::string>& GetCallStack();

    ////////////////////////////////
    /// METHOD NAME: IsInMain
    ////////////////////////////////
    bool IsInMain();

protected:

private:

    /// Symbolic call stack of process
    Stack<std::string> m_CallStack;

};

////////////////////////////////
/// METHOD NAME: ProcessMetadata::GetCallStack
////////////////////////////////
inline Stack<std::string>& ProcessMetadata::GetCallStack() { return m_CallStack; }

////////////////////////////////
/// METHOD NAME: ProcessMetadata::IsInMain
////////////////////////////////
inline bool ProcessMetadata::IsInMain() { return m_CallStack.Size() == 1; }

#endif