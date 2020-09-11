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
/// @tparam T Type of objects the queue holds
////////////////////////////////
template <typename T>
class Queue
{
public:

    /////////////////////////////////////
    /// @brief Constructs a new Queue object
    /////////////////////////////////////
    Queue() :
        m_Queue(SLList<T>())
    {}

    ////////////////////////////////
    /// @brief Pushes an element onto the queue
    ///
    /// @param element      Element to push onto queue
    ////////////////////////////////
    void Push(T element)
    {
        m_Queue.InsertBack(element);
    }

    ////////////////////////////////
    /// @brief Pops an element from the queue
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
    /// @brief Returns the next element in the queue
    ///
    /// @returns Element at front of queue
    /// @throw EmptyQueueException
    ////////////////////////////////
    T Peek() const
    {
        // Bounds check
        if (this->Size() == 0) throw EmptyQueueException();

        // Return front of list
        return m_Queue.Get(0);
    }

    ////////////////////////////////
    /// @brief Returns the size of the queue
    ///
    /// @return Number of elements in the queue
    ////////////////////////////////
    int Size() const
    {
        return m_Queue.GetLength();
    }

    ////////////////////////////////
    /// @struct EmptyQueueException
    ////////////////////////////////
    struct EmptyQueueException : public std::exception
    {
        /////////////////////////////////////
        /// @brief Returns the exception message
        /// 
        /// @return Exception message
        /////////////////////////////////////
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