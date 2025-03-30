#include <iostream>
#include <random>
#include <string>
#include "character.h"
#include "character.cpp"

using namespace std;

int main() {
    random_device ran_dev;
    mt19937 gen(ran_dev());
    
    string your_name;
    char choice = ' ';

    while (choice != 'y' && choice != 'n') {
        cout << "Start Game? (y/n) ";
        cin >> choice;
    }

    if (choice == 'n') {
        cout << "Maybe next time!\n";
    }

    cout << "Enter your name: ";
    cin >> your_name;

    GameCharacter<string> player(your_name);

    cout << "\nWelcome, " << your_name << "! You enter the dungeon...\n\n";
    enter_dungeon(player);
}
