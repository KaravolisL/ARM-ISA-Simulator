/////////////////////////////////
/// @file HashMapUT.cpp
///
/// @brief Unit Test for HashMap
///
/// @author Luke Karavolis
/////////////////////////////////

// SYSTEM INCLUDES
// (None)

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "UnitTest.hpp"
#include "HashMap.hpp"  // Test class
#include "SLList.hpp"

////////////////////////////////
/// Test Objects
////////////////////////////////
static HashMap<uint32_t> hashMap = HashMap<uint32_t>(5);
static std::string keys[] = {"ABC", "DEF", "GHI", "JKL", "MNOP", "QRS", "TUV", "WX", "YZ"};

////////////////////////////////
/// InsertAndGetTest Function
////////////////////////////////
bool InsertAndGetTest()
{
    for (uint32_t i = 0; i < 9; i++)
    {
        hashMap.Insert(keys[i], i);
    }

    for (uint32_t i = 0; i < 9; i++)
    {
        UNIT_ASSERT(hashMap.Get(keys[i]) == i);
    }

    return true;
}

////////////////////////////////
/// RemoveTest Function
////////////////////////////////
bool RemoveTest()
{
    uint32_t value = hashMap.Remove(keys[4]);
    UNIT_ASSERT(value == 4);

    try
    {
        hashMap.Get(keys[4]);
        UNIT_ASSERT(false);
    }
    catch(const HashMap<uint32_t>::KeyNotFoundException& e)
    {
        std::cerr << e.what() << '\n';
    }

    try
    {
        hashMap.Remove("BADKEY");
        UNIT_ASSERT(false);
    }
    catch(const HashMap<uint32_t>::KeyNotFoundException& e)
    {
        std::cerr << e.what() << '\n';
    }

    hashMap.Insert(keys[4], 4);

    return true;
}

////////////////////////////////
/// ContainsTest Function
////////////////////////////////
bool ContainsTest()
{
    UNIT_ASSERT(hashMap.Contains("ABC"));
    UNIT_ASSERT(!hashMap.Contains("BADKEY"));

    return true;
}

////////////////////////////////
/// GetKeysTest Function
////////////////////////////////
bool GetKeysTest()
{
    SLList<std::string> keyList = hashMap.GetKeys();

    keyList.PrintList();

    for (int i = 0; i < 9; i++)
    {
        bool found = false;
        for (SLList<std::string>::SLListIterator it = keyList.GetBegin();
             it != keyList.GetEnd();  
             it++)
        {
            if (*it == keys[i])
            {
                found = true;
                break;
            }
        }
        UNIT_ASSERT(found);
    }

    return true;
}

////////////////////////////////
/// CopyTest Function
////////////////////////////////
bool CopyTest()
{
    HashMap<uint32_t> otherHashMap = hashMap;

    for (int i = 0; i < 9; i++)
    {
        UNIT_ASSERT(otherHashMap.Get(keys[i]) == hashMap.Get(keys[i]));
    }

    return true;
}

////////////////////////////////
/// Main Function
////////////////////////////////
bool HashMapUT()
{
    UnitTest unitTest("Hash Map Unit Test");

    unitTest.AddSubTest(InsertAndGetTest);
    unitTest.AddSubTest(RemoveTest);
    unitTest.AddSubTest(ContainsTest);
    unitTest.AddSubTest(GetKeysTest);
    unitTest.AddSubTest(CopyTest);

    return unitTest.Run();
}