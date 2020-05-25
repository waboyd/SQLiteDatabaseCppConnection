#pragma once
#include "SQLite3.h"
#include <iostream>

class SQLiteStatement
{
private:
    sqlite3_stmt* prepared_statement;
    SQLiteStatement *next_statement;
    
    void compile_statement(sqlite3* database_connector, const char* statement_string);
    
public:
    SQLiteStatement(sqlite3* database_connector, const std::string statement_string);
    SQLiteStatement(sqlite3* database_connector, const char* statement_string);
    ~SQLiteStatement();
    
    void finalize();

};

