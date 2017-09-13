#include "Map.h"


Map::Map() {
	h = w = 0;
	M = Matrix(0, Row(0));
	P.x = P.y = -1;
}

Map::Map(int& x, int& y) {
	h = x;			w = y;
	M = Matrix(x, Row(y));
	P.x = P.y = -1;
}

void Map::readMatrix(ifstream &file) {
	for (int i = 0; i != M.size(); ++i) {
		for (int j = 0; j != M[0].size(); ++j) {
			file >> M[i][j];
			if (M[i][j] == 'S') {
				P.x = i ; P.y = j;
			}
		}
	}
}

void Map::printCurrentScreen() {
	cout << endl << endl << endl << endl;
	for (int i = 0; i != M.size(); ++i) {
		for (int j = 0; j != M[0].size(); ++j) {
			cout << M[i][j];
		}
		cout << endl;
	}
	//cout << "PLAYER: " << P.x << " | " << P.y << endl;
}


void Map::victory() {
	cout << endl << endl ;
	cout << "  L A   P A S T I L L A  " << endl << endl << endl;  
}


/* 0-1 LR			2-3 UD*/
int Map::updateMatrix(int& i) {
	//Player pl;
	//i = pl.getInput();

	//cout << "Update ... i = " << i << endl;
	if (i == 0) {
		if (M[P.x - 1][P.y] == '*' and M[P.x + 1][P.y] == '.' and M[P.x - 2][P.y] == '.') {
			//cout << "UP" << endl;
			M[P.x - 1][P.y] = 'S';
			M[P.x - 2][P.y] = '*';
			M[P.x][P.y] = '.';
			P.x -= 1;
		}
		else if (M[P.x - 1][P.y] == '.') {
			M[P.x - 1][P.y] = 'S';
			M[P.x][P.y] = '.';
			P.x -= 1;
		}
		else if (M[P.x - 1][P.y] == 'P') {
			M[P.x - 1][P.y] = 'P';
			M[P.x][P.y] = '.';
			victory();
			return 1;
		}
	}
	if (i == 2) {
		if (M[P.x + 1][P.y] == '*' and M[P.x - 1][P.y] == '.' and M[P.x + 2][P.y] == '.') {
			//cout << "DOWN" << endl;
			M[P.x + 1][P.y] = 'S';
			M[P.x + 2][P.y] = '*';
			M[P.x][P.y] = '.';
			P.x += 1;
		}
		else if (M[P.x + 1][P.y] == '.') {
			M[P.x + 1][P.y] = 'S';
			M[P.x][P.y] = '.';
			P.x += 1;
		}
		else if (M[P.x + 1][P.y] == 'P') {
			M[P.x + 1][P.y] = 'P';
			M[P.x][P.y] = '.';
			victory();
			return 1;
		}
	}
	if (i == 1) {

		//  5, 3

		//  5, 2 		5, 4		5, 5
		if (M[P.x][P.y - 1] == '*' and M[P.x][P.y + 1] == '.' and M[P.x][P.y - 2] == '.') {
			//cout << "LEFT" << endl;
			M[P.x][P.y - 1] = 'S';
			M[P.x][P.y - 2] = '*';
			M[P.x][P.y] = '.';
			P.y -= 1;
		}
		else if (M[P.x][P.y - 1] == '.') {
			M[P.x][P.y - 1] = 'S';
			M[P.x][P.y] = '.';
			P.y -= 1;
		}
		else if (M[P.x][P.y - 1] == 'P') {
			M[P.x][P.y - 1] = 'P';
			M[P.x][P.y] = '.';
			victory();
			return 1;
		}
	}
	if (i == 3) {
		if (M[P.x][P.y + 1] == '*' and M[P.x][P.y - 1] == '.' and M[P.x][P.y + 2] == '.') {
			//cout << "RIGHT" << endl;
			M[P.x][P.y + 1] = 'S';
			M[P.x][P.y + 2] = '*';
			M[P.x][P.y] = '.';
			P.y += 1;
		}
		else if (M[P.x][P.y + 1] == '.') {
			M[P.x][P.y+ 1] = 'S';
			M[P.x][P.y] = '.';
			P.y += 1;
		}
		else if (M[P.x][P.y + 1] == 'P') {
			M[P.x][P.y + 1] = 'P';
			M[P.x][P.y] = '.';
			victory();
			return 1;
		}
	}
	return 0;
	//else cout << "FAIL!" << endl;
}

Matrix Map::getMatrix() {
	return M;
}