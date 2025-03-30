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
/*  GameCharacter Implementation */
/* ============================= */

template <class T> GameCharacter<T>::GameCharacter() {
    name("Default");
    health(3);
    attack_power(10);
    defense(10);
}

template <class T> GameCharacter<T>::GameCharacter(string n, int h, int atk, int def) {
    name(n);
    health(h);
    attack_power(atk);
    defense(def);
}

template <class T> void GameCharacter<T>::attack(GameCharacter<T>& target) {
    T damage = attack_power - target.get_defense();
    if (damage < 0) {
        damage = 0;
    }
    cout << name << " attacks " << target.get_name() << " for " << damage << " damage!\n";
    target.take_damage(damage);
}

template <class T> void GameCharacter<T>::take_damage(int dmg) {
    health -= dmg;
    if (health < 0) {
        health = 0;
    }
    cout << name " now has " << health << " HP remaining.\n";
}

template <class T> bool GameCharacter<T>::is_defeated() const {
    return health == 0;
}

template <class T> string GameCharacter<T>::get_name() const {
    return name;
}

template <class T> int GameCharacter<T>::get_health() const {
    return health;
}

template <class T> int GameCharacter<T>::get_attack_power() const {
    return attack_power;
}

template <class T> int GameCharacter<T>::get_defense() const {
    return defense;
}

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

/* ============================= */
/*     Monster Implementation    */
/* ============================= */

template <class T> Monster<T>::Monster(string type, int h, int atk, int def, bool boss, string weak):
    GameCharacter<T>(type, h, atk, def), is_boss(boss), weakness(weak) {
}

template <class T> void Monster<T>::special_attack(Player<T>& player) {
    cout << name << " uses a powerful attack!\n";
    player.take_damage(attack_power * 1.5);
}

template <class T> bool Monster<T>::is_defeated() const {
    return h == 0;
}

template <class T> string Monster<T>::get_type() const { 
    return type; 
}

template <class T> string Monster<T>::get_weakness() const { 
    return weakness; 
}

/* ============================= */
/*      Dungeon Exploration      */
/* ============================= */

template <class T> void enter_dungeon(Player<T>& player) {
    random_device ran_dev;
    mt19937 gen(ran_dev());
    uniform_int_distribution<> event_type(1, 3);
    uniform_int_distribution<> coin_drop(5, 20);

    char continue_choice = 'y';

    while (continue_choice == 'y' && !player.is_defeated()) {
        int event = event_type(gen);

        switch(event) {
            case 1:
                cout << "You found some loot! You collected coins.\n";
                player.collect_coins(coin_drop(gen));
                break;

            case 2:
                cout << "A monster appeared!\n";

                Monster<T> enemy("Goblin", 30, 5, 1, false, "fire");
                while (!enemy.is_defeated() && !player.is_defeated()) {
                    cout << "Do you want to (1) Fight or (2) Run away? ";
                    int action;
                    cin >> action;

                    if (action == 1) {
                        player.attack(enemy);
                        if (!enemy.is_defeated()) {
                            enemy.attack(player);
                        }
                    } 
                    else if (action == 2) {
                        if (player.run_away()) {
                            break;
                        } 
                        else {
                            enemy.attack(player);
                        }
                    }
                }

                if (player.is_defeated()) {
                    cout << "You have perished in the dungeon. GAME OVER\n";
                    break;
                } 
                else if (enemy.is_defeated()) {
                    cout << "You defeated the " << enemy.get_type() << "!\n";
                }
                break;

            case 3:
                cout << "You found a potion! You restored health.\n";
                player.use_potion();
                break;
        }

        player.print_info();

        if (player.is_defeated()) {
            cout << "You have perished in the dungeon. GAME OVER\n";
            break;
        }

        cout << "Do you want to continue exploring? (y/n) ";
        cin >> continue_choice;
        cout << "\n";
    }
    if (continue_choice == 'n') {
        cout << "You leave the dungeon with your treasure.\n\n";
        player.print_info();
    }
}