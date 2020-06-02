#include "SQLiteConnection.h"
#include "SQLiteStatement.h"

SQLiteConnection::SQLiteConnection(const std::string database_file_path)
{
    this->database_setup(database_file_path.c_str());
}

SQLiteConnection::SQLiteConnection(const char* database_file_path)
{
    this->database_setup(database_file_path);
}

SQLiteConnection::SQLiteConnection(const SQLiteConnection& original)
{
    throw std::invalid_argument("An attempt was made to copy a SQLiteConnection object, which is not permitted.");
}

SQLiteConnection::~SQLiteConnection()
{
    this->close();    
}

void SQLiteConnection::operator=(const SQLiteConnection& original)
{
    throw std::invalid_argument("An attempt was made to copy a SQLiteConnection object, which is not permitted.");
}

void SQLiteConnection::database_setup(const char* database_file_path)
{
    int database_status;
    database_status = sqlite3_open(database_file_path, &this->database_connector);
    if(database_status != SQLITE_OK)
    {
        std::cerr << "The database could not be opened.\n" <<
                sqlite3_errmsg(this->database_connector) << std::endl;
        sqlite3_close(this->database_connector);
    }
    this->current_statement = NULL;
    this->statement_status = database_status;
}

int SQLiteConnection::close()
{
    int database_status;
    delete(this->current_statement);
    database_status = sqlite3_close(this->database_connector);
    if (database_status != SQLITE_OK)
    {
        std::cerr << "The database connection could not be closed.\n" <<
                sqlite3_errmsg(this->database_connector) << std::endl;
    }
    else {
        this->database_connector = NULL;
    }
    this->statement_status = database_status;
    return database_status;
}

/**
 * @brief Runs SQLite statements without storing or displaying results.
 * @param statements SQLite statements to run.
 * @return Final status of the statement execution.
 */
int SQLiteConnection::run_statements(const std::string statements)
{
    return this->run_statements(statements.c_str());
}

/**
 * @brief Runs SQLite statements without storing or displaying results.
 * @param statements SQLite statements to run.
 * @return Final status of the statement execution.
 */
int SQLiteConnection::run_statements(const char* statements)
{
    if (this->database_connector == NULL)
    {
        throw std::logic_error("An attempt was made to use a closed SQLite connection.\n");
    }
    SQLiteStatement compiled_statement(this->database_connector, statements);
    int execution_result;
    do
    {
        execution_result = compiled_statement.step();
    } while (execution_result == SQLITE_ROW || execution_result == SQLITESTATEMENT_NOT_FINISHED);
    if (execution_result != SQLITE_DONE)
    {
        std::cerr << "The statements could not be fully executed:\n" << statements << "\n" <<
                sqlite3_errstr(execution_result) << std::endl;        
    }
    this->statement_status = execution_result;
    return execution_result;
}

void SQLiteConnection::set_statement(const std::string statement)
{
    return this->set_statement(statement.c_str());
}

void SQLiteConnection::set_statement(const char* statement)
{
    if (this->current_statement != NULL)
    {
        delete(this->current_statement);
    }
    this->current_statement = new SQLiteStatement(this->database_connector, statement);
}
