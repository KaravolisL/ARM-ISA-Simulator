

#include "Process.hpp"

#include <stack>


///////////////////////////////////////
///
///
///////////////////////////////////////
Process::Process() :
    m_pProcessStack(),
    m_pProcessRegisters()
{
    m_pProcessStack = new std::stack<int>();
    m_pProcessRegisters = new Registers();
}


int Process::Main()
{

}
