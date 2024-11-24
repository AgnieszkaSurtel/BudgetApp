#ifndef BUDGETMANAGER_H
#define BUDGETMANAGER_H

#include <string>
#include <vector>
//#include "Income.h"   // Zak�adam, �e masz zdefiniowan� klas� Income
//#include "Expense.h"  // Zak�adam, �e masz zdefiniowan� klas� Expense

using namespace std;

class BudgetManager
{
private:
    int loggedUserId;                 // ID zalogowanego u�ytkownika
    string incomeFileName;            // Nazwa pliku z przychodami
    string expenseFileName;           // Nazwa pliku z wydatkami
//    vector<Income> incomes;           // Lista przychod�w
   // vector<Expense> expenses;         // Lista wydatk�w

public:
     BudgetManager();
    BudgetManager(const string& incomeFileName, const string& expenseFileName, int userId); // Konstruktor

    void addIncome();                  // Metoda dodaj�ca przych�d
    void addExpense();                 // Metoda dodaj�ca wydatek
    void showCurrentMonthBalance();    // Metoda wy�wietlaj�ca bilans bie��cego miesi�ca
    void showPreviousMonthBalance();   // Metoda wy�wietlaj�ca bilans poprzedniego miesi�ca
    void showCustomPeriodBalance();     // Metoda wy�wietlaj�ca bilans z wybranego okresu
};

#endif

