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
#include <catch2/catch.hpp>
#include "HashMap.hpp"  // Test class
#include "SLList.hpp"

TEST_CASE("HashMap Basic Functionality", "[data_structure]")
{
    std::string keys[] = {"ABC", "DEF", "GHI", "JKL", "MNOP", "QRS", "TUV", "WX", "YZ"};
    HashMap<uint32_t> hashMap = HashMap<uint32_t>(5);

    for (uint32_t i = 0; i < 9; i++)
    {
        hashMap.Insert(keys[i], i);
    }

    SECTION("Get")
    {
        for (uint32_t i = 0; i < 9; i++)
        {
            REQUIRE(hashMap.Get(keys[i]) == i);
        }
    }

    SECTION("Remove")
    {
        uint32_t value = hashMap.Remove(keys[4]);
        REQUIRE(value == 4);

        REQUIRE_THROWS_AS(hashMap.Get(keys[4]), HashMap<uint32_t>::KeyNotFoundException);
        REQUIRE_THROWS_AS(hashMap.Remove("BADKEY"), HashMap<uint32_t>::KeyNotFoundException);
    }

    SECTION("Contains")
    {
        REQUIRE(hashMap.Contains("ABC"));
        REQUIRE_FALSE(hashMap.Contains("BADKEY"));
    }

    SECTION("Get Keys")
    {
        SLList<std::string> keyList = hashMap.GetKeys();

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
            REQUIRE(found);
        }
    }

    SECTION("Copy")
    {
        HashMap<uint32_t> otherHashMap = hashMap;

        for (int i = 0; i < 9; i++)
        {
            REQUIRE(otherHashMap.Get(keys[i]) == hashMap.Get(keys[i]));
        }
    }
}
