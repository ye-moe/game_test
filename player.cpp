#include "character.h"
#include <random>
using namespace std;

/* ************************************************************* */
/* Name: Ye Moe                                                  */
/* Date: March 12 2024                                           */
/* Purpose: Implementations file                                 */
/* Input: None                                                   */
/* Output: Print function prints all the functions in the list   */
/* ************************************************************* */

/* ============================= */
/*     Player Implementation     */
/* ============================= */

template <class T> Player<T>::Player(string n):
    GameCharacter<T>(n, 100, 10, 2), lives(3), coins(0) {
}

template <class T> void Player<T>::collect_coins(int amount) {
    coins += amount;
    cout << name << " collected " << amount << " coins! Total: " << coins << "\n";
    if (coins >= 100) {
        lives += (coins / 100);
        coins %= 100;
        cout << name << " has collected over 100 coins! " << name << " has gained an extra life!\n";
    }
}

template <class T> void Player<T>::use_potion() {
    health += 20;
    cout << name << " used a potion and restored 20 HP! Current HP: " << health << "\n";
}

template <class T> bool Player<T>::run_away() {
    random_device ran_dev;
    mt19937 gen(ran_dev());
    uniform_int_distribution<> chance(1, 100);
    int roll = chance(gen);

    if (roll > 40) {
        cout << name << " successfully escaped!\n";
        return true;
    }
    else {
        cout << name << " failed to escape!\n";
        return false;
    }
}

template <class T> void Player<T>::print_info() const {
    cout << name << " has " << health << " HP, " << lives << " lives, and " << coins << " coins.\n";
}

template <class T> void Player<T>::add_to_inventory(string item) {
    inventory.push_back(item);  // Add item to inventory
    cout << name << " collected a " << item << "! Added to inventory.\n";
}