/////////////////////////////////
/// @file ListUT.cpp
///
/// @brief Unit Test for List
///
/// @author Luke Karavolis
/////////////////////////////////

// SYSTEM INCLUDES
#include <assert.h>
#include <iostream>

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "List.hpp"  // Test class

////////////////////////////////
/// Test Objects
////////////////////////////////
List<int> myList = List<int>(10);

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
        myList.Append(i);
    }

    for (int i = 0; i < 15; i++)
    {
        assert(myList[i] == i);
    }

    myList.PrintList();

    try
    {
        myList[15];
        assert(false);
    }
    catch(const IndexOutOfBoundsException& e)
    {
        std::cerr << e.what() << '\n';
    }
}

////////////////////////////////
/// GetLengthTest Function
////////////////////////////////
void GetLengthTest()
{
    assert(myList.GetLength() == 15);
    assert(!myList.IsEmpty());
}

////////////////////////////////
/// ReplaceTest Function
////////////////////////////////
void ReplaceTest()
{
    myList[0] = 100;
    assert(myList[0] == 100);

    try
    {
        myList[100] = 100;
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
    myList.Clear();
    assert(myList.GetLength() == 0);
    assert(myList.IsEmpty());
}

////////////////////////////////
/// InsertTest Function
////////////////////////////////
void InsertTest()
{
    for (int i = 0; i < 10; i++)
    {
        myList.Append(i);
    }

    myList.PrintList();

    myList.Insert(0, 100);
    assert(myList[0] == 100);
    for (int i = 1; i < 11; i++)
    {
        assert(myList[i] == i - 1);
    }

    myList.Insert(11, 11);
    assert(myList[11] == 11);
}

////////////////////////////////
/// RemoveTest Function
////////////////////////////////
void RemoveTest()
{
    myList.PrintList();

    int value = myList.Remove(0);
    assert(value == 100);
    assert(myList[0] == 0);

    myList.PrintList();

    value = myList.Remove(10);
    assert(value == 11);
    assert(myList[9] == 9);

    try
    {
        value = myList.Remove(10);
        assert(false);
    }
    catch(const IndexOutOfBoundsException& e)
    {
        std::cerr << e.what() << '\n';
    }
}

////////////////////////////////
/// SortTest Function
////////////////////////////////
void SortTest()
{
    // Reset the list
    myList.Clear();
    for (int i = 14; i >= 0; i--)
    {
        myList.Append(i);
    }

    myList.Sort();

    myList.PrintList();
    
    for (int i = 0; i < myList.GetLength(); i++)
    {
        assert(myList[i] == i);
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
    SortTest();

    teardown();

    std::cout << "List Unit Test Complete: SUCCESS";
    return 0;
}