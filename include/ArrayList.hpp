/////////////////////////////////
/// @file ArrayList.hpp
///
/// @brief Declarations and implementation for 
/// array backed list
///
/// @author Luke Karavolis
/////////////////////////////////
#ifndef ARRAY_LIST_HPP
#define ARRAY_LIST_HPP

// SYSTEM INCLUDES
#include <iostream> // For std::cout

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "IndexOutOfBoundsException.hpp" // For IndexOutOfBoundsException

////////////////////////////////
/// @class ArrayList
///
/// @brief Array-backed list class
/// @param T type stored in list
////////////////////////////////
template <typename T>
class ArrayList
{
public:

    ////////////////////////////////
    /// Constructor
    ////////////////////////////////
    ArrayList(int initialSize = 10) :
        m_length(0),
        m_list(new T[initialSize])
    {}

    ////////////////////////////////
    /// FUNCTION NAME: Append
    ///
    /// @param element   Element to be inserted
    ////////////////////////////////
    void Append(T element)
    {
        // If the array is filled, resize it
        if (this->GetSize() == m_length)
        {
            this->Resize();
        }

        m_list[m_length++] = element;
    }

    ////////////////////////////////
    /// FUNCTION NAME: operator[]
    ///
    /// @param index   Index of element to return
    /// @return Element at given value
    /// @throw IndexOutOfBoundsException
    ////////////////////////////////
    T& operator[](int index) const
    {
        if (index >= m_length || index < 0) throw IndexOutOfBoundsException(index);
        
        return m_list[index];
    }

    ////////////////////////////////
    /// FUNCTION NAME: Insert
    ///
    /// @param[in] index     Index at which to insert element
    /// @param[in] element   Element to be inserted
    /// @throw IndexOutOfBoundsException
    ////////////////////////////////
    void Insert(int index, T element)
    {
        if (index > m_length || index < 0) throw IndexOutOfBoundsException(index);

        // If the array is filled, resize it
        if (this->GetSize() == m_length)
        {
            this->Resize();
        }

        // Shift all element to the right
        for (int i = m_length - 1; i >= index; i--)
        {
            m_list[i+1] = m_list[i];
        }
        m_list[index] = element;
        this->m_length++;
    }

    ////////////////////////////////
    /// FUNCTION NAME: Clear
    ////////////////////////////////
    void Clear(void) { m_length = 0; }

    ////////////////////////////////
    /// FUNCTION NAME: Remove
    ///
    /// @brief Removes the element at the given
    /// index and replaces it with the element at
    /// the end of the list
    ///
    /// @param index    Index to remove
    /// @return Data stored at given index
    /// @throw IndexOutOfBoundsException
    ////////////////////////////////
    T Remove(int index)
    {
        // Bounds check
        if (index > (m_length - 1)) throw IndexOutOfBoundsException(index);

        T oldValue = m_list[index];

        if (index != --m_length)
        {
            m_list[index] = m_list[m_length];
        }
        return oldValue;
    }

    ////////////////////////////////
    /// FUNCTION NAME: GetLength
    ///
    /// @returns Length of list
    ////////////////////////////////
    int GetLength(void) const
    {
        return this->m_length;
    }

    ////////////////////////////////
    /// FUNCTION NAME: PrintList
    ////////////////////////////////
    void PrintList(void) const
    {
        for (int i = 0; i < m_length - 1; i++)
        {
            std::cout << m_list[i] << ", ";
        }
        std::cout << m_list[m_length - 1] << '\n';
    }

protected:

private:

    /// Number of elements in the list
    int m_length;

    /// Array of elements
    T* m_list;

    ////////////////////////////////
    /// FUNCTION NAME: GetSize
    ///
    /// @return Size of the array backing the list
    ////////////////////////////////
    int GetSize() { return (*(&m_list + 1) - m_list); }

    ////////////////////////////////
    /// FUNCTION NAME: Resize
    ///
    /// @brief Resizes the internal array
    /// by a factor of two
    ////////////////////////////////
    void Resize()
    {
        T* newList = new T[GetSize() * 2];
        for (int i = 0; i < m_length; i++)
        {
            newList[i] = m_list[i];
        }
        delete[] m_list;
        m_list = newList;
    }

};

#endif