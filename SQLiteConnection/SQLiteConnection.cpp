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
    this->current_statement = NULL;
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

int SQLiteConnection::run_statement(const std::string statement)
{
    return this->run_statements(statement.c_str());
}

int SQLiteConnection::run_statement(const char* statement)
{
    return this->run_statements(statement);
}

int SQLiteConnection::run_statements(const std::string statements)
{
    return this->run_statements(statements.c_str());
}

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
    this->set_statement(statement.c_str());
}

void SQLiteConnection::set_statement(const char* statement)
{
    if (this->current_statement != NULL)
    {
        delete(this->current_statement);
    }
    this->current_statement = new SQLiteStatement(this->database_connector, statement);
}

int SQLiteConnection::step_statement()
{
    if (this->current_statement == NULL)
    {
        throw std::logic_error("The step_statement() method was called with no current SQLite statement.");
    }
    this->statement_status = this->current_statement->step();
    return this->statement_status;
}

int SQLiteConnection::set_int_argument(int parameter_number, long long value)
{
    if (this->current_statement == NULL)
    {
        throw std::logic_error("The set_int_argument() method was called with no current SQLite statement.");
    }
    this->statement_status = this->current_statement->set_int_argument(parameter_number, value);
    return this->statement_status;
}

int SQLiteConnection::set_float_argument(int parameter_number, double value)
{
    if (this->current_statement == NULL)
    {
        throw std::logic_error("The set_float_argument() method was called with no current SQLite statement.");
    }
    this->statement_status = this->current_statement->set_float_argument(parameter_number, value);
    return this->statement_status;
}

std::string SQLiteConnection::get_result_string(int column_number)
{
    if (this->current_statement == NULL)
    {
        throw std::logic_error("The get_result_string() method was called with no current SQLite statement.");
    }    
    return this->current_statement->query_result_string(column_number);
}

char* SQLiteConnection::get_result_chars(int column_number)
{
    if (this->current_statement == NULL)
    {
        throw std::logic_error("The get_result_chars() method was called with no current SQLite statement.");
    }
    return (char*)this->current_statement->query_result_c_string(column_number);
}

long long SQLiteConnection::get_result_long(int column_number)
{
    if (this->current_statement == NULL)
    {
        throw std::logic_error("The get_result_long() method was called with no current SQLite statement.");
    }
    return this->current_statement->query_result_long(column_number);
}

double SQLiteConnection::get_result_double(int column_number)
{
    if (this->current_statement == NULL)
    {
        throw std::logic_error("The get_result_double() method was called with no current SQLite statement.");
    }
    return this->current_statement->query_result_double(column_number);
}

int SQLiteConnection::reset_statement()
{
    if (this->current_statement == NULL)
    {
        throw std::logic_error("The reset_statement() method was called with no current SQLite statement.");
    }
    this->statement_status = this->current_statement->reset();
    return this->statement_status;
}

int SQLiteConnection::finish_statement_execution()
{
    if (this->current_statement == NULL)
    {
        throw std::logic_error("The finish_statement_execution() method was called with no current SQLite statement.");
    }
    int execution_result;
    do
    {
        execution_result = this->current_statement->step();
    } while (execution_result == SQLITE_ROW || execution_result == SQLITESTATEMENT_NOT_FINISHED);
    if (execution_result != SQLITE_DONE)
    {
        std::cerr << "The current SQLite statement could not be completed.\n" << 
                sqlite3_errstr(execution_result) << std::endl;
    }
    this->statement_status = execution_result;
    return execution_result;
}

int SQLiteConnection::cancel_statement()
{
    if (this->current_statement == NULL)
    {
        this->statement_status = SQLITE_OK;
        return SQLITE_OK;
    }
    delete(this->current_statement);
    this->current_statement = NULL;
    this->statement_status = SQLITE_OK;
    return SQLITE_OK;   
}
