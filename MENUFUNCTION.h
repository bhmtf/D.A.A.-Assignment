#ifndef MENUFUNCTIONS_H_INCLUDED
#define MENUFUNCTIONS_H_INCLUDED

#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <string>
#include <functional>
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
vector<Car> soldCars; // Separate vector for sold cars

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
    quickSort(cars, 0, cars.size() - 1, [](const Car &a, const Car &b)
              { return a.id < b.id; });
    displayAllCars();
}

void sortCarsByPrice()
{
    quickSort(cars, 0, cars.size() - 1, [](const Car &a, const Car &b)
              { return a.price < b.price; });
    displayAllCars();
}

void sortCarsByBrand()
{
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
    selectionSort(cars, [](const Car &a, const Car &b)
                  { return a.brand < b.brand; });
    displayAllCars();
}

int binarySearch(const vector<Car> &arr, const string &brand)
{
    int left = 0, right = arr.size() - 1;
    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        if (arr[mid].brand == brand)
            return mid;
        if (arr[mid].brand < brand)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1;
}

void searchBestSellingCarByBrand()
{
    string brand;
    cout << "Enter car brand to search: ";
    cin >> brand;
    int index = binarySearch(cars, brand);
    if (index != -1)
    {
        cout << "Best-selling car found: " << endl;
        cout << "ID: " << cars[index].id << ", Brand: " << cars[index].brand << ", Color: " << cars[index].color
             << ", Country: " << cars[index].country << ", Year: " << cars[index].year << ", Price: " << cars[index].price << endl;
    }
    else
    {
        cout << "Best-selling car with brand " << brand << " not found." << endl;
    }
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
    for (const auto &car : soldCars)
    {
        totalSales += car.sold;
    }
    cout << "Total cars sold: " << totalSales << endl;
}

void purchaseCar()
{
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

        it->sold++;              // Increment the number of cars sold
        soldCars.push_back(*it); // Add to sold cars vector
        cars.erase(it);
    }
    else
    {
        cout << "Car with ID " << id << " not found." << endl;
    }
}

#endif // MENUFUNCTIONS_H_INCLUDED
