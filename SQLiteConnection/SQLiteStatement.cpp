#include "SQLiteStatement.h"
#include <string.h>

SQLiteStatement::SQLiteStatement(sqlite3* database_connector, const std::string statement_string)
{
    const char* statement_cstr = statement_string.c_str();
    this->compile_statement(database_connector, statement_cstr);
}

SQLiteStatement::SQLiteStatement(sqlite3* database_connector, const char* statement_string)
{
    this->compile_statement(database_connector, statement_string);
}

SQLiteStatement::~SQLiteStatement()
{
    this->finalize();
}

void SQLiteStatement::compile_statement(sqlite3* database_connector, const char* statement_string)
{
    const char* subsequent_statements;
    int prep_status;
    
    prep_status = sqlite3_prepare_v2(
        database_connector,         // sqlite3* db
        statement_string,             // const char* zSql
        -1,                         // int nByte
        &this->prepared_statement,  // sqlite3_stmt** ppStmt
        &subsequent_statements      // const char **pzTail
    );
    if (prep_status != SQLITE_OK) {
        // ToDo: Read the error code.
        delete(this);
        return;
    }
    if(strlen(subsequent_statements) > 2)
    {
        this->next_statement = new SQLiteStatement(database_connector, subsequent_statements);
    }
    else
    {
        this->next_statement = NULL;
    }    
}

void SQLiteStatement::finalize()
{
    int statement_status;
    statement_status = sqlite3_finalize(this->prepared_statement);
    if (statement_status != SQLITE_OK) {
        // ToDo: Read the error code.
        return;
    }
    this->prepared_statement = NULL;
    if (this->next_statement != NULL)
    {
        this->next_statement->finalize();
    }
}