/////////////////////////////////
/// SLListUT.cpp
///
/// @brief Unit Test for SLList
/////////////////////////////////

// SYSTEM INCLUDES
#include <assert.h>
#include <iostream>

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "SLList.hpp"   // Test class

////////////////////////////////
/// Test Objects
////////////////////////////////
SLList<int>* pMySLList = new SLList<int>();
SLList<int>::SLListIterator myListIterator = pMySLList->GetBegin();

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
        pMySLList->InsertBack(i);
    }

    for (int i = 0; i < 10; i++)
    {
        assert(i == pMySLList->Get(i));
    }

    // Insert 9 - 0 to front
    for (int i = 9; i >= 0; i--)
    {
        pMySLList->InsertFront(i);
    }

    for (int i = 9; i >= 0; i--)
    {
        assert(i == pMySLList->Get(i));
    }

    // TODO: Uncomment when exception is made
    // Test exception
    // try
    // {
    //     pMySLList->Get(100);
    //     assert(false);
    // }
    // catch(const std::exception& e)
    // {
    //     std::cerr << e.what() << '\n';
    // }
}

////////////////////////////////
/// GetLengthTest Function
////////////////////////////////
void GetLengthTest()
{
    assert(pMySLList->GetLength() == 20);
}

////////////////////////////////
/// ClearTest Function
////////////////////////////////
void ClearTest()
{
    pMySLList->Clear();
    assert(pMySLList->GetLength() == 0);
}

////////////////////////////////
/// RemoveTest Function
////////////////////////////////
void RemoveTest()
{
    for (int i = 0; i < 10; i++)
    {
        pMySLList->InsertBack(i);
    }

    pMySLList->PrintList();

    for (int i = 9; i >= 0; i--)
    {
        assert(pMySLList->GetLength() == i + 1);
        int removedValue = pMySLList->Remove(i);
        assert(i == removedValue);
    }

    // TODO: Uncomment when exception is made
    // Test exception
    // try
    // {
    //     pMySLList->Remove(100);
    //     assert(false);
    // }
    // catch(const std::exception& e)
    // {
    //     std::cerr << e.what() << '\n';
    // }
}

////////////////////////////////
/// IteratorTest Function
////////////////////////////////
void IteratorTest()
{
    for (int i = 0; i < 10; i++)
    {
        pMySLList->InsertBack(i);
    }

    int i = 0;
    for (myListIterator = pMySLList->GetBegin();
         myListIterator != pMySLList->GetEnd();
         myListIterator++)
    {
        assert(i == *myListIterator);
        i++;
    }
}

////////////////////////////////
/// Teardown Function
////////////////////////////////
void teardown()
{
    delete pMySLList;
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

    std::cout << "SLList Unit Test Complete: SUCCESS";
    return 0;
}

