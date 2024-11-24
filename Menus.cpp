#include "Menus.h"

void Menus::showTitle(const string& title) {
    cout << "=== " << title << " ===" << endl;
}

void Menus::showHomeMenu() {
    cout << "1. Login" << endl;
    cout << "2. Register" << endl;
    cout << "9. Exit" << endl;
    cout << endl;
    cout << "Your choice: ";
}

void Menus::showMainMenu() {
    cout << "1. Add income: " << endl;
    cout << "2. Add expense: " << endl;
    cout << "3. Current month balance: " << endl;
    cout << "4. Previous month balance: " << endl;
    cout << "5. Balance for custom period: " << endl;
    cout << "6. Change password: " << endl;
    cout << "8. Logout" << endl;
    cout << endl;
    cout << " Your choice: ";
}
