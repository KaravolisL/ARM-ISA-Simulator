/////////////////////////////////
/// @file MemoryManager.hpp
///
/// @brief Declarations for MemoryManager class
///
/// @author Luke Karavolis
/////////////////////////////////
#ifndef MEMORY_MANAGER_HPP
#define MEMORY_MANAGER_HPP

// SYSTEM INCLUDES
#include <fstream>
#include <exception>

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "Assert.hpp" // For ASSERT
#include "Logger.hpp" // For LOG_MEMORY

// FORWARD DECLARATIONS
// (None)

namespace Memory
{

////////////////////////////////
/// @class MemoryManager
///
/// @brief Class responsible for managing
/// memory operations
////////////////////////////////
class MemoryManager
{
public:

    /////////////////////////////////////
    /// @brief Get the singleton instance
    /// 
    /// @return singleton instance
    /////////////////////////////////////
    static MemoryManager& GetInstance()
    {
        /// Singleton instance
        static MemoryManager* pInstance = new MemoryManager();
        return *pInstance;
    }

    /////////////////////////////////////
    /// @brief Closes the memory file
    /////////////////////////////////////
    void Close()
    {
        m_memoryFile.close();
    }

    ////////////////////////////////
    /// @brief Initializes the memory file
    /// by writing zeros.
    ////////////////////////////////
    void Initialize();

    ////////////////////////////////
    /// @brief Writes data to the given address
    ///
    /// @tparam T       Size of data to write
    /// @param[in] address  Address to which to read
    /// @param[in] data     Data which to write
    ////////////////////////////////
    template <typename T>
    void Write(const uint32_t address, T data)
    {
        LOG_MEMORY("Writing %d to the address 0x%x", data, address);

        GoToAddress(address);
        m_memoryFile.write(reinterpret_cast<char*>(&data), sizeof(T));

        #ifdef BUILD_UNIT_TEST
        m_memoryFile.flush();
        #endif
    }

    ////////////////////////////////
    /// @brief Reads data from the given
    /// address and returns it
    ///
    /// @param[in] address  Address to which to read
    /// @tparam T       Size of data to read
    /// @return Data at given address
    ////////////////////////////////
    template <typename T>
    T Read(const uint32_t address)
    {
        GoToAddress(address);

        uint32_t word;
        m_memoryFile.read(reinterpret_cast<char*>(&word), sizeof(uint32_t));

        T data = static_cast<T>(word);

        LOG_MEMORY("Read %d from the address 0x%x", static_cast<uint32_t>(data), address);

        return data;
    }

    ////////////////////////////////
    /// @struct MemoryException
    ////////////////////////////////
    struct MemoryException : public std::exception
    {
        /////////////////////////////////////
        /// @brief Returns the exception message
        /// 
        /// @return Exception message 
        /////////////////////////////////////
        const char* what() const throw()
        {
            return "Memory Exception";
        }
    };

protected:

private:

    /// Name of the memory file
    const char* MEMORY_FILE_NAME = "Memory.bin";

    /// File input stream
    std::fstream m_memoryFile;

    ////////////////////////////////
    /// @brief Seeks the file stream
    /// to a given memory address
    ///
    /// @param[in] address  Address to which to go
    ////////////////////////////////
    void GoToAddress(const uint32_t address);

    ////////////////////////////////
    /// @brief Validates that the given
    /// address is within the bounds
    ///
    /// @param[in] address  Address to validate
    /// @throw MemoryException
    ////////////////////////////////
    void ValidateAddress(const uint32_t address) const;

    ////////////////////////////////
    /// @brief Reverse the bytes in a given
    /// integer
    ///
    /// @param[in] n Integer to reverse
    /// @return Reversed integer
    ////////////////////////////////
    template <class T>
    uint32_t ReverseBytes(T n) const
    {
        uint8_t numberOfBytes = 4;
        uint32_t reversedInteger = 0;
        uint8_t byteMask = 0xFF;

        reversedInteger |= (n & byteMask);

        for (uint8_t i = 0; i < (numberOfBytes - 1); i++)
        {
            reversedInteger <<= 8;
            n >>= 8;
            reversedInteger |= (n & byteMask);
        }

        return reversedInteger;
    }

    /////////////////////////////////////
    /// @brief Construct a new Memory Manager object
    ///
    /// @note Private to ensure singleton object
    /////////////////////////////////////
    MemoryManager() :
        m_memoryFile(std::fstream(MEMORY_FILE_NAME, std::fstream::in    |
                                                    std::fstream::out   |
                                                    std::fstream::trunc |
                                                    std::fstream::binary))
    {
        ASSERT(m_memoryFile.is_open(), "File did not open");
    }

    /////////////////////////////////////
    /// @brief Copy Constructor
    /////////////////////////////////////
    MemoryManager(MemoryManager const&);

    /////////////////////////////////////
    /// @brief Assignment Operator
    /////////////////////////////////////
    MemoryManager& operator=(MemoryManager const&);

};

} // Memory

#endif