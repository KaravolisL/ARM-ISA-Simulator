/////////////////////////////////
/// SLList.hpp
///
/// @brief Declarations and implementation for 
/// singly linked list
/////////////////////////////////
#ifndef SLLIST_HPP
#define SLLIST_HPP


template <typename T>
class SLList
{
public:

    ////////////////////////////////
    /// Constructor
    ////////////////////////////////
    SLList() :
        head(nullptr),
        length(0)
    {}


    ////////////////////////////////
    /// FUNCTION NAME: InsertFront
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

        this->length++;
    }

    ////////////////////////////////
    /// FUNCTION NAME: InsertBack
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

        this->length++;
    }

    ////////////////////////////////
    /// FUNCTION NAME: Get
    ///
    /// @param index   Index of element to return
    /// @return Element at given value
    /// @throw Index out of bounds
    ////////////////////////////////
    T Get(int index)
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
        throw "Index out of bounds";
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
        this->length = 0;
    }

    ////////////////////////////////
    /// FUNCTION NAME: Remove
    ///
    /// @param index    Index to remove
    /// @return Data stored at given index
    /// @throw Index out of bounds
    ////////////////////////////////
    T Remove(int index)
    {
        // Bounds check
        if (index > (length - 1)) throw "Index out of bounds";

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
        this->length--;
        return data;
    }

    ////////////////////////////////
    /// FUNCTION NAME: GetLength
    ///
    /// @returns Length of list
    ////////////////////////////////
    int GetLength(void) const
    {
        return this->length;
    }

    ////////////////////////////////
    /// FUNCTION NAME: PrintList
    ////////////////////////////////
    void PrintList(void)
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
        }
    }

protected:



private:

    ////////////////////////////////
    /// DATA TYPE NAME: Node
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
    } Node;

    Node* head;
    int length;

    friend std::ostream& operator<< (std::ostream& stream, const SLList<T>& list)
    {
        for (Node* pCurrentNode = list.head;
             pCurrentNode != nullptr;
             pCurrentNode = pCurrentNode->next)
        {
            stream << pCurrentNode->data;
            if (pCurrentNode->next != nullptr)
            {
                stream << "->";
            }
        }
        return stream;
    }
};

#endif