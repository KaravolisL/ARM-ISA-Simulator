/////////////////////////////////
/// @file Queue.hpp
///
/// @brief Declarations and implementation of 
/// Queue template class
///
/// @details Queue data structure backed
/// by a linked list enforcing FIFO operations
///
/// @author Luke Karavolis
/////////////////////////////////
#ifndef QUEUE_HPP
#define QUEUE_HPP

// SYSTEM INCLUDES
// (None)

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "SLList.hpp" // For SLList

// FORWARD DECLARATIONS
// (None)

////////////////////////////////
/// @class Queue
///
/// @brief Queue data structure
////////////////////////////////
template <typename T>
class Queue
{
public:

    ////////////////////////////////
    /// Constructor
    ////////////////////////////////
    Queue() :
        m_Queue(SLList<T>())
    {}

    ////////////////////////////////
    /// METHOD NAME: Push
    ///
    /// @param element      Element to push onto queue
    ////////////////////////////////
    void Push(T element)
    {
        m_Queue.InsertBack(element);
    }

    ////////////////////////////////
    /// METHOD NAME: Pop
    ///
    /// @return Element at front of queue
    /// @throw EmptyQueueException
    ////////////////////////////////
    T Pop()
    {
        if (this->Size() == 0) throw EmptyQueueException();

        return m_Queue.Remove(0);
    }

    ////////////////////////////////
    /// METHOD NAME: Peek
    ///
    /// @returns Element at front of queue
    /// @throw EmptyQueueException
    ////////////////////////////////
    T Peek()
    {
        // Bounds check
        if (this->Size() == 0) throw EmptyQueueException();

        // Return front of list
        return m_Queue.Get(0);
    }

    ////////////////////////////////
    /// METHOD NAME: Size
    ////////////////////////////////
    int Size()
    {
        return m_Queue.GetLength();
    }

    ////////////////////////////////
    /// @struct EmptyQueueException
    ////////////////////////////////
    struct EmptyQueueException : public std::exception
    {
        const char* what() const throw()
        {
            return "Empty Queue Exception";
        }
    };

protected:

private:

    /// Linked list to back Queue
    SLList<T> m_Queue;
};

#endif