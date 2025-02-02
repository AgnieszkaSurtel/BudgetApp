#include <iostream>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <iomanip>
#include <sstream>

#include "BudgetManager.h"
#include "DateMethods.h"
#include <locale>
#include "Markup.h"
#include "Operation.h"

using namespace std;

BudgetManager::BudgetManager(const string& incomeFileName, const string& expenseFileName, int loggedUserId)
    : incomeFile(incomeFileName), expenseFile(expenseFileName), LOGGED_USER_ID(loggedUserId)
{
    incomes = incomeFile.loadOperationsFromFile(loggedUserId);
    expenses = expenseFile.loadOperationsFromFile(loggedUserId);

    lastUsedIncomeExpenseId = loadLastUsedId("lastUsedId.xml");
}
Operation BudgetManager::addOperationDetails(Type type)
{

    string date, item;
    double amount;

    Operation operation;
    operation.userId = LOGGED_USER_ID;

    cout << "Enter date (YYYY-MM-DD): ";
    cin >> date;
    while (!DateMethods::validateDate(date))
    {
        cout << "Invalid date. Try again: ";
        cin >> date;
    }
    operation.date = DateMethods::convertStringDateToInt(date);

    cout << "Enter item description: ";
    cin.ignore();
    getline(cin, item);
    operation.item = item;

    cout << "Enter amount: ";
    cin >> amount;
    operation.amount = amount;

    return operation;
}
int BudgetManager::loadLastUsedId(const string& fileName)
{
    CMarkup xml;
    int lastId = 0;

    bool fileExists = xml.Load(fileName);
    if (!fileExists)
    {
        cout << "File doesn't exist, creating new file...\n";
        xml.SetDoc("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n");
        xml.AddElem("Root");
        xml.AddElem("LastUsedId", "0");
        xml.Save(fileName);
        return 0;
    }

    xml.FindElem("Root");
    xml.IntoElem();
    xml.FindElem("LastUsedId");
    lastId = stoi(xml.GetData());

    return lastId;
}

void BudgetManager::saveLastUsedId(int lastId)
{
    CMarkup xml;
    bool fileExists = xml.Load("lastUsedId.xml");

    if (!fileExists)
    {
        xml.SetDoc("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n");
        xml.AddElem("Root");
    }

    xml.FindElem("Root");
    xml.IntoElem();

    if (xml.FindElem("LastUsedId"))
    {
        xml.SetData(to_string(lastId));
    }
    else
    {
        xml.AddElem("LastUsedId", to_string(lastId));
    }
    xml.Save("lastUsedId.xml");
}

void BudgetManager::addTransaction(Type type)
{
    string date = getTransactionDate();
    string description = getTransactionDescription();
    double amount = getTransactionAmount();

    Operation newOperation;
    newOperation.userId = LOGGED_USER_ID;
    newOperation.date = DateMethods::convertStringDateToInt(date);
    newOperation.item = description;
    newOperation.amount = amount;

    newOperation.id = lastUsedIncomeExpenseId + 1;

    lastUsedIncomeExpenseId++;

    string fileName = (type == INCOME) ? "incomes.xml" : "expenses.xml";
    saveOperationToFile(newOperation, fileName);

    saveLastUsedId(lastUsedIncomeExpenseId);

    cout << "The transaction was saved successfully.\n";
}

void BudgetManager::saveOperationToFile(Operation& newOperation, const string& fileName)
{
    CMarkup xml;
    bool fileExists = xml.Load(fileName);

    if (!fileExists)
    {

        xml.SetDoc("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n");
        xml.AddElem("Root");
    }

    xml.FindElem("Root");
    xml.IntoElem();

    xml.AddElem("Operation");
    xml.IntoElem();
    xml.AddElem("Id", to_string(newOperation.id));
    xml.AddElem("UserId", to_string(newOperation.userId));
    xml.AddElem("Date", to_string(newOperation.date));
    xml.AddElem("Item", newOperation.item);
    xml.AddElem("Amount", to_string(newOperation.amount));
    xml.OutOfElem();

    xml.Save(fileName);
}

string BudgetManager::getTransactionDate()
{
    string date;
    char choice;

    cout << "Does it concern today's date? (y/n): ";
    cin >> choice;

    if (choice == 'y' || choice == 'Y')
    {
        date = DateMethods::getCurrentDateAsString();
    }
    else
    {
        cout << "Enter the date (YYYY-MM-DD): ";
        cin >> date;
        while (!DateMethods::validateDate(date))
        {
            cout << "Invalid date. Try again (YYYY-MM-DD): ";
            cin >> date;
        }
    }

    return date;
}

string BudgetManager::getTransactionDescription()
{
    string description;

    cout << "Enter a description: ";
    cin.ignore();
    getline(cin, description);

    return description;
}

double BudgetManager::getTransactionAmount()
{
    string amountStr;
    double amount;

    cout << "Enter the amount: ";
    getline(cin, amountStr);

    replace(amountStr.begin(), amountStr.end(), ',', '.');

    try
    {
        amount = stod(amountStr);
    }
    catch (const invalid_argument&)
    {
        cout << "Invalid amount. Please enter a numeric value.\n";
        throw;
    }
    catch (const out_of_range&)
    {
        cout << "Amount is out of range. Please enter a valid number.\n";
        throw;
    }

    return amount;
}
string BudgetManager::formatAmount(double amount)
{
    stringstream ss;
    ss << fixed << setprecision(2) << amount;
    return ss.str();
}

int BudgetManager::getLastOperationId(CMarkup& xml)
{
    int lastId = 0;

    if (xml.IntoElem())
    {
        xml.ResetPos();
        while (xml.FindElem("Operation"))
        {
            if (xml.FindChildElem("Id"))
            {
                int currentId = stoi(xml.GetChildData());
                lastId = max(lastId, currentId);
            }
        }
    }

    cout << "Final lastId: " << lastId << endl;
    return lastId;
}

void BudgetManager::addIncome()
{
    addTransaction(INCOME);
}

void BudgetManager::addExpense()
{
    addTransaction(EXPENSE);
}
double BudgetManager::calculateBalance(int startDate, int endDate, const Type& type)
{
    double total = 0.0;

    if (type == INCOME)
    {
        for (const Operation& income : incomes)
        {
            if (income.date >= startDate && income.date <= endDate)
            {
                total += income.amount;
            }
        }
    }
    else if (type == EXPENSE)
    {
        for (const Operation& expense : expenses)
        {
            if (expense.date >= startDate && expense.date <= endDate)
            {
                total += expense.amount;
            }
        }
    }

    return total;
}

void BudgetManager::showOperations(const vector<Operation>& operations, int startDate, int endDate)
{
    for (const Operation& op : operations)
    {
        if (op.date >= startDate && op.date <= endDate)
        {

            stringstream ss;
            ss << fixed << setprecision(2) << op.amount;
            string formattedAmount = ss.str();

            cout << DateMethods::convertIntDateToStringWithDashes(op.date) << " | "
                 << setw(10) << setfill(' ') << op.item << " | "
                 << formattedAmount << endl;
        }
    }
}
void BudgetManager::showCurrentMonthBalance()
{
    int currentMonthStart = DateMethods::getCurrentMonthFirstDayDate();
    int currentMonthEnd = DateMethods::getCurrentMonthLastDayDate();

    cout << "Current Month Start Date: " << currentMonthStart << endl;
    cout << "Current Month End Date: " << currentMonthEnd << endl;

    sortOperationsByDate(incomes);
    sortOperationsByDate(expenses);

    cout << "Current Month Transactions:" << endl;
    cout << "Date       | Description   | Amount" << endl;
    cout << "-----------------------------------" << endl;
    cout << "Incomes:" << endl;
    showOperations(incomes, currentMonthStart, currentMonthEnd);
    cout << "Expenses:" << endl;
    showOperations(expenses, currentMonthStart, currentMonthEnd);

    double incomeTotal = calculateBalance(currentMonthStart, currentMonthEnd, INCOME);
    double expenseTotal = calculateBalance(currentMonthStart, currentMonthEnd, EXPENSE);
    double balance = incomeTotal - expenseTotal;

    cout << "-----------------------------------" << endl;
    cout << "Total Incomes: " << fixed << setprecision(2) << incomeTotal << endl;
    cout << "Total Expenses: " << fixed << setprecision(2) << expenseTotal << endl;
    cout << "Balance: " << fixed << setprecision(2) << balance << endl;

    system ("pause");
    system ("cls");
}

void BudgetManager::showPreviousMonthBalance()
{
    int previousMonthStart = DateMethods::getPreviousMonthFirstDayDate();
    int previousMonthEnd = DateMethods::getPreviousMonthLastDayDate();

    sortOperationsByDate(incomes);
    sortOperationsByDate(expenses);

    cout << "Previous Month Transactions:" << endl;
    cout << "Date       | Description   | Amount" << endl;
    cout << "-----------------------------------" << endl;
    cout << "Incomes:" << endl;
    showOperations(incomes, previousMonthStart, previousMonthEnd);
    cout << "Expenses:" << endl;
    showOperations(expenses, previousMonthStart, previousMonthEnd);

    double incomeTotal = calculateBalance(previousMonthStart, previousMonthEnd, INCOME);
    double expenseTotal = calculateBalance(previousMonthStart, previousMonthEnd, EXPENSE);
    double balance = incomeTotal - expenseTotal;

    cout << "-----------------------------------" << endl;
    cout << "Total Incomes: " << fixed << setprecision(2) << incomeTotal << endl;
    cout << "Total Expenses: " << fixed << setprecision(2) << expenseTotal << endl;
    cout << "Balance: " << fixed << setprecision(2) << balance << endl;

    system ("pause");
    system ("cls");
}

void BudgetManager::showCustomPeriodBalance()
{
    string startDateStr, endDateStr;

    cout << "Enter the start date (YYYY-MM-DD): ";
    cin >> startDateStr;

    while (!DateMethods::validateDate(startDateStr))
    {
        cout << "Invalid start date. Try again: ";
        cin >> startDateStr;
    }
    int startDate = DateMethods::convertStringDateToInt(startDateStr);

    cout << "Enter the end date (YYYY-MM-DD): ";
    cin >> endDateStr;

    while (!DateMethods::validateDate(endDateStr))
    {
        cout << "Invalid end date. Try again: ";
        cin >> endDateStr;
    }
    int endDate = DateMethods::convertStringDateToInt(endDateStr);

    sortOperationsByDate(incomes);
    sortOperationsByDate(expenses);

    cout << "Transactions from " << startDateStr << " to " << endDateStr << ":" << endl;
    cout << "Date       | Description   | Amount" << endl;
    cout << "-----------------------------------" << endl;
    cout << "Incomes:" << endl;
    showOperations(incomes, startDate, endDate);
    cout << "Expenses:" << endl;
    showOperations(expenses, startDate, endDate);

    double incomeTotal = calculateBalance(startDate, endDate, INCOME);
    double expenseTotal = calculateBalance(startDate, endDate, EXPENSE);
    double balance = incomeTotal - expenseTotal;

    cout << "-----------------------------------" << endl;
    cout << "Total Incomes: " << fixed << setprecision(2) << incomeTotal << endl;
    cout << "Total Expenses: " << fixed << setprecision(2) << expenseTotal << endl;
    cout << "Balance: " << fixed << setprecision(2) << balance << endl;

    system("pause");
    system("cls");
}
void BudgetManager::sortOperationsByDate(vector<Operation>& operations)
{
    sort(operations.begin(), operations.end(), [](const Operation& a, const Operation& b)
    {
        return a.date < b.date;
    });
}
