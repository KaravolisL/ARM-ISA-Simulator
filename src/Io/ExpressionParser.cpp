/////////////////////////////////
/// @file ExpressionParser.cpp
///
/// @brief Implementation of ExpressionParser class
///
/// @copydetail ExpressionParser
///
/// @author Luke Karavolis
/////////////////////////////////

// SYSTEM INCLUDES
#include <iostream>
#include <string.h>
#include <stdexcept>

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "ExpressionParser.hpp" // Header for class

namespace Io
{

////////////////////////////////
/// METHOD NAME: ExpressionParser::Evaluate
////////////////////////////////
int ExpressionParser::Evaluate()
{
    char* leftOperand = strtok(const_cast<char*>(m_expression.c_str()), " ()");

    int leftInt;
    try
    {
        leftInt = static_cast<int>(std::stoul(leftOperand, nullptr, 16));
    }
    catch (const std::invalid_argument& e)
    {
        // left operand must already be a constant
        leftInt = m_rConstants.Get(leftOperand);
    }
    
    // Get operation
   char* operation = strtok(NULL, " ()");

   if (operation == NULL)
   {
       // expression is just a constant
       return leftInt;
   }

    // Get right operand
    char* rightOperand = strtok(NULL, " ()");

    int rightInt;
    try
    {
        rightInt = static_cast<int>(std::stoul(rightOperand, nullptr, 16));
    }
    catch (const std::invalid_argument& e)
    {
        // right operand must already be a constant
        rightInt = m_rConstants.Get(rightOperand);
    }

    if (strcmp(operation, "<<") == 0)
    {
        return leftInt << rightInt;
    }
    else if (strcmp(operation, "+") == 0)
    {
        return leftInt + rightInt;
    }
    else
    {
        throw std::invalid_argument("Unexpected operation");
    }
    
}

} // Io