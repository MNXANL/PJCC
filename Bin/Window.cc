#include "Window.h"



void Window::DisplayMatrix(vector<vector <char> > M) {
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
	SDL_Delay(10000);
}




bool Window::init(){
	//Initialization flag
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

bool Window::loadMedia(){
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

void Window::close()		{
	//Deallocate surfaces
	SDL_FreeSurface( wallS );	
	wallS = NULL;
	SDL_FreeSurface( groundS );	
	groundS = NULL;
	SDL_FreeSurface( rockS );	
	rockS = NULL;
	SDL_FreeSurface( playerS );	
	playerS = NULL;
	SDL_FreeSurface( pillS );	
	pillS = NULL;

	//Destroy window
	SDL_DestroyWindow( win );
	win = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}



Window::Window() {
	SCREEN_WIDTH = 800;
	SCREEN_HEIGHT = 600;
	surface = NULL;
	wallS = groundS = rockS = playerS = pillS = NULL;
}

Window::Window(vector<vector< char> > M) {
	SCREEN_WIDTH = 800;
	SCREEN_HEIGHT = 600;
	surface = NULL;
	wallS = groundS = rockS = playerS = pillS = NULL;


	init();
	loadMedia();
			
	SDL_BlitSurface( groundS, NULL, surface, NULL );
	
	DisplayMatrix(M);

	//Free resources and close SDL
	//close();
}

Window::~Window() {
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	SDL_Quit();
}