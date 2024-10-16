#pragma once
#include "DBConnection.h"
#include <ctime> 
#include <string>

class ClassThatUseDbInterface
{
public:
	ClassThatUseDbInterface() {};
	ClassThatUseDbInterface(DBConnectionInterface* dbHandle) {};
	virtual ~ClassThatUseDbInterface() {}

	virtual void openConnection(std::string dbName) = 0;
	virtual std::string useConnection(std::string query) = 0;
	virtual void closeConnection() = 0;

protected:
	DBConnectionInterface* _dbConnection = nullptr;
	bool _connectionEstablished = false;
};

class ClassThatUseDb : public ClassThatUseDbInterface
{
public:
	ClassThatUseDb(DBConnectionInterface* dbHandle); 
	virtual ~ClassThatUseDb() {};

	void openConnection(std::string dbName) override;
	std::string useConnection(std::string query) override;
	void closeConnection() override;
};
