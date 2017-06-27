#include "Player.h"

Player::Player() {}



int Player::getInput() { //Debug console
	char c; cin >> c;
	while (1) {
		if (c == 'w') return 0;
		if (c == 'a') return 1;
		if (c == 's') return 2;
		if (c == 'd') return 3;
	}
}

/*
int Player::getInput() {
	while (true) {	
		SDL_Event e;
		int num = 0;
		while (SDL_WaitEvent(&e)) {	
			cout << " *** IN *** " << endl;
			if (e.type == SDL_KEYDOWN)  {
				switch (e.key.keysym.sym){
					case SDLK_8:
						return 0;
						break;
					case SDLK_4:
						return 2;
						break;
					case SDLK_2:
						return 1;
						break;
					case SDLK_6:
						return 3;
						break;
					default:
						break;
				}
			}
		}
	}
}*/