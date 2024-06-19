#ifndef MENUFUNCTION_H_INCLUDED
#define MENUFUNCTION_H_INCLUDED

#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <string>
#include <functional>
#include <cctype>
#include <unordered_map>
#include "BILLINGFUNCTIONS.h"

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
vector<Car> soldCars;      // Separate vector for sold cars
vector<Car> purchasedCars; // Separate vector for purchased cars

string generateCarID(const string &brand)
{
    srand(time(0));
    int random_number = rand() % 1000000;
    return brand.substr(0, 3) + to_string(random_number);
}

bool isAlpha(const string &str)
{
    return all_of(str.begin(), str.end(), ::isalpha);
}

void addCar()
{
    string brand, color, country;
    int year;
    double price;
    time_t now = time(0);
    int currentYear = localtime(&now)->tm_year + 1900;

    try
    {
        cout << "Enter car brand: ";
        cin >> brand;
        if (!isAlpha(brand))
        {
            throw runtime_error("Brand should only contain alphabets.");
        }

        cout << "Enter car color: ";
        cin >> color;
        if (!isAlpha(color))
        {
            throw runtime_error("Color should only contain alphabets.");
        }

        cout << "Enter country of manufacture: ";
        cin >> country;
        if (!isAlpha(country))
        {
            throw runtime_error("Country should only contain alphabets.");
        }

        cout << "Enter year of manufacture: ";
        cin >> year;
        if (cin.fail() || year < 1886 || year > currentYear)
        { // 1886 is the year the first car was made
            throw runtime_error("Invalid year. Please enter a valid year.");
        }

        cout << "Enter price: ";
        cin >> price;
        if (cin.fail() || price < 0)
        {
            throw runtime_error("Invalid price. Please enter a valid price.");
        }

        string id = generateCarID(brand);
        cars.emplace_back(id, brand, color, country, year, price);
        cout << "Car added with ID: " << id << endl;
    }
    catch (const exception &e)
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << e.what() << endl;
    }
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
            try
            {
                cout << "Enter new car brand: ";
                cin >> car.brand;
                if (!isAlpha(car.brand))
                {
                    throw runtime_error("Brand should only contain alphabets.");
                }

                cout << "Enter new car color: ";
                cin >> car.color;
                if (!isAlpha(car.color))
                {
                    throw runtime_error("Color should only contain alphabets.");
                }

                cout << "Enter new country of manufacture: ";
                cin >> car.country;
                if (!isAlpha(car.country))
                {
                    throw runtime_error("Country should only contain alphabets.");
                }

                cout << "Enter new year of manufacture: ";
                cin >> car.year;
                time_t now = time(0);
                int currentYear = localtime(&now)->tm_year + 1900;
                if (cin.fail() || car.year < 1886 || car.year > currentYear)
                {
                    throw runtime_error("Invalid year. Please enter a valid year.");
                }

                cout << "Enter new price: ";
                cin >> car.price;
                if (cin.fail() || car.price < 0)
                {
                    throw runtime_error("Invalid price. Please enter a valid price.");
                }

                cout << "Car details updated." << endl;
                return;
            }
            catch (const exception &e)
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << e.what() << endl;
            }
        }
    }
    cout << "Car with ID " << id << " not found." << endl;
}

void displayAllCars()
{
    cout << left << setw(10) << "Car ID"
         << left << setw(15) << "Car Brand"
         << left << setw(6) << "Year"
         << left << setw(10) << "Color"
         << left << setw(10) << "Price"
         << left << setw(10) << "Country" << endl;
    cout << "-------------------------------------------------------------" << endl;
    for (const auto &car : cars)
    {
        cout << left << setw(10) << car.id
             << left << setw(15) << car.brand
             << left << setw(6) << car.year
             << left << setw(10) << car.color
             << left << setw(10) << car.price
             << left << setw(10) << car.country << endl;
    }
}

void displayPurchasedCars()
{
    cout << left << setw(10) << "Car ID"
         << left << setw(15) << "Car Brand"
         << left << setw(6) << "Year"
         << left << setw(10) << "Color"
         << left << setw(10) << "Price"
         << left << setw(10) << "Country" << endl;
    cout << "-------------------------------------------------------------" << endl;
    for (const auto &car : purchasedCars)
    {
        cout << left << setw(10) << car.id
             << left << setw(15) << car.brand
             << left << setw(6) << car.year
             << left << setw(10) << car.color
             << left << setw(10) << car.price
             << left << setw(10) << car.country << endl;
    }
}

int customPartition(vector<Car> &arr, int low, int high, function<bool(const Car &, const Car &)> comparator)
{
    Car pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++)
    {
        if (comparator(arr[j], pivot))
        {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void quickSort(vector<Car> &arr, int low, int high, function<bool(const Car &, const Car &)> comparator)
{
    if (low < high)
    {
        int pi = customPartition(arr, low, high, comparator);
        quickSort(arr, low, pi - 1, comparator);
        quickSort(arr, pi + 1, high, comparator);
    }
}

void sortCarsByID()
{
    if (cars.empty())
    {
        cout << "No cars available to sort." << endl;
        return;
    }
    quickSort(cars, 0, cars.size() - 1, [](const Car &a, const Car &b)
              { return a.id < b.id; });
    displayAllCars();
}

void sortCarsByPrice()
{
    if (cars.empty())
    {
        cout << "No cars available to sort." << endl;
        return;
    }
    quickSort(cars, 0, cars.size() - 1, [](const Car &a, const Car &b)
              { return a.price < b.price; });
    displayAllCars();
}

void sortCarsByBrand()
{
    if (cars.empty())
    {
        cout << "No cars available to sort." << endl;
        return;
    }
    quickSort(cars, 0, cars.size() - 1, [](const Car &a, const Car &b)
              { return a.brand < b.brand; });
    displayAllCars();
}

void selectionSort(vector<Car> &arr, function<bool(const Car &, const Car &)> comparator)
{
    int n = arr.size();
    for (int i = 0; i < n - 1; i++)
    {
        int minIndex = i;
        for (int j = i + 1; j < n; j++)
        {
            if (comparator(arr[j], arr[minIndex]))
            {
                minIndex = j;
            }
        }
        swap(arr[minIndex], arr[i]);
    }
}

void sortCarsByBestSellingBrand()
{
    if (purchasedCars.empty())
    {
        cout << "No cars have been purchased." << endl;
        return;
    }
    selectionSort(purchasedCars, [](const Car &a, const Car &b)
                  { return a.brand < b.brand; });
    displayPurchasedCars();
}

void searchBestSellingBrand()
{
    if (purchasedCars.empty())
    {
        cout << "No cars have been purchased." << endl;
        return;
    }

    unordered_map<string, int> brandCount;
    for (const auto &car : purchasedCars)
    {
        brandCount[car.brand]++;
    }

    string bestSellingBrand;
    int maxCount = 0;
    for (const auto &pair : brandCount)
    {
        if (pair.second > maxCount)
        {
            bestSellingBrand = pair.first;
            maxCount = pair.second;
        }
    }

    if (maxCount > 0)
    {
        cout << "Best-selling brand: " << bestSellingBrand << " with " << maxCount << " sales." << endl;
    }
    else
    {
        cout << "No sales data available." << endl;
    }
}

void searchCarByID()
{
    if (cars.empty())
    {
        cout << "No cars available." << endl;
        return;
    }
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
    if (soldCars.empty())
    {
        cout << "No cars have been sold." << endl;
        return;
    }
    int totalSales = 0;
    for (const auto &car : soldCars)
    {
        totalSales += car.sold;
    }
    cout << "Total cars sold: " << totalSales << endl;
}

void purchaseCar()
{
    if (cars.empty())
    {
        cout << "No cars available for purchase." << endl;
        return;
    }
    string id;
    cout << "Enter car ID to purchase: ";
    cin >> id;

    auto it = find_if(cars.begin(), cars.end(), [&id](const Car &car)
                      { return car.id == id; });

    if (it != cars.end())
    {
        string customerName, customerID;
        cout << "Enter customer name: ";
        cin >> customerName;
        cout << "Enter customer ID: ";
        cin >> customerID;

        double discount = 0.0; // Apply any discount logic here if needed
        double totalPrice = it->price - (it->price * discount);
        string orderNumber = generateOrderNumber();
        string date = getCurrentDate();

        bills.emplace_back(customerName, customerID, it->id, it->brand, it->year, it->color, it->price, orderNumber, totalPrice, date);

        cout << "Bill generated successfully!" << endl;
        cout << "Customer Name: " << customerName << endl;
        cout << "Customer ID: " << customerID << endl;
        cout << "Car ID: " << it->id << endl;
        cout << "Car Brand: " << it->brand << endl;
        cout << "Year of Production: " << it->year << endl;
        cout << "Color: " << it->color << endl;
        cout << "Price: " << it->price << endl;
        cout << "Order Number: " << orderNumber << endl;
        cout << "Total Price: " << totalPrice << endl;
        cout << "Date: " << date << endl;

        it->sold++;                   // Increment the number of cars sold
        soldCars.push_back(*it);      // Add to sold cars vector
        purchasedCars.push_back(*it); // Add to purchased cars vector
        cars.erase(it);
    }
    else
    {
        cout << "Car with ID " << id << " not found." << endl;
    }
}

#endif // MENUFUNCTION_H_INCLUDED
