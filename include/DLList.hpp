/////////////////////////////////
/// DLList.hpp
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
/// CLASS NAME: DLList
///
/// @brief Doubly linked list class
/// @param T type stored in list
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
        T data;
        Node* next;
        Node* prev;

        Node(T data) :
            data(data),
            next(nullptr),
            prev(nullptr)
        {}

        Node& operator=(Node const&);
        Node(Node const&);
    } Node;

public:

    ////////////////////////////////
    /// Constructor
    ////////////////////////////////
    DLList() :
        head(nullptr),
        tail(nullptr),
        m_Length(0)
    {}

    ////////////////////////////////
    /// FUNCTION NAME: InsertFront
    ///
    /// @param element   Element to be inserted
    ////////////////////////////////
    void InsertFront(T element)
    {
        // If the list is empty, make new element the head and tail
        if (this->head == nullptr)
        {
            assert(this->tail == nullptr);
            this->head = new Node(element);
            this->tail = this->head;
        }
        else
        {
            // Make this new node the head of the list
            Node* pNewNode = new Node(element);
            pNewNode->next = this->head;
            this->head->prev = pNewNode;
            this->head = pNewNode;
        }

        this->m_Length++;
    }

    ////////////////////////////////
    /// FUNCTION NAME: InsertBack
    ///
    /// @param element   Element to be inserted
    ////////////////////////////////
    void InsertBack(T element)
    {
        // If the list is empty, make new element the head and tail
        if (this->head == nullptr)
        {
            assert(this->tail == nullptr);
            this->head = new Node(element);
            this->tail = this->head;
        }
        else
        {
            // Append new node to the end
            Node* pNewNode = new Node(element);
            this->tail->next = pNewNode;
            pNewNode->prev = this->tail;
            this->tail = pNewNode;
        }

        this->m_Length++;
    }

    ////////////////////////////////
    /// FUNCTION NAME: Get
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
    /// FUNCTION NAME: Clear
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
        this->head = nullptr;
        this->tail = nullptr;
        this->m_Length = 0;
    }

    ////////////////////////////////
    /// FUNCTION NAME: Remove
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
        if (this->head == this->tail)
        {
            pOldNode = this->head;
            this->head = nullptr;
            this->tail = nullptr;
        }
        else
        {
            if (index == 0)
            {
                pOldNode = this->head;
                this->head = pOldNode->next;
                this->head->prev = nullptr;
            }
            else if (index == m_Length - 1)
            {
                pOldNode = this->tail;
                this->tail = pOldNode->prev;
                this->tail->next = nullptr;
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
        this->m_Length--;
        return data;
    }

    ////////////////////////////////
    /// FUNCTION NAME: GetLength
    ///
    /// @returns m_Length of list
    ////////////////////////////////
    uint32_t GetLength(void) const
    {
        return this->m_Length;
    }

    ////////////////////////////////
    /// FUNCTION NAME: PrintList
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
    /// FUNCTION NAME: GetBegin
    ////////////////////////////////
    DLListIterator GetBegin()
    {
        return DLListIterator(this->head);
    }

    ////////////////////////////////
    /// FUNCTION NAME: GetReverseBegin
    ////////////////////////////////
    DLListIterator GetReverseBegin()
    {
        return DLListIterator(this->tail);
    }

    ////////////////////////////////
    /// FUNCTION NAME: GetEnd
    ////////////////////////////////
    DLListIterator GetEnd()
    {
        return DLListIterator(this->tail->next);
    }

    ////////////////////////////////
    /// FUNCTION NAME: GetReverseEnd
    ////////////////////////////////
    DLListIterator GetReverseEnd()
    {
        return DLListIterator(this->head->prev);
    }

    ////////////////////////////////
    /// CLASS NAME: DLListIterator
    ///
    /// @brief Class used to iterate
    /// through a linked list
    ////////////////////////////////
    class DLListIterator
    {
    public:
        ////////////////////////////////
        /// Constructor
        ////////////////////////////////
        DLListIterator() :
            pNextNode(nullptr)
        {}

        DLListIterator(Node* startingNode) :
            pNextNode(startingNode)
        {}

        ////////////////////////////////
        /// Assignment Operator
        ////////////////////////////////
        DLListIterator& operator=(Node* pNode)
        { 
            this->pNextNode = pNode; 
            return *this; 
        }

        ////////////////////////////////
        /// Prefix ++ Operator
        //////////////////////////////// 
        DLListIterator& operator++() 
        { 
            if (this->pNextNode != nullptr)
            {
                this->pNextNode = this->pNextNode->next;
            }
            return *this; 
        } 
  
        ////////////////////////////////
        /// Postfix ++ Operator
        ////////////////////////////////
        DLListIterator operator++(int) 
        { 
            DLListIterator iterator = *this; 
            ++*this; 
            return iterator; 
        }

        ////////////////////////////////
        /// Prefix -- Operator
        //////////////////////////////// 
        DLListIterator& operator--() 
        { 
            if (this->pNextNode != nullptr)
            {
                this->pNextNode = this->pNextNode->prev;
            }
            return *this; 
        } 
  
        ////////////////////////////////
        /// Postfix -- Operator
        ////////////////////////////////
        DLListIterator operator--(int) 
        { 
            DLListIterator iterator = *this; 
            --*this; 
            return iterator; 
        }

        ////////////////////////////////
        /// Not Equal Operator
        ////////////////////////////////
        bool operator!=(const DLListIterator& iterator) 
        { 
            return this->pNextNode != iterator.pNextNode; 
        }

        ////////////////////////////////
        /// Dereference Operator
        ////////////////////////////////
        T operator*() const
        {
            return this->pNextNode->data;
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