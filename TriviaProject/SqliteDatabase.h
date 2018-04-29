#pragma once
#include "IDatabase.h"
class SqliteDatabase : public IDatabase
{
public:
	SqliteDatabase();
	~SqliteDatabase();
};

