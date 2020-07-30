/////////////////////////////////
/// SLList.hpp
///
/// @brief Declarations and implementation for 
/// singly linked list
/////////////////////////////////
#ifndef SLLIST_HPP
#define SLLIST_HPP

// SYSTEM INCLUDES
#include <iostream> // For std::cout

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "IndexOutOfBoundsException.hpp" // For IndexOutOfBoundsException

////////////////////////////////
/// CLASS NAME: SLList
///
/// @brief Singly List class
/// @param T type stored in list
////////////////////////////////
template <typename T>
class SLList
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

        Node(T data) :
            data(data),
            next(nullptr)
        {}

        Node& operator=(Node const&);
        Node(Node const&);
    } Node;

public:

    ////////////////////////////////
    /// Constructor
    ////////////////////////////////
    SLList() :
        head(nullptr),
        m_length(0)
    {}

    ////////////////////////////////
    /// Deconstructor
    ////////////////////////////////
    ~SLList()
    {
        this->Clear();
    }

    ////////////////////////////////
    /// METHOD NAME: InsertFront
    ///
    /// @param element   Element to be inserted
    ////////////////////////////////
    void InsertFront(T element)
    {
        // If the list is empty, make new element the head
        if (this->head == nullptr)
        {
            this->head = new Node(element);
        }
        else
        {
            // Make this new node the head of the list
            Node* newNode = new Node(element);
            newNode->next = this->head;
            this->head = newNode;
        }

        this->m_length++;
    }

    ////////////////////////////////
    /// METHOD NAME: InsertBack
    ///
    /// @param element   Element to be inserted
    ////////////////////////////////
    void InsertBack(T element)
    {
        // If the list is empty, make new element the head
        if (this->head == nullptr)
        {
            this->head = new Node(element);
        }
        else
        {
            // Traverse to the end of the list
            Node* pCurrentNode = this->head;
            while (pCurrentNode->next != nullptr)
            {
                pCurrentNode = pCurrentNode->next;
            }

            // Append new node to the end
            Node* pNewNode = new Node(element);
            pCurrentNode->next = pNewNode;
        }

        this->m_length++;
    }

    ////////////////////////////////
    /// METHOD NAME: Get
    ///
    /// @param index   Index of element to return
    /// @return Element at given value
    /// @throw IndexOutOfBoundsException
    ////////////////////////////////
    T Get(uint32_t index) const
    {
        return (*this)[index];
    }

    ////////////////////////////////
    /// METHOD NAME: operator[]
    ////////////////////////////////
    T& operator[](uint32_t index)
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

    const T& operator[](uint32_t index) const
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
    /// METHOD NAME: Clear
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
        this->m_length = 0;
    }

    ////////////////////////////////
    /// METHOD NAME: Remove
    ///
    /// @param index    Index to remove
    /// @return Data stored at given index
    /// @throw IndexOutOfBoundsException
    ////////////////////////////////
    T Remove(uint32_t index)
    {
        // Bounds check
        if ((index + 1) > m_length) throw IndexOutOfBoundsException(index);

        Node* pOldNode;
        // Edge case of removing head
        if (index == 0)
        {
            pOldNode = this->head;
            this->head = this->head->next;
        }
        else
        {
            Node* pPreviousNode = nullptr;
            for (Node* pCurrentNode = head;
                pCurrentNode != nullptr;
                pCurrentNode = pCurrentNode->next)
            {
                if (index-- == 0)
                {
                    pOldNode = pCurrentNode;
                    pPreviousNode->next = pCurrentNode->next;
                    break;
                }
                pPreviousNode = pCurrentNode;
            }
        }
        // Delete the node and return it's data;
        T data = pOldNode->data;
        delete pOldNode;
        this->m_length--;
        return data;
    }

    ////////////////////////////////
    /// METHOD NAME: GetLength
    ///
    /// @returns Length of list
    ////////////////////////////////
    uint32_t GetLength(void) const
    {
        return this->m_length;
    }

    ////////////////////////////////
    /// METHOD NAME: PrintList
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
                std::cout << "->";
            }
            else
            {
                std::cout << "\n";
            }
            
        }
    }

    // Forward declaration of iterator class
    class SLListIterator;

    ////////////////////////////////
    /// METHOD NAME: GetBegin
    ////////////////////////////////
    SLListIterator GetBegin() const
    {
        return SLListIterator(this->head);
    }

    ////////////////////////////////
    /// METHOD NAME: GetEnd
    ////////////////////////////////
    SLListIterator GetEnd() const
    {
        return SLListIterator(nullptr);
    }

    ////////////////////////////////
    /// CLASS NAME: SLListIterator
    ///
    /// @brief Class used to iterate
    /// through a linked list
    ////////////////////////////////
    class SLListIterator
    {
    public:
        ////////////////////////////////
        /// Constructor
        ////////////////////////////////
        SLListIterator() :
            pNextNode(head)
        {}

        SLListIterator(Node* startingNode) :
            pNextNode(startingNode)
        {}

        ////////////////////////////////
        /// Assignment Operator
        ////////////////////////////////
        SLListIterator& operator=(Node* pNode)
        { 
            this->pNextNode = pNode; 
            return *this; 
        }

        ////////////////////////////////
        /// Prefix ++ Operator
        //////////////////////////////// 
        SLListIterator& operator++() 
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
        SLListIterator operator++(int) 
        { 
            SLListIterator iterator = *this; 
            ++*this; 
            return iterator; 
        }

        ////////////////////////////////
        /// Not Equal Operator
        ////////////////////////////////
        bool operator!=(const SLListIterator& iterator) 
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
        SLList::Node* pNextNode;
    };

    ////////////////////////////////
    /// Copy Constructer
    ////////////////////////////////
    SLList(SLList const&);

    ////////////////////////////////
    /// Assignment operator
    ////////////////////////////////
    SLList& operator=(SLList const&);

protected:

private:

    /// Pointer to the head of the list
    Node* head;

    /// Number of elements in the list
    uint32_t m_length;

};

#endif