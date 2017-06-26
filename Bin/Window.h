#include <iostream>
#include <vector>
#include <algorithm>
#include <SDL2/SDL.h>
using namespace std;


class Window {
private:
	SDL_Window *win;
	SDL_Renderer *ren;
	int loadVideo();
	int loadRenderer();
	int createWindow();



public:
	Window();
};