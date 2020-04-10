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
DLB<int> myDLB();
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
}

////////////////////////////////
/// ContainsTest Function
////////////////////////////////
void ContainsTest()
{
    assert(myDLB.Contains(keys[i]));
    assert(!myDLB.Contains("BAD KEY"));
}

////////////////////////////////
/// UpdateTest Function
////////////////////////////////
void UpdateTest()
{
    for (int i = 0; i < 4; i++)
    {
        int oldValue = myDLB.Insert(keys[i], i*i);
        assert(oldValue == i);
        int newValue = myDLB.Get(i);
        assert(newValue == i*i);
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

    InsertTest();
    GetTest();
    ContainsTest();
    UpdateTest();

    teardown();

    std::cout << "DLB Unit Test Complete: SUCCESS";
    return 0;
}