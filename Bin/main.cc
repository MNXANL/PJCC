#include "Map.h"
#include "Window.h"
//#include "Player.h"


Map M;
Window win;

void run(int& i) {
	M.printCurrentScreen();
	M.updateMatrix(i);
	//win.DisplayMatrix(M.getMatrix());
}

int main() {
	int w, h; cin >> w >> h;
	M = Map(h, w);
	M.readMatrix();
	//win = Window(M.getMatrix());
	SDL_Event event;
	
	bool running = true;
	int i = -1;
	while (running) {
			/*
		while( SDL_PollEvent( &event ) != 0 ){
			if( event.type == SDL_QUIT )	{
				running = false;
			}
			else if (event.type == SDL_KEYDOWN) {
				switch( event.key.keysym.sym )	{
					case SDLK_UP:
					i = 0;
					break;

					case SDLK_LEFT:
					i = 1;
					break;

					case SDLK_DOWN:
					i = 2;
					break;

					case SDLK_RIGHT:
					i = 3;
					break;

					default:
					i = -1;
					break;
				}
			} else if (event.type == SDL_KEYUP) {
				i = -1;
			}
		}*/
			run(i);
	}
}