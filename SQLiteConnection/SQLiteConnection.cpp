#include "SQLiteConnection.h"

SQLiteConnection::SQLiteConnection(std::string database_name)
{
    int database_status;
    database_status = sqlite3_open(database_name.c_str(), &this->database_connector);
    if(database_status != SQLITE_OK){
        std::cerr << "The database could not be opened.\n" <<
                sqlite3_errmsg(this->database_connector);
        sqlite3_close(this->database_connector);
    }    
}

SQLiteConnection::~SQLiteConnection()
{
    this->close();    
}

int SQLiteConnection::close()
{
    int database_status;
    database_status = sqlite3_close(this->database_connector);
    if (database_status != SQLITE_OK)
    {
        std::cerr << "The database connection could not be closed.\n" <<
                sqlite3_errmsg(this->database_connector);
    }
    else {
//        delete(this->database_connector);
        this->database_connector = NULL;
    }
    return database_status;
}

