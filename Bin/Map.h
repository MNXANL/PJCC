#include <iostream>
#include <vector>
#include <algorithm>
#include <SDL2/SDL.h>
#include <fstream>
#include <string>
#include "Player.h"
using namespace std;

typedef vector<char> Row;
typedef vector<Row> Matrix;

struct Pos { int x;	int y; };

class Map {
private:

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
	void readMatrix(ifstream &file);
	void printCurrentScreen();
	int updateMatrix(int &i);
  	Matrix getMatrix();
  	void victory();
	
	/* data */
};