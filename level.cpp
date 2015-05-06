#include "common.h"

cLevel::cLevel() {
	this->playerStartX = 0;
	this->playerStartY = 0;
}

bool cLevel::isCompleted() {
	for(int x = 0; x < LVL_W; x ++) {
	    for(int y = 0; y < LVL_H; y ++) {
	        if(this->lvl[x][y].obj == OBJ_PILL_STD) {
	            return false;
	        }
	    }
	}

	return true;
}

void cLevel::load() {
	ifstream file;

    this->setBgImageFilename("gfx/bg1.bmp");

    file.open(this->getFilename().c_str());

    if (file.is_open()) {
		string inpLine, tag, tagData, strTemp;
    	ostringstream streamTemp;
    	int y = 0;

    	while((!file.eof()) && (y < LVL_H)) {
			getline(file,inpLine);

			for(int x = 0; x < LVL_W; x ++) {
				this->lvl[x][y].walkable = true;
				this->lvl[x][y].enemyWalkable = true;
				this->lvl[x][y].base = BASE_FLOOR_STD;
				this->lvl[x][y].obj = OBJ_NONE;

				if(inpLine[x] == '#') {
					this->lvl[x][y].walkable = false;
					this->lvl[x][y].enemyWalkable = false;
					this->lvl[x][y].base = BASE_WALL_STD;
				}
				else if(inpLine[x] == '=') {
					this->lvl[x][y].walkable = false;
					this->lvl[x][y].enemyWalkable = false;
					this->lvl[x][y].base = BASE_WALL_FRONT;
				}
				else if(inpLine[x] == '.') {
					this->lvl[x][y].base = BASE_FLOOR_STD;
					this->lvl[x][y].obj = OBJ_PILL_STD;
				}
				else if(inpLine[x] == 'o') {
					this->lvl[x][y].base = BASE_FLOOR_STD;
					this->lvl[x][y].obj = OBJ_PILL_BIG;
				}
				else if(inpLine[x] == '@') {
					this->playerStartX = x * TILE_W;
					this->playerStartY = y * TILE_H;
				}
				else if(inpLine[x] == '~') {
					this->lvl[x][y].walkable = false;
					this->lvl[x][y].base = BASE_GHOSTDOOR;
				}
				else if(inpLine[x] == 'W') {
					this->enemyStartX[0] = x * TILE_W;
					this->enemyStartY[0] = y * TILE_H;
				}
				else if(inpLine[x] == 'X') {
					this->enemyStartX[1] = x * TILE_W;
					this->enemyStartY[1] = y * TILE_H;
				}
				else if(inpLine[x] == 'Y') {
					this->enemyStartX[2] = x * TILE_W;
					this->enemyStartY[2] = y * TILE_H;
				}
				else if(inpLine[x] == 'Z') {
					this->enemyStartX[3] = x * TILE_W;
					this->enemyStartY[3] = y * TILE_H;
				}
			}

			y++;
		}
	}

    file.close();

    this->fixWalls();
}

void cLevel::fixWalls() {
	for(int x = 0; x < LVL_W; x ++) {
		this->lvl[x][LVL_H - 1].base = BASE_WALL_FRONT;
		if((x > 0) && (x < LVL_W - 1)) this->lvl[x][0].base = BASE_WALL_FRONT;
	}

	for(int x = 1; x < LVL_W - 1; x ++) {
		for(int y = 1; y < LVL_H - 1; y ++) {
			if((this->lvl[x][y].base == BASE_WALL_STD) && (this->lvl[x][y + 1].base != BASE_WALL_STD)) {
				this->lvl[x][y].base = BASE_WALL_FRONT;
			}
		}
	}

	for(int x = 1; x < LVL_W - 1; x ++) {
		for(int y = 1; y < LVL_H - 1; y ++) {
			if((this->lvl[x][y].base == BASE_FLOOR_STD) && (this->lvl[x][y - 1].base == BASE_WALL_FRONT)) {
				this->lvl[x][y].base = BASE_FLOOR_DOODAD_WALLUP;
			}
		}
	}

	for(int x = 1; x < LVL_W - 1; x ++) {
		for(int y = 1; y < LVL_H - 1; y ++) {
			if((this->lvl[x][y].base == BASE_FLOOR_STD) && (getRndInt(0,100) < 15)) {
				this->lvl[x][y].base = BASE_FLOOR_DOODAD1;
			}
		}
	}

	for(int x = 1; x < LVL_W - 1; x ++) {
		for(int y = 1; y < LVL_H - 1; y ++) {
			if((this->lvl[x][y].base == BASE_FLOOR_STD) && (getRndInt(0,100) < 15)) {
				this->lvl[x][y].base = BASE_FLOOR_DOODAD2;
			}
		}
	}
}

string cLevel::getBgImageFilename() {
	return this->bgImageFilename;
}
void cLevel::setBgImageFilename(string filename) {
	this->bgImageFilename = filename;
}

string cLevel::getBgMusicFilename() {
	return this->bgMusicFilename;
}
void cLevel::setBgMusicFilename(string filename) {
	this->bgMusicFilename = filename;
}

void cLevel::setLevelNum(int levelNum) {
	this->levelNum = levelNum;
}
int cLevel::getLevelNum() {
	return this->levelNum;
}
string cLevel::getFilename() {
	ostringstream streamTemp;
    streamTemp << "data/level" << levelNum << ".dat";
	return streamTemp.str();
}

bool cLevel::tileWalkable(int x, int y) {
		return this->lvl[x][y].walkable;
}
bool cLevel::tileEnemyWalkable(int x, int y) {
		return this->lvl[x][y].enemyWalkable;
}

cLevel::eTileBase cLevel::tileBase(int x, int y) {
	return this->lvl[x][y].base;
}

cLevel::eTileObj cLevel::tileObj(int x, int y) {
	return this->lvl[x][y].obj;
}
void cLevel::setTileObj(int x, int y, cLevel::eTileObj obj) {
	this->lvl[x][y].obj = obj;
}

int cLevel::getPlayerStartX() {
	return this->playerStartX;
}
int cLevel::getPlayerStartY() {
	return this->playerStartY;
}

int cLevel::getEnemyStartX(int idx) {
	return this->enemyStartX[idx];
}
int cLevel::getEnemyStartY(int idx) {
	return this->enemyStartY[idx];
}
