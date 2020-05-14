/////////////////////////////////
/// DLListUT.cpp
///
/// @brief Unit Test for DLList
/////////////////////////////////

// SYSTEM INCLUDES
#include <assert.h>
#include <iostream>

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "DLList.hpp"   // Test class

////////////////////////////////
/// Test Objects
////////////////////////////////
DLList<int>* pMyDLList = new DLList<int>();
DLList<int>::DLListIterator myListIterator = pMyDLList->GetBegin();

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
    // Insert 1 - 9 to back
    for (int i = 0; i < 10; i++)
    {
        pMyDLList->InsertBack(i);
    }

    for (int i = 0; i < 10; i++)
    {
        assert(i == pMyDLList->Get(i));
    }

    // Insert 9 - 0 to front
    for (int i = 9; i >= 0; i--)
    {
        pMyDLList->InsertFront(i);
    }

    for (int i = 9; i >= 0; i--)
    {
        assert(i == pMyDLList->Get(i));
    }

    // Test exception
    try
    {
        pMyDLList->Get(100);
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
    assert(pMyDLList->GetLength() == 20);
}

////////////////////////////////
/// ClearTest Function
////////////////////////////////
void ClearTest()
{
    pMyDLList->Clear();
    assert(pMyDLList->GetLength() == 0);
}

////////////////////////////////
/// RemoveTest Function
////////////////////////////////
void RemoveTest()
{
    for (int i = 0; i < 10; i++)
    {
        pMyDLList->InsertBack(i);
    }

    pMyDLList->PrintList();

    for (int i = 9; i >= 0; i--)
    {
        assert(pMyDLList->GetLength() == i + 1);
        int removedValue = pMyDLList->Remove(i);
        assert(i == removedValue);
    }

    // Test exception
    try
    {
        pMyDLList->Remove(100);
        assert(false);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

////////////////////////////////
/// IteratorTest Function
////////////////////////////////
void IteratorTest()
{
    for (int i = 0; i < 10; i++)
    {
        pMyDLList->InsertBack(i);
    }

    int i = 0;
    for (myListIterator = pMyDLList->GetBegin();
         myListIterator != pMyDLList->GetEnd();
         myListIterator++)
    {
        assert(i == *myListIterator);
        i++;
    }
    assert(i == 10);

    for (myListIterator = pMyDLList->GetReverseBegin();
         myListIterator != pMyDLList->GetReverseEnd();
         myListIterator--)
    {
        i--;
        assert(i == *myListIterator);
    }
    assert(i == 0);
}

////////////////////////////////
/// Teardown Function
////////////////////////////////
void teardown()
{
    delete pMyDLList;
}

////////////////////////////////
/// Main Function
////////////////////////////////
int main(int argc, char* argv[])
{
    setup();

    InsertAndGetTest();
    GetLengthTest();
    ClearTest();
    RemoveTest();
    IteratorTest();

    teardown();

    std::cout << "DLList Unit Test Complete: SUCCESS";
    return 0;
}