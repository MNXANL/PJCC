#include "Map.h"
#include "Window.h"
//#include "Player.h"


Map M;
Pos P; //Player

void run() {
	M.printCurrentScreen();
	M.updateMatrix(P);
}

int main() {
	int w, h; cin >> w >> h;
	M = Map(h, w);
	M.readMatrix();
	//Window win;
	while (1) {
		run();
	}	
}