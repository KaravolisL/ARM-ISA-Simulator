/////////////////////////////////
/// @file ListUT.cpp
///
/// @brief Unit Test for List
///
/// @author Luke Karavolis
/////////////////////////////////

// SYSTEM INCLUDES
// (None)

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include <catch2/catch.hpp>
#include "List.hpp"  // Test class

TEST_CASE("Basic functionality", "[data_structure]")
{
    List<uint32_t> list = List<uint32_t>(10);

    for (uint32_t i = 0; i < 15; i++)
    {
        list.Append(i);
    }

    for (uint32_t i = 0; i < 15; i++)
    {
        REQUIRE(list[i] == i);
    }

    REQUIRE_THROWS_AS(list[15], IndexOutOfBoundsException);

    REQUIRE(list.GetLength() == 15);
    REQUIRE_FALSE(list.IsEmpty());

    list[0] = 100;
    REQUIRE(list[0] == 100);
}

TEST_CASE("Insertion and Removal", "[data_structure]")
{
    List<uint32_t> list = List<uint32_t>(10);

    for (int i = 0; i < 10; i++)
    {
        list.Append(i);
    }

    list.Insert(0, 100);
    REQUIRE(list[0] == 100);
    for (uint32_t i = 1; i < 11; i++)
    {
        REQUIRE(list[i] == i - 1);
    }

    list.Insert(11, 11);
    REQUIRE(list[11] == 11);

    uint32_t value = list.Remove(0);
    REQUIRE(value == 100);
    REQUIRE(list[0] == 0);

    value = list.Remove(10);
    REQUIRE(value == 11);
    REQUIRE(list[9] == 9);

    REQUIRE_THROWS_AS(list.Remove(10), IndexOutOfBoundsException);
}

TEST_CASE("Sorting", "[data_structure][extended]")
{
    List<uint32_t> list = List<uint32_t>(10);

    for (int i = 14; i >= 0; i--)
    {
        list.Append(i);
    }

    list.Sort();
    
    for (uint32_t i = 0; i < list.GetLength(); i++)
    {
        REQUIRE(list[i] == i);
    }
}

TEST_CASE("Copying", "[data_structure][extended]")
{
    List<uint32_t> list = List<uint32_t>(10);
    List<uint32_t> otherList = list;

    for (uint32_t i = 0; i < otherList.GetLength(); i++)
    {
        REQUIRE(otherList[i] == list[i]);
        REQUIRE(&otherList[i] != &list[i]);
    }
}
