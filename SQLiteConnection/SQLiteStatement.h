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
    
    /**
     * @brief Change this object to process a new SQLite statement.
     * Previous statements are automatically discarded.
     * @param statement_string A SQLite statement to execute.
     */
    SQLiteStatement& operator=(const std::string statement_string);

    /**
     * @brief Change this object to process a new SQLite statement.
     * Previous statements are automatically discarded.
     * @param statement_string A SQLite statement to execute.
     */
    SQLiteStatement& operator=(const char* statement_string);
    
    /**
     * @brief Continue execution of the statement, and move to the next row of results (if applicable).
     * @return The SQLite status after executing the step.
     */
    int step();
    
    /**
     * @brief Set the statement to be executed from the beginning when the next step() call is made.
     * @return The SQLite status after resetting the statement.
     */
    int reset();
    
    /**
     * @brief End execution of the statement and free it.
     */
    void finalize();
    
    /**
     * @brief Set an integer value for a parameter of the statement.
     * @param parameter_number The index number of the parameter to set.
     * @param value The value of the argument.
     * @return The resulting SQLite status from the action.
     */
    int set_int_argument(int parameter_number, long long value);

    /**
     * @brief Set a floating point value for a parameter of the statement.
     * @param parameter_number The index number of the parameter to set.
     * @param value The value of the argument.
     * @return The resulting SQLite status from the action.
     */
    int set_float_argument(int parameter_number, double value);

    /**
     * @brief Return an integer value from the current row of the result of the query.
     * @param column_number The column number of the result to return, where the first column is 0.
     * @return The value of the element as a long long integer.
     */
    long long query_result_long(int column_number);
    
    /**
     * @brief Return a string value from the current row of the result of the query.
     * @param column_number The column number of the result to return, where the first column is 0.
     * @return The value of the element as a C++ string.
     */
    const std::string query_result_string(int column_number);

    /**
     * @brief Return an string value from the current row of the result of the query.
     * @param column_number The column number of the result to return, where the first column is 0.
     * @return The value of the element as a C-string.
     */
    const unsigned char* query_result_c_string(int column_number);
    
    /**
     * @brief Return a floating point value from the current row of the result of the query.
     * @param column_number The column number of the result to return, where the first column is 0.
     * @return The value of the element as a double.
     */
    double query_result_double(int column_number);

};

