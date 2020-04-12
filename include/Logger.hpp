/////////////////////////////////
/// @file Logger.hpp
///
/// @brief Declaration of Logger class
///
/// @details The logger class is used to
/// print debug messages while the program
/// is executing
///
/// @author Luke Karavolis
/////////////////////////////////
#ifndef LOGGER_HPP
#define LOGGER_HPP

// SYSTEM INCLUDES
// (None)

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
// (None)

// FORWARD DECLARATIONS
// (None)

////////////////////////////////
/// @class Logger
////////////////////////////////
class Logger
{
public:

    ////////////////////////////////
    /// METHOD NAME: GetInstance
    ////////////////////////////////
    Logger* GetInstance()
    {
        if (m_pInstance == nullptr)
        {
            m_pInstance = new Logger();
        }
        return m_pInstance;
    }

protected:

private:

    ////////////////////////////////
    /// Constructer
    ///
    /// @note Private to ensure singleton
    ////////////////////////////////
    Logger() {}

    /// Singleton instance
    static Logger* m_pInstance;

};

#endif