/////////////////////////////////
/// @file DLList.hpp
///
/// @brief Declarations and implementation for
/// doubly linked list
/////////////////////////////////
#ifndef DLLIST_HPP
#define DLLIST_HPP

// SYSTEM INCLUDES
#include <assert.h>
#include <iostream> // For std::cout

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "IndexOutOfBoundsException.hpp" // For IndexOutOfBoundsException

////////////////////////////////
/// @class DLList
///
/// @brief Doubly linked list class
/// @tparam T type stored in list
////////////////////////////////
template <typename T>
class DLList
{
private:

    ////////////////////////////////
    /// @struct Node
    ///
    /// @brief Data type used to store
    /// data in list and next node pointer
    ////////////////////////////////
    typedef struct Node
    {
        /// Data held by node
        T data;

        /// Pointer to the next node
        Node* next;

        /// Pointer to the previous node
        Node* prev;

        /////////////////////////////////////
        /// @brief Constructs a new Node object
        ///
        /// @param[in] data Data to be held by node
        /////////////////////////////////////
        Node(T data) :
            data(data),
            prev(nullptr),
            next(nullptr)
        {}

        /////////////////////////////////////
        /// @brief Assignment operator
        /////////////////////////////////////
        Node& operator=(Node const&);

        /////////////////////////////////////
        /// @brief Copy constructor
        /////////////////////////////////////
        Node(Node const&);

    } Node;

public:

    /////////////////////////////////////
    /// @brief Constructs a new DLList object
    /////////////////////////////////////
    DLList() :
        head(nullptr),
        tail(nullptr),
        m_Length(0)
    {}

    ////////////////////////////////
    /// @brief Inserts an element at the front of the list
    ///
    /// @param element   Element to be inserted
    ////////////////////////////////
    void InsertFront(T element)
    {
        // If the list is empty, make new element the head and tail
        if (head == nullptr)
        {
            assert(tail == nullptr);
            head = new Node(element);
            tail = head;
        }
        else
        {
            // Make this new node the head of the list
            Node* pNewNode = new Node(element);
            pNewNode->next = head;
            head->prev = pNewNode;
            head = pNewNode;
        }

        m_Length++;
    }

    ////////////////////////////////
    /// @brief Inserts an element at the back of the list
    ///
    /// @param element   Element to be inserted
    ////////////////////////////////
    void InsertBack(T element)
    {
        // If the list is empty, make new element the head and tail
        if (head == nullptr)
        {
            assert(tail == nullptr);
            head = new Node(element);
            tail = head;
        }
        else
        {
            // Append new node to the end
            Node* pNewNode = new Node(element);
            tail->next = pNewNode;
            pNewNode->prev = tail;
            tail = pNewNode;
        }

        m_Length++;
    }

    ////////////////////////////////
    /// @brief Retrieves an element from the list
    ///
    /// @param index   Index of element to return
    /// @return Element at given value
    /// @throw IndexOutOfBoundsException
    ////////////////////////////////
    T Get(uint32_t index) const
    {
        for (Node* pCurrentNode = head;
             pCurrentNode != nullptr;
             pCurrentNode = pCurrentNode->next)
        {
            if (index-- == 0)
            {
                return pCurrentNode->data;
            }
        }
        throw IndexOutOfBoundsException(index);
    }

    ////////////////////////////////
    /// @brief Frees all nodes in the list
    ////////////////////////////////
    void Clear(void)
    {
        Node* pNextNode;
        for (Node* pCurrentNode = head;
             pCurrentNode != nullptr;
             pCurrentNode = pNextNode)
        {
            // Save the next node and delete current
            pNextNode = pCurrentNode->next;
            delete pCurrentNode;
        }
        head = nullptr;
        tail = nullptr;
        m_Length = 0;
    }

    ////////////////////////////////
    /// @brief Removes an element from the list
    ///
    /// @param index    Index to remove
    /// @return Data stored at given index
    /// @throw IndexOutOfBoundsException
    ////////////////////////////////
    T Remove(uint32_t index)
    {
        // Bounds check
        if ((index + 1) > m_Length) throw IndexOutOfBoundsException(index);

        Node* pOldNode;
        // Deleting only node
        if (head == tail)
        {
            pOldNode = head;
            head = nullptr;
            tail = nullptr;
        }
        else
        {
            if (index == 0)
            {
                pOldNode = head;
                head = pOldNode->next;
                head->prev = nullptr;
            }
            else if (index == m_Length - 1)
            {
                pOldNode = tail;
                tail = pOldNode->prev;
                tail->next = nullptr;
            }
            else
            {
                for (Node* pCurrentNode = head;
                    pCurrentNode != nullptr;
                    pCurrentNode = pCurrentNode->next)
                {
                    if (index-- == 0)
                    {
                        pOldNode = pCurrentNode;
                        pCurrentNode->prev->next = pCurrentNode->next;
                        pCurrentNode->next->prev = pCurrentNode->prev;
                        break;
                    }
                }
            }
        }

        // Delete the node and return it's data;
        T data = pOldNode->data;
        delete pOldNode;
        m_Length--;
        return data;
    }

    /////////////////////////////////////
    /// @brief Gets the Length member
    ///
    /// @return Number of elements in the list
    /////////////////////////////////////
    uint32_t GetLength(void) const
    {
        return m_Length;
    }

    ////////////////////////////////
    /// @brief Prints the list to std::cout
    ////////////////////////////////
    void PrintList(void) const
    {
        for (Node* pCurrentNode = head;
                pCurrentNode != nullptr;
                pCurrentNode = pCurrentNode->next)
        {
            std::cout << pCurrentNode->data;
            if (pCurrentNode->next != nullptr)
            {
                std::cout << "<->";
            }
            else
            {
                std::cout << "\n";
            }

        }
    }

    // Forward declaration of iterator class
    class DLListIterator;

    ////////////////////////////////
    /// @brief Obtains an iterator from the beginning
    ///
    /// @return DLListIterator from beginning
    ////////////////////////////////
    DLListIterator GetBegin()
    {
        return DLListIterator(head);
    }

    ////////////////////////////////
    /// @brief Obtains a reverse iterator from the beginning
    ///
    /// @return DLListIterator from beginning
    ////////////////////////////////
    DLListIterator GetReverseBegin()
    {
        return DLListIterator(tail);
    }

    ////////////////////////////////
    /// @brief Obtains an iterator from the end
    ///
    /// @return DLListIterator from end
    ////////////////////////////////
    DLListIterator GetEnd()
    {
        return DLListIterator(tail->next);
    }

    ////////////////////////////////
    /// @brief Obtains a reverse iterator from the end
    ///
    /// @return DLListIterator from end
    ////////////////////////////////
    DLListIterator GetReverseEnd()
    {
        return DLListIterator(head->prev);
    }

    ////////////////////////////////
    /// @class DLListIterator
    ///
    /// @brief Class used to iterate
    /// through a linked list
    ////////////////////////////////
    class DLListIterator
    {
    public:
        /////////////////////////////////////
        /// @brief Constructs a new DLListIterator object
        /////////////////////////////////////
        DLListIterator() :
            pNextNode(nullptr)
        {}

        /////////////////////////////////////
        /// @brief Constructs a new DLListIterator object
        ///
        /// @param[in] startingNode Node at which to start
        /////////////////////////////////////
        DLListIterator(Node* startingNode) :
            pNextNode(startingNode)
        {}

        ////////////////////////////////
        /// @brief Assignment Operator
        ////////////////////////////////
        DLListIterator& operator=(Node* pNode)
        {
            pNextNode = pNode;
            return *this;
        }

        ////////////////////////////////
        /// @brief Prefix ++ Operator
        ////////////////////////////////
        DLListIterator& operator++()
        {
            if (pNextNode != nullptr)
            {
                pNextNode = pNextNode->next;
            }
            return *this;
        }

        ////////////////////////////////
        /// @brief Postfix ++ Operator
        ////////////////////////////////
        DLListIterator operator++(int)
        {
            DLListIterator iterator = *this;
            ++*this;
            return iterator;
        }

        ////////////////////////////////
        /// @brief Prefix -- Operator
        ////////////////////////////////
        DLListIterator& operator--()
        {
            if (pNextNode != nullptr)
            {
                pNextNode = pNextNode->prev;
            }
            return *this;
        }

        ////////////////////////////////
        /// @brief Postfix -- Operator
        ////////////////////////////////
        DLListIterator operator--(int)
        {
            DLListIterator iterator = *this;
            --*this;
            return iterator;
        }

        ////////////////////////////////
        /// @brief Not Equal Operator
        ////////////////////////////////
        bool operator!=(const DLListIterator& iterator)
        {
            return pNextNode != iterator.pNextNode;
        }

        ////////////////////////////////
        /// @brief Dereference Operator
        ////////////////////////////////
        T operator*() const
        {
            return pNextNode->data;
        }

    private:

        /// Pointer to the next element in the list
        DLList::Node* pNextNode;
    };

protected:

private:

    /// Pointer to the head of the list
    Node* head;

    /// Pointer to the last element in the list
    Node* tail;

    /// Number of elements in the list
    uint32_t m_Length;

};

#endif