#include "Process.hpp"

Process::~Process()
{
    free(m_pFileIterator);
}