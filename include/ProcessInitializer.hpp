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
    /// METHOD NAME: Initialize
    ///
    /// @brief Initializes the given file
    ///
    /// @param[in] fileName     File to be initialized
    ////////////////////////////////
    void InitializeFile(const char* fileName) const;

    /// Process that is to be initialized
    Process* m_pProcess;
};


#endif