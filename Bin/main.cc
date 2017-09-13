#include "Map.h"
#include "Window.h"
//#include "Player.h"


Map M;
Window wind;
ifstream file;

string stage;
SDL_Window *win;
SDL_Renderer *ren;
SDL_Surface* surface;
SDL_Surface* wallS, *groundS, *rockS, *playerS, *pillS;
Mix_Music* gMusic;


void launchNextMap() {
	string map = "Maps/Stage" + string(stage);
	map = map + string(".txt");

	file.open(map);

	int w, h;
	string ws, hs;
	file >> ws >> hs;
	cout << ws << " - " << map << endl;
	string::size_type sz;
	w = stoi(ws, &sz);
	h = stoi(hs, &sz);

	M = Map( h, w);
	M.readMatrix(file);
	file.close();
}

void close()		{
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

void displayWin() {
	M.victory();
}

void run(int& i) {
	//M.printCurrentScreen(); //debug
	int res = M.updateMatrix(i);
	if (res == 1) {
		displayWin();
		SDL_Delay(2000);
		++stage[0];
		launchNextMap();
	}
	else DisplayMatrix(M.getMatrix());
}

bool init(){
	//Initialization flag
	int SCREEN_WIDTH = 960;
	int SCREEN_HEIGHT = 544;
	bool success = true;
	
	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0 )	{
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
	stage = "0";
	launchNextMap();
	SDL_Event event;
	
	surface = NULL;
	wallS = groundS = rockS = playerS = pillS = NULL;
	gMusic = NULL;
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

					case SDLK_p:
					running = false;
					break;

					case SDLK_ESCAPE:
					return 0;
					break;

					case SDLK_r: //restart
					launchNextMap();
					break;

					case SDLK_m:
                    //If there is no music playing
                    if( Mix_PlayingMusic() == 0) {
                        Mix_PlayMusic( gMusic, -1 );
                    }
                    
                    else { //if music is being played
                        //If the music is paused
                        if( Mix_PausedMusic() == 1 ) {
                            Mix_ResumeMusic();
                        }
                        //If the music is playing
                        else {
                            Mix_PauseMusic();
                        }
                    }
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
		if (!running) return 0;
	}
}