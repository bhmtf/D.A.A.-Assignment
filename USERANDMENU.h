#ifndef USERANDMENU_H_INCLUDED
#define USERANDMENU_H_INCLUDED

#include <exception>
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include "MENUFUNCTIONS.h"

using namespace std;

// NOTE: username and password must have no spaces between.
// ^^ I cannot get getline() to work in this program and cin cannot read spaces

class User
{
private:
    string username;
    string password;

public:
    User() = default;
    User(string u, string p)
    {
        username = u;
        password = p;
    }

    string getName() const { return username; }
    string getPass() const { return password; }
};

class Menu : public User
{
private:
    vector<User> users; // A vector of all registered users...

public:
    // List of initial users...
    Menu()
    {
        users.push_back(User("Knee", "pass1"));
        users.push_back(User("aspas", "pass2"));
        users.push_back(User("Yeonarang", "pass3"));
    }

    void registerNew()
    {
        string user, pass;
        cout << "Enter username: ";
        cin >> user;

        cout << "Enter password: ";
        cin >> pass;

        if (doesUserExist(user))
        {
            cout << "Username already exists. Please choose a different username!" << endl;
        }
        else
        {
            users.push_back(User(user, pass));
            cout << "User: " << user << ", registered successfully!" << endl;
            carManagementMenu();
        }
    }

    bool userLogin()
    {
        string user, pass;
        cout << "Enter username: ";
        cin >> user;

        cout << "Enter password: ";
        cin >> pass;

        // Iterate through the vector.
        for (auto &u : users)
        {
            if (u.getName() == user && u.getPass() == pass)
            {
                cout << "Login successful. Welcome " << user << "!" << endl;
                carManagementMenu();
                return true;
            }
        }

        cout << "Wrong username or password!" << endl;
        return false;
    }

    bool doesUserExist(string &username) const
    {
        return find_if(users.begin(), users.end(), [&username](const User &user)
                       { return user.getName() == username; }) != users.end();
    }

    void displayMenu()
    {
        int choice;
        while (true)
        {
            cout << "1. Register" << endl;
            cout << "2. Login" << endl;
            cout << "3. Exit" << endl;
            cout << "Enter your choice: ";

            cin >> choice;

            switch (choice)
            {
            case 1:
                registerNew();
                break;

            case 2:
                if (userLogin())
                {
                    return;
                }
                break;

            case 3:
                cout << "Exiting :D" << endl;
                return;

            default:
                cout << "Invalid choice!" << endl;
            }
        }
    }

    void carManagementMenu()
    {
        int choice;
        while (true)
        {
            cout << "1. Add a new car\n2. Modify car data\n3. Display all cars\n4. Sort cars by brand\n5. Sort cars by price\n"
                 << "6. Search for a car by its ID\n7. Track the number of cars sold\n8. Remove a car record\n"
                 << "9. Sort cars by best-selling brand\n10. Exit\nEnter your choice: ";
            cin >> choice;

            switch (choice)
            {
            case 1:
                addCar();
                break;
            case 2:
                modifyCar();
                break;
            case 3:
                displayAllCars();
                break;
            case 4:
                sortCarsByBrand();
                break;
            case 5:
                sortCarsByPrice();
                break;
            case 6:
                searchCarByID();
                break;
            case 7:
                trackSales();
                break;
            case 8:
                removeCar();
                break;
            case 9:
                sortCarsByBestSellingBrand();
                break;
            case 10:
                return;
            default:
                cout << "Invalid choice. Please try again." << endl;
            }
        }
    }
};

#endif // USERANDMENU_H_INCLUDED
