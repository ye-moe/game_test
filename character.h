#include <iostream>
#include <string>
#include <vector>
using namespace std;

/* ************************************************************* */
/* Name: Ye Moe                                                  */
/* Date: March 12 2024                                           */
/* Purpose: Specifications file                                  */
/* Input: None                                                   */
/* Output: None                                                  */
/* ************************************************************* */

#ifndef CHARACTER_H
#define CHARACTER_H

// Base class: GameCharacter
template <class T> class GameCharacter {
    protected:
        string name;
        int health;
        int attack_power;
        int defense;

    public:
        GameCharacter();
        GameCharacter(string n, int h, int atk, int def);

        virtual void attack(GameCharacter<T>& target);
        virtual void take_damage(int dmg);
        virtual bool is_defeated() const;

        string get_name() const;
        int get_health() const;
        int get_attack_power() const;
        int get_defense() const;
};

// Inherited class: Player
template <class T> class Player : public GameCharacter<T> {
    private:
        int lives;
        int coins;
        double experience;
        vector<string> inventory;

    public:
        Player(string n);

        void collect_coins(int);
        void use_potion();
        bool run_away();
        void print_info() const;

        void add_to_inventory(string item);
        void level_up();
};

// Inherited class: Monster
template <class T> class Monster : public GameCharacter<T> {
    private:
        string type;
        bool is_boss;
        string weakness;
        
    public:
        Monster(string type, int h, int atk, int def, bool boss, string weak);

        void special_attack(Player<T>& player);
        bool is_defeated() const;
        string get_type() const;
        string get_weakness() const;
};

template <class T> void enter_dungeon(Player<T>& player);

#endif