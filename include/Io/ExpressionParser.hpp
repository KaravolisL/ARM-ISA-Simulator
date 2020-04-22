/////////////////////////////////
/// @file ExpressionParser.hpp
///
/// @brief Declarations for ExpressionParser class
///
/// @details This class is used to parse an expression.
/// It's created using a string and a constants dictionary.
/// It's main function Evaluate returns the result
///
/// @author Luke Karavolis
/////////////////////////////////
#ifndef EXPRESSION_PARSER_HPP
#define EXPRESSION_PARSER_HPP

// SYSTEM INCLUDES
// (None)

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include <DLB.hpp> // For DLB class

// FORWARD DECLARATIONS
// (None)

namespace Io
{

////////////////////////////////
/// @class ExpressionParser
///
/// @brief Class used to evaluate expressions
////////////////////////////////
class ExpressionParser
{
public:

    ////////////////////////////////
    /// Constructor
    ////////////////////////////////
    ExpressionParser(std::string expression, DLB<uint32_t>& rConstants) :
        m_expression(expression),
        m_rConstants(rConstants)
    {}

    ////////////////////////////////
    /// METHOD NAME: Evaluate
    ///
    /// @brief Evaluates the expression 
    ///
    /// @return Result of expression
    ////////////////////////////////
    int Evaluate();

protected:

private:

    /// Expression to be parsed
    std::string m_expression;

    /// Constants dictionary to be used
    DLB<uint32_t>& m_rConstants;

};

} // Io

#endif