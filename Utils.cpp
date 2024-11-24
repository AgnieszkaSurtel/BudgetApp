#include "Utils.h"

char Utils::getCharacter() {
    char character;
    std::cin >> character;


    while (std::cin.fail() || std::cin.get() != '\n') {
        std::cout << "Invalid input. Please enter a single character: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin >> character;
    }

    return character;
}
