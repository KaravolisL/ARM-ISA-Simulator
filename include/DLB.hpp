/////////////////////////////////
/// @file DLB.hpp
///
/// @brief Declaration and Implementation
/// for DLB data structure
///
/// @details Trie data structure backed
/// by linked lists
///
/// @author Luke Karavolis
/////////////////////////////////
#ifndef DLB_HPP
#define DLB_HPP

// SYSTEM INCLUDES
#include <string>

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
// (None)

// FORWARD DECLARATIONS
// (None)

////////////////////////////////
/// @class DLB
///
/// @brief Data structure associating
/// a string key to a value
////////////////////////////////
template <typename T>
class DLB
{
public:

    ////////////////////////////////
    /// Constructor
    ////////////////////////////////
    DLB() :
        m_pRoot(nullptr)
    {}

    ////////////////////////////////
    /// METHOD NAME: Insert
    ///
    /// @brief Adds a key:value pair
    /// to the trie
    ///
    /// @param key      Key to be added
    /// @param value    Value to be associated with key
    /// @return Value previously associated with given key
    /// @retval nullptr     - No value was stored previously
    ////////////////////////////////
    void Insert(const std::string& key, const T value)
    {
        // Start at the root
        DLBNode* pCurrentNode = m_pRoot;

        // For first letter...
        if (m_pRoot == nullptr) {
            // If this is the first word to be added, init the root
            m_pRoot = new DLBNode(key[0]);
            pCurrentNode = m_pRoot;
        } else {
            // Else find or add a node for the letter
            pCurrentNode = FindOrAddNode(m_pRoot, key[0]);
        }

        // For every additional letter in word...
        for (std::size_t i = 1; i < key.length(); i++) {
            char c = key[i];

            if (pCurrentNode->pChild == nullptr) {
                // If there is no next level, start one
                pCurrentNode->pChild = new DLBNode(c);
                pCurrentNode = pCurrentNode->pChild;
            } else {
                // Find or add a node on the next level
                pCurrentNode = FindOrAddNode(pCurrentNode->pChild, c);
            }
        }

        // Store the value in the terminating node
        pCurrentNode->value = value;
    }

    ////////////////////////////////
    /// METHOD NAME: Update
    ///
    /// @brief Adds a key:value pair
    /// to the trie
    ///
    /// @param key      Key to be added
    /// @param value    Value to be associated with key
    /// @return Value previously associated with given key
    ////////////////////////////////
    T Update(const std::string& key, T value)
    {
        // TODO
        throw "Not Implemented";
    }

    ////////////////////////////////
    /// METHOD NAME: Get
    ///
    /// @brief Retrieves the value associated
    /// with the given key
    ///
    /// @param key      Key to be searched
    /// @return Value associated with given key
    /// @throw KeyNotFoundException
    ////////////////////////////////
    T Get(const std::string& key)
    {
        DLBNode* pCurrentNode = m_pRoot;
        for (std::size_t i = 0; i < key.length(); i++)
        {
            char c = key[i];
            // For every node in list...
            while (pCurrentNode != nullptr)
            {
                if (pCurrentNode->character == c)
                {
                    break;
                }
                pCurrentNode = pCurrentNode->pRightSib;
            }

            // If we didn't find the character, the key isn't in the trie
            if (pCurrentNode == nullptr)
            {
                throw KeyNotFoundException();
            }

            // Go to the next linked list if we aren't at the end
            if (i < key.length() - 1)
            {
                pCurrentNode = pCurrentNode->pChild;
            }
        }

        // return the current node's value
        return pCurrentNode->value;
    }

    ////////////////////////////////
    /// METHOD NAME: Contains
    ///
    /// @brief Determines whether a key
    /// was added to the trie
    ///
    /// @param key      Key to be searched
    /// @return Whether a value exists for the key
    /// @retval true     - A value exists
    /// @retval false    - No value exists
    ////////////////////////////////
    bool Contains(const std::string& key)
    {
        try
        {
            this->Get(key);
            return true;
        }
        catch (const KeyNotFoundException& e)
        {
            return false;
        }
    }

protected:


private:

    ////////////////////////////////
    /// @class DLBNode
    ///
    /// @brief Data type used to store
    /// data in dlb trie
    ////////////////////////////////
    class DLBNode
    {
    public:
        char character;
        T value;
        DLBNode* pRightSib;
        DLBNode* pChild;

        DLBNode(char character) :
            character(character),
            value(),
            pRightSib(nullptr),
            pChild(nullptr)
        {}
    };

    /// Root of the DLB trie
    DLBNode* m_pRoot;

    ////////////////////////////////
    /// @exception KeyNotFoundException
    ///
    /// @brief Exception thrown when a key
    /// is not found in the trie
    ////////////////////////////////
    struct KeyNotFoundException : public std::exception
    {
        const char* what() const throw()
        {
            return "Key Not Found Exception";
        }
    };

    ////////////////////////////////
    /// METHOD NAME: FindOrAddNode
    ///
    /// @brief Finds a node given a starting node.
    /// Adds a new node if one isn't found
    ///
    /// @param startingNode     Node at which to start looking
    /// @param c                Character node should have
    /// @return Pointer to node that was found/added
    ////////////////////////////////
    DLBNode* FindOrAddNode(DLBNode* pStartingNode, char c) 
    {    
        DLBNode* pCurrentNode;
        DLBNode* pLastNode = nullptr;
        // For every node in list...
        for (pCurrentNode = pStartingNode;
             pCurrentNode != nullptr;
             pCurrentNode = pCurrentNode->pRightSib)
        {
            if (pCurrentNode->character == c) {
                // Existing node was found, so return it
                return pCurrentNode;
            }
            pLastNode = pCurrentNode;
        }

        // No node was found so add one to the end of the list
        pLastNode->pRightSib = new DLBNode(c);
        return pLastNode->pRightSib;
    }

};

#endif