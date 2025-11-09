#include "game.h"
#include <iostream>
#include <fstream>
#include <limits>
using namespace std;

// --- INTRO ---
void intro() {
    cout << "=====================================\n";
    cout << "   Fallout: New Vegas - Lone Wanderer\n";
    cout << "=====================================\n\n";
    cout << "You're at the Prospector Saloon in Goodsprings.\n";
    cout << "A stranger approaches you with a quest...\n";
    cout << "\"Courier, I need your help. Raiders have stolen a water chip.\"\n";
    cout << "\"Retrieve it from the old quarry and you'll be rewarded.\"\n\n";
}

// --- HEALTH BAR (Overloaded) ---
void showHealth(int health) {
    cout << "[Health: " << health << "]\n";
}

void showHealth(int health, int maxHealth) {
    cout << "[Health: " << health << "/" << maxHealth << "]\n";
}

// --- SAFE INPUT HANDLING ---
int getChoice(int min, int max) {
    int choice;
    while (true) {
        cout << "Enter choice (" << min << "-" << max << "): ";
        if (cin >> choice && choice >= min && choice <= max)
            return choice;
        else {
            cout << "Invalid input. Try again.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

void encounter(int &health) {
    string enemies[4] = {"Giant Radscorpion", "Fiend Raider", "Nightstalker", "Cazador"};
    int damage[4] = {20, 15, 25, 30};

    int enemyIndex = rand() % 4;
    cout << "You encounter a " << enemies[enemyIndex] << "!\n";

    cout << "1. Fight\n2. Run\n";
    int choice = getChoice(1, 2);

    if (choice == 1) {
        cout << "You fight bravely.\n";
        if (rand() % 2 == 0) {
            cout << "You defeat the enemy but take some damage!\n";
            health -= damage[enemyIndex];
        } else {
            cout << "You defeat the enemy without taking damage.\n";
        }
    } else {
        cout << "You run away but trip on a rock, losing 10 HP!\n";
        health -= 10;
    }

    if (health < 0) health = 0;
    showHealth(health);
}

// --- QUEST DECISION ---
bool questDecision(int &health) {
    cout << "\nYou reach the old quarry where the chip is hidden.\n";

    cout << "Before entering, you notice movement nearby...\n";
    encounter(health);
    if (health <= 0) return false;

    cout << "\nInside the quarry, you find two paths:\n";
    cout << "1. Dark tunnel\n2. Sunlit path over the ridge\n";

    int choice = getChoice(1, 2);

    if (choice == 1) {
        cout << "You enter the dark tunnel...\n";
        encounter(health); 
        if (health <= 0) return false;

        cout << "Inside, you find the water chip!\n";

        cout << "\nAs you make your way back toward Goodsprings, danger strikes again!\n";
        encounter(health);
        if (health <= 0) return false;

        cout << "You march back to the Prospector Saloon...\n";
        return true;
    } else {
        cout << "You climb the ridge and a Deathclaw ambushes you!\n";
        health -= 99;
        showHealth(health, 100);
        if (health <= 0) return false;

        cout << "Barely alive, you crawl away empty-handed...\n";
        return false;
    }
}

// --- END GAME ---
void endGame(bool win) {
    if (win) {
        cout << "\nYou return to the saloon, victorious.\n";
        cout << "The stranger thanks you and gives you 500 caps.\n";
        cout << "You have completed the quest!\n";
        saveResultToFile("WIN");
    } else {
        cout << "\nYou collapse in the Mojave Wasteland...\n";
        cout << "Your journey ends here.\n";
        saveResultToFile("LOSE");
    }
}

// --- SAVE RESULTS TO FILE ---
void saveResultToFile(const string &result) {
    ofstream file("results.txt", ios::app);
    if (!file) {
        cerr << "Error: Could not open results.txt for writing.\n";
        return;
    }
    file << "Game result: " << result << "\n";
    file.close();
}
