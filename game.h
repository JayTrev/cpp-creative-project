#ifndef GAME_H
#define GAME_H

#include <string>
using namespace std;

// Function declarations
void intro();
void showHealth(int health);
void showHealth(int health, int maxHealth); // overloaded function
int getChoice(int min, int max);
void encounter(int &health);
bool questDecision(int &health);
void endGame(bool win);
void saveResultToFile(const string &result);

#endif