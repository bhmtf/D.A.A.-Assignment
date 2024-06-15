#ifndef BILLINGFUNCTIONS_H_INCLUDED
#define BILLINGFUNCTIONS_H_INCLUDED

#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
#include <algorithm>

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

void generateBill()
{
    string customerName, customerID, carID;
    double discount = 0.0;

    cout << "Enter customer name: ";
    cin >> customerName;
    cout << "Enter customer ID: ";
    cin >> customerID;
    cout << "Enter car ID: ";
    cin >> carID;

    for (auto &car : cars)
    {
        if (car.id == carID)
        {
            double totalPrice = car.price - (car.price * discount);
            string orderNumber = generateOrderNumber();
            string date = getCurrentDate();

            bills.emplace_back(customerName, customerID, car.id, car.brand, car.year, car.color, car.price, orderNumber, totalPrice, date);
            cout << "Bill generated successfully!" << endl;
            cout << "Customer Name: " << customerName << endl;
            cout << "Customer ID: " << customerID << endl;
            cout << "Car ID: " << car.id << endl;
            cout << "Car Brand: " << car.brand << endl;
            cout << "Year of Production: " << car.year << endl;
            cout << "Color: " << car.color << endl;
            cout << "Price: " << car.price << endl;
            cout << "Order Number: " << orderNumber << endl;
            cout << "Total Price: " << totalPrice << endl;
            cout << "Date: " << date << endl;

            car.sold++;
            return;
        }
    }

    cout << "Car with ID " << carID << " not found." << endl;
}

void searchIssuedBills()
{
    int choice;
    string searchValue;

    cout << "Search by: 1. Customer ID 2. Bill Date" << endl;
    cin >> choice;

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

int partition(vector<Bill> &arr, int low, int high)
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

void quickSort(vector<Bill> &arr, int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
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
    string startDate, endDate;
    vector<Bill> filteredBills;

    cout << "Enter start date (YYYY-MM-DD): ";
    cin >> startDate;
    cout << "Enter end date (YYYY-MM-DD): ";
    cin >> endDate;

    // Sort bills by date
    sort(bills.begin(), bills.end(), [](const Bill &a, const Bill &b)
         { return a.date < b.date; });

    // Use binary search to find the range of bills within the specified date range
    int startIndex = binarySearchByDate(bills, startDate, true);
    int endIndex = binarySearchByDate(bills, endDate, false);

    if (startIndex == -1 || endIndex == -1 || startIndex > endIndex)
    {
        cout << "No bills found within the specified date range." << endl;
        return;
    }

    for (int i = startIndex; i <= endIndex; i++)
    {
        filteredBills.push_back(bills[i]);
    }

    quickSort(filteredBills, 0, filteredBills.size() - 1);

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
