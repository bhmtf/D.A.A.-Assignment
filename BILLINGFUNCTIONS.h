#ifndef BILLINGFUNCTIONS_H_INCLUDED
#define BILLINGFUNCTIONS_H_INCLUDED

#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <limits>

using namespace std;

class Bill
{
public:
    string customerName;
    string customerID;
    string carID;
    string carBrand;
    int year;
    string color;
    double price;
    string orderNumber;
    double totalPrice;
    string date;

    Bill(string customerName, string customerID, string carID, string carBrand, int year, string color, double price, string orderNumber, double totalPrice, string date) : customerName(customerName), customerID(customerID), carID(carID), carBrand(carBrand), year(year), color(color), price(price), orderNumber(orderNumber), totalPrice(totalPrice), date(date) {}
};

vector<Bill> bills;

string generateOrderNumber()
{
    srand(time(0));
    int random_number = rand() % 1000000;
    return "ORD" + to_string(random_number);
}

string getCurrentDate()
{
    time_t now = time(0);
    tm *ltm = localtime(&now);
    string date = to_string(1900 + ltm->tm_year) + "-" + to_string(1 + ltm->tm_mon) + "-" + to_string(ltm->tm_mday);
    return date;
}

void searchIssuedBills()
{
    int choice;
    string searchValue;

    cout << "Search by: 1. Customer ID 2. Bill Date" << endl;
    if (!(cin >> choice))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a number." << endl;
        return;
    }

    cout << "Enter search value: ";
    cin >> searchValue;

    if (choice == 1)
    {
        for (const auto &bill : bills)
        {
            if (bill.customerID == searchValue)
            {
                cout << "Customer Name: " << bill.customerName << endl;
                cout << "Customer ID: " << bill.customerID << endl;
                cout << "Car ID: " << bill.carID << endl;
                cout << "Car Brand: " << bill.carBrand << endl;
                cout << "Year of Production: " << bill.year << endl;
                cout << "Color: " << bill.color << endl;
                cout << "Price: " << bill.price << endl;
                cout << "Order Number: " << bill.orderNumber << endl;
                cout << "Total Price: " << bill.totalPrice << endl;
                cout << "Date: " << bill.date << endl;
            }
        }
    }
    else if (choice == 2)
    {
        for (const auto &bill : bills)
        {
            if (bill.date == searchValue)
            {
                cout << "Customer Name: " << bill.customerName << endl;
                cout << "Customer ID: " << bill.customerID << endl;
                cout << "Car ID: " << bill.carID << endl;
                cout << "Car Brand: " << bill.carBrand << endl;
                cout << "Year of Production: " << bill.year << endl;
                cout << "Color: " << bill.color << endl;
                cout << "Price: " << bill.price << endl;
                cout << "Order Number: " << bill.orderNumber << endl;
                cout << "Total Price: " << bill.totalPrice << endl;
                cout << "Date: " << bill.date << endl;
            }
        }
    }
    else
    {
        cout << "Invalid choice!" << endl;
    }
}

int customPartitionBills(vector<Bill> &arr, int low, int high)
{
    Bill pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++)
    {
        if (arr[j].totalPrice < pivot.totalPrice)
        {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void quickSortBills(vector<Bill> &arr, int low, int high)
{
    if (low < high)
    {
        int pi = customPartitionBills(arr, low, high);
        quickSortBills(arr, low, pi - 1);
        quickSortBills(arr, pi + 1, high);
    }
}

int binarySearchByDate(const vector<Bill> &arr, const string &date, bool findStart)
{
    int left = 0, right = arr.size() - 1;
    int result = -1;
    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        if (arr[mid].date == date)
        {
            result = mid;
            if (findStart)
            {
                right = mid - 1;
            }
            else
            {
                left = mid + 1;
            }
        }
        else if (arr[mid].date < date)
        {
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }
    return result;
}

void generatePurchaseReport()
{
    int startYear, endYear;
    vector<Bill> filteredBills;

    cout << "Enter start year (YYYY): ";
    if (!(cin >> startYear))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a year." << endl;
        return;
    }
    cout << "Enter end year (YYYY): ";
    if (!(cin >> endYear))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a year." << endl;
        return;
    }

    // Convert the date string to an integer year for comparison
    auto getYear = [](const string &date)
    {
        return stoi(date.substr(0, 4));
    };

    // Filter bills by the specified year range
    for (const auto &bill : bills)
    {
        int billYear = getYear(bill.date);
        if (billYear >= startYear && billYear <= endYear)
        {
            filteredBills.push_back(bill);
        }
    }

    // Sort filtered bills by date
    sort(filteredBills.begin(), filteredBills.end(), [](const Bill &a, const Bill &b)
         { return a.date < b.date; });

    // Sort filtered bills by total price
    quickSortBills(filteredBills, 0, filteredBills.size() - 1);

    double totalSales = 0;
    for (const auto &bill : filteredBills)
    {
        cout << "Customer Name: " << bill.customerName << endl;
        cout << "Customer ID: " << bill.customerID << endl;
        cout << "Car ID: " << bill.carID << endl;
        cout << "Car Brand: " << bill.carBrand << endl;
        cout << "Year of Production: " << bill.year << endl;
        cout << "Color: " << bill.color << endl;
        cout << "Price: " << bill.price << endl;
        cout << "Order Number: " << bill.orderNumber << endl;
        cout << "Total Price: " << bill.totalPrice << endl;
        cout << "Date: " << bill.date << endl;
        totalSales += bill.totalPrice;
    }
    cout << "Total Sales: " << totalSales << endl;
}

#endif // BILLINGFUNCTIONS_H_INCLUDED
