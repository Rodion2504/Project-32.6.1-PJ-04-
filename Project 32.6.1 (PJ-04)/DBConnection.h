#pragma once
#include <string>
#include "gmock/gmock.h"

class DBConnectionInterface
{
public:
	DBConnectionInterface() {};
	virtual ~DBConnectionInterface() {};

	virtual bool open(std::string dbName) = 0;
	virtual void close() = 0;
	virtual std::string execQuery(std::string query) = 0;

};

class DBConnection : public DBConnectionInterface
{
public:
	DBConnection() {};
	virtual ~DBConnection() {};

	virtual bool open(std::string dbName) override { return true; };
	virtual void close() override {};
	virtual std::string execQuery(std::string query) override { return std::string(); };
};

class MockDBConnection : public DBConnectionInterface
{
public:
	MOCK_METHOD(bool, open, (std::string dbName), (override));
	MOCK_METHOD(void, close, (), (override));
	MOCK_METHOD(std::string, execQuery, (std::string query), (override));
};