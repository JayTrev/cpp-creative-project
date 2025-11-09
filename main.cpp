#include "game.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

int main() {
	std::srand((unsigned)std::time(nullptr));
	int health = 100;

	intro();
	showHealth(health, 100);

	bool success = questDecision(health);
	endGame(success);

	std::cout << "\n(Program finished)\n";
	return 0;
}
