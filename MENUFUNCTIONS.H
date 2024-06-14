#ifndef MENUFUNCTIONS_H_INCLUDED
#define MENUFUNCTIONS_H_INCLUDED

#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <string>

using namespace std;

class Car
{
public:
    string id;
    string brand;
    string color;
    string country;
    int year;
    double price;
    int sold;

    Car(string id, string brand, string color, string country, int year, double price) : id(id), brand(brand), color(color), country(country), year(year), price(price), sold(0) {}
};

vector<Car> cars;

string generateCarID(const string &brand)
{
    srand(time(0));
    int random_number = rand() % 1000000;
    return brand.substr(0, 3) + to_string(random_number);
}

void addCar()
{
    string brand, color, country;
    int year;
    double price;

    cout << "Enter car brand: ";
    cin >> brand;
    cout << "Enter car color: ";
    cin >> color;
    cout << "Enter country of manufacture: ";
    cin >> country;
    cout << "Enter year of manufacture: ";
    cin >> year;
    cout << "Enter price: ";
    cin >> price;

    string id = generateCarID(brand);
    cars.emplace_back(id, brand, color, country, year, price);
    cout << "Car added with ID: " << id << endl;
}

void modifyCar()
{
    string id;
    cout << "Enter car ID to modify: ";
    cin >> id;

    for (auto &car : cars)
    {
        if (car.id == id)
        {
            cout << "Enter new car brand: ";
            cin >> car.brand;
            cout << "Enter new car color: ";
            cin >> car.color;
            cout << "Enter new country of manufacture: ";
            cin >> car.country;
            cout << "Enter new year of manufacture: ";
            cin >> car.year;
            cout << "Enter new price: ";
            cin >> car.price;
            cout << "Car details updated." << endl;
            return;
        }
    }
    cout << "Car with ID " << id << " not found." << endl;
}

void displayAllCars()
{
    for (const auto &car : cars)
    {
        cout << "ID: " << car.id << ", Brand: " << car.brand << ", Color: " << car.color
             << ", Country: " << car.country << ", Year: " << car.year << ", Price: " << car.price << endl;
    }
}

void sortCarsByBrand()
{
    sort(cars.begin(), cars.end(), [](const Car &a, const Car &b)
         { return a.brand < b.brand; });
    displayAllCars();
}

void sortCarsByPrice()
{
    sort(cars.begin(), cars.end(), [](const Car &a, const Car &b)
         { return a.price < b.price; });
    displayAllCars();
}

void searchCarByID()
{
    string id;
    cout << "Enter car ID to search: ";
    cin >> id;

    for (const auto &car : cars)
    {
        if (car.id == id)
        {
            cout << "ID: " << car.id << ", Brand: " << car.brand << ", Color: " << car.color
                 << ", Country: " << car.country << ", Year: " << car.year << ", Price: " << car.price << endl;
            return;
        }
    }
    cout << "Car with ID " << id << " not found." << endl;
}

void trackSales()
{
    int totalSales = 0;
    for (const auto &car : cars)
    {
        totalSales += car.sold;
    }
    cout << "Total cars sold: " << totalSales << endl;
}

void removeCar()
{
    string id;
    cout << "Enter car ID to remove: ";
    cin >> id;

    for (auto it = cars.begin(); it != cars.end(); ++it)
    {
        if (it->id == id)
        {
            cars.erase(it);
            cout << "Car with ID " << id << " removed." << endl;
            return;
        }
    }
    cout << "Car with ID " << id << " not found." << endl;
}

void sortCarsByBestSellingBrand()
{
    sort(cars.begin(), cars.end(), [](const Car &a, const Car &b)
         { return a.sold > b.sold; });
    displayAllCars();
}

#endif