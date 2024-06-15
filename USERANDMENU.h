#ifndef USERANDMENU_H_INCLUDED
#define USERANDMENU_H_INCLUDED

#include <exception>
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include "MENUFUNCTION.h"
#include "BILLINGFUNCTIONS.h"

using namespace std;

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
            cout << "1. Add a new car\n2. Modify car data\n3. Display all cars\n4. Sort cars by ID\n5. Sort cars by brand\n6. Sort cars by price\n"
                 << "7. Search for a car by its ID\n8. Track the number of cars sold\n9. Purchase a car (remove from list and generate bill)\n"
                 << "10. Sort cars by best-selling brand and search for the best-selling brand\n11. Search for issued bills\n"
                 << "12. Generate a report of all company purchases\n13. Exit\nEnter your choice: ";
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
                sortCarsByID();
                break;
            case 5:
                sortCarsByBrand();
                break;
            case 6:
                sortCarsByPrice();
                break;
            case 7:
                searchCarByID();
                break;
            case 8:
                trackSales();
                break;
            case 9:
                purchaseCar();
                break;
            case 10:
                sortCarsByBestSellingBrand();
                searchBestSellingCarByBrand();
                break;
            case 11:
                searchIssuedBills();
                break;
            case 12:
                generatePurchaseReport();
                break;
            case 13:
                return;
            default:
                cout << "Invalid choice. Please try again." << endl;
            }
        }
    }
};

#endif // USERANDMENU_H_INCLUDED
