#include "Utils.h"

using namespace std;

char Utils::getCharacter()
{
    char character;
    cin >> character;


    while (cin.fail() || cin.get() != '\n')
    {
        cout << "Invalid input. Please enter a single character: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> character;
    }

    return character;
}
