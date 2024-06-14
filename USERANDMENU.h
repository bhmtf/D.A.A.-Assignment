#ifndef USERANDMENU_H_INCLUDED
#define USERANDMENU_H_INCLUDED

#include <exception>
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

// NOTE: username and password must have no spaces between.
// ^^ I cannot get getline() to work in this program and cin cannot read spaes

class User {
    private:
        string username;
        string password;
    
    public:
        User() = default;
        User(string u, string p) {
            username = u;
            password = p;
        }

        string getName() const { return username; }
        string getPass() const { return password; }
};

class Menu : public User {
    private:
        vector <User> users; // A vector of all registered users...
    
    public:
        // List of initial users...
        Menu() {
            users.push_back(User("Knee", "pass1"));
            users.push_back(User("aspas", "pass2"));
            users.push_back(User("Yeonarang", "pass3"));
        }

        void registerNew() {
            string user, pass;
            cout << "Enter username: ";
            cin >> user;

            cout << "Enter password: ";
            cin >> pass;

            if(doesUserExist(user)) {
                cout << "Username already exists. Please choose a different username!" << endl;
            } else {
                users.push_back(User(user, pass));
                cout << "User: " << user << ", registered succesfully!" << endl;
            }
        }

        void userLogin() {
            string user, pass;
            cout << "Enter username: ";
            cin >> user;

            cout << "Enter password: ";
            cin >> pass;

                // vvv Ini untuk iterate through the vector.
            for(auto& u : users) {
                if(u.getName() == user && u.getPass() == pass) {
                    cout << "Login succesfull. Welcome " << user << "!" << endl;
                
                    // Insert function that redirects to the main program itself...
                    return;
                }
            }

            cout << "Wrong username or password!" << endl;
        }

        // Gw ChatGPT function ini lol
        bool doesUserExist(string &username) const {
            return find_if(users.begin(), users.end(), [&username](const User& user) {
                return user.getName() == username;
            }) != users.end();
        } 

        void displayMenu() {
            int choice;
            while(true) {
                cout << "1. Register" << endl;
                cout << "2. Login" << endl;
                cout << "3. Exit" << endl;
                cout << "Enter your choice: ";

                
                cin >> choice;

                switch(choice) {
                    case 1:
                        registerNew();
                        break;
                    
                    case 2:
                        userLogin();
                        break;

                    case 3:
                        cout << "Exiting :D" << endl;
                        return;
                    
                    default:
                        cout << "Invalid choice!" << endl;
                        
                }
            }
        }
};

#endif // USERANDMENU_H_INCLUDED