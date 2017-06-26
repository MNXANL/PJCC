#include <iostream>
#include <vector>
#include <algorithm>
#include <SDL2/SDL.h>
#include "Player.h"
using namespace std;

struct Pos { int x;	int y; };

class Map {
private:
	typedef vector<char> Row;
	typedef vector<Row> Matrix;

	Matrix M;
	int h, w;	//Height Width
	Pos P;

	enum KeyPressSurfaces{
		KEY_UP,
		KEY_DOWN,
		KEY_LEFT,
		KEY_RIGHT
	};

public:
	Map();
	Map(int &x, int &y);
	//~Map();
	void readMatrix();
	void printCurrentScreen();
	void updateMatrix(Pos &P);
  
	
	/* data */
};