#include <iostream>
?#include "ClassThatUseDb.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"

class SomeTestSuite : public ::testing::Test
{
protected:

    void SetUp(DBConnectionInterface* mockPointer)
    {
        testObject = new ClassThatUseDb(mockPointer);
    }

    void TearDown()
    {
        delete testObject;
    }

    ClassThatUseDbInterface* testObject;
};

TEST_F(SomeTestSuite, CASE_filledName)
{
    std::string dbName = "TestName";
    std::string dbRequest = "DB request";
    std::string dbShouldReply = "DB reply";
    std::string dbReply;

    MockDBConnection mDBConnection;
    SetUp(&mDBConnection);

    EXPECT_CALL(mDBConnection, open).WillOnce(::testing::Return(true)); 
    EXPECT_CALL(mDBConnection, execQuery).WillOnce(::testing::Return(dbShouldReply));
    EXPECT_CALL(mDBConnection, close).Times(1); 

    testObject->openConnection(dbName);
    dbReply = testObject->useConnection(dbRequest);
    testObject->closeConnection();

    EXPECT_EQ(dbReply, dbShouldReply);
}

TEST_F(SomeTestSuite, CASE_emptyName)
{
    std::string dbName = "";
    std::string dbRequest = "DB request";
    std::string dbShouldNotReply = "DB reply"; 
    std::string dbReply;

    MockDBConnection mDBConnection;
    SetUp(&mDBConnection);

    EXPECT_CALL(mDBConnection, open).Times(0); 
    EXPECT_CALL(mDBConnection, execQuery).Times(0);
    EXPECT_CALL(mDBConnection, close).Times(0);

    testObject->openConnection(dbName);
    dbReply = testObject->useConnection(dbRequest);
    testObject->closeConnection();

    EXPECT_NE(dbReply, dbShouldNotReply); 
    EXPECT_EQ(dbReply, "");
}