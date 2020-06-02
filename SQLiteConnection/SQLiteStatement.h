#pragma once
#include "SQLite3.h"
#include <iostream>

#define SQLITESTATEMENT_NOT_FINISHED    5001

class SQLiteStatement
{
private:
    // No SQLiteStatement object should be copied.
    SQLiteStatement(const SQLiteStatement& original);
    void operator=(const SQLiteStatement& original);
    sqlite3 *database_connector;
    sqlite3_stmt *prepared_statement;
    SQLiteStatement *next_statement;
    bool is_completed;
    
    void compile_statement(const char* statement_string);
    
public:
    SQLiteStatement();
    SQLiteStatement(sqlite3* database_connector);
    SQLiteStatement(sqlite3* database_connector, const std::string statement_string);
    SQLiteStatement(sqlite3* database_connector, const char* statement_string);
    ~SQLiteStatement();
    
    SQLiteStatement& operator=(const std::string statement_string);
    SQLiteStatement& operator=(const char* statement_string);
    
    int step();
    void finalize();

};

