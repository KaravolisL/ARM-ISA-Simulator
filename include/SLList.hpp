/////////////////////////////////
/// @file SLList.hpp
///
/// @brief Declarations and implementation for 
/// singly linked list
///
/// @author Luke Karavolis
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
/// @class SLList
///
/// @brief Singly List class
/// @tparam T type stored in list
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
        /// Data held by node
        T data;

        /// Pointer to the next node
        Node* next;

        /////////////////////////////////////
        /// @brief Constructs a new Node object
        /// 
        /// @param[in] data Data to be held by node
        /////////////////////////////////////
        Node(T data) :
            data(data),
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
    /// @brief Constructs a new SLList object
    /////////////////////////////////////
    SLList() :
        head(nullptr),
        m_length(0)
    {}

    /////////////////////////////////////
    /// @brief Destroys the SLList object
    /////////////////////////////////////
    ~SLList()
    {
        Clear();
    }

    ////////////////////////////////
    /// @brief Inserts an element at the beginning of the list
    ///
    /// @param element   Element to be inserted
    ////////////////////////////////
    void InsertFront(T element)
    {
        // If the list is empty, make new element the head
        if (head == nullptr)
        {
            head = new Node(element);
        }
        else
        {
            // Make this new node the head of the list
            Node* newNode = new Node(element);
            newNode->next = head;
            head = newNode;
        }

        m_length++;
    }

    ////////////////////////////////
    /// @brief Insert an element at the end of the list
    ///
    /// @param element   Element to be inserted
    ////////////////////////////////
    void InsertBack(T element)
    {
        // If the list is empty, make new element the head
        if (head == nullptr)
        {
            head = new Node(element);
        }
        else
        {
            // Traverse to the end of the list
            Node* pCurrentNode = head;
            while (pCurrentNode->next != nullptr)
            {
                pCurrentNode = pCurrentNode->next;
            }

            // Append new node to the end
            Node* pNewNode = new Node(element);
            pCurrentNode->next = pNewNode;
        }

        m_length++;
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
        return (*this)[index];
    }

    /////////////////////////////////////
    /// @copybrief Get()
    /// 
    /// @param[in] index    Index of element to get
    /// @return Reference to element
    /// @throw IndexOutOfBoundsException
    /////////////////////////////////////
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

    /////////////////////////////////////
    /// @copydoc T& operator[](uint32_t)  
    /////////////////////////////////////
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
        m_length = 0;
    }

    ////////////////////////////////
    /// @brief Removes a given item from the list
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
            pOldNode = head;
            head = head->next;
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
        m_length--;
        return data;
    }

    /////////////////////////////////////
    /// @brief Gets the Length member
    /// 
    /// @return Length of the list
    /////////////////////////////////////
    uint32_t GetLength(void) const
    {
        return m_length;
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
    /// @brief Obtains an iterator from the beginning
    ///
    /// @return SLListIterator from beginning
    ////////////////////////////////
    SLListIterator GetBegin() const
    {
        return SLListIterator(head);
    }

    ////////////////////////////////
    /// @brief Obtains an iterator from the end
    ///
    /// @return SLListIterator from end
    ////////////////////////////////
    SLListIterator GetEnd() const
    {
        return SLListIterator(nullptr);
    }

    ////////////////////////////////
    /// @class SLListIterator
    ///
    /// @brief Class used to iterate
    /// through a linked list
    ////////////////////////////////
    class SLListIterator
    {
    public:
        /////////////////////////////////////
        /// @brief Constructs a new SLListIterator object
        /////////////////////////////////////
        SLListIterator() :
            pNextNode(nullptr)
        {}

        /////////////////////////////////////
        /// @brief Constructs a new SLListIterator object
        /// 
        /// @param[in] startingNode Node at which to begin
        /////////////////////////////////////
        SLListIterator(Node* startingNode) :
            pNextNode(startingNode)
        {}

        ////////////////////////////////
        /// @brief Assignment operator
        ////////////////////////////////
        SLListIterator& operator=(Node* pNode)
        { 
            pNextNode = pNode; 
            return *this; 
        }

        ////////////////////////////////
        /// @brief Prefix ++ Operator
        //////////////////////////////// 
        SLListIterator& operator++() 
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
        SLListIterator operator++(int) 
        { 
            SLListIterator iterator = *this; 
            ++*this; 
            return iterator; 
        }

        ////////////////////////////////
        /// @brief Not Equal Operator
        ////////////////////////////////
        bool operator!=(const SLListIterator& iterator) 
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
        SLList::Node* pNextNode;
    };

    ////////////////////////////////
    /// @brief Copy Constructer
    ////////////////////////////////
    SLList(SLList const&);

    ////////////////////////////////
    /// @brief Assignment operator
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