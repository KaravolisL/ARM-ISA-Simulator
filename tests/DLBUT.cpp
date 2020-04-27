/////////////////////////////////
/// @file DLBUT.cpp
///
/// @brief Unit Test for DLB
///
/// @author Luke Karavolis
/////////////////////////////////

// SYSTEM INCLUDES
#include <assert.h>
#include <iostream>

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "DLB.hpp"  // Test class

////////////////////////////////
/// Test Objects
////////////////////////////////
DLB<int> myDLB = DLB<int>();
std::string keys[] = {"ABC", "ABD", "BCD", "ABCD"};

////////////////////////////////
/// Setup Function
////////////////////////////////
void setup()
{

}

////////////////////////////////
/// InsertTest Function
////////////////////////////////
void InsertTest()
{
    for (int i = 0; i < 4; i++)
    {
        myDLB.Insert(keys[i], i);
    }
}

////////////////////////////////
/// GetTest Function
////////////////////////////////
void GetTest()
{
    for (int i = 0; i < 4; i++)
    {
        int item = myDLB.Get(keys[i]);
        assert(item == i);
    }

    try
    {
        myDLB.Get("A");
        assert(false);
    }
    catch(const DLB<int>::KeyNotFoundException& e)
    {
        std::cerr << e.what() << '\n';
    }
    
}

////////////////////////////////
/// ContainsTest Function
////////////////////////////////
void ContainsTest()
{
    assert(myDLB.Contains(keys[0]));
    assert(!myDLB.Contains("BAD KEY"));
    assert(!myDLB.Contains("AB"));
}

////////////////////////////////
/// UpdateTest Function
////////////////////////////////
void UpdateTest()
{
    // TODO: Enable when Update is implemented
    // for (int i = 0; i < 4; i++)
    // {
    //     int oldValue = myDLB.Insert(keys[i], i*i);
    //     assert(oldValue == i);
    //     int newValue = myDLB.Get(i);
    //     assert(newValue == i*i);
    // }
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

    InsertTest();
    GetTest();
    ContainsTest();
    // UpdateTest();

    teardown();

    std::cout << "DLB Unit Test Complete: SUCCESS";
    return 0;
}