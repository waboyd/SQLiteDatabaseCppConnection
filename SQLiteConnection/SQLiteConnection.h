#pragma once
#include <iostream>
#include "SQLite3.h"

class SQLiteConnection
{
private:
    sqlite3 *database_connector;

public:
    SQLiteConnection(std::string database_name);
    ~SQLiteConnection();
    
    int close();
};

