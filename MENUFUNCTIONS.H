#ifndef MENUFUNCTIONS_H_INCLUDED
#define MENUFUNCTIONS_H_INCLUDED

#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <string>
#include <functional>

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

void quickSort(vector<Car> &arr, int low, int high, function<bool(const Car &, const Car &)> comparator)
{
    if (low < high)
    {
        int pi = partition(arr, low, high, comparator);
        quickSort(arr, low, pi - 1, comparator);
        quickSort(arr, pi + 1, high, comparator);
    }
}

int partition(vector<Car> &arr, int low, int high, function<bool(const Car &, const Car &)> comparator)
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

#endif // MENUFUNCTIONS_H_INCLUDED
