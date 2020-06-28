/////////////////////////////////
/// @file ProcessInitializer.hpp
///
/// @brief Declarations for the ProcessInitializer
/// class
///
/// @details This class is used to
/// initialize a process prior to its execution
///
/// @author Luke Karavolis
/////////////////////////////////
#ifndef PROCESS_INITIALIZER_HPP
#define PROCESS_INITIALIZER_HPP

// SYSTEM INCLUDES
// (None)

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
// (None)

// FORWARD DECLARATIONS
class Process;

namespace Io
{
class LineParser;
}

////////////////////////////////
/// @class ProcessInitializer
///
/// @brief Declarations for the 
/// ProcessInitializer class
////////////////////////////////
class ProcessInitializer
{
public:
    /////////////////////////////////////
    /// Constructor
    /////////////////////////////////////
    ProcessInitializer(Process* pProcess) :
        m_pProcess(pProcess)
    {}

    ////////////////////////////////
    /// METHOD NAME: Initialize
    ///
    /// @brief Begins the initialization of the
    /// process using the given main file
    ///
    /// @param[in] fileName     File to be initialized
    ////////////////////////////////
    void Initialize(const char* fileName) const;

protected:


private:

    ////////////////////////////////
    /// METHOD NAME: InitializeFile
    ///
    /// @brief Initializes the given file
    ///
    /// @param[in] fileName     File to be initialized
    ////////////////////////////////
    void InitializeFile(const char* fileName) const;

    ////////////////////////////////
    /// METHOD NAME: HandleMemoryDirective
    ///
    /// @brief Handles the DCD and DCB directives
    ///
    /// @param[in,out] rLineParser  Parser of current line
    ////////////////////////////////
    void HandleMemoryDirective(Io::LineParser& rLineParser) const;

    /// Process that is to be initialized
    Process* m_pProcess;
};


#endif