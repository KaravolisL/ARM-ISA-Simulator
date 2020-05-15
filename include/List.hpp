/////////////////////////////////
/// @file List.hpp
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
/// @class List
///
/// @brief Array-backed list class
/// @param T type stored in list
////////////////////////////////
template <typename T>
class List
{
public:

    ////////////////////////////////
    /// Constructor
    ////////////////////////////////
    List(int initialSize = 10) :
        m_length(0),
        m_arraySize(initialSize),
        m_list(new T[initialSize])
    {}

    ////////////////////////////////
    /// Deconstructor
    ////////////////////////////////
    ~List()
    {
        delete[] m_list;
    }

    ////////////////////////////////
    /// Copy Constructer
    ////////////////////////////////
    List(const List& original)
    {
        m_length = original.m_length;
        m_arraySize = original.m_arraySize;
        m_list = new T[m_arraySize];
        // Copy elements into new array
        for (uint32_t i = 0; i < m_length; i++)
        {
            (*this)[i] = original[i];
        }
    }

    ////////////////////////////////
    /// METHOD NAME: Append
    ///
    /// @param element   Element to be inserted
    ////////////////////////////////
    void Append(T element)
    {
        // If the array is filled, resize it
        if (m_arraySize == m_length)
        {
            this->Resize();
        }

        m_list[m_length++] = element;
    }

    ////////////////////////////////
    /// METHOD NAME: Operator[]
    ////////////////////////////////
    T& operator[](const int index)
    {
        if (index >= m_length || index < 0) throw IndexOutOfBoundsException(index);
        return m_list[index];
    }

    const T& operator[](const int index) const
    {
        if (index >= m_length || index < 0) throw IndexOutOfBoundsException(index);
        return m_list[index];
    }

    ////////////////////////////////
    /// METHOD NAME: Insert
    ///
    /// @param[in] index     Index at which to insert element
    /// @param[in] element   Element to be inserted
    /// @throw IndexOutOfBoundsException
    ////////////////////////////////
    void Insert(int index, T element)
    {
        if (index > m_length || index < 0) throw IndexOutOfBoundsException();

        // If the array is filled, resize it
        if (m_arraySize == m_length)
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
    /// METHOD NAME: Clear
    ////////////////////////////////
    void Clear(void) { m_length = 0; }

    ////////////////////////////////
    /// METHOD NAME: Remove
    ///
    /// @brief Removes the element at the given
    /// index and shifts all elements to the left
    ///
    /// @param index    Index to remove
    /// @return Data stored at given index
    /// @throw IndexOutOfBoundsException
    ////////////////////////////////
    T Remove(int index)
    {
        // Bounds check
        if (index > (m_length - 1)) throw IndexOutOfBoundsException();

        T oldValue = m_list[index];

        for (int i = index; i < m_length - 1; i++)
        {
            m_list[i] = m_list[i+1];
        }
        m_length--;
        return oldValue;
    }

    ////////////////////////////////
    /// METHOD NAME: GetLength
    ///
    /// @returns Length of list
    ////////////////////////////////
    int GetLength(void) const
    {
        return this->m_length;
    }

    ////////////////////////////////
    /// METHOD NAME: Sort
    ///
    /// @brief Sorts the list using an
    /// insertion sort algorithm. Allows
    /// the user to specify how elements are compared
    ///
    /// @param compare Function pointer used to compare elements
    ///                Defaulted to use simple < operator
    ////////////////////////////////
    void Sort(bool (*compare)(T&, T&) = [](T& a, T& b) {return a < b;})
    {
        // Iterate n - 1 times
        for (int i = 0; i < m_length - 1; i++)
        {
            // Start with the max being the current element
            uint32_t minsPosition = i;

            // Iterate over the remaining elements
            for (int j = i + 1; j < m_length; j++)
            {
                // If we found a new min, update it
                if (compare(m_list[j], m_list[minsPosition]))
                {
                    minsPosition = j;
                }
            }

            // Swap the current element with the min element
            T currentElement = m_list[i];
            m_list[i] = m_list[minsPosition];
            m_list[minsPosition] = currentElement;
        }
    }

    ////////////////////////////////
    /// METHOD NAME: PrintList
    ////////////////////////////////
    void PrintList(void) const
    {
        for (int i = 0; i < m_length; i++)
        {
            std::cout << m_list[i];
            if (i != m_length - 1)
            {
                std::cout << ", ";
            }
        }
        std::cout << '\n';
    }

protected:

private:

    /// Number of elements in the list
    int m_length;

    /// Size of the array
    int m_arraySize;

    /// Array of elements
    T* m_list;

    ////////////////////////////////
    /// METHOD NAME: Resize
    ///
    /// @brief Resizes the internal array
    /// by a factor of two
    ////////////////////////////////
    void Resize()
    {
        m_arraySize *= 2;
        T* newList = new T[m_arraySize];
        for (int i = 0; i < m_length; i++)
        {
            newList[i] = m_list[i];
        }
        delete[] m_list;
        m_list = newList;
    }

    ////////////////////////////////
    /// Assignment operator
    ///
    /// @note Private to prevent use
    ////////////////////////////////
    List& operator=(List const&);

};

#endif