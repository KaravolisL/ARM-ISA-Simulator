/////////////////////////////////
/// Stack.hpp
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
/// CLASS NAME: Stack
///
/// @brief Stack data structure backed
/// by a singly linked list
/// @param E Type stored in stack
////////////////////////////////
template <typename E>
class Stack
{
public:
    ////////////////////////////////
    /// Constructor
    ////////////////////////////////
    Stack() :
        m_Stack(SLList<E>())
    {}

    ////////////////////////////////
    /// METHOD NAME: Push
    ///
    /// @param element      Element to push onto stack
    ////////////////////////////////
    void Push(E element)
    {
        m_Stack.InsertFront(element);
    }

    ////////////////////////////////
    /// METHOD NAME: Pop
    ///
    /// @returns Element on top of stack
    /// @throw EmptyStackException
    ////////////////////////////////
    E Pop()
    {
        // Bounds check
        if (this->Size() == 0) throw EmptyStackException();

        // Remove and return the front of the list
        return m_Stack.Remove(0);
    }

    ////////////////////////////////
    /// METHOD NAME: Peek
    ///
    /// @returns Element on top of stack
    /// @throw EmptyStackException
    ////////////////////////////////
    E Peek() const
    {
        // Bounds check
        if (this->Size() == 0) throw EmptyStackException();

        // Return front of list
        return m_Stack.Get(0);
    }

    ////////////////////////////////
    /// METHOD NAME: Size
    ////////////////////////////////
    int Size() const
    {
        return m_Stack.GetLength();
    }

protected:


private:

    /// SLList used to represent stack
    SLList<E> m_Stack;

    struct EmptyStackException : public std::exception
    {
        const char* what() const throw()
        {
            return "Empty Stack Exception";
        }
    };
};


#endif