/////////////////////////////////
/// @file HashMap.hpp
///
/// @brief Declaration and implementation
/// of a hash map data structure
///
/// @author Luke Karavolis
/////////////////////////////////
#ifndef HASH_MAP_HPP
#define HASH_MAP_HPP

// SYSTEM INCLUDES
#include <assert.h>
#include <string>
#include <cmath>

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "SLList.hpp" // For SLList

////////////////////////////////
/// @class HashMap
///
/// @brief HashMap data structure
/// @param T Type of values stored
////////////////////////////////
template <typename T>
class HashMap
{
public:
    ////////////////////////////////
    /// Constructor
    ////////////////////////////////
    HashMap(uint32_t size = 11) :
        m_pKeys(new std::string[size]),
        m_pValues(new T[size]),
        m_numElements(0),
        m_size(size)
    {}

    ////////////////////////////////
    /// Deconstructor
    ////////////////////////////////
    ~HashMap()
    {
        delete[] m_pKeys;
        delete[] m_pValues;
    }

    ////////////////////////////////
    /// Copy Constructer
    ////////////////////////////////
    HashMap(const HashMap& rOther) :
        m_pKeys(new std::string[rOther.m_size]),
        m_pValues(new T[rOther.m_size]),
        m_numElements(rOther.m_numElements),
        m_size(rOther.m_size)
    {
        for (uint32_t i = 0; i < m_size; i++)
        {
            m_pKeys[i] = rOther.m_pKeys[i];
            m_pValues[i] = rOther.m_pValues[i];
        }
    }

    ////////////////////////////////
    /// METHOD NAME: Insert
    ///
    /// @param key      Key at which to insert
    /// @param value    Value to associate with key
    ////////////////////////////////
    void Insert(std::string key, T value)
    {
        if (m_numElements == m_size)
        {
            this->Rehash();
        }

        uint32_t hash = CalculateHash(key);
        if (m_pKeys[hash] == "" || m_pKeys[hash] == key)
        {
            m_pKeys[hash] = key;
            m_pValues[hash] = value;
        }
        else
        {
            // Loop around table until an empty spot is found
            uint32_t i;
            for (i = hash + 1; i != hash; i = (i + 1) % m_size)
            {
                if (m_pKeys[i] == "")
                {
                    m_pKeys[i] = key;
                    m_pValues[i] = value;
                    break;
                }
            }
            assert(m_pKeys[i] == key);
            assert(m_pValues[i] == value);
        }
        m_numElements++;
    }

    ////////////////////////////////
    /// METHOD NAME: Get
    ///
    /// @param rKey      Key whose value to retrieve
    /// @return Values associated with key
    /// @throw KeyNotFoundException
    ////////////////////////////////
    T Get(const std::string& rKey) const
    {
        uint32_t hash = CalculateHash(rKey);
        if (m_pKeys[hash] == rKey)
        {
            return m_pValues[hash];
        }
        else
        {
            // Loop around table until the key is found
            for (uint32_t i = hash + 1; i != hash; i = (i + 1) % m_size)
            {
                if (m_pKeys[i] == rKey)
                {
                    return m_pValues[i];
                }
            }
        }
        throw KeyNotFoundException();
    }

    ////////////////////////////////
    /// METHOD NAME: Remove
    ///
    /// @param rKey      Key to remove
    /// @return Value associated with key that was removed
    /// @throw KeyNotFoundException
    ////////////////////////////////
    T Remove(const std::string& rKey)
    {
        m_numElements--;
        uint32_t hash = CalculateHash(rKey);
        if (m_pKeys[hash] == rKey)
        {
            m_pKeys[hash] = "";
            return m_pValues[hash];
        }
        else
        {
            // Loop around table until the key is found
            for (uint32_t i = hash + 1; i != hash; i = (i + 1) % m_size)
            {
                if (m_pKeys[i] == rKey)
                {
                    m_pKeys[i] = "";
                    return m_pValues[i];
                }
            }
        }
        throw KeyNotFoundException();
    }

    ////////////////////////////////
    /// METHOD NAME: Contains
    ///
    /// @param rKey      Key to look for
    /// @return Whether key exists in the hash
    /// @retval true    - Key is in hash
    /// @retval false   - Key is not in hash
    ////////////////////////////////
    bool Contains(const std::string& rKey) const
    {
        try
        {
            Get(rKey);
            return true;
        }
        catch(const KeyNotFoundException& e)
        {
            return false;
        }
    }

    ////////////////////////////////
    /// METHOD NAME: GetKeys
    ///
    /// @return A linked list of the keys in the hash map
    ////////////////////////////////
    SLList<std::string> GetKeys() const
    {
        SLList<std::string> keysList = SLList<std::string>();
        for (uint32_t i = 0; i < m_size; i++)
        {
            if (m_pKeys[i] != "")
            {
                keysList.InsertBack(m_pKeys[i]);
            }
        }
        return keysList;
    }

    ////////////////////////////////
    /// @exception KeyNotFoundException
    ///
    /// @brief Exception thrown when a key
    /// is not found in the hash map
    ////////////////////////////////
    struct KeyNotFoundException : public std::exception
    {
        const char* what() const throw()
        {
            return "Key Not Found Exception";
        }
    };

protected:


private:

    /// Array to store keys
    std::string* m_pKeys;

    /// Array to store values
    T* m_pValues;

    /// Number of elements that were added
    uint32_t m_numElements;

    /// Size of HashMap
    uint32_t m_size;

    ////////////////////////////////
    /// METHOD NAME: CalculateHash
    ///
    /// @brief Calculates the index of the string
    /// using Horner's method
    ///
    /// @param rStr     String to be hashed
    ////////////////////////////////
    uint32_t CalculateHash(const std::string& rStr) const
    {
        uint64_t hash = 0;
        for (int i = rStr.length() - 1; i >= 0; i--)
        {
            char character = rStr[rStr.length() - i - 1];
            hash += static_cast<uint8_t>(character) * (pow(256, i));
        }
        return hash % m_size;
    }

    ////////////////////////////////
    /// METHOD NAME: Rehash
    ///
    /// @brief Increases the size of the hash
    /// map to the next prime number. Subsequently,
    /// all key:value pairs will be rehashed
    ////////////////////////////////
    void Rehash()
    {
        // Resize to at least twice the current
        m_size = NextPrime(m_size * 2);

        std::string* pNewKeys = new std::string[m_size];
        T* pNewValues = new T[m_size];

        // For every element, rehash into the new arrays
        for (uint32_t i = 0; i < m_numElements; i++)
        {
            uint32_t hash = CalculateHash(m_pKeys[i]);
            if (pNewKeys[hash] == "")
            {
                pNewKeys[hash] = m_pKeys[i];
                pNewValues[hash] = m_pValues[i];
            }
            else
            {
                for (uint32_t i = hash + 1; i < hash; i = (i + 1) % m_size)
                {
                    if (pNewKeys[i] == "")
                    {
                        pNewKeys[hash] = m_pKeys[i];
                        pNewValues[hash] = m_pValues[i];
                    }
                }
            }
        }

        // Delete old arrays
        delete[] m_pKeys;
        delete[] m_pValues;

        // Update pointers to the new arrays
        m_pKeys = pNewKeys;
        m_pValues = pNewValues;
    }

    ////////////////////////////////
    /// METHOD NAME: NextPrime
    ///
    /// @brief Helper method to determine the
    /// next prime number after the given number
    ///
    /// @param[in] N    Starting point
    /// @return The next prime number greater than n
    ////////////////////////////////
    int NextPrime(const int N) const
    { 
        // Base case 
        if (N <= 1) return 2; 
    
        int prime = N; 
        bool found = false; 
    
        // Loop continuously until IsPrime returns 
        // true for a number greater than n 
        while (!found)
        { 
            prime++; 
    
            if (IsPrime(prime))
            {
                found = true;
            }
        } 
    
        return prime; 
    }

    ////////////////////////////////
    /// METHOD NAME: IsPrime
    ///
    /// @brief Helper method to determine if
    /// a number is prime or not
    ///
    /// @param[in] n    Number to investigate
    /// @return Whether number is prime
    /// @retval true    - Number is prime
    /// @retval false   - Number is not prime
    ////////////////////////////////
    bool IsPrime(const int n) const
    {
        // Corner cases
        if (n <= 1)  return false;
        if (n <= 3)  return true;

        // This is checked so that we can skip
        // middle five numbers in below loop
        if (n % 2 == 0 || n % 3 == 0) return false;

        for (int i = 5; i * i <= n; i = i + 6)
        {
            if (n % i == 0 || n % (i + 2) == 0)
            {
                return false;
            }
        }
        return true;
    }

    ////////////////////////////////
    /// Assignment operator
    ///
    /// @note Disallow assignment operator
    ////////////////////////////////
    HashMap& operator=(HashMap const&);
};


#endif