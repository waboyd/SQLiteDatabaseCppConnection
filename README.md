# SQLDatabaseCppConnection
This is a set of simple classes to connect to a SQLite database within a C++ program. This set of classes provides some of the same functionality provided by the SQLite C interface, adapted for object-oriented use. The classes use the C commands for SQLite internally to allow execution of SQL statements from an object of SQLiteConnection. The benefits of using this library include:
* Method calls with fewer parameters
* Internal error checking
* Methods for complete command processing

This was designed specifically for a set of personal projects, but it may be applied to other projects when useful. No guarantees are made regarding functionality of or updates to this set of classes.

The MIT License is applied to this software. You have permission to use and modify the software for any purpose, but please give me, William Boyd, credit for the creation of the original version of this software.

You may email me at bwilliam@hotmail.com if you have questions or comments.

Some code was adapted from the tutorial for the C interface at https://www.sqlite.org/.

## Using SQLiteConnection
SQLiteConnection is a class that represents a connection to a SQLite database. It must be instantiated with the file path of a SQLite database.

	#include "SQLiteConnection.h"
	
	SQLiteConnection sample_connection("..\\DatabaseFolder\\DatabaseFile.db");
	
Once a SQLiteConnection object has been created, a SQL command can be run using the run\_statement method. The run\_statements method is equivalent.

	std::string table_creation_statement =
		"CREATE TABLE test_table\n"
		"(\n"
		"`entry_number` INTEGER NOT NULL PRIMARY KEY,\n"
		"`int_value` INTEGER DEFAULT 0,\n"
		"`description` TEXT\n"
		");";

	sample_connection.run_statement(table_creation_statement);
	sample_connection.run_statements(
		"INSERT INTO test_table\n"
        "(`entry_number`, `int_value`, `description`)\n"
        "VALUES\n"
        "(1, 32767, \'First entry\'),\n"
        "(5, -32768, \'Second entry\');\n"
        "INSERT INTO test_table\n"
        "(`int_value`, `description`)\n"
        "VALUES\n"
        "(43, \'Third entry\');"
		);

To return values from a database, more steps are required. The SQLiteConnection object can have one current SQL statement at a time. The current SQL statement is set with the method set\_statement.

	std::string sql_info_request_1 =
        "SELECT int_value FROM test_table\n"
        "ORDER BY entry_number ASC;";
    sample_connection.set_statement(sql_info_request_1);
	
Then, the results of the query can be stepped through, row by row, using the step\_statement method. The values from a row can be obtained using the methods get\_result\_string, get\_result\_chars, get\_result\_long, and get\_result\_double, depending on the type of the value that should be returned. The argument for these methods is the column index of the value in the query results, where the first column has an index of 0.

    int status;
	long test_value;
	status = sample_connection.step_statement();
    while (status == SQLITE_ROW)
    {
        test_value = sample_connection.get_result_double(0);
        std::cout << "Value from query: " << test_value << "\n";
        status = sample_connection.step_statement();
    }

The current statement can be reset for execution from the beginning using the reset\_statement method. Use finish\_statement\_execution to complete execution of the current statement. The current statement will stop and be removed as the current statement if the method cancel\_statement is called.

The method close can be used to close the connection to SQLite. This method is automatically called when the SQLiteConnection object is destroyed, so there may not be a need to call the close method.
