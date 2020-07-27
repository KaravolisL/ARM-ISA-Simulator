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
#include "UnitTest.hpp"
#include "List.hpp"  // Test class

////////////////////////////////
/// Test Objects
////////////////////////////////
List<uint32_t> myList = List<uint32_t>(10);

////////////////////////////////
/// AppendAndGetTest Function
////////////////////////////////
bool AppendAndGetTest()
{
    // Test Append
    for (uint32_t i = 0; i < 15; i++)
    {
        myList.Append(i);
    }

    for (uint32_t i = 0; i < 15; i++)
    {
        UNIT_ASSERT(myList[i] == i);
    }

    myList.PrintList();

    try
    {
        myList[15];
        UNIT_ASSERT(false);
    }
    catch(const IndexOutOfBoundsException& e)
    {
        std::cerr << e.what() << '\n';
    }

    return true;
}

////////////////////////////////
/// GetLengthTest Function
////////////////////////////////
bool GetLengthTest()
{
    UNIT_ASSERT(myList.GetLength() == 15);
    UNIT_ASSERT(!myList.IsEmpty());

    return true;
}

////////////////////////////////
/// ReplaceTest Function
////////////////////////////////
bool ReplaceTest()
{
    myList[0] = 100;
    UNIT_ASSERT(myList[0] == 100);

    try
    {
        myList[100] = 100;
        UNIT_ASSERT(false);
    }
    catch(const IndexOutOfBoundsException& e)
    {
        std::cerr << e.what() << '\n';
    }

    return true;
}

////////////////////////////////
/// ClearTest Function
////////////////////////////////
bool ClearTest()
{
    myList.Clear();
    UNIT_ASSERT(myList.GetLength() == 0);
    UNIT_ASSERT(myList.IsEmpty());

    return true;
}

////////////////////////////////
/// InsertTest Function
////////////////////////////////
bool InsertTest()
{
    for (int i = 0; i < 10; i++)
    {
        myList.Append(i);
    }

    myList.PrintList();

    myList.Insert(0, 100);
    UNIT_ASSERT(myList[0] == 100);
    for (uint32_t i = 1; i < 11; i++)
    {
        UNIT_ASSERT(myList[i] == i - 1);
    }

    myList.Insert(11, 11);
    UNIT_ASSERT(myList[11] == 11);

    return true;
}

////////////////////////////////
/// RemoveTest Function
////////////////////////////////
static bool RemoveTest()
{
    myList.PrintList();

    int value = myList.Remove(0);
    UNIT_ASSERT(value == 100);
    UNIT_ASSERT(myList[0] == 0);

    myList.PrintList();

    value = myList.Remove(10);
    UNIT_ASSERT(value == 11);
    UNIT_ASSERT(myList[9] == 9);

    try
    {
        value = myList.Remove(10);
        UNIT_ASSERT(false);
    }
    catch(const IndexOutOfBoundsException& e)
    {
        std::cerr << e.what() << '\n';
    }

    return true;
}

////////////////////////////////
/// SortTest Function
////////////////////////////////
bool SortTest()
{
    // Reset the list
    myList.Clear();
    for (int i = 14; i >= 0; i--)
    {
        myList.Append(i);
    }

    myList.Sort();

    myList.PrintList();
    
    for (uint32_t i = 0; i < myList.GetLength(); i++)
    {
        UNIT_ASSERT(myList[i] == i);
    }

    return true;
}

////////////////////////////////
/// CopyTest Function
////////////////////////////////
static bool CopyTest()
{
    List<uint32_t> otherList = myList;

    for (uint32_t i = 0; i < otherList.GetLength(); i++)
    {
        UNIT_ASSERT(otherList[i] == myList[i]);
        UNIT_ASSERT(&otherList[i] != &myList[i]);
    }

    return true;
}

////////////////////////////////
/// Main Function
////////////////////////////////
bool ListUT()
{
    UnitTest unitTest("List Unit Test");

    unitTest.AddSubTest(AppendAndGetTest);
    unitTest.AddSubTest(GetLengthTest);
    unitTest.AddSubTest(ReplaceTest);
    unitTest.AddSubTest(ClearTest);
    unitTest.AddSubTest(InsertTest);
    unitTest.AddSubTest(RemoveTest);
    unitTest.AddSubTest(SortTest);
    unitTest.AddSubTest(CopyTest);

    return unitTest.Run();
}
