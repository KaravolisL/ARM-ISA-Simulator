/////////////////////////////////
/// DLListUT.cpp
///
/// @brief Unit Test for DLList
/////////////////////////////////

// SYSTEM INCLUDES
// (None)

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include <catch2/catch.hpp>
#include "DLList.hpp"   // Test class
#include "SLList.hpp"

TEMPLATE_TEST_CASE("Linked List Basic Functionality", "[data_structure]", (DLList<uint32_t>), (SLList<uint32_t>))
{
    TestType list = TestType();

    SECTION("Insert Front")
    {
        for (uint32_t i = 0; i < 10; i++)
        {
            list.InsertBack(i);
        }

        for (uint32_t i = 0; i < 10; i++)
        {
            REQUIRE(i == list.Get(i));
        }

        REQUIRE(list.GetLength() == 10);
        list.Clear();
        REQUIRE(list.GetLength() == 0);
    }

    SECTION("Insert Back")
    {
        for (int i = 9; i >= 0; i--)
        {
            list.InsertFront(static_cast<uint32_t>(i));
        }

        for (int i = 9; i >= 0; i--)
        {
            REQUIRE(static_cast<uint32_t>(i) == list.Get(i));
        }

        REQUIRE_THROWS_AS(list.Get(100), IndexOutOfBoundsException);
        REQUIRE(list.GetLength() == 10);
    }

    SECTION("Removal")
    {
        for (uint32_t i = 0; i < 10; i++)
        {
            list.InsertBack(i);
        }

        for (int i = 9; i >= 0; i--)
        {
            REQUIRE(list.GetLength() == static_cast<uint32_t>(i) + 1);
            REQUIRE(static_cast<uint32_t>(i) == list.Remove(i));
        }

        REQUIRE_THROWS_AS(list.Remove(100), IndexOutOfBoundsException);
    }
}

TEST_CASE("SLList Iterator Test", "[data_structure][extended]")
{
    SLList<int> list = SLList<int>();
    SLList<int>::SLListIterator iterator;

    for (int i = 0; i < 10; i++)
    {
        list.InsertBack(i);
    }

    int i = 0;
    for (iterator = list.GetBegin();
         iterator != list.GetEnd();
         iterator++)
    {
        REQUIRE(i == *iterator);
        i++;
    }
    REQUIRE(i == 10);
}

TEST_CASE("DLList Iterator Test", "[data_structure][extended]")
{
    DLList<int> list = DLList<int>();
    DLList<int>::DLListIterator iterator;

    for (int i = 0; i < 10; i++)
    {
        list.InsertBack(i);
    }

    int i = 0;
    for (iterator = list.GetBegin();
         iterator != list.GetEnd();
         iterator++)
    {
        REQUIRE(i == *iterator);
        i++;
    }
    REQUIRE(i == 10);

    for (iterator = list.GetReverseBegin();
         iterator != list.GetReverseEnd();
         iterator--)
    {
        i--;
        REQUIRE(i == *iterator);
    }
    REQUIRE(i == 0);
}
