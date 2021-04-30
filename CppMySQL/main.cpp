#include <iostream>
#include <stdlib.h>
#include <windows.h>
#include <mysql.h>
#include <sstream>
#include <string>

// CONNECTION DATA
const char* hostname = "localhost";
const char* username = "root";
const char* password = "";
const char* database = "movies_test_database";
unsigned int port = 3306;
const char* unixsocket = NULL;
unsigned long clientflag = 0;
//

MYSQL* connect_to_database()
{
    MYSQL* conn;
    conn = mysql_init(0);
    conn = mysql_real_connect(conn, hostname, username, password, database, port, unixsocket, clientflag);

    if (conn)
    {
        std::cout << "Succesfully connected to database" << std::endl;
        return conn;
    }
    else
    {
        std::cout << "There was an error while trying to connect to database" << std::endl;
        return conn;
    }
}

void insert_into_DB(MYSQL* conn)
{
    int qstate = 0;
    std::stringstream ss;
    std::string nazwadb;
    std::cout << "Input the name of the movie you want to insert: " << std::endl;
    std::cin.sync();
    std::getline(std::cin, nazwadb);
    ss << "INSERT INTO movies (Name) VALUES ('"+nazwadb+"');";
    std::string query = ss.str();
    const char* q = query.c_str();
    qstate = mysql_query(conn, q);
    if (qstate == 0)
    {
        std::cout << "Record succesfully inserted" << std::endl;
    }
    else
    {
        std::cout << "Failed to insert" << std::endl;
    }
}

void update_DB(MYSQL* conn)
{
    int qstate = 0;
    std::stringstream ss;
    std::string nazwadb_old, nazwadb_new;
    std::cout << "Input the name of the movie you want to update: " << std::endl;
    std::cin.sync();
    std::getline(std::cin, nazwadb_old);
    std::cout << "Input new name: " << std::endl;
    std::cin.sync();
    std::getline(std::cin, nazwadb_new);
    ss << "UPDATE movies SET Name = '"+nazwadb_new+"' WHERE Name = '"+nazwadb_old+"';";
    std::string query = ss.str();
    const char* q = query.c_str();
    qstate = mysql_query(conn, q);
    if (qstate == 0)
    {
        std::cout << "Record succesfully updated" << std::endl;
    }
    else
    {
        std::cout << "Failed to update" << std::endl;
    }
}
void delete_from_DB(MYSQL* conn)
{
    int qstate = 0;
    std::stringstream ss;
    std::string nazwadb;
    std::cout << "Input the name of the movie you want to delete: " << std::endl;
    std::cin.sync();
    std::getline(std::cin, nazwadb);
    ss << "DELETE FROM movies WHERE Name = '"+nazwadb+"';";
    std::string query = ss.str();
    const char* q = query.c_str();
    qstate = mysql_query(conn, q);
    if (qstate == 0)
    {
        std::cout << "Record succesfully deleted" << std::endl;
    }
    else
    {
        std::cout << "Failed to delete" << std::endl;
    }
}
void display_DB(MYSQL* conn)
{
    MYSQL_ROW row;
    MYSQL_RES* res;
    if (conn)
    {
        int qstate = mysql_query(conn, "SELECT * FROM movies ORDER BY movieID;");
        if(!qstate)
        {
            res = mysql_store_result(conn);
            int count = mysql_num_fields(res);
            while (row = mysql_fetch_row(res))
            {
                for (int i = 0; i<count; i++ )
                {
                    std::cout << "\t" << row[i];
                }
                std::cout << std::endl;
            }
        }

    }
    else
    {
        std::cout << "There was an error while displaying database contents" << std::endl;
    }
}

int main()
{
    bool running = TRUE;
    std::cout << "Simple MYSQL database CRUD management tool v.1.0 \nCreated for databases course by: Daniel Klata" << std::endl;
    MYSQL* conn = connect_to_database();
    if (conn)
    {
        while(running)
        {
            int choice = 0;
            std::cout << "Currently connected to: " << hostname << "/" << username << "/" << database << std::endl;
            std::cout << std::endl << "1. Create (Insert)" << std::endl << "2. Read (Display)" << std::endl << "3. Update" << std::endl << "4. Delete" << std::endl << "5. Exit program" << std::endl;
            std::cout << std::endl << "Select action: ";
            std::cin >> choice;
            system("cls");

            switch(choice)
            {
            case 1:
                insert_into_DB(conn);
                system("pause");
                break;
            case 2:
                display_DB(conn);
                system("pause");
                break;
            case 3:
                update_DB(conn);
                system("pause");
                break;
            case 4:
                delete_from_DB(conn);
                system("pause");
                break;
            case 5:
                running = FALSE;
                break;
            default:
                std::cout << "Error: Wrong input" << std::endl;
                system("pause");
                break;
            }
            system("cls");
        }
    }
    else
    {
        std::cout << "Could not connect to database. ";
    }
    std::cout << "Exiting program" << std::endl;
    system("pause");
    return 0;
}
