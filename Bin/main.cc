#include "Map.h"
#include "Window.h"
//#include "Player.h"


Map M;
Window wind;

SDL_Window *win;
SDL_Renderer *ren;
SDL_Surface* surface;
SDL_Surface* wallS, *groundS, *rockS, *playerS, *pillS;


void DisplayMatrix(vector<vector <char> > M) {
	SDL_Rect srcrect;
	srcrect.x = 10;
	srcrect.y = 10;
	srcrect.w = 40;
	srcrect.h = 40;

	
	for (int i = 0; i != M.size(); ++i) {
		for (int j = 0; j != M[0].size(); ++j) {

			srcrect.x = 10 + 40*j;
			srcrect.y = 10 + 40*i;

			if (M[i][j] == '#') SDL_BlitSurface( wallS, NULL, surface, &srcrect );
			if (M[i][j] == '.') SDL_BlitSurface( groundS, NULL, surface, &srcrect );
			if (M[i][j] == '*') SDL_BlitSurface( rockS, NULL, surface, &srcrect );
			if (M[i][j] == 'S') SDL_BlitSurface( playerS, NULL, surface, &srcrect );
			if (M[i][j] == 'P') SDL_BlitSurface( pillS, NULL, surface, &srcrect );
		}
	}
	SDL_UpdateWindowSurface( win );
}

void run(int& i) {
	M.printCurrentScreen();
	M.updateMatrix(i);
	DisplayMatrix(M.getMatrix());
}

bool init(){
	//Initialization flag
	int SCREEN_WIDTH = 800;
	int SCREEN_HEIGHT = 600;
	bool success = true;
	
	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )	{
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
		success = false;
	}
	else	{
		//Create window
		win = SDL_CreateWindow( "P J C C", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		//ren = SDL_CreateRenderer(win, -1, 0);
		//SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);

		if( win == NULL )		{
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
			success = false;
		}
		else		{
			//Get window surface
			surface = SDL_GetWindowSurface( win );
		}
	}

	return success;
}

bool loadMedia(){
	//Loading success flag
	bool success = true;

	//Load splash image
	wallS = SDL_LoadBMP( "Textures/Wall.bmp" );
	groundS = SDL_LoadBMP( "Textures/Ground.bmp" );
	rockS = SDL_LoadBMP( "Textures/WallMove.bmp" );
	playerS = SDL_LoadBMP( "Textures/Player.bmp" );
	pillS = SDL_LoadBMP( "Textures/Pill.bmp" );
	//bg = SDL_LoadBMP( "Textures/Wall.bmp" );
	if( pillS == NULL )	{
		printf( "Unable to load images %s! SDL Error: %s\n", "Textures/*.bmp", SDL_GetError() );
		success = false;
	}

	return success;
}


int main() {
	int w, h; cin >> w >> h;
	M = Map(h, w);
	M.readMatrix();
	SDL_Event event;
	

	surface = NULL;
	wallS = groundS = rockS = playerS = pillS = NULL;


	init();
	loadMedia();
			
	SDL_BlitSurface( groundS, NULL, surface, NULL );


	bool running = true;
	int i = -1;
	while (running) {
		while( SDL_WaitEvent( &event ) != 0 ){
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
			} 
			else if (event.type == SDL_KEYUP) {
				i = -1;
			}
			run(i);
		}
	}
}