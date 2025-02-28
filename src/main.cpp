#include <mysql.h>
#include <mysql/mysql_connection.h>
#include <mysql/cppconn/statement.h>
#include <mysql/cppconn/resultset.h>
#include <mysql/cppconn/prepared_statement.h>
#include <iostream>
#include <string>

using namespace std;
using namespace sql::mysql;

void insertUser(sql::Connection *con, const string &name, int age)
{
    unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("INSERT INTO Users(Name, Age) VALUES (?, ?)"));
    pstmt->setString(1, name);
    pstmt->setInt(2, age);
    pstmt->executeUpdate();
}

void updateUser(sql::Connection *con, int id, const string &name, int age)
{
    unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("UPDATE Users SET Name = ?, Age = ? WHERE ID = ?"));
    pstmt->setString(1, name);
    pstmt->setInt(2, age);
    pstmt->setInt(3, id);
    pstmt->executeUpdate();
}

void deleteUser(sql::Connection *con, int id)
{
    unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("DELETE FROM Users WHERE ID = ?"));
    pstmt->setInt(1, id);
    pstmt->executeUpdate();
}

void displayUsers(sql::Connection *con)
{
    unique_ptr<sql::Statement> stmt(con->createStatement());
    unique_ptr<sql::ResultSet> res(stmt->executeQuery("SELECT * FROM Users"));

    while (res->next())
    {
        cout << "ID: " << res->getInt("ID") << ", Name: " << res->getString("Name") << ", Age: " << res->getInt("Age") << endl;
    }
}

int main()
{
    try
    {
        // Create a connection
        MySQL_Driver *driver = sql::mysql::get_mysql_driver_instance();
        unique_ptr<sql::Connection> con(driver->connect("tcp://127.0.0.1:3306", "root", "root"));

        // Connect to the database
        con->setSchema("testdb");

        int choice;
        while (true)
        {
            cout << "1. Insert User\n2. Update User\n3. Delete User\n4. Display Users\n5. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;

            if (choice == 1)
            {
                string name;
                int age;
                cout << "Enter name: ";
                cin >> name;
                cout << "Enter age: ";
                cin >> age;
                insertUser(con.get(), name, age);
            }
            else if (choice == 2)
            {
                int id;
                string name;
                int age;
                cout << "Enter ID: ";
                cin >> id;
                cout << "Enter new name: ";
                cin >> name;
                cout << "Enter new age: ";
                cin >> age;
                updateUser(con.get(), id, name, age);
            }
            else if (choice == 3)
            {
                int id;
                cout << "Enter ID to delete: ";
                cin >> id;
                deleteUser(con.get(), id);
            }
            else if (choice == 4)
            {
                displayUsers(con.get());
            }
            else if (choice == 5)
            {
                break;
            }
            else
            {
                cout << "Invalid choice. Please try again.\n";
            }
        }
    }
    catch (sql::SQLException &e)
    {
        cout << "SQLException: " << e.what() << endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
