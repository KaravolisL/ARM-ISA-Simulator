/////////////////////////////////
/// @file DLBUT.cpp
///
/// @brief Unit Test for DLB
///
/// @author Luke Karavolis
/////////////////////////////////

// SYSTEM INCLUDES
// (None)

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include <catch2/catch.hpp>
#include "DLB.hpp"  // Test class

TEST_CASE("DLB Basic Functionality", "[data_structure]")
{
    DLB<int> dlb = DLB<int>();
    std::string keys[] = {"ABC", "ABD", "BCD", "ABCD"};

    for (int i = 0; i < 4; i++)
    {
        dlb.Insert(keys[i], i);
    }

    SECTION("Get")
    {
        for (int i = 0; i < 4; i++)
        {
            int item = dlb.Get(keys[i]);
            REQUIRE(item == i);
        }
        REQUIRE_THROWS_AS(dlb.Get("BADKEY"), DLB<int>::KeyNotFoundException);
    }

    SECTION("Contains")
    {
        REQUIRE(dlb.Contains(keys[0]));
        REQUIRE(!dlb.Contains("BAD KEY"));
        REQUIRE(!dlb.Contains("AB"));
    }

    SECTION("Update")
    {
        // TODO: Enable when Update is implemented
        // for (int i = 0; i < 4; i++)
        // {
        //     REQUIRE(dlb.Insert(keys[i], i*i) == i);
        //     REQUIRE(dlb.Get(i) == i*i);
        // }
    }
}
