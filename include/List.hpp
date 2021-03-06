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
#include <cstring>
#include <sstream> // For std::stringstream

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "IndexOutOfBoundsException.hpp" // For IndexOutOfBoundsException

////////////////////////////////
/// @class List
///
/// @brief Array-backed list class
/// @tparam T type stored in list
////////////////////////////////
template <typename T>
class List
{
public:

    /////////////////////////////////////
    /// @brief Constructs a new List object
    ///
    /// @param[in] initialSize Initial size of list
    /////////////////////////////////////
    List(uint32_t initialSize = 10) :
        m_length(0),
        m_arraySize(initialSize),
        m_list(new T[initialSize])
    {}

    /////////////////////////////////////
    /// @brief Destroys the List object
    /////////////////////////////////////
    ~List()
    {
        delete[] m_list;
    }

    ////////////////////////////////
    /// @brief Copy Constructer
    ////////////////////////////////
    List(const List& rOther) :
        m_length(rOther.m_length),
        m_arraySize(rOther.m_arraySize),
        m_list(new T[rOther.m_arraySize])
    {
        std::memcpy(m_list, rOther.m_list, (sizeof(T) * m_length));
    }

    ////////////////////////////////
    /// @brief Appends an element to the end of the list
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
    /// @brief Operator[]
    ////////////////////////////////
    T& operator[](const uint32_t index)
    {
        if (index >= m_length) throw IndexOutOfBoundsException(index);
        return m_list[index];
    }

    ////////////////////////////////
    /// @brief Operator[]
    ////////////////////////////////
    const T& operator[](const uint32_t index) const
    {
        if (index >= m_length) throw IndexOutOfBoundsException(index);
        return m_list[index];
    }

    ////////////////////////////////
    /// @brief Inserts an element at a given index
    ///
    /// @param[in] index     Index at which to insert element
    /// @param[in] element   Element to be inserted
    /// @throw IndexOutOfBoundsException
    ////////////////////////////////
    void Insert(uint32_t index, T element)
    {
        if (index > m_length) throw IndexOutOfBoundsException();

        // If the array is filled, resize it
        if (m_arraySize == m_length)
        {
            this->Resize();
        }

        // Shift all element to the right
        for (int32_t i = m_length - 1; i >= static_cast<int32_t>(index); i--)
        {
            m_list[i+1] = m_list[i];
        }
        m_list[index] = element;
        this->m_length++;
    }

    ////////////////////////////////
    /// @brief Clears the list
    ////////////////////////////////
    void Clear(void) { m_length = 0; }

    ////////////////////////////////
    /// @brief Removes the element at the given
    /// index and shifts all elements to the left
    ///
    /// @param index    Index to remove
    /// @return Data stored at given index
    /// @throw IndexOutOfBoundsException
    ////////////////////////////////
    T Remove(uint32_t index)
    {
        // Bounds check
        if (index > (m_length - 1)) throw IndexOutOfBoundsException();

        T oldValue = m_list[index];

        for (uint32_t i = index; i < m_length - 1; i++)
        {
            m_list[i] = m_list[i+1];
        }
        m_length--;
        return oldValue;
    }

    ////////////////////////////////
    /// @brief Gets the length member
    ///
    /// @returns Length of list
    ////////////////////////////////
    uint32_t GetLength(void) const
    {
        return this->m_length;
    }

    ////////////////////////////////
    /// @brief Determines whether the list is empty
    ///
    /// @returns Whether the list is empty
    ////////////////////////////////
    bool IsEmpty(void) const
    {
        return (m_length == 0);
    }

    ////////////////////////////////
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
        for (uint32_t i = 0; i < m_length - 1; i++)
        {
            // Start with the max being the current element
            uint32_t minsPosition = i;

            // Iterate over the remaining elements
            for (uint32_t j = i + 1; j < m_length; j++)
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
    /// @brief Converts the list to a string object
    ////////////////////////////////
    std::string ToString(void) const
    {
        std::stringstream stream;
        for (uint32_t i = 0; i < m_length; i++)
        {
            stream << static_cast<uint32_t>(m_list[i]);
            if (i != m_length - 1)
            {
                stream << ", ";
            }
        }
        return stream.str();
    }

    ////////////////////////////////
    ///@brief Prints the list to std::cout
    ////////////////////////////////
    void PrintList(void) const
    {
        for (uint32_t i = 0; i < m_length; i++)
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
    uint32_t m_length;

    /// Size of the array
    uint32_t m_arraySize;

    /// Array of elements
    T* m_list;

    ////////////////////////////////
    /// @brief Resizes the internal array
    /// by a factor of two
    ////////////////////////////////
    void Resize()
    {
        m_arraySize *= 2;
        T* newList = new T[m_arraySize];
        for (uint32_t i = 0; i < m_length; i++)
        {
            newList[i] = m_list[i];
        }
        delete[] m_list;
        m_list = newList;
    }

    ////////////////////////////////
    /// @brief Assignment operator
    ///
    /// @note Private to prevent use
    ////////////////////////////////
    List& operator=(List const&);

};

#endif