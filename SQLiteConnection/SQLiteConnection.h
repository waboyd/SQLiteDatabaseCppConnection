#pragma once
#include <iostream>
#include <vector>
#include "SQLite3.h"
#include "SQLiteStatement.h"

class SQLiteConnection
{
private:
    sqlite3 *database_connector;
    SQLiteStatement *current_statement;
    int statement_status;
    
    // No SQLiteConnection object should be copied.
    SQLiteConnection(const SQLiteConnection& original);
    void operator=(const SQLiteConnection& original);

    /**
     * @brief Set up and initialize this SQLiteConnection object.
     * @param database_file_path The path and name of the database file to open. 
     */
    void database_setup(const char* database_file_path);

public:
    SQLiteConnection(const std::string database_file_path);
    SQLiteConnection(const char* database_file_path);
    ~SQLiteConnection();
    
    /**
     * @brief Close this connection to SQLite.
     * This object is not usable after it is closed.
     * The close() method is automatically called in the destructor for the class SQLiteConnection.
     * @return The status returned from the SQLite close statement.
     */
    int close();

    /**
     * @brief Runs a set of SQLite statements, each of which ends with a semicolon.
     * This method does not retrieve information from the database.
     * @param statements SQLite statements to execute.
     * @return The final status of the execution of the statements.
     */
    int run_statement(const std::string statement);

    /**
     * @brief Runs a set of SQLite statements, each of which ends with a semicolon.
     * This method does not retrieve information from the database.
     * @param statements SQLite statements to execute.
     * @return The final status of the execution of the statements.
     */
    int run_statement(const char* statement);

    /**
     * @brief Runs a set of SQLite statements, each of which ends with a semicolon.
     * This method does not retrieve information from the database.
     * @param statements SQLite statements to execute.
     * @return The final status of the execution of the statements.
     */
    int run_statements(const std::string statements);

    /**
     * @brief Runs a set of SQLite statements, each of which ends with a semicolon.
     * This method does not retrieve information from the database.
     * @param statements SQLite statements to execute.
     * @return The final status of the execution of the statements.
     */
    int run_statements(const char* statements);
    
    /**
     * @brief Associates this object with a set of SQLite statements that can then be stepped through.
     * This method replaces any previously set statement for this object.
     * The methods step_statement(), get_result_string(), get_result_chars(), get_result_long(),
     * get_result_double(), finish_statement_execution(), reset_statement(), and cancel_statement() are
     * all related to the currently set SQLite statement.
     * @param statement SQLite statement to set as the current statement.
     * @return The status from compilation of the SQLite statement.
     */
    void set_statement(const std::string statement);

    /**
     * @brief Associates this object with a set of SQLite statements that can then be stepped through.
     * This method replaces any previously set statement for this object.
     * The methods step_statement(), set_int_argument(), set_float_argument(), get_result_string(),
     * get_result_chars(), get_result_long(), get_result_double(), finish_statement_execution(),
     * and cancel_statement() are all related to the currently set SQLite statement.
     * @param statement SQLite statement to set as the current statement.
     * @return The status from compilation of the SQLite statement.
     */
    void set_statement(const char* statement);
    
    /**
     * @brief Step to the next row of the SQLite statement query result.
     * The statement must first be set using the set_statement method.
     * @return The current status of the SQLite statement execution.
     */
    int step_statement();
    
    /**
     * @brief Set an integer value for a parameter in the current SQLite statement.
     * The statement must first be set using the set_statement method.
     * @param parameter_number The index number of the parameter to set.
     * @param value The value of the argument.
     * @return The resulting SQLite status from the action.
     */
    int set_int_argument(int parameter_number, long long value);
    
    /**
     * @brief Set an floating-point value for a parameter in the current SQLite statement.
     * The statement must first be set using the set_statement method.
     * @param parameter_number The index number of the parameter to set.
     * @param value The value of the argument.
     * @return The resulting SQLite status from the action.
     */
    int set_float_argument(int parameter_number, double value);
    
    /**
     * @brief Read the value from the current row of the current statement as a C++ string.
     * The statement must first be set using the set_statement method.
     * @param column_number The column number to read, where the first column is 0.
     * @return The value of the element as a C++ string.
     */
    std::string get_result_string(int column_number) const;
    
    /**
     * @brief Read the value from the current row of the current statement as a C string.
     * The statement must first be set using the set_statement method.
     * @param column_number The column number to read, where the first column is 0.
     * @return The value of the element as a C string.
     */
    char* get_result_chars(int column_number) const;
    
    /**
     * @brief Read the value from the current row of the current statement as a long int.
     * The statement must first be set using the set_statement method.
     * @param column_number The column number to read, where the first column is 0.
     * @return The value of the element as a long int.
     */
    long long get_result_long(int column_number) const;
    
    /**
     * @brief Read the value from the current row of the current statement as a double.
     * The statement must first be set using the set_statement method.
     * @param column_number The column number to read, where the first column is 0.
     * @return The value of the element as a double.
     */
    double get_result_double(int column_number) const;
    
    /**
     * @brief Reset the current SQLite statement, so that the statement will be ready to execute from the beginning.
     * The statement must first be set using the set_statement method.
     * @return The status of the SQLite statement after the reset.
     */
    int reset_statement();
    
    /**
     * @brief Complete execution of the current SQLite statements, and remove them from this object. 
     * The statement must first be set using the set_statement method.
     * @return The final status of the SQLite statement after execution.
     */
    int finish_statement_execution();
    
    /**
     * @brief Stop execution of the current SQLite statement and remove it, if a statement is set.
     * If no statement is currently set, nothing is done, and SQLITE_OK is returned.
     * @return The SQLite status from the finalize statement.
     */
    int cancel_statement();
    
    /**
     * @brief Query a single column of integer values from the database and return the results as a list.
     * @param statement SQLite query of exactly one table column.
     * @return The list of integer results from the query.
     */
    std::vector<long long> query_long_column(const char* statement);

    /**
     * @brief Query a single column of integer values from the database and return the results as a list.
     * @param statement SQLite query of exactly one table column.
     * @return The list of integer results from the query.
     */
    std::vector<long long> query_long_column(const std::string statement);

    /**
     * @brief Query a single column of string values from the database and return the results as a list.
     * @param statement SQLite query of exactly one table column.
     * @return The list of integer results from the query.
     */
    std::vector<std::string> query_string_column(const char* statement);
    
    /**
     * @brief Query a single column of string values from the database and return the results as a list.
     * @param statement SQLite query of exactly one table column.
     * @return The list of integer results from the query.
     */
    std::vector<std::string> query_string_column(const std::string statement);

    /**
     * @brief Query and return columns of integer values from the database.
     * @param statement SQLite query of integer columns.
     * @return The lists of integer results from the query. Each element of the outer vector is one row of the query results.
     */
    std::vector<std::vector<long long>> query_long_columns(const char* statement);

    /**
     * @brief Query and return columns of integer values from the database.
     * @param statement SQLite query of integer columns.
     * @return The lists of integer results from the query. Each element of the outer vector is one row of the query results.
     */
    std::vector<std::vector<long long>> query_long_columns(const std::string statement);

    /**
     * @brief Query and return columns of string values from the database.
     * @param statement SQLite query.
     * @return The lists of results from the query as strings. Each element of the outer vector is one row of the query results.
     */
    std::vector<std::vector<std::string>> query_string_columns(const char* statement);

    /**
     * @brief Query and return columns of string values from the database.
     * @param statement SQLite query.
     * @return The lists of results from the query as strings. Each element of the outer vector is one row of the query results.
     */
    std::vector<std::vector<std::string>> query_string_columns(const std::string statement);
};
