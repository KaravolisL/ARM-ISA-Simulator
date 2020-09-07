/////////////////////////////////
/// @file Stack.hpp
///
/// @brief Declaration and implementation
/// of a stack data structure backed
/// by a singly linked list
///
/// @author Luke Karavolis
/////////////////////////////////
#ifndef STACK_HPP
#define STACK_HPP

// SYSTEM INCLUDES
// (None)

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "SLList.hpp"       // For SLList<T>

////////////////////////////////
/// @class Stack
///
/// @brief Stack data structure backed
/// by a singly linked list
/// @param E Type stored in stack
////////////////////////////////
template <typename E>
class Stack
{
public:
    /////////////////////////////////////
    /// @brief Constructs a new Stack object
    /////////////////////////////////////
    Stack() :
        m_Stack(SLList<E>())
    {}

    /////////////////////////////////////
    /// @brief Places an element on the top of the stack
    /// 
    /// @param[in] element Element to push
    /////////////////////////////////////
    void Push(E element)
    {
        m_Stack.InsertFront(element);
    }

    ////////////////////////////////
    /// @brief Removes the element on the top of the stack
    ///
    /// @returns Element on top of stack
    /// @throw EmptyStackException
    ////////////////////////////////
    E Pop()
    {
        // Bounds check
        if (Size() == 0) throw EmptyStackException();

        // Remove and return the front of the list
        return m_Stack.Remove(0);
    }

    ////////////////////////////////
    /// @brief Returns the top of the stack
    ///
    /// @returns Element on top of stack
    /// @throw EmptyStackException
    ////////////////////////////////
    E Peek() const
    {
        // Bounds check
        if (Size() == 0) throw EmptyStackException();

        // Return front of list
        return m_Stack.Get(0);
    }

    /////////////////////////////////////
    /// @brief Retrieves the size of the stack
    /// 
    /// @return Number of elements on stack
    /////////////////////////////////////
    uint32_t Size() const
    {
        return m_Stack.GetLength();
    }

    /////////////////////////////////////
    /// @brief Prints the stack to std::cout  
    /////////////////////////////////////
    void PrintStack() const
    {
        return m_Stack.PrintList();
    }

    ////////////////////////////////
    /// @struct EmptyStackException
    ///
    /// @brief Exception used when operations
    /// are done on an empty stack
    ////////////////////////////////
    struct EmptyStackException : public std::exception
    {
        /////////////////////////////////////
        /// @brief Returns the expection message
        /// 
        /// @return Exception message
        /////////////////////////////////////
        const char* what() const throw()
        {
            return "Empty Stack Exception";
        }
    };

protected:


private:

    /// SLList used to represent stack
    SLList<E> m_Stack;

};


#endif