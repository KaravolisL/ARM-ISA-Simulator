#ifndef PROCESS_HPP
#define PROCESS_HPP

/// Statndard includes
#include <stack>

/// C Project includes
// (none)

/// C++ Project includes
#include "Registers.hpp"

class Process
{
    public:

        /////////////////////////////////////
        /// Constructor
        ///
        ///
        /////////////////////////////////////
        Process();

        /////////////////////////////////////
        /// Destructor
        ///
        /////////////////////////////////////
        ~Process();


        int Main();

    protected:




    private:

        std::stack<int>* m_pProcessStack;

        Registers* m_pProcessRegisters;


};


#endif