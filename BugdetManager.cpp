#include <iostream>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <iomanip>
#include <sstream>

#include "BudgetManager.h"
#include "DateMethods.h"
#include "Markup.h"
#include "Operation.h"
#include "OperationFile.h"

using namespace std;

BudgetManager::BudgetManager(const string& incomeFileName, const string& expenseFileName, int loggedUserId)
    : incomeFile(incomeFileName), expenseFile(expenseFileName), LOGGED_USER_ID(loggedUserId)
{
    incomes = incomeFile.loadOperationsFromFile(loggedUserId);
    expenses = expenseFile.loadOperationsFromFile(loggedUserId);

    int incomeLastId = incomeFile.getLastOperationIdFromFile();
    int expenseLastId = expenseFile.getLastOperationIdFromFile();
    lastUsedIncomeExpenseId = max(incomeLastId, expenseLastId);
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
string BudgetManager::formatAmount(double amount)
{
    stringstream ss;
    ss << fixed << setprecision(2) << amount;
    return ss.str();
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
    OperationFile operationFile(fileName);

    operationFile.saveOperationToFile(newOperation, fileName);


    cout << "The transaction was saved successfully.\n";
    system ("pause");
    system ("cls");

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

    while (true)
    {
        try
        {

            if (amountStr.find_first_not_of("0123456789.") != string::npos ||
                    count(amountStr.begin(), amountStr.end(), '.') > 1)
            {
                throw invalid_argument("Invalid input. Please enter a valid numeric value.");
            }


            amount = stod(amountStr);
            break;
        }
        catch (const invalid_argument& e)
        {

            cout << "Invalid input. Please enter a valid numeric value : " << endl;
            cout << "Enter the amount: ";
            getline(cin, amountStr);
        }
        catch (const out_of_range& e)
        {

            cout << "Amount is out of range. Please enter a valid number." << endl;
            cout << "Enter the amount: ";
            getline(cin, amountStr);
        }
    }

    return amount;
}

void BudgetManager::addIncome()
{
    addTransaction(INCOME);
    incomes = incomeFile.loadOperationsFromFile(LOGGED_USER_ID);
}

void BudgetManager::addExpense()
{
    addTransaction(EXPENSE);
    expenses = expenseFile.loadOperationsFromFile(LOGGED_USER_ID);
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
                 << formatAmount(op.amount) << endl;
        }
    }
}
void BudgetManager::showCurrentMonthBalance()
{
    int currentMonthStart = DateMethods::getCurrentMonthFirstDayDate();
    int currentMonthEnd = DateMethods::getCurrentMonthLastDayDate();


    cout << "Current Month Start Date: " << DateMethods::convertIntDateToStringWithDashes(currentMonthStart) << endl;
    cout << "Current Month End Date: " << DateMethods::convertIntDateToStringWithDashes(currentMonthEnd) << endl;
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

    cout << "Total Incomes: " << formatAmount(incomeTotal) << endl;
    cout << "Total Expenses: " << formatAmount(expenseTotal) << endl;
    cout << "Balance: " << formatAmount(balance) << endl;
    system ("pause");
    system ("cls");
}

void BudgetManager::showPreviousMonthBalance()
{
    int previousMonthStart = DateMethods::getPreviousMonthFirstDayDate();
    int previousMonthEnd = DateMethods::getPreviousMonthLastDayDate();

    sortOperationsByDate(incomes);
    sortOperationsByDate(expenses);
    cout << "Previous Month Start Date: " << DateMethods::convertIntDateToStringWithDashes(previousMonthStart) << endl;
    cout << "Previous Month End Date: " << DateMethods::convertIntDateToStringWithDashes(previousMonthEnd) << endl;

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
