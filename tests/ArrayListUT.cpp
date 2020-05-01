/////////////////////////////////
/// @file ArrayListUT.cpp
///
/// @brief Unit Test for ArrayList
///
/// @author Luke Karavolis
/////////////////////////////////

// SYSTEM INCLUDES
#include <assert.h>
#include <iostream>

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "ArrayList.hpp"  // Test class

////////////////////////////////
/// Test Objects
////////////////////////////////
ArrayList<int> myArrayList = ArrayList<int>(10);

////////////////////////////////
/// Setup Function
////////////////////////////////
void setup()
{

}

////////////////////////////////
/// AppendAndGetTest Function
////////////////////////////////
void AppendAndGetTest()
{
    // Test Append
    for (int i = 0; i < 15; i++)
    {
        myArrayList.Append(i);
    }

    for (int i = 0; i < 15; i++)
    {
        assert(myArrayList.Get(i) == i);
    }

    myArrayList.PrintList();

    try
    {
        myArrayList.Get(15);
        assert(false);
    }
    catch(const IndexOutOfBoundsException& e)
    {
        // std::cerr << e.what() << '\n';
    }
}

////////////////////////////////
/// GetLengthTest Function
////////////////////////////////
void GetLengthTest()
{
    assert(myArrayList.GetLength() == 15);
}

////////////////////////////////
/// ReplaceTest Function
////////////////////////////////
void ReplaceTest()
{
    myArrayList.Replace(0, 100);
    assert(myArrayList.Get(0) == 100);

    try
    {
        myArrayList.Replace(100, 100);
        assert(false);
    }
    catch(const IndexOutOfBoundsException& e)
    {
        std::cerr << e.what() << '\n';
    }
}

////////////////////////////////
/// ClearTest Function
////////////////////////////////
void ClearTest()
{
    myArrayList.Clear();
    assert(myArrayList.GetLength() == 0);
}

////////////////////////////////
/// InsertTest Function
////////////////////////////////
void InsertTest()
{
    for (int i = 0; i < 10; i++)
    {
        myArrayList.Append(i);
    }

    myArrayList.Insert(0, 100);
    assert(myArrayList.Get(0) == 100);
    for (int i = 1; i < 11; i++)
    {
        assert(myArrayList.Get(i) == i - 1);
    }

    myArrayList.Insert(11, 11);
    assert(myArrayList.Get(11) == 11);
}

////////////////////////////////
/// RemoveTest Function
////////////////////////////////
void RemoveTest()
{
    myArrayList.PrintList();

    int value = myArrayList.Remove(0);
    assert(value == 100);
    assert(myArrayList.Get(0) == 11);

    myArrayList.PrintList();

    value = myArrayList.Remove(10);
    assert(value == 9);
    assert(myArrayList.Get(9) == 8);

    try
    {
        value = myArrayList.Remove(10);
        assert(false);
    }
    catch(const IndexOutOfBoundsException& e)
    {
        std::cerr << e.what() << '\n';
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

    AppendAndGetTest();
    GetLengthTest();
    ReplaceTest();
    ClearTest();
    InsertTest();
    RemoveTest();

    teardown();

    std::cout << "ArrayList Unit Test Complete: SUCCESS";
    return 0;
}