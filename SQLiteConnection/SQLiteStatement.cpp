#include "SQLiteStatement.h"
#include <string.h>

SQLiteStatement::SQLiteStatement()
{
    // An object instatiated with this is not usable until associated with a database and statement.
}

SQLiteStatement::SQLiteStatement(const SQLiteStatement& original)
{
    throw std::invalid_argument("An attempt was made to copy a SQLiteStatement object, which is not permitted.");
}

SQLiteStatement::SQLiteStatement(sqlite3* database_connector)
{
    this->database_connector = database_connector;
}

SQLiteStatement::SQLiteStatement(sqlite3* database_connector, const std::string statement_string)
{
    const char* statement_cstr = statement_string.c_str();
    this->database_connector = database_connector;
    this->compile_statement(statement_cstr);
}

SQLiteStatement::SQLiteStatement(sqlite3* database_connector, const char* statement_string)
{
    this->database_connector = database_connector;
    this->compile_statement(statement_string);
}

SQLiteStatement::~SQLiteStatement()
{
    this->finalize();
}

void SQLiteStatement::operator=(const SQLiteStatement& original)
{
    throw std::invalid_argument("An attempt was made to copy a SQLiteStatement object, which is not permitted.");
}

void SQLiteStatement::compile_statement(const char* statement_string)
{
    const char* subsequent_statements;
    int prep_status;
    
    prep_status = sqlite3_prepare_v2(
        this->database_connector,   // sqlite3* db
        statement_string,           // const char* zSql
        -1,                         // int nByte
        &this->prepared_statement,  // sqlite3_stmt** ppStmt
        &subsequent_statements      // const char **pzTail
    );
    if (prep_status != SQLITE_OK) {
        // Explain the error.
        std::cerr << sqlite3_errstr(prep_status) << std::endl;
        delete(this);
        return;
    }
    if(strlen(subsequent_statements) > 2)
    {
        this->next_statement = new SQLiteStatement(this->database_connector, subsequent_statements);
    }
    else
    {
        this->next_statement = NULL;
    }
    this->is_completed = false;
}

SQLiteStatement& SQLiteStatement::operator =(const std::string statement_string)
{
    return this->operator =(statement_string.c_str());
}

SQLiteStatement& SQLiteStatement::operator=(const char* statement_string)
{
    this->finalize();
    this->compile_statement(statement_string);
    return *this;
}

int SQLiteStatement::step()
{
    int step_result;
    if (this->is_completed && this->next_statement != NULL)
    {
        step_result = this->next_statement->step();
    }
    else{
        step_result = sqlite3_step(this->prepared_statement);
        if (step_result == SQLITE_DONE)
        {
            this->is_completed = true;
            if (this->next_statement != NULL)
                step_result = SQLITESTATEMENT_NOT_FINISHED;
        }
        else if (step_result != SQLITE_ROW && step_result != SQLITESTATEMENT_NOT_FINISHED)
        {
            // Give the error message.
            std::cerr << sqlite3_errstr(step_result);
        }
    }
    return step_result;
}

void SQLiteStatement::finalize()
{
    int statement_status;
    if (this->prepared_statement != NULL)
    {
        statement_status = sqlite3_finalize(this->prepared_statement);
        if (statement_status != SQLITE_OK)
        {
            // Explain the error.
            std::cerr << sqlite3_errstr(statement_status) << std::endl;
            return;
        }
        this->prepared_statement = NULL;
    }
    if (this->next_statement != NULL)
    {
        delete(this->next_statement);
    }
}