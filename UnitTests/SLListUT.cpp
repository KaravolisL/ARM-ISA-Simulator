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
    // for (int i = 9; i >= 0; i--)
    // {
    //     assert(i == pMySLList->Remove())
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

    teardown();

    std::cout << "SLList Unit Test Complete: SUCCESS";
    return 0;
}

