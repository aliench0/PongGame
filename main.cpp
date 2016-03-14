#include <iostream>
#include "Game.h"

int main(int argc, char* args[]) {
	try {
		Game pong;
		pong.runGame();
	} catch (const std::exception& ex) {
		std::cout << ex.what();
	}
	return 0;
}
