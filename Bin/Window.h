#include <iostream>
#include <vector>
#include <algorithm>
#include <SDL2/SDL.h>
using namespace std;


class Window {
private:
	SDL_Window *win;
	SDL_Renderer *ren;
	SDL_Surface* surface;
	SDL_Surface* wallS, *groundS, *rockS, *playerS, *pillS;

	int SCREEN_WIDTH;
	int SCREEN_HEIGHT;

	bool init();
	bool loadMedia();
	void close();

public:
	Window();
	Window(vector<vector <char> > M);
	~Window();

	void DisplayMatrix(vector<vector <char> > M);
};