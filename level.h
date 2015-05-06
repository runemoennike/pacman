#ifndef LEVEL_H
#define LEVEL_H

using namespace std;

#define LVL_W 20
#define LVL_H 15

class cLevel {
	public:
		enum eTileBase {
			BASE_FLOOR_STD,
			BASE_FLOOR_DOODAD1,
			BASE_FLOOR_DOODAD2,
			BASE_FLOOR_DOODAD_WALLUP,
			BASE_WALL_STD,
			BASE_WALL_FRONT,
			BASE_GHOSTDOOR
		};
		enum eTileObj {
			OBJ_NONE,
			OBJ_PILL_STD,
			OBJ_PILL_BIG
		};

		cLevel();

		void load();
		void fixWalls();
		bool isCompleted();

		void setLevelNum(int levelNum);
		int getLevelNum();
		string getFilename();

		void setBgImageFilename(string filename);
		string getBgImageFilename();
		void setBgMusicFilename(string filename);
		string getBgMusicFilename();

		bool tileWalkable(int x, int y);
		bool tileEnemyWalkable(int x, int y);
		eTileBase tileBase(int x, int y);
		eTileObj tileObj(int x, int y);

		void setTileObj(int x, int y, eTileObj obj);

		int getPlayerStartX();
		int getPlayerStartY();
		int getEnemyStartX(int idx);
		int getEnemyStartY(int idx);


	private:
		struct sTile {
			bool walkable;
			bool enemyWalkable;
			eTileBase base;
			eTileObj obj;
		};

		sTile lvl[LVL_W][LVL_H];

		string bgImageFilename;
		string bgMusicFilename;
		int levelNum;

		int playerStartX;
		int playerStartY;

		int enemyStartX[MAX_ENEMIES];
		int enemyStartY[MAX_ENEMIES];
};

#endif
