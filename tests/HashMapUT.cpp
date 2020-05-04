/////////////////////////////////
/// @file HashMapUT.cpp
///
/// @brief Unit Test for HashMap
///
/// @author Luke Karavolis
/////////////////////////////////

// SYSTEM INCLUDES
#include <assert.h>
#include <iostream>

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "HashMap.hpp"  // Test class
#include "SLList.hpp"

////////////////////////////////
/// Test Objects
////////////////////////////////
HashMap<uint32_t> hashMap = HashMap<uint32_t>(5);
std::string keys[] = {"ABC", "DEF", "GHI", "JKL", "MNOP", "QRS", "TUV", "WX", "YZ"};

////////////////////////////////
/// Setup Function
////////////////////////////////
void setup()
{

}

////////////////////////////////
/// InsertAndGetTest Function
////////////////////////////////
void InsertAndGetTest()
{
    for (uint32_t i = 0; i < 9; i++)
    {
        hashMap.Insert(keys[i], i);
    }

    for (uint32_t i = 0; i < 9; i++)
    {
        assert(hashMap.Get(keys[i]) == i);
    }
}

////////////////////////////////
/// RemoveTest Function
////////////////////////////////
void RemoveTest()
{
    uint32_t value = hashMap.Remove(keys[4]);
    assert(value == 4);

    try
    {
        hashMap.Get(keys[4]);
        assert(false);
    }
    catch(const HashMap<uint32_t>::KeyNotFoundException& e)
    {
        std::cerr << e.what() << '\n';
    }

    try
    {
        hashMap.Remove("BADKEY");
        assert(false);
    }
    catch(const HashMap<uint32_t>::KeyNotFoundException& e)
    {
        std::cerr << e.what() << '\n';
    }

    hashMap.Insert(keys[4], 4);
}

////////////////////////////////
/// ContainsTest Function
////////////////////////////////
void ContainsTest()
{
    assert(hashMap.Contains("ABC"));
    assert(!hashMap.Contains("BADKEY"));
}

////////////////////////////////
/// GetKeysTest Function
////////////////////////////////
void GetKeysTest()
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
        assert(found);
    }

}

////////////////////////////////
/// Teardown Function
////////////////////////////////
void teardown()
{

}

////////////////////////////////
/// Main Function
////////////////////////////////
int main(int argc, char* argv[])
{
    setup();

    InsertAndGetTest();
    RemoveTest();
    ContainsTest();
    GetKeysTest();

    teardown();

    std::cout << "HashMap Unit Test Complete: SUCCESS";
    return 0;
}