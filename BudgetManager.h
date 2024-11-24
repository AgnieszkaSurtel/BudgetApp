#ifndef BUDGETMANAGER_H
#define BUDGETMANAGER_H

#include <string>
#include <vector>
//#include "Income.h"   // Zak³adam, ¿e masz zdefiniowan¹ klasê Income
//#include "Expense.h"  // Zak³adam, ¿e masz zdefiniowan¹ klasê Expense

using namespace std;

class BudgetManager
{
private:
    int loggedUserId;                 // ID zalogowanego u¿ytkownika
    string incomeFileName;            // Nazwa pliku z przychodami
    string expenseFileName;           // Nazwa pliku z wydatkami
//    vector<Income> incomes;           // Lista przychodów
   // vector<Expense> expenses;         // Lista wydatków

public:
     BudgetManager();
    BudgetManager(const string& incomeFileName, const string& expenseFileName, int userId); // Konstruktor

    void addIncome();                  // Metoda dodaj¹ca przychód
    void addExpense();                 // Metoda dodaj¹ca wydatek
    void showCurrentMonthBalance();    // Metoda wyœwietlaj¹ca bilans bie¿¹cego miesi¹ca
    void showPreviousMonthBalance();   // Metoda wyœwietlaj¹ca bilans poprzedniego miesi¹ca
    void showCustomPeriodBalance();     // Metoda wyœwietlaj¹ca bilans z wybranego okresu
};

#endif

